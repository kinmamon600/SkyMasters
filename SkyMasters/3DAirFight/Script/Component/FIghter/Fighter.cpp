// ライブラリ・ヘッダ
#include "Actor/Actor.h"
#include "Fighter.h"
#include "FighterDataLoader.h"
#include "Manual.h"
#include "ManualCamera.h"
#include "../Transform.h"
#include "../PhysicsColliderSphere.h"

// 初期化
void Fighter::Initialize()
{

}

// 更新
void Fighter::Update()
{
	switch (m_currentState)
	{
	case Fighter::PlayerState::Manual:
	{
		// 機体制御
		Manual* manuComp = m_owner->GetComponent<Manual>();
		manuComp->FighterControl();

		// カメラ設定
		ManualCamera* manuCameraComp = p_myCamera->GetComponent<ManualCamera>();
		Transform* trComp = m_owner->GetComponent<Transform>();
		PhysicsColliderSphere* pcComp = m_owner->GetComponent<PhysicsColliderSphere>();
		manuCameraComp->SetCamera(trComp, pcComp, 0, 0, 60.0f);
	}
		break;
	case Fighter::PlayerState::Automatic:
		break;
	case Fighter::PlayerState::Dead:
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

