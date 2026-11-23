#include "Sound.h"
#include "../Actor/Actor.h"
#include "../Game/Game.h"
#include "../Game/SoundManager/SoundManager.h"

// BGMの再生
void Sound::PlayBGM(BGM id)
{
	return m_owner->GetGame()->GetSoundManager()->PlayBGM(id);
}

// BGMの完全停止
void Sound::StopBGM()
{
	return m_owner->GetGame()->GetSoundManager()->StopBGM();
}

// SEの再生
void Sound::PlaySE(SE id)
{
	return m_owner->GetGame()->GetSoundManager()->PlaySE(id);
}