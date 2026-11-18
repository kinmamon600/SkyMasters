#pragma once

#include "SceneBase.h"
#include"../Game/GameManager.h"
#include "../Actor/Actor.h"
#include"../Loader/FighterDataLoader.h"
#include<vector>

class FighterPickScene : public SceneBase
{
public:
	FighterPickScene(SceneManager* sceneManager, GameManager* gameManager) : SceneBase(sceneManager,gameManager){};

    // “Ç‚İ‚İ
    bool Load() override;

    // ‰Šú‰»
    void Initialize() override;

    // XV
    void Execute() override;

    // I—¹
    SceneType Terminate() override;

private:
    std::unique_ptr<Actor> cameraObject;
    std::unique_ptr<Actor> buttonManagerObject;
    std::unique_ptr<Actor> backgroundObject;
    std::vector<std::unique_ptr<Actor>>  bodyObject;
    std::vector<std::unique_ptr<Actor>>  wingObject;
    std::vector<std::unique_ptr<Actor>>  diffuserObject;

    std::vector<int> bodyHandles;
    std::vector<int> wingHandles;
    std::vector<int> diffuserHandles;

    FighterDataLoader m_loader;

    int pickUI = -1;
    int backgroundHandle = -1;
};
