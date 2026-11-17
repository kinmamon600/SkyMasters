#pragma once
#include"../../Actor/Actor.h"
#include"../Component.h"
#include"../ComponentUpdateOrder.h"
#include"../Input.h"
#include"../../Scene/SceneBase.h"
#include"../Fighter/FighterDataLoader.h"

class FighterPickButtonManager : public Component
{
public:
	FighterPickButtonManager(Actor* owner)
		:Component(owner, static_cast<int>(ComponentUpdateOrder::Behaviour)) {};

	void Update()override;

	void SetBodyActor(std::vector<std::unique_ptr<Actor>>& actors);
	void SetBodyID();

	void SetWingActor(std::vector<std::unique_ptr<Actor>>& actors);

	void SetDiffActor(std::vector<std::unique_ptr<Actor>>& actors);

	

private:

	int bodyID;
	int wingID;
	int diffuserID;
	int spwID;
	int pickParts;

	FighterDataLoader* m_load;

	enum RowParts
	{
		Body,
		Wing,
		Diffuser,
		//Spw,
	};
};