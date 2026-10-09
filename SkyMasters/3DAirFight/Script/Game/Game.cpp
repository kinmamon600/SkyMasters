// ライブラリ・ヘッダ
#include "Game.h"

// デストラクタ
Game::~Game()
{
    delete sceneManager;
    sceneManager = nullptr;
}


// ゲームの初期化
void Game::Initialize()
{
    sceneManager = new SceneManager();
}

// ゲームの更新
void Game::Update()
{
    // シーンの更新
    sceneManager->Update();
}
