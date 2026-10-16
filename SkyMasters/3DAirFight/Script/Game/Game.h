#ifndef _GAME_H
#define _GAME_H

// ライブラリ・ヘッダ
#include "Scene/SceneManager.h"

class Game
{
public:
    Game() : sceneManager(nullptr) {}
    ~Game();

    // ゲームの初期化
    void Initialize();
    // ゲームの更新
    void Update();
    // ゲームのロード
    void Load();

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);
private:
    // シーン管理クラス
    SceneManager* sceneManager;

    // 存在するActorの動的配列
    std::vector<class Actor*>mActors;
    // 保留中のActorの動的配列
    std::vector<class Actor*>mPendingActors;

    // Actorを追加しようとしているか
    bool mUpdatingActors;
};

#endif