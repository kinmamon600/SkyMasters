// ライブラリ・ヘッダ
#include "SelectMenuScene.h"

void SelectMenuScene::Initialize()
{
	// 機体データの生成
	hangar = new Hangar;

	// 地形生成
	terrain = new Terrain;

	// 前に選択していた機体とカラーパレットの取得
	player1FighterID = player1Settings->GetFighterID();
	player2FighterID = player2Settings->GetFighterID();

	player1ColorPaletteID = player1Settings->GetColorPaletteID();
	player2ColorPaletteID = player2Settings->GetColorPaletteID();
}

void SelectMenuScene::Execute()
{
	// 選択・決定
	Player1Selection();
	Player2Selection();

	// 背景表示
	terrain->DisplayAsBackground();

	if (player1CanInputDecision && player2CanInputDecision)
	{
		RequestSceneChange();
	}
}

SceneType SelectMenuScene::Terminate()
{
	// 地形の消去
	delete terrain;
	terrain = nullptr;

	// 機体情報の消去
	delete hangar;
	hangar = nullptr;

	return SceneType::GameScene;
}

void SelectMenuScene::Player1Selection()
{
	// 機体選択
	if (player1Input->GetDigitalX() == 0)
	{
		player1CanInputX = true;
	}
	else
	{
		if (player1CanInputX)
		{
			player1CanInputX = false;
			player1FighterID = (player1FighterID + player1Input->GetDigitalX() + TOTAL_FIGHTER_NUM) % TOTAL_FIGHTER_NUM;
		}
	}

	// カラーパレット選択
	if (player1Input->GetL())
	{
		if (player1CanInputL)
		{
			player1CanInputL = false;
			player1ColorPaletteID = (player1ColorPaletteID - 1 + TOTAL_COLORPARETTE_NUM) % TOTAL_COLORPARETTE_NUM;
		}
	}
	else
	{
		player1CanInputL = true;
	}

	if (player1Input->GetR())
	{
		if (player1CanInputR)
		{
			player1CanInputR = false;
			player1ColorPaletteID = (player1ColorPaletteID + 1 + TOTAL_COLORPARETTE_NUM) % TOTAL_COLORPARETTE_NUM;
		}
	}
	else
	{
		player1CanInputR = true;
	}

	if (player1Input->GetEast())
	{
		if (player1CanInputDecision)
		{
			player1CanInputDecision = false;
			player1IsDecision = !player1IsDecision;
		}
	}
	else
	{
		player1CanInputDecision = true;
	}
}

void SelectMenuScene::Player2Selection()
{
	// 機体選択
	if (player2Input->GetDigitalX() == 0)
	{
		player2CanInputX = true;
	}
	else
	{
		if (player2CanInputX)
		{
			player2CanInputX = false;
			player2FighterID = (player2FighterID + player2Input->GetDigitalX() + TOTAL_FIGHTER_NUM) % TOTAL_FIGHTER_NUM;
		}
	}

	// カラーパレット選択
	if (player2Input->GetL())
	{
		if (player2CanInputL)
		{
			player2CanInputL = false;
			player2ColorPaletteID = (player2ColorPaletteID - 1 + TOTAL_COLORPARETTE_NUM) % TOTAL_COLORPARETTE_NUM;
		}
	}
	else
	{
		player2CanInputL = true;
	}

	if (player2Input->GetR())
	{
		if (player2CanInputR)
		{
			player2CanInputR = false;
			player2ColorPaletteID = (player2ColorPaletteID + 1 + TOTAL_COLORPARETTE_NUM) % TOTAL_COLORPARETTE_NUM;
		}
	}
	else
	{
		player2CanInputR = true;
	}

	if (player2Input->GetEast())
	{
		if (player2CanInputDecision)
		{
			player2CanInputDecision = false;
			player2IsDecision = !player2IsDecision;
		}
	}
	else
	{
		player2CanInputDecision = true;
	}
}
