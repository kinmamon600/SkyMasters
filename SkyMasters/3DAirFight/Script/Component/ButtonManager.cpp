#include"ButtonManager.h"
#include"Input.h"
#include"../Scene/SceneBase.h"

void ButtonManager::Update()
{
	Input* inComp = m_owner->GetComponent<Input>();

	// ‰E“ü—Í
	if (inComp->GetButton(Input::Button::RIGHT) /* || inComp->GetAnalog(Input::Analog::LX) > 0*/)
	{
		m_currentButton++;

		m_currentButton %= TitleButtonType::Count;

		printfDx("%d\n", m_currentButton);
	}

	// ¶“ü—Í
	if (inComp->GetButton(Input::Button::LEFT) /* || inComp->GetAnalog(Input::Analog::LX) < 0*/)
	{
		m_currentButton--;

		m_currentButton %= TitleButtonType::Count;

		printfDx("%d\n", m_currentButton);
	}

	// Œˆ’è
	if (inComp->GetButton(Input::Button::EAST))
	{
		printfDx("Œˆ’è‚µ‚½‚æ\n");

		switch (m_currentButton)
		{
		case ButtonManager::TitleButtonType::Start:
			sb->RequestSceneChange();
			break;
		case ButtonManager::TitleButtonType::End:
			sb->RequestSceneChange();
			break;
		default:
			break;
		}
	}
}