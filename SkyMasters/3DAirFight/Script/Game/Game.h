#ifndef _GAME_H
#define _GAME_H

#include<vector>
#include <algorithm>

// ライブラリ・ヘッダ
//#include "../Input/InputManager.h"

// 前方宣言
class Actor;
class Component;
class SceneManager;
class InputManager;
class ComponentManager;

class Game
{
public:
    Game() : sceneManager(nullptr), p_inputManager(nullptr), p_componentManager(nullptr), mUpdatingActors(false) {}
    ~Game();

    // ゲームの初期化
    void Initialize();

    // ゲームの更新
    void Update();

    // 新規アクターの追加
    void AddActor(Actor* actor);

    // アクターの削除
    void RemoveActor(Actor* actor);

    // コンポーネントの追加
    void AddComponent(Component* component);

    // コンポーネントの削除
    void RemoveComponent(Component* component);

    // 入力管理クラスの取得
    InputManager* GetInputManager() const;

    // 存在するActorの動的配列
    std::vector<Actor*> mActors;

    // 保留中のActorの動的配列
    std::vector<Actor*> mPendingActors;
private:
    // シーン管理クラス
    SceneManager* sceneManager;

    // 入力管理クラス
    InputManager* p_inputManager;

    // コンポーネント管理クラス
    ComponentManager* p_componentManager;

    // Actorを追加しようとしているか
    bool mUpdatingActors;
};
#endif