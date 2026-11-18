#pragma once

// 前方宣言
class Actor;

class Component
{
public:
	// コンストラクタ
	Component(class Actor* owner, int updateOrder);

	// デストラクタ
	virtual ~Component();

	// 更新
	virtual void Update();

	// アップデート順の取得
	int GetUpdateOrder() const;

	// 自身がアタッチされているアクターの取得
	Actor* GetOwner() const;

protected:
	Actor* m_owner;
	int m_updateOrder;
};
