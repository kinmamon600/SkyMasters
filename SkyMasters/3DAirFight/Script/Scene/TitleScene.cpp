#include"TitleScene.h"
#include"SceneManager.h"
#include"../Screen/Screen.h"
#include"../Game/Game.h"
#include "../Game/SoundManager/SoundLilst.h"
#include"../Component/ButtonManager/TitleButtonManager.h"
#include"../Component/Input.h"
#include"../Component/Camera.h"
#include"../Component/UIRenderer.h"
#include"../Component/Transform.h"
#include"../Component/BackgroundRenderer.h"
#include"../Component/Sound.h"


// 読み込み
bool TitleScene::Load()
{
	// 非同期開始
	SetUseASyncLoadFlag(TRUE);

	startHandle = LoadGraph("../Sprites/Button_START.png");
	endHandle = LoadGraph("../Sprites/Button_END.png");
	backgroundHandle = LoadGraph("../Sprites/Title_Background.png");
	titleHandle = LoadGraph("../Sprites/Title.png");

	// 非同期終了
	SetUseASyncLoadFlag(FALSE);

	return true;
}

// 初期化
void TitleScene::Initialize()
{
	// 芥一の生成
	startButtonObject = std::make_unique<Actor>(p_sceneManager->p_game);		// スタートボタン
	endButtonObject = std::make_unique<Actor>(p_sceneManager->p_game);			// エンドボタン
	buttonManagerObject = std::make_unique<Actor>(p_sceneManager->p_game);		// ボタンマネージャー
	cameraObject = std::make_unique<Actor>(p_sceneManager->p_game);				// カメラ
	backgroundObject = std::make_unique<Actor>(p_sceneManager->p_game);			// 背景
	titleLogoObject = std::make_unique<Actor>(p_sceneManager->p_game);			// タイトルロゴ
	bgmObject = std::make_unique<Actor>(p_sceneManager->p_game);				// BGM

	// ボタンマネージャー
	new TitleButtonManager(buttonManagerObject.get(),this);
	new Input(buttonManagerObject.get());
	new Sound(buttonManagerObject.get());

	// カメラ
	new Camera(cameraObject.get());
	
	// スタートボタン
	UIRenderer* startSprite = new UIRenderer(startButtonObject.get());
	startSprite->SetGrphHandle(startHandle);
	Transform* startTr = new Transform(startButtonObject.get());
	startTr->SetPosition(VGet(Screen::Width / 3, Screen::Height / 3 * 2, 0.0f));

	// エンドボタン
	UIRenderer* endSprite = new UIRenderer(endButtonObject.get());
	endSprite->SetGrphHandle(endHandle);
	Transform* endTr = new Transform(endButtonObject.get());
	endTr->SetPosition(VGet(Screen::Width / 3 * 2, Screen::Height / 3 * 2, 0.0f));

	// 背景
	BackgroundRenderer* backComp = new BackgroundRenderer(backgroundObject.get());
	backComp->SetGrphHandle(backgroundHandle);

	// タイトルロゴ
	UIRenderer* titleUI = new UIRenderer(titleLogoObject.get());
	titleUI->SetGrphHandle(titleHandle);
	Transform* titleTr = new Transform(titleLogoObject.get());
	titleTr->SetPosition(VGet(Screen::Width / 2, Screen::Height / 3 * 1, 0.0f));

	// BGM
	Sound* bgm = new Sound(bgmObject.get());
	//bgm->PlayBGM(BGM::Title);
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