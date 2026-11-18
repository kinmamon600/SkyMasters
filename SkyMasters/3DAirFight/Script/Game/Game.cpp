// ライブラリ・ヘッダ
#include "Game.h"
#include "GameManager.h"
#include "../Actor/Actor.h"
#include "../Scene/SceneManager.h"
#include "../Input/InputManager.h"
#include "../Component/ComponentManager.h"

// デストラクタ
Game::~Game()
{
	
}

// ゲームの初期化
void Game::Initialize() 
{
	// 各マネージャクラスの初期化
	sceneManager = new SceneManager(this);
	p_inputManager = new InputManager{};
	p_componentManager = new ComponentManager{};
	p_gameManager = new GameManager{};
}

// ゲームの更新
void Game::Update()
{
	// 入力の更新
	// falseが返ってきたとき(コントローラが減った時等)は以降の処理を行わない
	//if (!UpdateInput()) { return; }
	UpdateInput();

	// 保留状態のアクターを新規登録
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

    // シーンの更新
	SceneStep current_step = sceneManager->GetSceneStep();
    sceneManager->Update();

	// ロード・初期化・シーン終了時はコンポーネント・アクターを更新しない
	if (current_step != SceneStep::Execute)
	{
		return;
	}

	// 物理演算更新
	SDP::SimulatePhysics();

	// コンポーネントの更新
	p_componentManager->Update();

	// アクターの更新
	for (Actor* act : mActors)
	{
		act->Update();
	}
}

// ゲームの終了
// アクターやコンポーネントのメモリを解放する
void Game::Terminate()
{
	// 全アクターの解放
	// アクターの解放時に連鎖的にコンポーネントも解放される
	for (Actor* act : mActors)
	{
		auto iter = std::find(mActors.begin(), mActors.end(), act);
		if (iter != mActors.end())
		{
			mActors.erase(iter);
			delete act;
		}
	}

	// 各マネージャの解放
	delete p_componentManager;
	p_componentManager = nullptr;

	delete p_inputManager;
	p_inputManager = nullptr;

	delete sceneManager;
	sceneManager = nullptr;
}

// 新規アクターの追加
void Game::AddActor(Actor* actor)
{
	// 保留に追加
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

// アクターの削除
void Game::RemoveActor(Actor* actor)
{
	// 保留中のActorに入っているか
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// 配列の最後と入れ替えてからポップする
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Actorに入っているか
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// 配列の最後と入れ替えてからポップする
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

// コンポーネントの追加
void Game::AddComponent(Component* component)
{
	p_componentManager->AddComponent(component);
}

// コンポーネントの削除
void Game::RemoveComponent(Component* component)
{
	p_componentManager->RemoveComponent(component);
}

// 全アクターの削除
void Game::RemoveActorAll()
{
	// 全アクターの解放
	// アクターの解放時に連鎖的にコンポーネントも解放される
	//for (Actor* act : mActors)
	//{
	//	auto iter = std::find(mActors.begin(), mActors.end(), act);
	//	if (iter != mActors.end())
	//	{
	//		mActors.erase(iter);
	//		delete act;
	//	}
	//}
	while (!mActors.empty())
	{
		Actor* act = mActors.back();
		delete act;
	}
}

// 入力管理クラスの取得
InputManager* Game::GetInputManager() const
{
	return p_inputManager;
}

// 入力の更新
// 以降の処理の実行可否を返す
bool Game::UpdateInput()
{
	// ロード中の時は問答無用でtrue
	if (sceneManager->GetSceneStep() == SceneStep::Load)
	{
		return true;
	}

	// 前のフレームから引き続きコントローラ数が減っていたらゲームの実行処理を行わない
	// 変わりにコントローラの接続画面を表示
	if (p_inputManager->WasControllerRemoved())
	{
		p_inputManager->DispControllerSettingsWindow();
		return false;
	}

	// 入力の更新
	p_inputManager->Update();

	// このフレームからコントローラ数が減っていたらゲームの実行処理を行わない
	// 変わりにコントローラの接続画面を表示
	if (p_inputManager->WasControllerRemoved())
	{
		p_inputManager->DispControllerSettingsWindow();
		return false;
	}
}
