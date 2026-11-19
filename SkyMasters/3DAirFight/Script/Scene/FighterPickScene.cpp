#include"FighterPickScene.h"

#include"SceneManager.h"
#include"../Screen/Screen.h"
#include"../Game/Game.h"

#include"../Component/Input.h"
#include"../Component/Camera.h"
#include"../Component/UIRenderer.h"
#include"../Component/BackgroundRenderer.h"
#include"../Component/Transform.h"
#include"../Component/ButtonManager/FighterPickButtonManager.h"

#include"../Loader/FighterDataLoader.h"
#include"../Loader/FighterPartsID.h"

#include<string>

// 読み込み
bool FighterPickScene::Load()
{
    m_loader.LoadBody();
    m_loader.LoadWing();
    m_loader.LoadDiffuser();
    m_loader.LoadSpecialWeapon();

    short dataNum = m_loader.GetDataNum();
    bodyHandles.resize(dataNum);
    wingHandles.resize(dataNum);
    diffuserHandles.resize(dataNum);

    // 機体のモデルを配列に
    for (int i = 0; i < dataNum; i++)
    {
        std::string bodyHandle = "../Sprites/Body/BodyParts" + std::to_string(i) + ".png";
        bodyHandles[i] = LoadGraph(bodyHandle.c_str());
    }

    // 翼のモデルを配列に
    for (int i = 0; i < dataNum; i++)
    {
        std::string wingHandle = "../Sprites/Wing/WingParts" + std::to_string(i) + ".png";
        wingHandles[i] = LoadGraph(wingHandle.c_str());
    }

    // ディフューザーのモデルを配列に
    for (int i = 0; i < dataNum; i++)
    {
        std::string diffHandle = "../Sprites/Diffuser/DiffuserParts" + std::to_string(i) + ".png";
        diffuserHandles[i] = LoadGraph(diffHandle.c_str());
    }

    pickUI = LoadGraph("../Sprites/FighterPick_UI.png");
    backgroundHandle = LoadGraph("../Sprites/FighterPick_Background.png");

	return true;
}

// 初期化
void FighterPickScene::Initialize()
{
    short dataNum = m_loader.GetDataNum();
    bodyObject.resize(dataNum);
    wingObject.resize(dataNum);
    diffuserObject.resize(dataNum);

    // 機体のActorとCompの生成・ハンドルの設定
    for (short i = 0; i < dataNum; i++)
    {
        bodyObject[i] = std::make_unique<Actor>(p_sceneManager->p_game);
        
        UIRenderer* bodyUI = new UIRenderer(bodyObject[i].get());
        bodyUI->SetGrphHandle(bodyHandles[i]);
        Transform* bodyTr = new Transform(bodyObject[i].get());
        bodyTr->SetPosition(VGet(Screen::Width / 4, Screen::Height / 2, 0.0f));
    }

    // 翼のActorとCompの生成・ハンドルの設定
    for (short i = 0; i < dataNum; i++)
    {
        wingObject[i] = std::make_unique<Actor>(p_sceneManager->p_game);
        
        UIRenderer* wingUI = new UIRenderer(wingObject[i].get());
        wingUI->SetGrphHandle(wingHandles[i]);
        Transform* wingTr = new Transform(wingObject[i].get());
        wingTr->SetPosition(VGet(Screen::Width / 2, Screen::Height / 2, 0.0f));
    }

    // ディフューザーのActorとCompの生成・ハンドルの設定
    for (short i = 0; i < dataNum; i++)
    {
        diffuserObject[i] = std::make_unique<Actor>(p_sceneManager->p_game);
        
        UIRenderer* diffUI = new UIRenderer(diffuserObject[i].get());
        diffUI->SetGrphHandle(diffuserHandles[i]);
        Transform* diffTr = new Transform(diffuserObject[i].get());
        diffTr->SetPosition(VGet((Screen::Width / 4) * 3, Screen::Height / 2, 0.0f));
    }

    // 芥一の生成
    cameraObject = std::make_unique<Actor>(p_sceneManager->p_game);
    buttonManagerObject = std::make_unique<Actor>(p_sceneManager->p_game);
    backgroundObject = std::make_unique<Actor>(p_sceneManager->p_game);

    // カメラ 
    new Camera(cameraObject.get());

    // ボタンマネージャー
    new Input(buttonManagerObject.get());
    new FighterPickButtonManager(buttonManagerObject.get(), bodyObject, wingObject, diffuserObject, m_loader, this);
    UIRenderer* UIComp = new UIRenderer(buttonManagerObject.get());
    UIComp->SetGrphHandle(pickUI);
    Transform* buttonTr = new Transform(buttonManagerObject.get());
    buttonTr->SetPosition(VGet(Screen::Width / 4, Screen::Height / 2, 0.0f));
    buttonTr->SetScale(VGet(0.5f, 0.5f, 0.0f));
    
    // 背景
    BackgroundRenderer* backComp = new BackgroundRenderer(backgroundObject.get());
    backComp->SetGrphHandle(backgroundHandle);

}

// 更新
void FighterPickScene::Execute()
{
    FighterPickButtonManager* fpbm = buttonManagerObject->GetComponent<FighterPickButtonManager>();
    fpbm->BodyVisibleID();
    fpbm->WingVisibleID();
    fpbm->DiffuserVisibleID();
}

// 終了
SceneType FighterPickScene::Terminate()
{
    FighterPartsID id;

    FighterPickButtonManager* fpbm = buttonManagerObject->GetComponent<FighterPickButtonManager>();
    id.bodyID = fpbm->GetBodyID();
    id.wingID = fpbm->GetWingID();
    id.diffuserID = fpbm->GetDiffuserID();

    p_gameManager->SetFighterPartsID(id);

    return SceneType::GameScene;
}