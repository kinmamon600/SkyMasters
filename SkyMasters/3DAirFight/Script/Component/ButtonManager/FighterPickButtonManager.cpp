#include"FighterPickButtonManager.h"
#include"../Input.h"
#include"../UIRenderer.h"

void FighterPickButtonManager::Update()
{
	Input* inComp = m_owner->GetComponent<Input>();

	// ã“ü—Í
	if (inComp->GetButtonDown(Input::Button::UP) /* || inComp->GetAnalog(Input::Analog::LX) > 0*/)
	{
		switch (pickParts)
		{
		case Body:
			bodyID++;
			bodyID = (bodyID + m_load->GetDataNum()) % m_load->GetDataNum();
			break;
		case Wing:
			wingID++;
			wingID = (wingID + m_load->GetDataNum()) % m_load->GetDataNum();
			break;
		case Diffuser:
			diffuserID++;
			diffuserID = (diffuserID + m_load->GetDataNum()) % m_load->GetDataNum();
			break;
		//case Spw:
		//	spwID++;
		//	spwID = (spwID + m_load->GetDataNum()) % m_load->GetDataNum();
		//	break;
		default:
			break;
		}
	}

	// ‰º“ü—Í
	if (inComp->GetButtonDown(Input::Button::DOWN) /* || inComp->GetAnalog(Input::Analog::LX) < 0*/)
	{
		switch (pickParts)
		{
		case Body:
			bodyID--;
			bodyID = (bodyID + m_load->GetDataNum()) % m_load->GetDataNum();
			break;
		case Wing:
			wingID--;
			wingID = (wingID + m_load->GetDataNum()) % m_load->GetDataNum();
			break;
		case Diffuser:
			diffuserID--;
			diffuserID = (diffuserID + m_load->GetDataNum()) % m_load->GetDataNum();
			break;
			//case Spw:
			//	spwID--;
			//	spwID = (spwID + m_load->GetDataNum()) % m_load->GetDataNum();
			//	break;
		default:
			break;
		}
	}

	// Œˆ’è
	if (inComp->GetButtonDown(Input::Button::EAST))
	{
		pickParts++;

		if (pickParts = m_load->GetDataNum())
		{

		}

		pickParts = (pickParts + m_load->GetDataNum()) % m_load->GetDataNum();
	}

	// ƒLƒƒƒ“ƒZƒ‹
	if (inComp->GetButtonDown(Input::Button::SOUTH))
	{
		pickParts--;

		pickParts = (pickParts + m_load->GetDataNum()) % m_load->GetDataNum();
	}
}

void FighterPickButtonManager::SetBodyActor(std::vector<std::unique_ptr<Actor>>& actors)
{
	short dataNum = m_load->GetDataNum();

	for (short i = 0; i < dataNum; i++)
	{
		UIRenderer* bodyUIComp = actors[i]->GetComponent<UIRenderer>();
		if (i == bodyID)
		{
			bodyUIComp->SetIsVisible(true);
		}
		else
		{
			bodyUIComp->SetIsVisible(false);
		}
	}
}

void FighterPickButtonManager::SetWingActor(std::vector<std::unique_ptr<Actor>>& actors)
{
	short dataNum = m_load->GetDataNum();

	for (short i = 0; i < dataNum; i++)
	{
		UIRenderer* wingUIComp = actors[i]->GetComponent<UIRenderer>();
		if (i == wingID)
		{
			wingUIComp->SetIsVisible(true);
		}
		else
		{
			wingUIComp->SetIsVisible(false);
		}
	}
}

void FighterPickButtonManager::SetDiffActor(std::vector<std::unique_ptr<Actor>>&  actors)
{
	short dataNum = m_load->GetDataNum();

	for (short i = 0; i < dataNum; i++)
	{
		UIRenderer* diffUIComp = actors[i]->GetComponent<UIRenderer>();
		if (i == diffuserID)
		{
			diffUIComp->SetIsVisible(true);
		}
		else
		{
			diffUIComp->SetIsVisible(false);
		}
	}
}