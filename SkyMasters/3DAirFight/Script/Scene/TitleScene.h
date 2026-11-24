#pragma once

#include "SceneBase.h"
#include "../Actor/Actor.h"

class TitleScene :public SceneBase
{
public:
    TitleScene(SceneManager* sceneManager, GameManager* gameManager) : SceneBase(sceneManager, gameManager) {};

    // 読み込み
    bool Load() override;

    // 初期化
    void Initialize() override;

    // 更新
    void Execute() override;

    // 終了
    SceneType Terminate() override;

private:
    std::unique_ptr<Actor> startButtonObject;      // スタートボタン
    std::unique_ptr<Actor> endButtonObject;        // エンドボタン
    std::unique_ptr<Actor> buttonManagerObject;    // ボタンマネージャー
    std::unique_ptr<Actor> cameraObject;           // カメラ
    std::unique_ptr<Actor> backgroundObject;       // 背景
    std::unique_ptr<Actor> titleLogoObject;        // タイトルロゴ
    std::unique_ptr<Actor> bgmObject;              // BGM

    // 画像ハンドル
    int startHandle = -1;        // スタートボタン
    int endHandle = -1;          // エンドボタン
    int backgroundHandle = -1;   // 背景
    int titleHandle = -1;        // タイトルロゴ
};