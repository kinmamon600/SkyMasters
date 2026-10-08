#ifndef _GAME_H
#define _GAME_H

// ライブラリ・ヘッダ
#include "Scene/MainScene.h"

class Game
{
public:
    // コンストラクタ
    Game() : mainScene(nullptr) {}

    // デストラクタ
    ~Game();

    // ゲームの初期化
    void Initialize();

    // ゲームの更新
    void Update();

private:
    // シーン管理クラス
    MainScene* mainScene;
};

#endif