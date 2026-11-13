#include"TitleScene.h"
#include"SceneManager.h"
#include"../Screen/Screen.h"
#include"../Game/Game.h"
#include"../Component/ButtonManager.h"
#include"../Component/Input.h"
#include"../Component/Camera.h"
#include"../Component/UIRenderer.h"
#include"../Component/Transform.h"


// ì«Ç›çûÇ›
bool TitleScene::Load()
{
	startHandle = LoadGraph("../Sprites/bomb.png");
	endHandle = LoadGraph("../Sprites/bomb.png");

	return true;
}

// èâä˙âª
void TitleScene::Initialize()
{
	startButtonObject = std::make_unique<Actor>(p_sceneManager->p_game);
	endButtonObject = std::make_unique<Actor>(p_sceneManager->p_game);
	buttonManagerObject = std::make_unique<Actor>(p_sceneManager->p_game);
	cameraObject = std::make_unique<Actor>(p_sceneManager->p_game);

	new ButtonManager(buttonManagerObject.get(),this);
	new Input(buttonManagerObject.get());
	new Camera(cameraObject.get());
	new UIRenderer( startButtonObject.get());
	new UIRenderer( endButtonObject.get());
	new Transform( startButtonObject.get());
	new Transform( endButtonObject.get());

	UIRenderer* startSprite = startButtonObject->GetComponent<UIRenderer>();
	startSprite->SetGrphHandle(startHandle);

	UIRenderer* endSprite = endButtonObject->GetComponent<UIRenderer>();
	endSprite->SetGrphHandle(endHandle);

	Transform* StartTr = startButtonObject->GetComponent<Transform>();
	StartTr->SetPosition(VGet(Screen::Width / 3, Screen::Height / 3 * 2, 0));

	Transform* endTr = endButtonObject->GetComponent<Transform>();
	endTr->SetPosition(VGet(Screen::Width / 3 * 2, Screen::Height / 3 * 2, 0));
}

// çXêV
void TitleScene::Execute()
{
	
}

// èIóπ
SceneType TitleScene::Terminate()
{
	ButtonManager* buttonComp = buttonManagerObject->GetComponent<ButtonManager>();

	switch (buttonComp->m_currentButton)
	{
	case ButtonManager::TitleButtonType::Start:
		return SceneType::GameScene;
		break;
	case ButtonManager::TitleButtonType::End:
		return SceneType::Exit;
		break;
	default:
		break;
	}
}