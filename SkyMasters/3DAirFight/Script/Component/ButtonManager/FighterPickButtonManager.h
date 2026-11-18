#pragma once
#include"../../Actor/Actor.h"
#include"../Component.h"
#include"../ComponentUpdateOrder.h"
#include"../Input.h"
#include"../../Scene/SceneBase.h"
#include"../../Loader/FighterDataLoader.h"

class FighterPickButtonManager : public Component
{
public:
	FighterPickButtonManager(Actor* owner,
		const std::vector<std::unique_ptr<Actor>>& body,
		const std::vector<std::unique_ptr<Actor>>& wing,
		const std::vector<std::unique_ptr<Actor>>& diffuser,
		FighterDataLoader& loader,
		SceneBase* base);

	void Update()override;

	void BodyID();
	void WingID();
	void DiffuserID();

	

private:

	const std::vector<std::unique_ptr<Actor>>& m_bodyObject;
	const std::vector<std::unique_ptr<Actor>>& m_wingObject;
	const std::vector<std::unique_ptr<Actor>>& m_diffObject;

	int bodyID = 0;
	int wingID = 0;
	int diffuserID = 0;
	int spwID = 0;
	int pickParts = 0;

	FighterDataLoader& m_load;

	SceneBase* sb;

	enum RowParts
	{
		Body,
		Wing,
		Diffuser,
		//Spw,
	};
};