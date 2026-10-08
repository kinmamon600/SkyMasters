#ifndef _SCENE_H
#define _SCENE_H

// ライブラリ・ヘッダ

// シーン種類
enum class Scene
{
	TitleMenuScene,	// タイトルメニュー画面
	SelectMenuScene,// セレクトメニュー画面
	GameScene,		// ゲーム画面
	CreditScene,	// クレジット画面
	Count,			// シーン数
	Invariable,		// 不変 シーンの遷移設定用
	Exit			// ゲーム終了
};

#endif