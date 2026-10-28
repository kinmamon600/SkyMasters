// ライブラリ・ヘッダ
#include "Game.h"
#include "../Actor/Actor.h"
#include "../Scene/SceneManager.h"
#include "../Input/InputManager.h"

// デストラクタ
Game::~Game()
{
    delete sceneManager;
    sceneManager = nullptr;

	delete p_inputManager;
	p_inputManager = nullptr;
}

// ゲームの初期化
void Game::Initialize() 
{
	sceneManager = new SceneManager(this);
	p_inputManager = new InputManager{};
}

// ゲームの更新
void Game::Update()
{
	// 入力の更新
	p_inputManager->Update();

    // シーンの更新
    sceneManager->Update();
	for (Actor* act : mActors)
	{
		act->Update();
	}
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
