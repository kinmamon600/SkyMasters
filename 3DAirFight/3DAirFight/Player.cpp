// ライブラリ・ヘッダ
#include "Player.h"

// クラス「PlayerSettings」の関数等

void PlayerSettings::SetDispArea(unsigned int minX, unsigned int minY, unsigned int maxX, unsigned int maxY)
{
	dispArea_minX = minX;
	dispArea_minY = minY;
	dispArea_maxX = maxX;
	dispArea_maxY = maxY;

	dispArea_centerX = dispArea_minX + (dispArea_maxX - dispArea_minX) / 2;
	dispArea_centerY = dispArea_minY + (dispArea_maxY - dispArea_minY) / 2;
}

void PlayerSettings::SetFighterID(unsigned short id) { fighterID = id; }
unsigned short PlayerSettings::GetFighterID() const { return fighterID; }

void PlayerSettings::SetColorPaletteID(unsigned short id) { colorPaletteID = id; }
unsigned short PlayerSettings::GetColorPaletteID() const { return colorPaletteID; }

unsigned int PlayerSettings::GetDispArea_MinX() const { return dispArea_minX; }
unsigned int PlayerSettings::GetDispArea_MinY() const { return dispArea_minY; }
unsigned int PlayerSettings::GetDispArea_MaxX() const { return dispArea_maxX; }
unsigned int PlayerSettings::GetDispArea_MaxY() const { return dispArea_maxY; }
unsigned int PlayerSettings::GetDispArea_CenterX() const { return dispArea_centerX; }
unsigned int PlayerSettings::GetDispArea_CenterY() const { return dispArea_centerY; }

// クラス「Player」の関数等

void Player::Init(FighterParams* fighter_params)
{
	fighterParams = fighter_params;

	for (unsigned int i = 0; i < FIGHTER_BEAM_MAX; ++i)
	{
		beamsID[i] = -1;
		beamVector[i] = VGet(0.0f, 0.0f, 0.0f);
	}

	hp = HP_MAX;
}

void Player::SetState(PlayerState next_state)
{
	state = next_state;
}

void Player::CreateFighter(const VECTOR& _position, const VECTOR& _direction)
{
	// 機体重量の取得
	float mass = fighterParams->GetMass();
	mass /= FIGHTER_PARTS_NUM;

	// 自機の生成 & IDの取得
	for (unsigned short i = 0; i < FIGHTER_PARTS_NUM; ++i)
	{
		SDP::MeshDatas* p_fighter_mesh = fighterParams->GetMeshes(i);
		partsID.SetPartsID(i, SDP::CreatePhysicalConvexMesh(_position, p_fighter_mesh, kPfxMotionTypeActive, mass, GetColorU8(255, 255, 255, 0)));
	}

	// 自機の詳細設定
	for (unsigned short i = 0; i < FIGHTER_PARTS_NUM; ++i)
	{
		// 自機を不動ジョイントで結合
		for (unsigned short j = FIGHTER_PARTS_NUM - 1; j > i; --j)
		{
			jointsID[i + j] = SDP::AddPhysicalJointFixed(partsID.GetPartsID(i), partsID.GetPartsID(j), VGet(0.0f, 0.0f, 0.0f));
		}

		// 自機の反射係数設定
		SDP::SetRestitution(partsID.GetPartsID(i), FIGHTER_RESTITUTION);

		// 自機の摩擦設定
		SDP::SetFriction(partsID.GetPartsID(i), FIGHTER_FRICTION);
	}

	// 自機の向きを回転で設定
	SDP::SetRotate(partsID.GetPartsID(), _direction);

	// 基準方向の取得
	stdAxis_X = SDP::GetDirection(partsID.GetPartsID(), VGet(1.0f, 0.0f, 0.0f));
	stdAxis_Y = SDP::GetDirection(partsID.GetPartsID(), VGet(0.0f, 1.0f, 0.0f));
	stdAxis_Z = SDP::GetDirection(partsID.GetPartsID(), VGet(0.0f, 0.0f, 1.0f));
}

void Player::FighterControl(GameInput* input)
{
	// 撃墜されていたらreturn
	if (state == PlayerState::ShootDown) { return; }

	// 自機の座標・向きの取得
	VECTOR fighter_pos = SDP::GetPosition(partsID.GetPartsID());
	VECTOR fighter_forward = VScale(stdAxis_Z, -1.0f);
	
	// 速度設定
	// hpが0なら0
	VECTOR linear_velocity = VScale(fighter_forward, fighterParams->GetDefaultSpeed());

	// 角速度設定 & ヨー時の傾き設定
	// プレイヤー操作時で無ければ0
	float pitch = 0.0f;
	float yaw = 0.0f;
	float roll = 0.0f;

	float current_yawslopeangle = 0.0f;
	float target_yawslopeangle = 0.0f;
	
	if (state == PlayerState::PlayerControl)
	{
		pitch = -(float)(input->GetY()) / JOYPAD_MAX * fighterParams->GetPitchAngularVelocity();
		yaw = -(float)(input->GetX()) / JOYPAD_MAX * fighterParams->GetYawAngularVelocity();

		if (input->GetL()) { roll += fighterParams->GetRollAngularVelocity(); }
		if (input->GetR()) { roll -= fighterParams->GetRollAngularVelocity(); }

		target_yawslopeangle = -(float)(input->GetX()) / JOYPAD_MAX * YAW_SLOPEANGLE_MAX;

		if (target_yawslopeangle > yawSlopeAngle)
		{
			float spd = VariableTransition_QuadraticFluctuation((target_yawslopeangle - yawSlopeAngle) / (YAW_SLOPEANGLE_MAX * 2.0f),
				YAW_SLOPEANGLE_MINSPEED, YAW_SLOPEANGLE_MAXSPEED);
			current_yawslopeangle = yawSlopeAngle + spd / FPS;
			if (current_yawslopeangle > target_yawslopeangle) { current_yawslopeangle = target_yawslopeangle; }
		}
		else if (target_yawslopeangle < yawSlopeAngle)
		{
			float spd = VariableTransition_QuadraticFluctuation((yawSlopeAngle - target_yawslopeangle) / (YAW_SLOPEANGLE_MAX * 2.0f),
				YAW_SLOPEANGLE_MINSPEED, YAW_SLOPEANGLE_MAXSPEED);
			current_yawslopeangle = yawSlopeAngle - spd / FPS;
			if (current_yawslopeangle < target_yawslopeangle) { current_yawslopeangle = target_yawslopeangle; }
		}
		else
		{
			current_yawslopeangle = target_yawslopeangle;
		}
	}

	VECTOR control_angularvelocity = VGet(stdAxis_X.x * pitch + stdAxis_Y.x * yaw + stdAxis_Z.x * roll,
								  stdAxis_X.y * pitch + stdAxis_Y.y * yaw + stdAxis_Z.y * roll,
								  stdAxis_X.z * pitch + stdAxis_Y.z * yaw + stdAxis_Z.z * roll);

	float yawslopeangle_changeamount = current_yawslopeangle - yawSlopeAngle;
	VECTOR yawslope_angularvelocity = VGet(stdAxis_Z.x * yawslopeangle_changeamount, 
										   stdAxis_Z.y * yawslopeangle_changeamount, 
										   stdAxis_Z.z * yawslopeangle_changeamount);
	yawSlopeAngle = current_yawslopeangle;

	VECTOR angular_velocity = VAdd(control_angularvelocity, yawslope_angularvelocity);

	// 代入
	for (unsigned short i = 0; i < FIGHTER_PARTS_NUM; ++i)
	{
		SDP::SetLinerVelocity(partsID.GetPartsID(i), linear_velocity);
		SDP::SetAngularVelocity(partsID.GetPartsID(i), angular_velocity);
	}
}

void Player::FighterTransformCorrection()
{
	// プレイヤー操作時で無ければreturn
	if (state != PlayerState::PlayerControl) { return; }

	// 一番動いていないオブジェクトに座標を合わせる
	VECTOR pars_pos[FIGHTER_PARTS_NUM - 1];
	for (unsigned short i = 1; i < FIGHTER_PARTS_NUM - 1; ++i)
	{
		pars_pos[i] = SDP::GetPosition(partsID.GetPartsID(i));
	}
	
	float dist = VSize(VAdd(position, VScale(pars_pos[0], -1)));
	int std_id = 0;
	for (unsigned short i = 1; i < FIGHTER_PARTS_NUM - 1; ++i)
	{
		if (VSize(VAdd(position, VScale(pars_pos[i], -1))) < dist)
		{
			dist = VSize(VAdd(position, VScale(pars_pos[i], -1)));
			std_id = i;
		}
	}

	// ローテートも合わせる
	VECTOR std_rotate = SDP::GetRotate(partsID.GetPartsID(std_id));

	for (unsigned short i = 0; i < FIGHTER_PARTS_NUM; ++i)
	{
		SDP::SetPosition(partsID.GetPartsID(i), pars_pos[std_id]);
		SDP::SetRotate(partsID.GetPartsID(i), std_rotate);
	}

	// 現在の座標・向き設定
	position = pars_pos[std_id];
}

void Player::SetStandardAxis()
{
	// プレイヤー操作時で無ければreturn
	if (state != PlayerState::PlayerControl) { return; }

	// 物理演算による現在値をロドリゲスの回転公式でヨーの傾き分補正
	VECTOR direction = SDP::GetDirection(partsID.GetPartsID(), VGet(1.0f, 0.0f, 0.0f));
	VECTOR axis = SDP::GetDirection(partsID.GetPartsID(), VGet(0.0f, 0.0f, 1.0f));
	float rad = yawSlopeAngle * DX_PI_F / 180.0f;
	float c = std::cos(rad);
	float s = std::sin(rad);

	stdAxis_X = VAdd(VScale(direction, c), VScale(VCross(axis, direction), s));

	direction = SDP::GetDirection(partsID.GetPartsID(), VGet(0.0f, 1.0f, 0.0f));
	stdAxis_Y = VAdd(VScale(direction, c), VScale(VCross(axis, direction), s));

	// Z方向は変わらないので現在値を代入
	stdAxis_Z = SDP::GetDirection(partsID.GetPartsID(), VGet(0.0f, 0.0f, 1.0f));
}

void Player::SetCameraPosition()
{
	// 自機の座標と向きの取得
	VECTOR fighter_pos = SDP::GetPosition(partsID.GetPartsID());
	VECTOR fighter_forward = SDP::GetDirection(partsID.GetPartsID(), VGet(0.0f, 0.0f, -1.0f));

	// 注視点の設定
	VECTOR fixation_pos = VScale(fighter_forward, FIXATION_DISTANCE);
	fixation_pos = VAdd(fixation_pos, fighter_pos);

	// カメラ座標の設定
	VECTOR camera_pos = VScale(fighter_forward, -1.0f);

	// カメラをロドリゲスの回転公式で自機正面が見えるよう位置調整
	VECTOR axis = VCross(camera_pos, stdAxis_Y);
	float rad = FIGHTER_CAMERA_ANGLE * DX_PI_F / 180.0f;
	float c = std::cos(rad);
	float s = std::sin(rad);

	camera_pos = VAdd(VScale(camera_pos, c), VScale(VCross(axis, camera_pos), s));
	camera_pos = VAdd(VScale(camera_pos, DEFAULT_CAMERA_DISTANCE), fighter_pos);

	SetCameraPositionAndTargetAndUpVec(camera_pos, fixation_pos, stdAxis_Y);
}

void Player::InitCameraPosition(PlayerSettings* settings)
{
	// 自機の座標と向きの取得
	VECTOR fighter_pos = SDP::GetPosition(partsID.GetPartsID());
	VECTOR fighter_forward = SDP::GetDirection(partsID.GetPartsID(), VGet(0.0f, 0.0f, -1.0f));

	// 注視点の設定
	VECTOR fixation_pos = VScale(fighter_forward, FIXATION_DISTANCE);
	fixation_pos = VAdd(fixation_pos, fighter_pos);

	// カメラ座標の設定
	VECTOR camera_pos = VScale(fighter_forward, -1.0f);
	VECTOR fighter_upward = SDP::GetDirection(partsID.GetPartsID(), VGet(0.0f, 1.0f, 0.0f));
	VECTOR axis = VCross(camera_pos, fighter_upward);

	float rad = FIGHTER_CAMERA_ANGLE * DX_PI_F / 180.0f;
	float c = std::cos(rad);
	float s = std::sin(rad);

	// カメラをロドリゲスの回転公式で自機正面が見えるよう位置調整
	camera_pos = VAdd(VScale(camera_pos, c), VScale(VCross(axis, camera_pos), s));
	camera_pos = VAdd(VScale(camera_pos, DEFAULT_CAMERA_DISTANCE), fighter_pos);

	SetCameraPositionAndTarget_UpVecY(camera_pos, fixation_pos);

	previousFixationX = (float)settings->GetDispArea_CenterX();
	previousFixationY = (float)settings->GetDispArea_CenterY();
	SetCameraScreenCenter(previousFixationX, previousFixationY);
}

void Player::SetDispCenter(PlayerSettings* settings, GameInput* input)
{
	// プレイヤー操作時で無ければ単にセンター
	if (state != PlayerState::PlayerControl)
	{
		SetCameraScreenCenter(settings->GetDispArea_CenterX(), settings->GetDispArea_CenterY());
		return;
	}

	float target_x = settings->GetDispArea_CenterX() - input->GetX() / (float)JOYPAD_MAX * (float)FIXATION_RADIUS;
	float target_y = settings->GetDispArea_CenterY() + input->GetY() / (float)JOYPAD_MAX * (float)FIXATION_RADIUS;

	float current_x = previousFixationX;
	float current_y = previousFixationY;

	float spd = 0.0f;

	if (current_x < target_x)
	{
		spd = VariableTransition_QuadraticDecrease((target_x - current_x) / (float)(FIXATION_RADIUS * 2), 
			FIXATION_MOVE_MINSPEED, FIXATION_MOVE_MAXSPEED);
		current_x += spd / FPS;
		if (current_x > target_x) { current_x = target_x; }
	}
	else if (current_x > target_x)
	{
		spd = VariableTransition_QuadraticDecrease((current_x - target_x) / (float)(FIXATION_RADIUS * 2),
			FIXATION_MOVE_MINSPEED, FIXATION_MOVE_MAXSPEED);
		current_x -= spd / FPS;
		if (current_x < target_x) { current_x = target_x; }
	}

	if (current_y < target_y)
	{
		spd = VariableTransition_QuadraticDecrease((target_y - current_y) / (float)(FIXATION_RADIUS * 2),
			FIXATION_MOVE_MINSPEED, FIXATION_MOVE_MAXSPEED);
		current_y += spd / FPS;
		if (current_y > target_y) { current_y = target_y; }
	}
	else if (current_y > target_y)
	{
		spd = VariableTransition_QuadraticDecrease((current_y - target_y) / (float)(FIXATION_RADIUS * 2),
			FIXATION_MOVE_MINSPEED, FIXATION_MOVE_MAXSPEED);
		current_y -= spd / FPS;
		if (current_y < target_y) { current_y = target_y; }
	}

	SetCameraScreenCenter(current_x, current_y);
	previousFixationX = current_x;
	previousFixationY = current_y;
}

void Player::ShootBeam(SDP::MeshDatas* beam_mesh)
{
	// 残弾があり撃てるか確認
	unsigned short remain_ammo = 0;
	for (unsigned short i = 0; i < FIGHTER_BEAM_MAX; ++i)
	{
		if (beamsID[i] == -1)
		{
			++remain_ammo;
		}
	}

	if (remain_ammo < fighterParams->GetMuzzleNum()) { return; }

	// 銃口の数だけビーム発射
	for (unsigned short i = 0; i < fighterParams->GetMuzzleNum(); ++i)
	{
		for (unsigned short j = 0; j < FIGHTER_BEAM_MAX; ++j)
		{
			if (beamsID[j] == -1)
			{
				// ビームの出現位置設定
				VECTOR offset = fighterParams->GetMuzzlePosition(i);
				VECTOR beam_pos_x = VScale(SDP::GetDirection(partsID.GetPartsID(), VGet(1.0f, 0.0f, 0.0f)), offset.x);
				VECTOR beam_pos_y = VScale(SDP::GetDirection(partsID.GetPartsID(), VGet(0.0f, 1.0f, 0.0f)), offset.y);
				VECTOR beam_pos_z = VScale(SDP::GetDirection(partsID.GetPartsID(), VGet(0.0f, 0.0f, 1.0f)), offset.z);
				VECTOR beam_pos = VAdd(VAdd(VAdd(beam_pos_x, beam_pos_y), beam_pos_z), SDP::GetPosition(partsID.GetPartsID()));

				// ビームの発射
				beamsID[j] = SDP::CreatePhysicalLargeTriMesh(beam_pos, beam_mesh, kPfxMotionTypeTrigger, 0.0f, GetColorU8(255, 240, 0, 0));
				
				// ビームの向き設定
				SDP::SetRotate(beamsID[j], SDP::GetRotate(partsID.GetPartsID()));

				// ビームのベクトル設定
				beamVector[j] = VScale(SDP::GetDirection(partsID.GetPartsID(), VGet(0.0f, 0.0f, -1.0f)), BEAM_SPEED / FPS);
				break;
			}
		}
	}
}

void Player::Attack(GameInput* input, SDP::MeshDatas* beam_mesh)
{
	// プレイヤー操作時で無ければreturn
	if (state != PlayerState::PlayerControl) { return; }

	// ビームの発射
	if (input->GetWest())
	{
		if (canAttack)
		{
			canAttack = false;
			ShootBeam(beam_mesh);
		}
	}
	else
	{
		canAttack = true;
	}
}

void Player::BeamUpdate(Terrain* terrain)
{
	for (unsigned short i = 0; i < FIGHTER_BEAM_MAX; ++i)
	{
		if (beamsID[i] != -1)
		{
			// ビームの現在座標の取得
			VECTOR pos = SDP::GetPosition(beamsID[i]);

			// ビームがエリア外にあれば消去
			if (VSize(pos) > COMBAT_AREA)
			{
				SDP::DestroyPhysicalObject(beamsID[i]);
				beamsID[i] = -1;
				continue;
			}

			// ビームが地形に当たったら消去
			for (int j = 0; j < TERRAIN_OBJECT_NUM; ++j)
			{
				if (SDP::IsContact(beamsID[i], terrain->GetID(j)))
				{
					SDP::DestroyPhysicalObject(beamsID[i]);
					beamsID[i] = -1;
					continue;
				}
			}

			// ビームの座標設定
			SDP::SetPosition(beamsID[i], VAdd(pos, beamVector[i]));
		}
	}
}

int Player::GetBeamID(unsigned int num) const
{
	return beamsID[num];
}

void Player::ClearBeamID(unsigned int num)
{
	beamsID[num] = -1;
}

bool Player::ChangeHP(short amount)
{
	hp += amount;
	//printfDx("%d\n", amount);

	if (hp < 1)
	{
		return true;
	}

	return false;
}

void Player::ShootDown()
{
	// ジョイント接続の解除
	for (unsigned short i = 0; i < FIGHTER_JOINT_NUM; ++i)
	{
		SDP::DestroyJoint(jointsID[i]);
	}

	// 非接触設定の解除
	for (unsigned short i = 0; i < FIGHTER_PARTS_NUM; ++i)
	{
		for (int j = FIGHTER_PARTS_NUM - 1; j > i; --j)
		{
			SDP::ReleaseNonContactPair(partsID.GetPartsID(i), partsID.GetPartsID(j));
		}
	}

	// はじけ飛ぶベクトルの設定
	for (unsigned short i = 0; i < FIGHTER_PARTS_NUM; ++i)
	{
		SDP::SetLinerVelocity(partsID.GetPartsID(i), VGet(0.0f, GRAVITY_SCALE * -10.0f / FPS, 0.0f));
	}
}

bool Player::Damage_OpponentBeam(Player* opponent)
{
	bool resolution = false;

	for (int i = 0; i < FIGHTER_BEAM_MAX; ++i)
	{
		int beam_id = opponent->GetBeamID(i);
		if (beam_id == -1) { continue; }

		bool isDamage = false;

		for (unsigned short i = 0; i < FIGHTER_PARTS_NUM; ++i)
		{
			isDamage = isDamage || SDP::IsContact(partsID.GetPartsID(i), beam_id);
		}

		if (isDamage)
		{
			resolution = ChangeHP(-BEAM_DAMAGE);
			SDP::DestroyPhysicalObject(beam_id);
			opponent->ClearBeamID(i);
		}
	}

	return resolution;
}

bool Player::Damage_Terrain(Terrain* terrain)
{
	bool resolution = false;

	for (int i = 0; i < TERRAIN_OBJECT_NUM; ++i)
	{
		int terrain_id = terrain->GetID(i);
		if (terrain_id == -1) { continue; }

		bool isDamage = false;

		for (unsigned short i = 0; i < FIGHTER_PARTS_NUM; ++i)
		{
			isDamage = isDamage || SDP::IsContact(partsID.GetPartsID(i), terrain_id);
		}

		if (isDamage)
		{
			resolution = ChangeHP(-TERRAIN_DAMAGE);
		}
	}

	return resolution;
}

void Player::MatchOver()
{
	// 自身のHPが0なら撃墜演出実行
	if (hp < 1)
	{
		state = PlayerState::ShootDown;
		ShootDown();
	}
}

float Player::GetYPos()
{
	return SDP::GetPosition(partsID.GetPartsID()).y;
}
