#include "Fighter.h"
#include "FighterDataLoader.h"

// 初期化
void Fighter::Initialize()
{

}

// 更新
void Fighter::Execute()
{
	switch (m_currentState)
	{
	case Fighter::Manual:
		break;
	case Fighter::Automatic:
		break;
	case Fighter::Dead:
		break;
	}
}

// 終了
//void Fighter::Terminate(){}

// ステートの変更
void Fighter::ChangeState(PlayerState state)
{
	m_currentState = state;
}

FighterStatus Fighter::AddStatus(short bodyID, short wingID, short diffID, short spwID)
{
	// CSVから各パーツのデータを取得
	BodyData body = m_loader.GetBody(bodyID);
	WingData wing = m_loader.GetWing(wingID);
	DiffuserData diffuser = m_loader.GetDiffuser(diffID);
	SpecialWeaponData weapon = m_loader.GetSpecialWeapon(spwID);

	// ステータスを計算
	m_status = CalculateFighterStatus(body, wing, diffuser, weapon);

	return m_status;
}

