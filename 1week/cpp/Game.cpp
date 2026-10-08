// ライブラリ・ヘッダ
#include "Game.h"

Game::~Game()
{
    delete player1Settings;
    player1Settings = nullptr;
    delete player2Settings;
    player2Settings = nullptr;

    delete player1Input;
    player1Input = nullptr;
    delete player2Input;
    player2Input = nullptr;

    delete mainScene;
    mainScene = nullptr;
}

void Game::Initialize()
{
    // 各プレイヤーの設定保持オブジェクトの生成
    player1Settings = new PlayerSettings();
    player2Settings = new PlayerSettings();

    // 各プレイヤーの入力取得保持オブジェクトの生成
    player1Input = new GameInput();
    player2Input = new GameInput();

    // 各プレイヤーの専有画面エリアの設定
    player1Settings->SetDispArea(0, 0, WINDOW_CENTER_X, WINDOW_SIZE_Y);
    player2Settings->SetDispArea(WINDOW_CENTER_X, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y);

    // 各プレイヤーの入力設定
    player1Input->SetGamepad(DX_INPUT_PAD1);
    player2Input->SetGamepad(DX_INPUT_PAD2);

    mainScene = new MainScene(player1Settings, player2Settings, player1Input, player2Input);
}

void Game::Update()
{
    // 入力更新
    player1Input->Update();
    player2Input->Update();

    // シーンの更新
    mainScene->Update();
}
