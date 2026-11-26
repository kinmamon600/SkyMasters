// ライブラリ・ヘッダ
#include <functional>
#include "DxLib.h"

#include"Cannon.h"
#include "../../Actor/Actor.h"
#include "../Detector.h"
#include "../../Component/Transform.h"
#include "../Bullet.h"
#include "../../Component/ModelRenderer.h"
#include "../../Component/PhysicsCollider.h"

// コンストラクタ
Cannon::Cannon(Actor* owner, int hp, int atk, int bullet)
	:EnemyBase(owner, hp, atk) 
{
	// 検知判定の生成
	//Actor* detector = new Actor(owner->GetGame());
	p_detector = std::make_unique<Actor>(owner->GetGame());
	Transform* tr = owner->GetComponent<Transform>();
	new Detector(p_detector.get(), tr->GetPosition(), m_detectionRadius, ActorLayer::Player,
		[this](Actor* p_player) {this->DetectPlayer(p_player); });

	// 弾のモデルハンドルの設定
	m_bulletModelhandle = bullet;

	// 時間設定
	m_countStartTime = (float)GetNowCount() / 1000.0f;
}

// デストラクタ
Cannon::~Cannon()
{

}

// 更新処理
void Cannon::Update()
{

}

// コライダーがアタッチされている時、接触時に呼ばれる
//void Cannon::IsContact(const Actor* ohter)
//{
//
//}

// プレイヤーを検知したときに呼ばれる
void Cannon::DetectPlayer(Actor* p_player)
{
	//printfDx("どこにおるんぢゃワレェ\n");

	// クールタイムが終わったら攻撃
	float current_time = (float)GetNowCount() / 1000.0f;
	if (current_time - m_countStartTime > m_ct)
	{
		m_countStartTime = current_time;

		Attack(p_player);
	}
}

// 攻撃
void Cannon::Attack(Actor* target)
{
	// 自身とターゲットのトランスフォーム取得
	Transform* my_tr = m_owner->GetComponent<Transform>();
	Transform* target_tr = target->GetComponent<Transform>();

	// 座標とベクトルの取得
	VECTOR my_pos = my_tr->GetPosition();
	VECTOR shoot_vec = VNorm(VSub(target_tr->GetPosition(), my_pos));

	// 内積を使って正面の判断
	PhysicsCollider* pcComp = m_owner->GetComponent<PhysicsCollider>();
	VECTOR up_vec = pcComp->GetDirection(VGet(0.0f, 1.0f, 0.0f));

	float dot = VDot(shoot_vec, up_vec);
	if (dot > 0)
	{
		shoot_vec = VScale(shoot_vec, m_projectileSpeed);

		// 弾の生成
		Actor* bullet = new Actor(m_owner->GetGame());
		bullet->SetLayer(ActorLayer::EnemyBullet);

		Transform* bullet_tr = new Transform(bullet);
		bullet_tr->SetPosition(my_pos);

		ModelRenderer* bullet_renderer = new ModelRenderer(bullet);
		bullet_renderer->SetModelHandle(m_bulletModelhandle);
		bullet_renderer->SetScale(VGet(0.1f, 0.1f, 0.1f));

		bullet_renderer->SetDiffuse(GetColorF(0.0f, 0.0f, 0.0f, 1.0f));
		bullet_renderer->SetSpecular(GetColorF(0.0f, 0.0f, 0.0f, 1.0f));
		bullet_renderer->SetEmissive(GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
		bullet_renderer->SetAmbient(GetColorF(0.0f, 0.0f, 0.0f, 1.0f));
		bullet_renderer->SetSpecularPower(0.0f);

		new Bullet(bullet, shoot_vec, 0.0f);
	}
}
