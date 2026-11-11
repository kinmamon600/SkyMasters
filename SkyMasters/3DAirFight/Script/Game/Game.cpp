// ライブラリ・ヘッダ
#include "Game.h"
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
}

// ゲームの更新
void Game::Update()
{
	// 入力の更新
	// falseが返ってきたとき(コントローラが減った時等)は以降の処理を行わない
	//if (!UpdateInput()) { return; }

    // シーンの更新
    sceneManager->Update();

	// アクターの更新(コンポーネントも)
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
		delete act;
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
