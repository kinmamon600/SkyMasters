#ifndef _COMPONENTMANAGER_H
#define _COMPONENTMANAGER_H

// ライブラリ・ヘッダ
#include <vector>

// 前方宣言
class Component;

/// <summary>
/// コンポーネントの管理クラス
/// コンポーネントの更新等を行う
/// ※所有権は持たない
/// </summary>
class ComponentManager
{
public:
	// コンストラクタ
	ComponentManager() {};

	// デストラクタ
	~ComponentManager() {};

	// コンポーネントの追加
	void AddComponent(Component* component);

	// コンポーネントの削除
	void RemoveComponent(Component* component);

	// コンポーネントの更新
	// アクターは関係なくコンポーネントの更新順にのっとって更新
	void Update();

private:
	// コンポーネントのポインタ可変長配列
	// Actorが所有権を持つのでただアドレスを持つだけ
	// 処理系コンポーネントとレンダリング系コンポーネントを別に保持
	std::vector<class Component*> p_processComponents;
	std::vector<class Component*> p_renderComponents;
};

#endif