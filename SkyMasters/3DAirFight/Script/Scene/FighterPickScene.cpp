#include"FighterPickScene.h"
#include"SceneManager.h"
#include"../Screen/Screen.h"
#include"../Game/Game.h"
#include"../Component/Input.h"
#include"../Component/Camera.h"
#include"../Component/UIRenderer.h"
#include"../Component/Transform.h"
#include"../Component/ButtonManager/FighterPickButtonManager.h"
#include"../Loader/FighterDataLoader.h"

#include<string>

// 読み込み
bool FighterPickScene::Load()
{
    m_loader.LoadBody();
    m_loader.LoadWing();
    m_loader.LoadDiffuser();
    m_loader.LoadSpecialWeapon();

    short dataNum = m_loader.GetDataNum();

    // 機体のモデルを配列に
    for (int i = 0; i < dataNum; i++)
    {
        std::string bodyHandle = "../Sprites/Body/BodyParts" + std::to_string(i) + ".mv1";
        bodyHandles[i] = MV1LoadModel(bodyHandle.c_str());
    }

    // 翼のモデルを配列に
    for (int i = 0; i < dataNum; i++)
    {
        std::string wingHandle = "../Sprites/Wing/WingParts" + std::to_string(i) + ".mv1";
        bodyHandles[i] = MV1LoadModel(wingHandle.c_str());
    }

    // ディフューザーのモデルを配列に
    for (int i = 0; i < dataNum; i++)
    {
        std::string diffHandle = "../Sprites/Diffuser/DiffuserParts" + std::to_string(i) + ".mv1";
        bodyHandles[i] = MV1LoadModel(diffHandle.c_str());
    }

	return true;
}

// 初期化
void FighterPickScene::Initialize()
{
    short dataNum = m_loader.GetDataNum();

    // 芥一の生成
    cameraObject = std::make_unique<Actor>(p_sceneManager->p_game);
    buttonManagerObject = std::make_unique<Actor>(p_sceneManager->p_game);

    // 機体のActorとCompの生成・ハンドルの設定
    for (short i = 0; i < dataNum; i++)
    {
        bodyObject[i] = std::make_unique<Actor>(p_sceneManager->p_game);
        new UIRenderer(bodyObject[i].get());
        new Transform(bodyObject[i].get());

        UIRenderer* bodyUI = bodyObject[i]->GetComponent<UIRenderer>();
        bodyUI->SetGrphHandle(bodyHandles[i]);
        Transform* bodyTr = bodyObject[i]->GetComponent<Transform>();
        bodyTr->SetPosition(VGet(Screen::Width / 4, Screen::Height / 2, 0.0f));
    }

    // 翼のActorとCompの生成・ハンドルの設定
    for (short i = 0; i < dataNum; i++)
    {
        wingObject[i] = std::make_unique<Actor>(p_sceneManager->p_game);
        new UIRenderer(wingObject[i].get());
        new Transform(wingObject[i].get());

        UIRenderer* wingUI = wingObject[i]->GetComponent<UIRenderer>();
        wingUI->SetGrphHandle(wingHandles[i]);
    }

    // ディフューザーのActorとCompの生成・ハンドルの設定
    for (short i = 0; i < dataNum; i++)
    {
        diffuserObject[i] = std::make_unique<Actor>(p_sceneManager->p_game);
        new UIRenderer(diffuserObject[i].get());
        new Transform(diffuserObject[i].get());

        UIRenderer* diffUI = diffuserObject[i]->GetComponent<UIRenderer>();
        diffUI->SetGrphHandle(diffuserHandles[i]);
        Transform* diffTr = wingObject[i]->GetComponent<Transform>();
        diffTr->SetPosition(VGet(Screen::Width / 4 * 2, Screen::Height / 2, 0.0f));
    }

    // コンポーネントの生成  
    new Camera(cameraObject.get());

    new Input(buttonManagerObject.get());
    new FighterPickButtonManager(buttonManagerObject.get());

}

// 更新
void FighterPickScene::Execute()
{

}

// 終了
SceneType FighterPickScene::Terminate()
{
    return SceneType::Exit;
}