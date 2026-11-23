// ライブラリ・ヘッダ
#include <memory>
#include "DxLib.h"

#include "World/WorldSettings.h"
#include "Screen/Screen.h"
#include "Actor/Actor.h"
#include "Fighter.h"
#include "../Transform.h"
#include "../Input.h"
//#include "../PhysicsColliderSphere.h"
//#include "../PhysicsColliderBox.h"
#include "../PhysicsColliderCylinder.h"
#include "../UIRenderer.h"
#include "../ModelRenderer.h"
#include "../Camera.h"

#include "../../Loader/FighterDataLoader.h"
#include "Manual.h"
#include "ManualCamera.h"
#include "Automatic.h"
#include "AutomaticCamera.h"
#include "../../Behavior/Bullet.h"

// コンストラクタ
Fighter::Fighter(Actor* owner, unsigned short pl_num, MATRIX mat, int beam, int reticle)
	: Behavior(owner), m_playerNum(pl_num), m_beamModelHandle(beam)
{
	// レイヤー設定
	owner->SetLayer(ActorLayer::Player);

	// 自身が使用する画面範囲の設定
	m_dispAreaMin.x = ((m_playerNum - 1) % 2) * Screen::Width / 2;
	m_dispAreaMax.x = m_dispAreaMin.x + Screen::Width / 2;

	m_dispAreaMin.y = ((m_playerNum - 1) / 2) * Screen::Height / 2;
	m_dispAreaMax.y = m_dispAreaMin.y + Screen::Height / 2;

	m_dispCenter.x = m_dispAreaMin.x + Screen::Width / 4;
	m_dispCenter.y = m_dispAreaMin.y + Screen::Height / 4;

	// コンポーネントのアタッチ
	Transform* tr = new Transform(owner);
	tr->SetMatrix(mat);

	new PhysicsColliderCylinder(owner, VGet(0.0f, 0.0f, 0.0f), 2.0f, 0.5f, PhysicsCollider::Active, 1.0f);

	ModelRenderer* model_renderer = new ModelRenderer(owner);
	model_renderer->SetModelHandle(MV1LoadModel("../3DModel/testFighter.mv1"));

	Input* input = new Input(owner);
	input->SetPlayerNum(static_cast<Input::PlayerNum>(m_playerNum - 1));

	new Manual(owner);
	new Automatic(owner);

	// カメラのアクター生成
	p_myCamera = new Actor(owner->GetGame());
	Camera* camera = new Camera(p_myCamera);
	camera->SetDispArea(m_dispAreaMin.x, m_dispAreaMin.y, m_dispAreaMax.x, m_dispAreaMax.y);
	camera->SetDispCenter(m_dispCenter.x, m_dispCenter.y);
	new ManualCamera(p_myCamera);
	new AutomaticCamera(p_myCamera);

	// レティクルのアクター生成
	p_myReticle = new Actor(owner->GetGame());
	Transform* reticle_tr = new Transform(p_myReticle);
	reticle_tr->SetScale(VGet(0.5f, 0.5f, 0.5f));
	UIRenderer* reticleRenderer = new UIRenderer(p_myReticle);
	reticleRenderer->SetGrphHandle(reticle);
}

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
		VECTOR ctrl_value = manuComp->FighterControl();

		// カメラ設定
		ManualCamera* manuCameraComp = p_myCamera->GetComponent<ManualCamera>();
		Transform* trComp = m_owner->GetComponent<Transform>();
		PhysicsCollider* pcComp = m_owner->GetComponent<PhysicsCollider>();
		manuCameraComp->SetCamera(this, trComp, pcComp, ctrl_value.x, ctrl_value.y, 60.0f);

		//VECTOR pos = trComp->GetPosition();
		//pos.y = 0.0f;
		//
		//if (VSize(pos) > WorldSettings::WorldRadius)
		//{
		//	printfDx("エリア外\n\n");
		//}

		// 別ステートへの遷移分岐
		Input* input = m_owner->GetComponent<Input>();
		if (input->GetButtonDown(Input::L))
		{
			m_automaticDirection = input->GetAnalog(Input::LY);
			m_currentState = Fighter::PlayerState::Automatic;
		}

		// 攻撃
		if (input->GetButtonDown(Input::ZR))
		{
			VECTOR direction = pcComp->GetDirection(VGet(0.0f, 0.0f, -1.0f));
			Attack(VScale(direction, 500.0f), VScale(direction, 9000000.0f));
		}
	}
		break;
	case Fighter::PlayerState::Automatic:
	{
		// 機体制御
		Automatic* autoComp = m_owner->GetComponent<Automatic>();

		if (!autoComp->Turn((float)m_automaticDirection))
		{
			m_currentState = Fighter::PlayerState::Manual;

			// カメラ設定
			ManualCamera* manuCameraComp = p_myCamera->GetComponent<ManualCamera>();
			Transform* trComp = m_owner->GetComponent<Transform>();
			PhysicsCollider* pcComp = m_owner->GetComponent<PhysicsCollider>();
			manuCameraComp->SetCamera(this, trComp, pcComp, 0.0f, 0.0f, 60.0f);
		}
		else
		{
			// カメラ設定
			AutomaticCamera* autoCameraComp = p_myCamera->GetComponent<AutomaticCamera>();
			PhysicsCollider* pcComp = m_owner->GetComponent<PhysicsCollider>();
			Transform* trComp = m_owner->GetComponent<Transform>();
			autoCameraComp->TurnCamera(this, autoComp, pcComp, trComp);
		}
	}
		break;
	case Fighter::PlayerState::Dead:
		break;
	}

	// レティクルの描画
	Camera* cam = p_myCamera->GetComponent<Camera>();
	Transform* reticleTr = p_myReticle->GetComponent<Transform>();
	unsigned int x = 0;
	unsigned int y = 0;
	cam->GetDispCenter(&x, &y);
	reticleTr->SetPosition(VGet(x, y, 0.0f));

	//printfDx("Speed:%f\n", m_currentSpeed);

	//Transform* trComp = m_owner->GetComponent<Transform>();
	//VECTOR rote = trComp->GetRotation();
	//printfDx("　　 %f, %f, %f\n", rote.x, rote.y, rote.z);
}

// 当たり判定
void Fighter::IsContact(const Actor* other)
{
	//printfDx("ヒット！\n");
}

// ステートの変更
void Fighter::ChangeState(PlayerState state)
{
	m_currentState = state;
}

// 通常攻撃
void Fighter::Attack(VECTOR offset, VECTOR velocity)
{
	// アクター生成
	Actor* obj = new Actor(m_owner->GetGame());

	// 機体のトランスフォームと行列取得
	Transform* fighter_tr = m_owner->GetComponent<Transform>();
	MATRIX mat = fighter_tr->GetMatrix();

	// トランスフォームのアタッチと設定
	Transform* tr = new Transform(obj);
	tr->SetMatrix(mat);
	tr->SetPosition(VAdd(fighter_tr->GetPosition(), offset));

	VECTOR fighter_rote = fighter_tr->GetRotation();
	VECTOR bullet_rote = VGet(fighter_rote.x, fighter_rote.y, fighter_rote.z);
	//tr->SetRotation(bullet_rote);

	// モデルのアタッチ
	ModelRenderer* renderer = new ModelRenderer(obj);
	renderer->SetModelHandle(m_beamModelHandle);
	renderer->SetScale(VGet(0.1f, 0.1f, 0.1f));
	renderer->SetEmissive(GetColorF(0.2f, 1.0f, 0.0f, 1.0f));

	// 弾ビヘイビアをアタッチ
	new Bullet(obj, velocity);
}
