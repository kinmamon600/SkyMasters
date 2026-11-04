// ライブラリ・ヘッダ
#include "Screen/Screen.h"
#include "ControllerUI.h"
#include "ControllerInput.h"
#include "ControllerDeviceData.h"

// デストラクタ
ControllerUI::~ControllerUI()
{
	m_controllerInput = nullptr;
}

// 入力状態の描画
void ControllerUI::Disp()
{
	// 枠の描画
	DrawBox(m_ox + 20, m_oy + 20, Screen::Width / 2 - 20, Screen::Height / 2 - 20, m_colorOn, FALSE);

	unsigned int center_x = m_ox + Screen::Width / 4;
	unsigned int center_y = m_ox + Screen::Height / 4;

	// コントローラ種類に合わせて描画変更
	switch (m_controllerInput->GetControllerType())
	{
	case DX_PADTYPE_XBOX_360:
	case DX_PADTYPE_XBOX_ONE:
		break;

	case DX_PADTYPE_DUAL_SHOCK_3:
	case DX_PADTYPE_DUAL_SHOCK_4:
	case DX_PADTYPE_DUAL_SENSE:
		break;

	case DX_PADTYPE_SWITCH_JOY_CON_L:
		break;

	case DX_PADTYPE_SWITCH_JOY_CON_R:
		break;

	case DX_PADTYPE_SWITCH_PRO_CTRL:
	case DX_PADTYPE_SWITCH_HORI_PAD:
		break;

	case DX_PADTYPE_OTHER:
		break;

	default:
		break;
	}
}

// ボタンの色を返す
unsigned int ControllerUI::ButtonColor(bool button)
{
	if (button)
	{
		return m_colorOn;
	}
	return m_colorOff;
}

// Lスティックの描画
void ControllerUI::DispStickL(unsigned int x, unsigned int y)
{
	int jx = m_controllerInput->GetLeftX();
	int jy = m_controllerInput->GetLeftY();
	float j_mag = (float)m_areaRadius / (float)ANALOG_INPUT_MAX;
	DrawCircle(x, y, m_areaRadius, m_colorOff, FALSE);
	DrawCircle(x + jx * j_mag, y - jy * j_mag, m_buttonRadius, m_colorOn, TRUE);
}

// Rスティックの描画
void ControllerUI::DispStickR(unsigned int x, unsigned int y)
{
	int jx = m_controllerInput->GetRightX();
	int jy = m_controllerInput->GetRightY();
	float j_mag = (float)m_areaRadius / (float)ANALOG_INPUT_MAX;
	DrawCircle(x, y, m_areaRadius, m_colorOff, FALSE);
	DrawCircle(x + jx * j_mag, y - jy * j_mag, m_buttonRadius, m_colorOn, TRUE);
}

// 4ボタンの描画
void ControllerUI::Disp4Button(unsigned int x, unsigned int y)
{
	int offset = m_areaRadius - m_buttonRadius;
	DrawCircle(x, y - offset, m_buttonRadius, ButtonColor(m_controllerInput->GetNorth()), TRUE);
	DrawCircle(x, y + offset, m_buttonRadius, ButtonColor(m_controllerInput->GetSouth()), TRUE);
	DrawCircle(x - offset, y, m_buttonRadius, ButtonColor(m_controllerInput->GetWest()), TRUE);
	DrawCircle(x + offset, y, m_buttonRadius, ButtonColor(m_controllerInput->GetEast()), TRUE);
}

// 十字キーの描画
void ControllerUI::DispArrow(unsigned int x, unsigned int y)
{
	int offset = m_areaRadius - m_buttonRadius;
	DrawBox(x - m_buttonRadius, y - offset - m_buttonRadius, x + m_buttonRadius, y - offset + m_buttonRadius, ButtonColor(m_controllerInput->GetArrowUp()), TRUE);
	DrawBox(x - m_buttonRadius, y + offset - m_buttonRadius, x + m_buttonRadius, y + offset + m_buttonRadius, ButtonColor(m_controllerInput->GetArrowDown()), TRUE);
	DrawBox(x - offset - m_buttonRadius, y - m_buttonRadius, x - offset + m_buttonRadius, y + m_buttonRadius, ButtonColor(m_controllerInput->GetArrowLeft()), TRUE);
	DrawBox(x + offset - m_buttonRadius, y - m_buttonRadius, x + offset + m_buttonRadius, y + m_buttonRadius, ButtonColor(m_controllerInput->GetArrowRight()), TRUE);
}

// 個別の円形ボタンを描画
void ControllerUI::DispCircleButton(unsigned int x, unsigned int y, bool button)
{
	DrawCircle(x, y, m_buttonRadius, ButtonColor(button), TRUE);
}

// 個別の四角ボタンを描画
void ControllerUI::DispBoxButton(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, bool button)
{
	DrawBox(x1 - m_buttonRadius, y1 - m_buttonRadius, x2 + m_buttonRadius, y2 + m_buttonRadius, ButtonColor(button), TRUE);
}
