#include"TitleButtonManager.h"
#include"../Input.h"
#include "../Sound.h"
#include"../../Scene/SceneBase.h"

void TitleButtonManager::Update()
{
	Input* inComp = m_owner->GetComponent<Input>();

	// ‰E“ü—Í
	if (inComp->GetButtonDown(Input::Button::RIGHT) /* || inComp->GetAnalog(Input::Analog::LX) > 0*/)
	{
		m_currentButton++;

		m_currentButton = (m_currentButton + TitleButtonType::Count) % TitleButtonType::Count;
	}

	// ¶“ü—Í
	if (inComp->GetButtonDown(Input::Button::LEFT) /* || inComp->GetAnalog(Input::Analog::LX) < 0*/)
	{
		m_currentButton--;

		m_currentButton = (m_currentButton + TitleButtonType::Count) % TitleButtonType::Count;
	}

	// Œˆ’è
	if (inComp->GetButtonDown(Input::Button::EAST))
	{
		switch (m_currentButton)
		{
		case TitleButtonManager::TitleButtonType::Start:
		{
			Sound* startSE = m_owner->GetComponent<Sound>();
			startSE->PlaySE(SE::OK_Button);
			sb->RequestSceneChange();
		}
			break;
		case TitleButtonManager::TitleButtonType::End:
		{
			Sound* endSE = m_owner->GetComponent<Sound>();
			endSE->PlaySE(SE::Cancel_Button);
			sb->RequestSceneChange();
		}
			break;
		default:
			break;
		}
	}
}