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
#include "../Sound.h"
#include "../../Actor/ActorLayer.h"

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

	new Sound(owner);

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
	p_myReticle1 = new Actor(owner->GetGame());
	Transform* reticle_tr1 = new Transform(p_myReticle1);
	reticle_tr1->SetScale(VGet(0.1f, 0.1f, 0.1f));
	UIRenderer* reticleRenderer1 = new UIRenderer(p_myReticle1);
	reticleRenderer1->SetGrphHandle(reticle);

	p_myReticle2 = new Actor(owner->GetGame());
	Transform* reticle_tr2 = new Transform(p_myReticle2);
	reticle_tr2->SetScale(VGet(0.05f, 0.05f, 0.05f));
	UIRenderer* reticleRenderer2 = new UIRenderer(p_myReticle2);
	reticleRenderer2->SetGrphHandle(reticle);
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

		// エリア判定
		VECTOR pos = trComp->GetPosition();

		float xz_size = std::sqrt(pos.x * pos.x + pos.z * pos.z);

		// XZ方向にエリア外なら自動的にターン
		if (xz_size >= WorldSettings::WorldRadius * 0.9f)
		{
			float height_center = (WorldSettings::WorldLength - WorldSettings::FloorHeight) / 2.0f + WorldSettings::FloorHeight;

			if (pos.y < height_center)
			{
				m_automaticDirection = 1;
			}
			else
			{
				m_automaticDirection = -1;
			}

			m_currentState = Fighter::PlayerState::Automatic;
		}

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
			Attack(VScale(direction, 10.0f), VScale(direction, 1100.0f));
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
	default:
		break;
	}

	// レティクルの設定
	SetRericlePos();

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

// 通知を受け取る
void Fighter::OnNotify(EventList event)
{
	//printfDx("お便りが届いたヨ\n");
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
	Actor* bullet = new Actor(m_owner->GetGame());
	bullet->SetLayer(ActorLayer::PlayerBullet);

	// 機体のトランスフォームと行列取得
	Transform* fighter_tr = m_owner->GetComponent<Transform>();
	MATRIX mat = fighter_tr->GetMatrix();

	// トランスフォームのアタッチと設定
	Transform* tr = new Transform(bullet);
	tr->SetMatrix(mat);
	tr->SetPosition(VAdd(fighter_tr->GetPosition(), offset));

	VECTOR fighter_rote = fighter_tr->GetRotation();
	VECTOR bullet_rote = VGet(fighter_rote.x, fighter_rote.y, fighter_rote.z);
	//tr->SetRotation(bullet_rote);

	// モデルのアタッチ
	ModelRenderer* renderer = new ModelRenderer(bullet);
	renderer->SetModelHandle(m_beamModelHandle);
	renderer->SetScale(VGet(0.03f, 0.03f, 0.08f));

	renderer->SetDiffuse(GetColorF(0.0f, 0.0f, 0.0f, 1.0f));
	renderer->SetSpecular(GetColorF(0.0f, 0.0f, 0.0f, 1.0f));
	renderer->SetEmissive(GetColorF(1.0f, 1.0f, 0.0f, 1.0f));
	renderer->SetAmbient(GetColorF(0.0f, 0.0f, 0.0f, 1.0f));
	renderer->SetSpecularPower(0.0f);

	// 弾ビヘイビアをアタッチ
	new Bullet(bullet, velocity, 200.0f);

	// 効果音再生
	Sound* sound = m_owner->GetComponent<Sound>();
	sound->PlaySE(SE::Fighter_Shot);
}

// レティクル位置の設定
void Fighter::SetRericlePos()
{
	UIRenderer* renderer1 = p_myReticle1->GetComponent<UIRenderer>();
	UIRenderer* renderer2 = p_myReticle2->GetComponent<UIRenderer>();

	switch (m_currentState)
	{
	case Fighter::PlayerState::Automatic:
	case Fighter::PlayerState::Dead:
		renderer1->SetIsVisible(false);
		renderer2->SetIsVisible(false);
		return;
		break;
	default:
		break;
	}

	renderer1->SetIsVisible(true);
	renderer2->SetIsVisible(false);

	Camera* camera = p_myCamera->GetComponent<Camera>();
	Transform* fighter_tr = m_owner->GetComponent<Transform>();
	PhysicsCollider* pc = m_owner->GetComponent<PhysicsCollider>();

	VECTOR pos1 = camera->ConvPos2Disp(VAdd(fighter_tr->GetPosition(), VScale(pc->GetDirection(VGet(0.0f, 0.0f, -1.0f)), m_reticleDistance)));
	VECTOR pos2 = camera->ConvPos2Disp(VAdd(fighter_tr->GetPosition(), VScale(pc->GetDirection(VGet(0.0f, 0.0f, -1.0f)), m_reticleDistance * 2.0f)));
	
	// 範囲外の時ひとまず原点に
	if (pos1.z < 0.0f || pos1.z > 1.0f)
	{
		pos1.x = 0.0f;
		pos1.y = 0.0f;
	}

	if (pos2.z < 0.0f || pos2.z > 1.0f)
	{
		pos2.x = 0.0f;
		pos2.y = 0.0f;
	}

	Transform* reticle_tr1 = p_myReticle1->GetComponent<Transform>();
	reticle_tr1->SetPosition(VGet(pos1.x, pos1.y, 0.0f));

	Transform* reticle_tr2 = p_myReticle2->GetComponent<Transform>();
	reticle_tr2->SetPosition(VGet(pos2.x, pos2.y, 0.0f));
}
