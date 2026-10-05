// ライブラリ・ヘッダ
#include "SceneBase.h"

bool SceneBase::IsSceneChangeRequested() const
{
	return sceneChangeRequested;
}

void SceneBase::RequestSceneChange()
{
	sceneChangeRequested = true;
}
