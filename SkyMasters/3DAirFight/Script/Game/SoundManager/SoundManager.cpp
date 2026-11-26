#include "SoundManager.h"
#include"DxLib.h"

// コンストラクタ
SoundManager::SoundManager()
{
    m_bgmHandles.resize(static_cast<int>(BGM::BGM_Count));
    m_seHandles.resize(static_cast<int>(SE::SE_Count));

    // BGM
    m_bgmHandles[static_cast<int>(BGM::Title)] = LoadSoundMem("../Sound/BGM/Title.mp3");
    m_bgmHandles[static_cast<int>(BGM::Tutorial_Battle)] = LoadSoundMem("../Sound/BGM/Tutorial_Battle.mp3");
    m_bgmHandles[static_cast<int>(BGM::FighterPick)] = LoadSoundMem("../Sound/BGM/FighterPick.mp3");

    // SE
    m_seHandles[static_cast<int>(SE::OK_Button)] = LoadSoundMem("../Sound/SE/OK_Button.wav");
    m_seHandles[static_cast<int>(SE::Cancel_Button)] = LoadSoundMem("../Sound/SE/Cancel_Button.wav");
    m_seHandles[static_cast<int>(SE::Pick_Slide)] = LoadSoundMem("../Sound/SE/Pick_Slide.wav");
    m_seHandles[static_cast<int>(SE::Fighter_Shot)] = LoadSoundMem("../Sound/SE/Fighter_Shot.wav");
    m_seHandles[static_cast<int>(SE::Explosion)] = LoadSoundMem("../Sound/SE/Explosion.wav");
    m_seHandles[static_cast<int>(SE::Enemy_Explosion)] = LoadSoundMem("../Sound/SE/Enemy_Explosion.wav");

}

// BGMの再生
void SoundManager::PlayBGM(BGM id)
{
    int index = static_cast<int>(id);

    // 同じBGMなら再生し直さない
    if (m_currentBGM == index)
    {
        return;
    }

    StopBGM();

    PlaySoundMem(m_bgmHandles[index], DX_PLAYTYPE_LOOP);

    m_currentBGM = index;

}

// BGMの完全停止
void SoundManager::StopBGM()
{
    if (m_currentBGM == -1)
    {
        return;
    }

    StopSoundMem(m_bgmHandles[m_currentBGM]);

    m_currentBGM = -1;
}

// SEの再生
void SoundManager::PlaySE(SE id)
{
    int index = static_cast<int>(id);

    PlaySoundMem(m_seHandles[index], DX_PLAYTYPE_BACK);
}