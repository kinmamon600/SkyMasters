// ライブラリ・ヘッダ
#include "SceneBase.h"

// シーン遷移するかの取得
bool SceneBase::IsSceneChangeRequested() const
{
	return sceneChangeRequested;
}

// シーンの切り替えリクエスト
void SceneBase::RequestSceneChange()
{
	sceneChangeRequested = true;
}
