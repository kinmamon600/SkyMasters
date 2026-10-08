// ライブラリ・ヘッダ
#include "Game.h"

// デストラクタ
Game::~Game()
{
    delete mainScene;
    mainScene = nullptr;
}

// ゲームの初期化
void Game::Initialize()
{
    mainScene = new MainScene();
}

// ゲームの更新
void Game::Update()
{
    // シーンの更新
    mainScene->Update();
}
