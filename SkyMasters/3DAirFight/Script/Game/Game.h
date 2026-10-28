#ifndef _GAME_H
#define _GAME_H

#include<vector>
#include <algorithm>

// ライブラリ・ヘッダ

// 前方宣言
class Actor;
class SceneManager;
class InputManager;

class Game
{
public:
    Game() : sceneManager(nullptr), p_inputManager(nullptr), mUpdatingActors(false) {}
    ~Game();

    // ゲームの初期化
    void Initialize();

    // ゲームの更新
    void Update();

    // 新規アクターの追加
    void AddActor(Actor* actor);

    // アクターの削除
    void RemoveActor(Actor* actor);

    // 存在するActorの動的配列
    std::vector<Actor*> mActors;

    // 保留中のActorの動的配列
    std::vector<Actor*> mPendingActors;
private:
    // シーン管理クラス
    SceneManager* sceneManager;

    // 入力管理クラス
    InputManager* p_inputManager;

    // Actorを追加しようとしているか
    bool mUpdatingActors;
};
#endif