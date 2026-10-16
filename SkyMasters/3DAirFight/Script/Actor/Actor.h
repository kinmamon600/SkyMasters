#pragma once
#include <vector>

class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor(class Game* game);
	virtual ~Actor();

	// Update
	void Update();
	void UpdateComponents();
	virtual void UpdateActor();

	virtual void Draw();

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }

	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	State mState;

	std::vector<class Component*> mComponents;
	class Game* mGame;
};
