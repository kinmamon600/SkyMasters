// ライブラリ・ヘッダ
#include <string>

#include "DxLib.h"  // https://dxlib.xsrv.jp/dxfunc.html
#include "SuperDxPhysics.h"

#include "Settings.h"
#include "FontHandle.h"
#include "Game.h"

#include "Fighter.h"

// 名前空間
using namespace sce::PhysicsEffects;

// メイン
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 画面モードの設定
	SetGraphMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, COLOR_BIT, FPS);
	SetWindowSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
	ChangeWindowMode(FALSE);				// フルスクリーン表示
	SetMouseDispFlag(FALSE);				// マウスカーソル非表示
	SetMainWindowText(WINDOW_NAME.c_str());	// ウィンドウ名

	// ＤＸライブラリの初期化
	if (DxLib_Init() < 0)
	{
		// エラーが発生したらプログラム終了
		return -1;
	}

	// 物理世界の初期化
	if (!SDP::PhysicsInit(PHYSICS_WORLD_SIZE))
	{
		// エラーが発生したらプログラム終了
		return -1;
	}

	// 重力設定
	SDP::SetGravity(GRAVITY_SCALE);

	// 全機体のスケール初期化
	InitFightersScale();

	// 描画設定
	SetUseZBuffer3D(TRUE);		// Ｚバッファを有効にする
	SetWriteZBuffer3D(TRUE);	// Ｚバッファへの書き込みを有効にする
	SetGlobalAmbientLight(GetColorF(0.5f, 0.5f, 0.5f, 1.0f));
	
	// 地形設定
	//SDP::InitScale(LargeMeshVtxCount, LargeMeshVtx, 20.0f);

	// ゲーム生成
	Game* game = new Game();
	game->Initialize();

	// メインループ
	while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != 1)
	{
		// 画面クリア
		DxLib::ClearDrawScreen();

		// ゲームの更新
		game->Update();

		printfDx("%d\n", GetDrawCallCount());

		ScreenFlip();		// ダブルバッファで画面表示
		WaitTimer(FRAME_MS);// 一定時間待つ
	}

	delete game;

	// 物理世界の後始末
	SDP::PhysicsRelease();

	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}