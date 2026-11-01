// ライブラリ・ヘッダ
#include <cmath>
#include "ControllerInput.h"
#include "ControllerTypeKeyConfiguration.h"

// 定数
const double JOYSTICK_DEAD_ZONE = 0.25;			// ジョイスティックのデッドゾーン
const int XBOX_THUMB_SCALE_DIVISOR = 32;		// XBOXコントローラのジョイスティック値の除数
const unsigned int XBOX_TRIGGER_THRESHOLD = 30;	// XBOXコントローラのアナログトリガの閾値

// 新規コントローラのセットアップ
void ControllerInput::SetUp(int gamepad_num)
{
	// デバイス情報の設定
	m_deviceData.SetUp(gamepad_num);
	
	// 使用状況・接続状態更新
	m_isUse = true;
	m_isConnected = true;

	// コントローラ種類別のキーコンフィグを設定
	switch (m_deviceData.GetControllerType())
	{
	case DX_PADTYPE_DUAL_SHOCK_3:
		m_keyConfiguration = CtrlTypeKeyCon::DUAL_SHOCK_3;
		break;

	case DX_PADTYPE_DUAL_SHOCK_4:
		m_keyConfiguration = CtrlTypeKeyCon::DUAL_SHOCK_4;
		break;

	case DX_PADTYPE_DUAL_SENSE:
		m_keyConfiguration = CtrlTypeKeyCon::DUAL_SENSE;
		break;

	case DX_PADTYPE_SWITCH_JOY_CON_L:
		m_keyConfiguration = CtrlTypeKeyCon::SWITCH_JOY_CON_L;
		break;

	case DX_PADTYPE_SWITCH_JOY_CON_R:
		m_keyConfiguration = CtrlTypeKeyCon::SWITCH_JOY_CON_R;
		break;

	case DX_PADTYPE_SWITCH_PRO_CTRL:
		m_keyConfiguration = CtrlTypeKeyCon::SWITCH_PRO_CTRL;
		break;

	case DX_PADTYPE_SWITCH_HORI_PAD:
		m_keyConfiguration = CtrlTypeKeyCon::SWITCH_HORI_PAD;
		break;

	case DX_PADTYPE_OTHER:
		m_keyConfiguration = CtrlTypeKeyCon::OTHER;
		break;

	default:
		// XBOX系は設定しない
		break;
	}

	// 入力のクリア
	ClearInput();

	// デッドゾーン設定
	SetJoypadDeadZone(gamepad_num, JOYSTICK_DEAD_ZONE);
}

// コントローラ番号の設定
void ControllerInput::SetGamepadNum(int new_num)
{
	// 使用状況・接続状態更新
	m_isUse = true;
	m_isConnected = true;

	m_deviceData.SetGamepadNum(new_num);
}

// 入力の更新
void ControllerInput::Update()
{
	// 1つ前の入力状態を保持
	SetPreviousInput();

	// 使用しない設定の時return
	if (!m_isUse) { return; }

	// 入力更新
	// 入力タイプに合わせて分岐
	switch (m_deviceData.GetInputType())
	{
	case ControllerDeviceData::InputType::XBOX:
		UpdateXboxInput();
		break;

	case ControllerDeviceData::InputType::DIRECT:
		UpdateDirectInput();
		break;

	default:
		return;
		break;
	}
}

// このインプットクラスを使用しないように設定
void ControllerInput::SetNonUse()
{
	m_isUse = false;
}

// ゲッター (デジタル:現状)
bool ControllerInput::GetArrowUp()			const { return m_currentArrowUp; }
bool ControllerInput::GetArrowRight()		const { return m_currentArrowRight; }
bool ControllerInput::GetArrowDown()		const { return m_currentArrowDown; }
bool ControllerInput::GetArrowLeft()		const { return m_currentArrowLeft; }

bool ControllerInput::GetNorth()			const { return m_currentNorth; }
bool ControllerInput::GetEast()				const { return m_currentEast; }
bool ControllerInput::GetSouth()			const { return m_currentSouth; }
bool ControllerInput::GetWest()				const { return m_currentWest; }

bool ControllerInput::GetL()				const { return m_currentL; }
bool ControllerInput::GetR()				const { return m_currentR; }
bool ControllerInput::GetZL()				const { return m_currentZL; }
bool ControllerInput::GetZR()				const { return m_currentZR; }

bool ControllerInput::GetStart()			const { return m_currentStart; }
bool ControllerInput::GetSelect()			const { return m_currentSelect; }

// ゲッター (デジタル:押した瞬間)
bool ControllerInput::GetDownArrowUp()		const { return (m_currentArrowUp && !m_previousArrowUp); }
bool ControllerInput::GetDownArrowRight()	const { return (m_currentArrowRight && !m_previousArrowRight); }
bool ControllerInput::GetDownArrowDown()	const { return (m_currentArrowDown && !m_previousArrowDown); }
bool ControllerInput::GetDownArrowLeft()	const { return (m_currentArrowLeft && !m_previousArrowLeft); }

bool ControllerInput::GetDownNorth()		const { return (m_currentNorth && !m_previousNorth); }
bool ControllerInput::GetDownEast()			const { return (m_currentEast && !m_previousEast); }
bool ControllerInput::GetDownSouth()		const { return (m_currentSouth && !m_previousSouth); }
bool ControllerInput::GetDownWest()			const { return (m_currentWest && !m_previousWest); }

bool ControllerInput::GetDownL()			const { return (m_currentL && !m_previousL); }
bool ControllerInput::GetDownR()			const { return (m_currentR && !m_previousR); }
bool ControllerInput::GetDownZL()			const { return (m_currentZL && !m_previousZL); }
bool ControllerInput::GetDownZR()			const { return (m_currentZR && !m_previousZR); }

bool ControllerInput::GetDownStart()		const { return (m_currentStart && !m_previousStart); }
bool ControllerInput::GetDownSelect()		const { return (m_currentSelect && !m_previousSelect); }

// ゲッター (デジタル:離した瞬間)
bool ControllerInput::GetUpArrowUp()		const { return (!m_currentArrowUp && m_previousArrowUp); }
bool ControllerInput::GetUpArrowRight()		const { return (!m_currentArrowRight && m_previousArrowRight); }
bool ControllerInput::GetUpArrowDown()		const { return (!m_currentArrowDown && m_previousArrowDown); }
bool ControllerInput::GetUpArrowLeft()		const { return (!m_currentArrowLeft && m_previousArrowLeft); }

bool ControllerInput::GetUpNorth()			const { return (!m_currentNorth && m_previousNorth); }
bool ControllerInput::GetUpEast()			const { return (!m_currentEast && m_previousEast); }
bool ControllerInput::GetUpSouth()			const { return (!m_currentSouth && m_previousSouth); }
bool ControllerInput::GetUpWest()			const { return (!m_currentWest && m_previousWest); }

bool ControllerInput::GetUpL()				const { return (!m_currentL && m_previousL); }
bool ControllerInput::GetUpR()				const { return (!m_currentR && m_previousR); }
bool ControllerInput::GetUpZL()				const { return (!m_currentZL && m_previousZL); }
bool ControllerInput::GetUpZR()				const { return (!m_currentZR && m_previousZR); }

bool ControllerInput::GetUpStart()			const { return (!m_currentStart && m_previousStart); }
bool ControllerInput::GetUpSelect()			const { return (!m_currentSelect && m_previousSelect); }

// ゲッター (軸)
int ControllerInput::GetLeftX()				const { return m_leftX; }
int ControllerInput::GetLeftY()				const { return m_leftY; }
int ControllerInput::GetRightX()			const { return m_rightX; }
int ControllerInput::GetRightY()			const { return m_rightY; }

int ControllerInput::GetArrowX() const
{
	return ((m_currentArrowRight == true) ? 1 : 0) + ((m_currentArrowLeft == true) ? -1 : 0);
}

int ControllerInput::GetArrowY() const
{
	return ((m_currentArrowUp == true) ? 1 : 0) + ((m_currentArrowDown == true) ? -1 : 0);
}

// ゲッター (入力以外)
bool ControllerInput::GetIsUse()								const { return m_isUse; }
int ControllerInput::GetGamePadNumber()							const { return m_deviceData.GetGamepadNum(); }
bool ControllerInput::GetIsConnect()							const { return m_isConnected; }
unsigned int ControllerInput::GetControllerType()				const { return m_deviceData.GetControllerType(); }
ControllerDeviceData::InputType ControllerInput::GetInputType() const { return m_deviceData.GetInputType(); };
ControllerDeviceData ControllerInput::GetDeviceData()			const { return m_deviceData; }

// 入力のクリア
void ControllerInput::ClearInput()
{
	m_leftX = 0;
	m_leftY = 0;
	m_rightX = 0;
	m_rightY = 0;

	m_currentArrowUp = false;
	m_currentArrowRight = false;
	m_currentArrowDown = false;
	m_currentArrowLeft = false;

	m_currentNorth = false;
	m_currentEast = false;
	m_currentSouth = false;
	m_currentWest = false;

	m_currentL = false;
	m_currentR = false;
	m_currentZL = false;
	m_currentZR = false;

	m_currentStart = false;
	m_currentSelect = false;

	SetPreviousInput();
}

// コントローラ番号の更新(コントローラ数が変化した場合に実行)
void ControllerInput::UpdateControllerNumber(int new_num)
{
	m_deviceData.SetGamepadNum(new_num);
}

// 1つ前の入力の設定
void ControllerInput::SetPreviousInput()
{
	m_previousArrowUp = m_currentArrowUp;
	m_previousArrowRight = m_currentArrowRight;
	m_previousArrowDown = m_currentArrowDown;
	m_previousArrowLeft = m_currentArrowLeft;

	m_previousNorth = m_currentNorth;
	m_previousEast = m_currentEast;
	m_previousSouth = m_currentSouth;
	m_previousWest = m_currentWest;

	m_previousL = m_currentL;
	m_previousR = m_currentR;
	m_previousZL = m_currentZL;
	m_previousZR = m_currentZR;

	m_previousStart = m_currentStart;
	m_previousSelect = m_currentSelect;
}

// XBOXコントローラとしての入力更新
void ControllerInput::UpdateXboxInput()
{
	// 入力状態の取得
	XINPUT_STATE input_state;
	if (GetJoypadXInputState(m_deviceData.GetGamepadNum(), &input_state) != 0)
	{
		// エラー時(コントローラの接続が切れた場合等)は更新しない
		m_isConnected = false;
		return;
	}

	// 更新
	m_leftX = XboxThumbScale(input_state.ThumbLX);
	m_leftY = XboxThumbScale(input_state.ThumbLY);
	m_rightX = XboxThumbScale(input_state.ThumbRX);
	m_rightY = XboxThumbScale(input_state.ThumbRY);

	JoyStickNormalization(&m_leftX, &m_leftY);
	JoyStickNormalization(&m_rightX, &m_rightY);

	m_currentArrowUp = input_state.Buttons[XINPUT_BUTTON_DPAD_UP];
	m_currentArrowRight = input_state.Buttons[XINPUT_BUTTON_DPAD_RIGHT];
	m_currentArrowDown = input_state.Buttons[XINPUT_BUTTON_DPAD_DOWN];
	m_currentArrowLeft = input_state.Buttons[XINPUT_BUTTON_DPAD_LEFT];

	m_currentNorth = input_state.Buttons[XINPUT_BUTTON_Y];
	m_currentEast = input_state.Buttons[XINPUT_BUTTON_B];
	m_currentSouth = input_state.Buttons[XINPUT_BUTTON_A];
	m_currentWest = input_state.Buttons[XINPUT_BUTTON_X];

	m_currentL = input_state.Buttons[XINPUT_BUTTON_LEFT_SHOULDER];
	m_currentR = input_state.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER];
	m_currentZL = (input_state.LeftTrigger > XBOX_TRIGGER_THRESHOLD) ? true : false;
	m_currentZR = (input_state.RightTrigger > XBOX_TRIGGER_THRESHOLD) ? true : false;

	m_currentStart = input_state.Buttons[XINPUT_BUTTON_START];
	m_currentSelect = input_state.Buttons[XINPUT_BUTTON_BACK];
}

// Directコントローラとしての入力更新
void ControllerInput::UpdateDirectInput()
{
	// 入力状態の取得
	DINPUT_JOYSTATE input_state;
	if (GetJoypadDirectInputState(m_deviceData.GetGamepadNum(), &input_state) != 0)
	{
		// エラー時(コントローラの接続が切れた場合等)は更新しない
		m_isConnected = false;
		return;
	}

	// 更新
	m_leftX = input_state.*(m_keyConfiguration.leftXAxis);
	m_leftY = -(input_state.*(m_keyConfiguration.leftYAxis));
	m_rightX = input_state.*(m_keyConfiguration.rightXAxis);
	m_rightY = -(input_state.*(m_keyConfiguration.rightYAxis));

	JoyStickNormalization(&m_leftX, &m_leftY);
	JoyStickNormalization(&m_rightX, &m_rightY);

	// 十字キー
	// オイラー角の100倍
	m_currentArrowUp = false;
	m_currentArrowRight = false;
	m_currentArrowDown = false;
	m_currentArrowLeft = false;
	switch (input_state.POV[0])
	{
	case 0:		// 上
		m_currentArrowUp = true;
		break;
	case 4500:  // 右上
		m_currentArrowUp = true;
		m_currentArrowRight = true;
		break;
	case 9000:  // 右
		m_currentArrowRight = true;
		break;
	case 13500: // 右下
		m_currentArrowRight = true;
		m_currentArrowDown = true;
		break;
	case 18000: // 下
		m_currentArrowDown = true;
		break;
	case 22500: // 左下
		m_currentArrowDown = true;
		m_currentArrowLeft = true;
		break;
	case 27000: // 左
		m_currentArrowLeft = true;
		break;
	case 31500: // 左上
		m_currentArrowUp = true;
		m_currentArrowLeft = true;
		break;
	default:	// ニュートラル
		break;
	}

	m_currentNorth = input_state.Buttons[m_keyConfiguration.northIdx];
	m_currentEast = input_state.Buttons[m_keyConfiguration.eastIdx];
	m_currentSouth = input_state.Buttons[m_keyConfiguration.southIdx];
	m_currentWest = input_state.Buttons[m_keyConfiguration.westIdx];

	m_currentL = input_state.Buttons[m_keyConfiguration.lIdx];
	m_currentR = input_state.Buttons[m_keyConfiguration.rIdx];
	m_currentZL = input_state.Buttons[m_keyConfiguration.zlIdx];
	m_currentZR = input_state.Buttons[m_keyConfiguration.zrIdx];
	
	m_currentStart = input_state.Buttons[DIRECTINPUT_BUTTON_START];
	m_currentSelect = input_state.Buttons[DIRECTINPUT_BUTTON_SELECT];
}

// XBOXコントローラのジョイスティック値のスケーリング
int ControllerInput::XboxThumbScale(int input_num)
{
	int return_num = input_num / XBOX_THUMB_SCALE_DIVISOR;

	if (return_num > ANALOG_INPUT_MAX)
	{
		return ANALOG_INPUT_MAX;
	}

	if (return_num < -ANALOG_INPUT_MAX)
	{
		return -ANALOG_INPUT_MAX;
	}

	return return_num;
}

// ジョイスティックの正規化
void ControllerInput::JoyStickNormalization(int* p_x, int* p_y)
{
	float x = static_cast<float>(*p_x);
	float y = static_cast<float>(*p_y);
	float mag = sqrtf(x * x + y * y);

	if (mag == 0.0f) { return; }

	if (mag > static_cast<float>(ANALOG_INPUT_MAX))
	{
		x *= static_cast<float>(ANALOG_INPUT_MAX) / mag;
		y *= static_cast<float>(ANALOG_INPUT_MAX) / mag;
	}

	*p_x = static_cast<int>(x);
	*p_y = static_cast<int>(y);
}
