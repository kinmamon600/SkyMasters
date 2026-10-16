// ライブラリ・ヘッダ

#include "DxLib.h"  // https://dxlib.xsrv.jp/dxfunc.html
#include "SuperDxPhysics.h"

#include "Game.h"

// メイン
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 画面モードの設定
	SetGraphMode(1920, 1080, 32, 60);
	SetWindowSize(1920, 1080);
	ChangeWindowMode(FALSE);		// フルスクリーン表示
	SetMouseDispFlag(FALSE);		// マウスカーソル非表示
	SetMainWindowText("SKY MASTES");// ウィンドウ名

	// ＤＸライブラリの初期化
	if (DxLib_Init() < 0)
	{
		// エラーが発生したらプログラム終了
		return -1;
	}

	// 物理世界の初期化
	if (!SDP::PhysicsInit(VGet(100.0f, 100.0f, 100.0f)))
	{
		// エラーが発生したらプログラム終了
		return -1;
	}

	// 描画設定
	SetUseZBuffer3D(TRUE);		// Ｚバッファを有効にする
	SetWriteZBuffer3D(TRUE);	// Ｚバッファへの書き込みを有効にする
	SetGlobalAmbientLight(GetColorF(0.5f, 0.5f, 0.5f, 1.0f));
	
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

		ScreenFlip();	// ダブルバッファで画面表示
		WaitTimer(16);	// 一定時間待つ
	}

	delete game;

	// 物理世界の後始末
	SDP::PhysicsRelease();

	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}