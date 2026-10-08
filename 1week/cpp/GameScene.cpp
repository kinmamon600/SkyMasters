// ライブラリ・ヘッダ
#include "DxLib.h"  // https://dxlib.xsrv.jp/dxfunc.html
#include "SuperDxPhysics.h"

#include "GameScene.h"
#include "Input.h"
#include "Fighter.h"
#include "Player.h"

void GameScene::Initialize()
{
	// カメラの設定
	SetCameraNearFar(GAMESCENE_CAMNEAR, GAMESCENE_CAMFAR);

	// 機体データの生成
	hangar = new Hangar;

	// プレイヤーの生成
	player1 = new Player;
	player2 = new Player;

	// 地形生成
	terrain = new Terrain;
	terrain->CreateTerrain();

	// プレイヤーの初期設定
	player1->Init(hangar->GetFighter(player1Settings->GetFighterID()));
	player2->Init(hangar->GetFighter(player2Settings->GetFighterID()));
	player1->CreateFighter(VGet(50.0f, 150.0f, 2000.0f), VGet(0.0f, 0.0f, 0.0f));
	player2->CreateFighter(VGet(-50.0f, 150.0f, 2000.0f), VGet(0.0f, 0.0f, 0.0f));
	player1->InitCameraPosition(player1Settings);
	player2->InitCameraPosition(player2Settings);
}

void GameScene::Execute()
{
	GameSceneStep next_step = currentStep;
	
	switch (currentStep)
	{
	case GameSceneStep::Intro:
		next_step = Intro();
		break;

	case GameSceneStep::Fight:
		next_step = Fight();
		break;

	case GameSceneStep::Outro:
		next_step = Outro();
		break;

	default:
		break;
	}

	stepTimer = ((double)GetNowCount() / 1000.0) - startTime;

	if (next_step != currentStep)
	{
		currentStep = next_step;
		startTime += stepTimer;
		stepTimer = 0.0;
	}
}

GameSceneStep GameScene::Intro()
{
	// 機体制御
	player1->FighterControl(player1Input);
	player2->FighterControl(player2Input);

	// 物理シミュレーション
	SDP::PhysicsSimulate();

	// 軸方向の設定
	player1->SetStandardAxis();
	player2->SetStandardAxis();

	// プレイヤー1描画
	// 描画範囲設定
	SetDrawArea(player1Settings->GetDispArea_MinX(), player1Settings->GetDispArea_MinY(),
		player1Settings->GetDispArea_MaxX(), player1Settings->GetDispArea_MaxY());

	// カメラ位置設定
	player1->SetCameraPosition();
	player1->SetDispCenter(player1Settings, player1Input);

	// 空の描画
	DrawBox(player1Settings->GetDispArea_MinX(), player1Settings->GetDispArea_MinY(),
		player1Settings->GetDispArea_MaxX(), player1Settings->GetDispArea_MaxY(),
		GetSkyColor(player1->GetYPos()), TRUE);

	// 物理オブジェクトのポリゴン描画
	SDP::RenderPhysicalObject();


	// プレイヤー2描画
	// 描画範囲設定
	SetDrawArea(player2Settings->GetDispArea_MinX(), player2Settings->GetDispArea_MinY(),
		player2Settings->GetDispArea_MaxX(), player2Settings->GetDispArea_MaxY());

	// カメラ位置設定
	player2->SetCameraPosition();
	player2->SetDispCenter(player2Settings, player2Input);

	// 空の描画
	DrawBox(player2Settings->GetDispArea_MinX(), player2Settings->GetDispArea_MinY(),
		player2Settings->GetDispArea_MaxX(), player2Settings->GetDispArea_MaxY(),
		GetSkyColor(player2->GetYPos()), TRUE);

	// 物理オブジェクトのポリゴン描画
	SDP::RenderPhysicalObject();

	if (stepTimer > GAMESCENE_INTRO_TIME)
	{
		player1->SetState(PlayerState::PlayerControl);
		player2->SetState(PlayerState::PlayerControl);
		return GameSceneStep::Fight;
	}

	return GameSceneStep::Intro;
}

GameSceneStep GameScene::Fight()
{
	// 機体制御
	player1->FighterControl(player1Input);
	player2->FighterControl(player2Input);

	// ビームの更新
	player1->BeamUpdate(terrain);
	player2->BeamUpdate(terrain);

	// 物理シミュレーション
	SDP::PhysicsSimulate();

	// 決着がついたかの情報
	bool resolution = false;

	// 地形によるダメージ
	resolution = resolution || player1->Damage_Terrain(terrain);
	resolution = resolution || player2->Damage_Terrain(terrain);

	// トランスフォーム補正
	player1->FighterTransformCorrection();
	player2->FighterTransformCorrection();

	// 軸方向の設定
	player1->SetStandardAxis();
	player2->SetStandardAxis();

	// ビームによるダメージ
	resolution = resolution || player1->Damage_OpponentBeam(player2);
	resolution = resolution || player2->Damage_OpponentBeam(player1);

	// エリアによるダメージ


	// 攻撃
	player1->Attack(player1Input, hangar->GetBeamMeshData());
	player2->Attack(player2Input, hangar->GetBeamMeshData());

	// プレイヤー1描画
	// 描画範囲設定
	SetDrawArea(player1Settings->GetDispArea_MinX(), player1Settings->GetDispArea_MinY(),
		player1Settings->GetDispArea_MaxX(), player1Settings->GetDispArea_MaxY());

	// カメラ位置設定
	player1->SetCameraPosition();
	player1->SetDispCenter(player1Settings, player1Input);

	// 空の描画
	DrawBox(player1Settings->GetDispArea_MinX(), player1Settings->GetDispArea_MinY(),
		player1Settings->GetDispArea_MaxX(), player1Settings->GetDispArea_MaxY(),
		GetSkyColor(player1->GetYPos()), TRUE);

	// 物理オブジェクトのポリゴン描画
	SDP::RenderPhysicalObject();


	// プレイヤー2描画
	// 描画範囲設定
	SetDrawArea(player2Settings->GetDispArea_MinX(), player2Settings->GetDispArea_MinY(),
		player2Settings->GetDispArea_MaxX(), player2Settings->GetDispArea_MaxY());

	// カメラ位置設定
	player2->SetCameraPosition();
	player2->SetDispCenter(player2Settings, player2Input);

	// 空の描画
	DrawBox(player2Settings->GetDispArea_MinX(), player2Settings->GetDispArea_MinY(),
		player2Settings->GetDispArea_MaxX(), player2Settings->GetDispArea_MaxY(),
		GetSkyColor(player2->GetYPos()), TRUE);

	// 物理オブジェクトのポリゴン描画
	SDP::RenderPhysicalObject();

	// 決着がついていたら対戦終了
	if (resolution)
	{
		player1->MatchOver();
		player2->MatchOver();

		return GameSceneStep::Outro;
	}

	return GameSceneStep::Fight;
}

GameSceneStep GameScene::Outro()
{
	// 機体制御
	player1->FighterControl(player1Input);
	player2->FighterControl(player2Input);

	// ビームの更新
	player1->BeamUpdate(terrain);
	player2->BeamUpdate(terrain);

	// 物理シミュレーション
	SDP::PhysicsSimulate();

	// トランスフォーム補正
	player1->FighterTransformCorrection();
	player2->FighterTransformCorrection();

	// 軸方向の設定
	player1->SetStandardAxis();
	player2->SetStandardAxis();

	// プレイヤー1描画
	// 描画範囲設定
	SetDrawArea(player1Settings->GetDispArea_MinX(), player1Settings->GetDispArea_MinY(),
		player1Settings->GetDispArea_MaxX(), player1Settings->GetDispArea_MaxY());

	// カメラ位置設定
	player1->SetCameraPosition();
	player1->SetDispCenter(player1Settings, player1Input);

	// 空の描画
	DrawBox(player1Settings->GetDispArea_MinX(), player1Settings->GetDispArea_MinY(),
		player1Settings->GetDispArea_MaxX(), player1Settings->GetDispArea_MaxY(),
		GetSkyColor(player1->GetYPos()), TRUE);

	// 物理オブジェクトのポリゴン描画
	SDP::RenderPhysicalObject();


	// プレイヤー2描画
	// 描画範囲設定
	SetDrawArea(player2Settings->GetDispArea_MinX(), player2Settings->GetDispArea_MinY(),
		player2Settings->GetDispArea_MaxX(), player2Settings->GetDispArea_MaxY());

	// カメラ位置設定
	player2->SetCameraPosition();
	player2->SetDispCenter(player2Settings, player2Input);

	// 空の描画
	DrawBox(player2Settings->GetDispArea_MinX(), player2Settings->GetDispArea_MinY(),
		player2Settings->GetDispArea_MaxX(), player2Settings->GetDispArea_MaxY(),
		GetSkyColor(player2->GetYPos()), TRUE);

	// 物理オブジェクトのポリゴン描画
	SDP::RenderPhysicalObject();

	if (stepTimer > GAMESCENE_OUTRO_TIME)
	{
		RequestSceneChange();
		stepTimer = 0.0;
	}

	return GameSceneStep::Outro;
}

SceneType GameScene::Terminate()
{
	// オブジェクト消去
	delete hangar;
	hangar = nullptr;

	delete player1;
	player1 = nullptr;
	delete player2;
	player2 = nullptr;

	delete terrain;
	terrain = nullptr;
	
	// セレクトメニューに戻る
	//return SceneType::SelectMenuScene;
	return SceneType::TitleMenuScene;
}
