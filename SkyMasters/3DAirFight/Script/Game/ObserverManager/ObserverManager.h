#ifndef _OBSERVERMANAGER_H
#define _OBSERVERMANAGER_H

// ライブラリ・ヘッダ
#include <vector>

// 前方宣言
class Behavior;
enum class EventList;

/// <summary>
/// 通知管理クラス
/// </summary>
class ObserverManager
{
public:
	// コンストラクタ
	ObserverManager(){}

	// デストラクタ
	~ObserverManager(){}

	// ビヘイビアの追加
	void AddBehavior(Behavior* behavior);

	// ビヘイビアの削除
	void RemoveBehavior(Behavior* behavior);

	// ビヘイビアに通知する
	void Notify(EventList event);

private:
	// ビヘイビアの配列
	std::vector<Behavior*> p_behaviors = {};
};

#endif