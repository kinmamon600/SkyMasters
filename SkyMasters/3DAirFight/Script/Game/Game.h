#ifndef _GAME_H
#define _GAME_H

#include<vector>
#include <algorithm>

// ライブラリ・ヘッダ


class SceneManager;
class Actor;

class Game
{
public:
    Game() : sceneManager(nullptr), mUpdatingActors(false) {}
    ~Game();

    // ゲームの初期化
    void Initialize();
    // ゲームの更新
    void Update();

    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);

    // 存在するActorの動的配列
    std::vector<Actor*> mActors;
    // 保留中のActorの動的配列
    std::vector<Actor*> mPendingActors;
private:
    // シーン管理クラス
    SceneManager* sceneManager;

    // Actorを追加しようとしているか
    bool mUpdatingActors;
};
#endif