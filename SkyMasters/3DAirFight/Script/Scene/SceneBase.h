#ifndef _SCENEBASE_H
#define _SCENEBASE_H

// ライブラリ・ヘッダ
#include "SceneDefine.h"

#include <memory>

// 前方宣言
class SceneManager;
class GameManager;

/// <summary>
/// 全シーン共通の基底クラス
/// </summary>
class SceneBase
{
public:
	// コンストラクタ
	SceneBase(SceneManager* sceneManager,GameManager* gameManager) 
		: p_sceneManager(sceneManager),p_gameManager(gameManager) {};

	// 仮想デストラクタ
	//virtual ~SceneBase() = default;
	~SceneBase() {};

	// シーンの初期化
	virtual void Initialize() = 0;

	// シーンの処理実行
	virtual void Execute() = 0;

	// シーンのロード
	virtual bool Load() = 0;

	// シーンの終了
	// 戻り値として次のシーンを返す
	virtual SceneType Terminate() = 0;

	// シーン遷移するかの取得
	bool IsSceneChangeRequested() const;

	// シーンの切り替えリクエスト
	void RequestSceneChange();

protected:

	// シーンマネージャ
	SceneManager* p_sceneManager;

	GameManager* p_gameManager;

private:
	// シーン遷移するか
	bool sceneChangeRequested = false;

};

#endif