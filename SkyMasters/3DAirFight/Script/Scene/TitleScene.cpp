#include"TitleScene.h"
#include"SceneManager.h"
#include"../Screen/Screen.h"
#include"../Game/Game.h"
#include"../Component/ButtonManager/TitleButtonManager.h"
#include"../Component/Input.h"
#include"../Component/Camera.h"
#include"../Component/UIRenderer.h"
#include"../Component/Transform.h"
#include"../Component/BackgroundRenderer.h"


// 読み込み
bool TitleScene::Load()
{
	startHandle = LoadGraph("../Sprites/Button_START.png");
	endHandle = LoadGraph("../Sprites/Button_END.png");
	backgroundHandle = LoadGraph("../Sprites/Title_Background.png");

	return true;
}

// 初期化
void TitleScene::Initialize()
{
	// 芥一の生成
	startButtonObject = std::make_unique<Actor>(p_sceneManager->p_game);
	endButtonObject = std::make_unique<Actor>(p_sceneManager->p_game);
	buttonManagerObject = std::make_unique<Actor>(p_sceneManager->p_game);
	cameraObject = std::make_unique<Actor>(p_sceneManager->p_game);
	backgroundObject = std::make_unique<Actor>(p_sceneManager->p_game);

	// 昆布の生成
	new TitleButtonManager(buttonManagerObject.get(),this);
	new Input(buttonManagerObject.get());
	new Camera(cameraObject.get());
	new UIRenderer(startButtonObject.get());
	new UIRenderer(endButtonObject.get());
	new Transform(startButtonObject.get());
	new Transform(endButtonObject.get());
	new BackgroundRenderer(backgroundObject.get());

	// スタートボタン
	UIRenderer* startSprite = startButtonObject->GetComponent<UIRenderer>();
	startSprite->SetGrphHandle(startHandle);
	Transform* startTr = startButtonObject->GetComponent<Transform>();
	startTr->SetPosition(VGet(Screen::Width / 3, Screen::Height / 3 * 2, 0.0f));

	// エンドボタン
	UIRenderer* endSprite = endButtonObject->GetComponent<UIRenderer>();
	endSprite->SetGrphHandle(endHandle);
	Transform* endTr = endButtonObject->GetComponent<Transform>();
	endTr->SetPosition(VGet(Screen::Width / 3 * 2, Screen::Height / 3 * 2, 0.0f));

	// 背景
	BackgroundRenderer* backComp = backgroundObject->GetComponent<BackgroundRenderer>();
	backComp->SetGrphHandle(backgroundHandle);
}

// 更新
void TitleScene::Execute()
{
	Transform* startTr = startButtonObject->GetComponent<Transform>();

	Transform* endTr = endButtonObject->GetComponent<Transform>();

	TitleButtonManager* buttonComp = buttonManagerObject->GetComponent<TitleButtonManager>();

	switch (buttonComp->m_currentButton)
	{
	case TitleButtonManager::TitleButtonType::Start:
		startTr->SetScale(VGet(0.2f, 0.2f, 0.0f));
		endTr->SetScale(VGet(0.15f, 0.15f, 0.0f));
		break;
	case TitleButtonManager::TitleButtonType::End:
		endTr->SetScale(VGet(0.2f, 0.2f, 0.0f));
		startTr->SetScale(VGet(0.15f, 0.15f, 0.0f));
		break;
	default:
		break;
	}
}

// 終了
SceneType TitleScene::Terminate()
{
	TitleButtonManager* buttonComp = buttonManagerObject->GetComponent<TitleButtonManager>();

	switch (buttonComp->m_currentButton)
	{
	case TitleButtonManager::TitleButtonType::Start:
		return SceneType::FighterPickScene;
		break;
	case TitleButtonManager::TitleButtonType::End:
		return SceneType::Exit;
		break;
	default:
		break;
	}
}