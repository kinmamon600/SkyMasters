// ライブラリ・ヘッダ
#include "Input.h"
#include "../Input/InputManager.h"
#include "../Game/Game.h"
#include "../Actor/Actor.h"

// 取得する入力のプレイヤー番号の設定
void Input::SetPlayerNum(PlayerNum player_num)
{
	m_playerNum = player_num;
}

// ボタン入力の取得
bool Input::GetButton(Button button) const
{
	return mOwner->GetGame()->GetInputManager()->GetButton(static_cast<int>(m_playerNum), static_cast<InputManager::Button>(button));
}

// ボタン入力の取得 (押したとき)
bool Input::GetButtonDown(Button button) const
{
	return mOwner->GetGame()->GetInputManager()->GetButtonDown(static_cast<int>(m_playerNum), static_cast<InputManager::Button>(button));
}

// ボタン入力の取得 (離したとき)
bool Input::GetButtonUp(Button button) const
{
	return mOwner->GetGame()->GetInputManager()->GetButtonUp(static_cast<int>(m_playerNum), static_cast<InputManager::Button>(button));
}

// アナログ入力の取得
int Input::GetAnalog(Analog analog) const
{
	return mOwner->GetGame()->GetInputManager()->GetAnalog(static_cast<int>(m_playerNum), static_cast<InputManager::Analog>(analog));
}