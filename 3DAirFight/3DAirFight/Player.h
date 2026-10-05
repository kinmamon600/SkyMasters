#ifndef _PLAYER_H
#define _PLAYER_H

// ライブラリ・ヘッダ
#include <cmath>

#include "DxLib.h"  // https://dxlib.xsrv.jp/dxfunc.html
#include "SuperDxPhysics.h"

#include "VariableTransition.h"
#include "Settings.h"
#include "Input.h"
#include "Fighter.h"
#include "Beam.h"
#include "Terrain.h"

// 定数
// 自機とカメラの距離
const float DEFAULT_CAMERA_DISTANCE = 34.0f;
const float BOOST_CAMERA_DISTANCE = 36.0f;
const float BRAKE_CAMERA_DISTANCE = 28.0f;

// カメラの移動速度
//const float CAMERA_MOVE_SPEED = 5.0f;

// 自機と注視点の距離
const float FIXATION_DISTANCE = 12.0f;

// 注視点の画面上移動半径
const unsigned int FIXATION_RADIUS = 40;

// 注視点の最大・最小画面上移動速度
const float FIXATION_MOVE_MAXSPEED = 100.0f;
const float FIXATION_MOVE_MINSPEED = 10.0f;

// 自機とカメラの角度(Y方向)
const float FIGHTER_CAMERA_ANGLE = 12.0f;

// ヨー時の機体の傾き角最大
const float YAW_SLOPEANGLE_MAX = 55.0f;

// ヨー時の機体の傾き最大・最小角速度
const float YAW_SLOPEANGLE_MAXSPEED = 220.0f;
const float YAW_SLOPEANGLE_MINSPEED = 10.0f;

// プレイヤーHPの最大値
const unsigned short HP_MAX = 200;


/// <summary>
/// プレイヤーの設定管理クラス
/// 選択した機体や個別設定の保持
/// </summary>
class PlayerSettings
{
public:
	// コンストラクタ
	PlayerSettings() {};
	
	// デストラクタ
	~PlayerSettings() {};

	// 専有画面エリアの設定
	void SetDispArea(unsigned int minX, unsigned int minY, unsigned int maxX, unsigned int maxY);

	// 使用機体IDの設定
	void SetFighterID(unsigned short id);

	// 使用機体IDの取得
	unsigned short GetFighterID() const;

	// 使用カラーパレットIDの設定
	void SetColorPaletteID(unsigned short id);

	// 使用カラーパレットIDの取得
	unsigned short GetColorPaletteID() const;

	// 専有画面エリア座標の取得
	unsigned int GetDispArea_MinX() const;
	unsigned int GetDispArea_MinY() const;
	unsigned int GetDispArea_MaxX() const;
	unsigned int GetDispArea_MaxY() const;
	unsigned int GetDispArea_CenterX() const;
	unsigned int GetDispArea_CenterY() const;

private:
	// 専有画面エリア座標
	unsigned int dispArea_minX = 0;
	unsigned int dispArea_minY = 0;
	unsigned int dispArea_maxX = 0;
	unsigned int dispArea_maxY = 0;

	// 専有画面エリアの中心座標
	unsigned int dispArea_centerX = 0;
	unsigned int dispArea_centerY = 0;

	// 選択機体ID
	unsigned short fighterID = 0;

	// 選択カラーパレットID
	unsigned short colorPaletteID = 0;
};

// プレイヤーの状態
enum class PlayerState
{
	ProgramControl,	// プログラムによる制御
	PlayerControl,	// プレイヤーによる制御
	ShootDown,		// 撃墜 バラバラになる
	Count,			// ステート数
};

/// <summary>
/// プレイヤーの管理・制御クラス
/// HP等もここ
/// </summary>
class Player
{
public:
	// コンストラクタ
	Player() {};

	// デストラクタ
	~Player() {};

	// 初期化関数
	void Init(FighterParams* fighter_params);

	// プレイヤーの状態設定
	void SetState(PlayerState next_state);

	// 機体の生成
	void CreateFighter(const VECTOR& _position, const VECTOR& _direction);

	// 機体の制御
	void FighterControl(GameInput* input);

	// 機体のトランスフォーム補正
	void FighterTransformCorrection();

	// 機体の基準軸方向設定
	void SetStandardAxis();

	// カメラ位置の設定
	void SetCameraPosition();

	// カメラ位置の初期設定
	void InitCameraPosition(PlayerSettings* settings);

	// 画面中心の設定
	void SetDispCenter(PlayerSettings* settings, GameInput* input);

	// 攻撃処理
	void Attack(GameInput* input, SDP::MeshDatas* beam_mesh);

	// ビームの更新
	void BeamUpdate(Terrain* terrain);

	// 自機のビームIDの取得
	int GetBeamID(unsigned int num) const;

	// 自機のビームIDのクリア
	void ClearBeamID(unsigned int num);

	// 相手のビームによるダメージの判定
	bool Damage_OpponentBeam(Player* opponent);

	// 地形によるダメージの判定
	bool Damage_Terrain(Terrain* terrain);
	
	// 対戦の終了
	void MatchOver();

	// 自機のY座標の取得(空の描画用)
	float GetYPos();

private:
	// プレイヤーの設定
	FighterParams* fighterParams{};

	// プレイヤーのステート
	PlayerState state = PlayerState::ProgramControl;

	// 各パーツのID
	FighterPartsID partsID{};

	// パーツどうしのジョイントID
	unsigned int jointsID[FIGHTER_JOINT_NUM]{};

	// 機体制御関係変数
	VECTOR position = VGet(0.0f, 0.0f, 0.0f);
	VECTOR direction = VGet(0.0f, 0.0f, 0.0f);
	float yawSlopeAngle = 0.0f;

	VECTOR stdAxis_X = VGet(0.0f, 0.0f, 0.0f);
	VECTOR stdAxis_Y = VGet(0.0f, 0.0f, 0.0f);
	VECTOR stdAxis_Z = VGet(0.0f, 0.0f, 0.0f);

	// カメラ制御関係変数
	float previousFixationX = 0.0f;	// 前フレームの注視点画面上位置
	float previousFixationY = 0.0f;

	// 攻撃関係変数
	int beamsID[FIGHTER_BEAM_MAX]{};
	VECTOR beamVector[FIGHTER_BEAM_MAX]{};

	// 攻撃ボタンのフラグ
	bool canAttack = false;

	// HP
	short hp = 0;

	// ビームの発射
	void ShootBeam(SDP::MeshDatas* beam_mesh);

	// HPの変化
	bool ChangeHP(short amount);

	// 撃墜される いわゆるDeath的な
	void ShootDown();
};

#endif