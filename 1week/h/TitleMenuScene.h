#ifndef _TITLEMENUSCENE_H
#define _TITLEMENUSCENE_H

// ライブラリ・ヘッダ
#include "SceneDefine.h"
#include "SceneBase.h"
#include "GameInput.h"
#include "Player.h"
#include "Terrain.h"

// 定数

// 選択項目
enum class TitleMenuSelectionItems
{
	Start,	// ゲーム開始
	Credit,	// クレジット表示
	Exit,	// ゲーム終了
	Count,	// 項目数
};

// 選択項目の表示テキスト
const std::string TITLEMENU_SELECTIONITEMS_TEXT[static_cast<unsigned short>(TitleMenuSelectionItems::Count)]
{
	"ゲームスタート",
	"クレジット",
	"ゲーム終了",
};

// 選択項目のY方向位置(カーソル位置)
const unsigned int TITLEMENU_SELECTIONITEMS_OFFSET_Y[static_cast<unsigned short>(TitleMenuSelectionItems::Count)]
{
	550,
	650,
	750,
};

/// <summary>
/// タイトルメニューシーン
/// </summary>
class TitleMenuScene : public SceneBase
{
public:
	// コンストラクタ
	TitleMenuScene(GameInput* player_input)
		: playerInput(player_input) {};

	// デストラクタ
	~TitleMenuScene() = default;

	// シーンの初期化
	void Initialize() override;

	// シーンの処理実行
	void Execute() override;

	// シーンの終了
	// 戻り値として次のシーンを返す
	SceneType Terminate() override;

private:
	// プレイヤーの入力
	GameInput* playerInput;

	// 地形(背景表示用)
	Terrain* terrain{};

	// 入力フラグ
	bool canInputY = false;
	bool canDecision = false;

	// 現在の選択項目
	TitleMenuSelectionItems currentSelectionItems = TitleMenuSelectionItems::Start;

	// 項目の選択
	void ItemSelection();

	// 項目の決定
	void ItemDecision();
};

#endif