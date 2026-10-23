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

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }

	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	template <typename T>
	T* GetComponent()
	{
		for (class Component* component : mComponents)
		{
			T* result = dynamic_cast<T*>(component);

			if (result != nullptr)
			{
				return result;
			}
		}
		return nullptr;
	}

private:
	State mState;

	std::vector<class Component*> mComponents;
	class Game* mGame;
};
