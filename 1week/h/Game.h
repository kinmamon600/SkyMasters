#ifndef _GAME_H
#define _GAME_H

// ライブラリ・ヘッダ
#include "MainScene.h"
#include "GameInput.h"
#include "Player.h"

class Game
{
public:
    // コンストラクタ
    Game()
        : player1Settings(nullptr), player2Settings(nullptr), player1Input(nullptr), player2Input(nullptr),
        mainScene(nullptr) {}

    // デストラクタ
    ~Game();

    // 初期化
    void Initialize();

    // ゲームの更新
    void Update();

private:
    // 各プレイヤーの設定
    // 全シーンで共通
    PlayerSettings* player1Settings;
    PlayerSettings* player2Settings;

    // 各プレイヤーの入力
    // 全シーンで共通
    GameInput* player1Input;
    GameInput* player2Input;

    // シーン管理クラス
    MainScene* mainScene;
};

#endif