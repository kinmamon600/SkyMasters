#pragma once

enum class BGM
{				   
	Title,		   // タイトルシーン 
	Tutorial_Battle,	   // チュートリアルシーン
	//Game,		   // ゲームシーン
	FighterPick,   // キャラ選択シーン

	BGM_Count,	   // BGMの数
};

enum class SE
{
	OK_Button,          // 決定ボタン
	Cancel_Button,		// キャンセルボタン

	Pick_Slide,			// キャラ選択シーンの移動時

	Fighter_Shot,		// 自機の発射

	Explosion,

	Enemy_Explosion,	// 敵撃破時の爆発

	SE_Count,			// SEの数
};