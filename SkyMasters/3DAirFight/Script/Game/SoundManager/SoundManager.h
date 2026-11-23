#pragma once
#include "SoundLilst.h"

#include<vector>

class SoundManager 
{
public:
    SoundManager();

    ~SoundManager(){}

    // BGMの再生
    void PlayBGM(BGM id);

    // BGMの完全停止
    void StopBGM();

    // BGMの一時停止
    //void PauseBGM();

    // SEの再生
    void PlaySE(SE id);

    // 音量
    //void SetBGMVolume(int volume);
    //void SetSEVolume(int volume);
private:
    std::vector<int> m_bgmHandles;
    std::vector<int> m_seHandles;

    int m_currentBGM = -1;

};