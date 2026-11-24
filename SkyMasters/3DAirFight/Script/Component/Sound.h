#pragma once
#include "DxLib.h"
#include "Component.h"
#include "ComponentUpdateOrder.h"
#include "../Game/SoundManager/SoundLilst.h"

#include <vector>

class Sound : public Component
{
public:
    // コンストラクタ
	Sound(Actor* owner)
		:Component(owner, static_cast<int>(ComponentUpdateOrder::Input)) {}

    // デストラクタ
    ~Sound(){}

    // BGMの再生
    void PlayBGM(BGM id);

    // BGMの完全停止
    void StopBGM();

    // SEの再生
    void PlaySE(SE id);
private:
    std::vector<int> m_bgmHandles;
    std::vector<int> m_seHandles;

    int m_currentBGM = -1;
};