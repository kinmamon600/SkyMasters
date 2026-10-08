// ライブラリ・ヘッダ
#include "TitleMenuScene.h"

void TitleMenuScene::Initialize()
{
	// カメラ描画範囲の設定
	SetCameraNearFar(TERRAIN_BACKGROUND_CAMNEAR, TERRAIN_BACKGROUND_CAMFAR);
	
	// 地形の背景設定
	terrain = new Terrain;
}

void TitleMenuScene::Execute()
{
	// 背景表示
	terrain->DisplayAsBackground();

	// タイトルロゴの表示
	//SetFontSize(100);
	//DrawString(50, 50, WINDOW_NAME.c_str(), GetColor(255, 255, 255));
	//DrawStringToHandle(200, 200, WINDOW_NAME.c_str(), GetColor(255, 255, 255), GetLargeFontHandle());

	// 選択項目の表示
	/*for (int i = 0; i < static_cast<unsigned short>(TitleMenuSelectionItems::Count); ++i)
	{
		int x_pos = WINDOW_CENTER_X - (GetDrawStringWidthToHandle(TITLEMENU_SELECTIONITEMS_TEXT[i].c_str(),
			strlen(TITLEMENU_SELECTIONITEMS_TEXT[i].c_str()), mediumFontHandle) / 2);
		DrawStringToHandle(x_pos, TITLEMENU_SELECTIONITEMS_OFFSET_Y[i], TITLEMENU_SELECTIONITEMS_TEXT[i].c_str(), GetColor(255, 255, 255), mediumFontHandle);
		printfDx("%d:%d\n", i, x_pos);
	}*/

	// 項目の選択・決定
	//ItemSelection();
	ItemDecision();
}

SceneType TitleMenuScene::Terminate()
{
	// 地形の消去
	delete terrain;
	terrain = nullptr;

	// 決定・次のシーン設定
	switch (currentSelectionItems)
	{
	case TitleMenuSelectionItems::Start:
		return SceneType::SelectMenuScene;
		break;

	case TitleMenuSelectionItems::Credit:
		return SceneType::CreditScene;
		break;

	case TitleMenuSelectionItems::Exit:
		return SceneType::Exit;
		break;

	default:
		break;
	}

	return SceneType::TitleMenuScene;
}

void TitleMenuScene::ItemSelection()
{
	short y_input = playerInput->GetDigitalY();

	if (y_input == 0)
	{
		canInputY = true;
	}
	else
	{
		if (canInputY)
		{
			canInputY = false;

			// 選択項目の変更
			short item_cnt = static_cast<short>(TitleMenuSelectionItems::Count);
			currentSelectionItems
				= static_cast<TitleMenuSelectionItems>((static_cast<short>(currentSelectionItems) - y_input + item_cnt) % item_cnt);
			//printfDx("%d\n", currentSelectionItems);
		}
	}
}

void TitleMenuScene::ItemDecision()
{
	if (playerInput->GetEast())
	{
		if (canDecision)
		{
			canDecision = false;
			RequestSceneChange();
		}
	}
	else
	{
		canDecision = true;
	}
}
