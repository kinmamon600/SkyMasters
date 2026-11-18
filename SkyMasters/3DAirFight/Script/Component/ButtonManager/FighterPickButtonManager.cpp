#include"FighterPickButtonManager.h"
#include"../../Screen/Screen.h"
#include"../Input.h"
#include"../UIRenderer.h"
#include"../Transform.h"

// コンストラクタ
FighterPickButtonManager::FighterPickButtonManager(Actor* owner,
	const std::vector<std::unique_ptr<Actor>>& body,
	const std::vector<std::unique_ptr<Actor>>& wing,
	const std::vector<std::unique_ptr<Actor>>& diffuser,
	FighterDataLoader& loader,
	SceneBase* base)
	:Component(owner, static_cast<int>(ComponentUpdateOrder::Behaviour)),
		m_bodyObject(body),
		m_wingObject(wing),
		m_diffObject(diffuser),
		m_load(loader)
{
	sb = base;
}


void FighterPickButtonManager::Update()
{
	Input* inComp = m_owner->GetComponent<Input>();
	Transform* tr = m_owner->GetComponent<Transform>();

	// 上入力
	if (inComp->GetButtonDown(Input::Button::UP) /* || inComp->GetAnalog(Input::Analog::LX) > 0*/)
	{
		switch (pickParts)
		{
		case Body:
			bodyID++;
			bodyID = (bodyID + m_load.GetDataNum()) % m_load.GetDataNum();
			break;
		case Wing:
			wingID++;
			wingID = (wingID + m_load.GetDataNum()) % m_load.GetDataNum();
			break;
		case Diffuser:
			diffuserID++;
			diffuserID = (diffuserID + m_load.GetDataNum()) % m_load.GetDataNum();
			break;
		//case Spw:
		//	spwID++;
		//	spwID = (spwID + m_load->GetDataNum()) % m_load->GetDataNum();
		//	break;
		default:
			break;
		}
	}

	// 下入力
	if (inComp->GetButtonDown(Input::Button::DOWN) /* || inComp->GetAnalog(Input::Analog::LX) < 0*/)
	{
		switch (pickParts)
		{
		case Body:
			bodyID--;
			bodyID = (bodyID + m_load.GetDataNum()) % m_load.GetDataNum();
			break;
		case Wing:
			wingID--;
			wingID = (wingID + m_load.GetDataNum()) % m_load.GetDataNum();
			break;
		case Diffuser:
			diffuserID--;
			diffuserID = (diffuserID + m_load.GetDataNum()) % m_load.GetDataNum();
			break;
			//case Spw:
			//	spwID--;
			//	spwID = (spwID + m_load->GetDataNum()) % m_load->GetDataNum();
			//	break;
		default:
			break;
		}
	}

	// 決定
	if (inComp->GetButtonDown(Input::Button::EAST))
	{
		pickParts++;

		if (pickParts == m_load.GetDataNum())
		{
			sb->RequestSceneChange();
		}

		pickParts = (pickParts + m_load.GetDataNum()) % m_load.GetDataNum();

		switch (pickParts)
		{
		case Body:
			tr->SetPosition(VGet(Screen::Width / 4, Screen::Height / 2, 0.0f));
			break;
		case Wing:
			tr->SetPosition(VGet((Screen::Width / 4) * 2, Screen::Height / 2, 0.0f));
			break;
		case Diffuser:
			tr->SetPosition(VGet((Screen::Width / 4) * 3, Screen::Height / 2, 0.0f));
			break;
		default:
			break;
		}
	}

	// キャンセル
	if (inComp->GetButtonDown(Input::Button::SOUTH))
	{
		pickParts--;

		pickParts = (pickParts + m_load.GetDataNum()) % m_load.GetDataNum();

		switch (pickParts)
		{
		case Body:
			tr->SetPosition(VGet(Screen::Width / 4, Screen::Height / 2, 0.0f));
			break;
		case Wing:
			tr->SetPosition(VGet((Screen::Width / 4) * 2, Screen::Height / 2, 0.0f));
			break;
		case Diffuser:
			tr->SetPosition(VGet((Screen::Width / 4) * 3, Screen::Height / 2, 0.0f));
			break;
		default:
			break;
		}
	}
}

// 選んだ機体だけ表示
void FighterPickButtonManager::BodyVisibleID()
{
	short dataNum = m_load.GetDataNum();

	for (short i = 0; i < dataNum; i++)
	{
		UIRenderer* bodyUIComp = m_bodyObject[i]->GetComponent<UIRenderer>();
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

// 選んだ翼だけ表示
void FighterPickButtonManager::WingVisibleID()
{
	short dataNum = m_load.GetDataNum();

	for (short i = 0; i < dataNum; i++)
	{
		UIRenderer* wingUIComp = m_wingObject[i]->GetComponent<UIRenderer>();
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

// 選んだディフューザーだけ表示
void FighterPickButtonManager::DiffuserVisibleID()
{
	short dataNum = m_load.GetDataNum();

	for (short i = 0; i < dataNum; i++)
	{
		UIRenderer* diffUIComp = m_diffObject[i]->GetComponent<UIRenderer>();
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

// bodyIDを取得する
short FighterPickButtonManager::GetBodyID()
{
	return bodyID;
}

// wingIDを取得する
short FighterPickButtonManager::GetWingID()
{
	return wingID;
}

// diffuserIDを取得する
short FighterPickButtonManager::GetDiffuserID()
{
	return diffuserID;
}