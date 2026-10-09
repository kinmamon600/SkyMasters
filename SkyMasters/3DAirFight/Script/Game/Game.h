#ifndef _GAME_H
#define _GAME_H

// ライブラリ・ヘッダ
#include "Scene/SceneManager.h"

class Game
{
public:
    // コンストラクタ
    Game() : sceneManager(nullptr) {}

    // デストラクタ
    ~Game();

    // ゲームの初期化
    void Initialize();

    // ゲームの更新
    void Update();

    void Load();

private:
    // シーン管理クラス
    SceneManager* sceneManager;
};

#endif