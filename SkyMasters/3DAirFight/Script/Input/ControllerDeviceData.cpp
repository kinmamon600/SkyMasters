// ライブラリ・ヘッダ
#include "ControllerDeviceData.h"

// データ設定
void ControllerDeviceData::SetUp(int gamepad_num)
{
	// デバイス情報:コントローラ番号の設定
	m_gamepadNum = gamepad_num;

	// コントローラの種類設定
	m_controllerType = GetJoypadType(m_gamepadNum);

	// 入力タイプ設定
	DINPUT_JOYSTATE tmp;
	if (CheckJoypadXInput(m_gamepadNum) == TRUE)
	{
		// XBOX
		m_inputType = InputType::XBOX;
	}
	else if (GetJoypadDirectInputState(m_gamepadNum, &tmp) == 0)
	{
		// Direct
		m_inputType = InputType::DIRECT;
	}
	else
	{
		// どちらでもない
		m_inputType = InputType::None;
		return;
	}

	// デバイス情報:IDとGUIDの設定
	if (m_inputType == InputType::DIRECT)
	{
		GUID instance, product;
		if (GetJoypadGUID(m_gamepadNum - DX_INPUT_PAD1, &instance, &product) == 0)
		{
			m_vid = static_cast<unsigned short>(product.Data1 & 0xFFFF);			// 下位16bitを抽出
			m_pid = static_cast<unsigned short>((product.Data1 >> 16) & 0xFFFF);	// 上位16bitを抽出
			m_guidInstance = instance;
		}
	}
}

// コントローラ番号の設定
void ControllerDeviceData::SetGamepadNum(int new_num)
{
	m_gamepadNum = new_num;
}

// ゲッター
int ControllerDeviceData::GetGamepadNum() const { return m_gamepadNum; }
unsigned int ControllerDeviceData::GetControllerType() const { return m_controllerType; }
ControllerDeviceData::InputType ControllerDeviceData::GetInputType() const { return m_inputType; }
unsigned short ControllerDeviceData::GetVID() const { return m_vid; }
unsigned short ControllerDeviceData::GetPID() const { return m_pid; }
GUID ControllerDeviceData::GetGuidInstance() const { return m_guidInstance; }
