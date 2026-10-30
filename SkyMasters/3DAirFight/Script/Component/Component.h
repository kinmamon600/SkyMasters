#pragma once

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
	int GetUpdateOrder() const { return m_updateOrder; }

protected:
	class Actor* m_owner;
	int m_updateOrder;
};
