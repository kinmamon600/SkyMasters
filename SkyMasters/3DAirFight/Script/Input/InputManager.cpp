// ライブラリ・ヘッダ
#include <vector>
#include <iterator>

#include "InputManager.h"
#include "ControllerDeviceData.h"

// コンストラクタ
InputManager::InputManager()
{
	// コントローラの入力配列の初期化
	for (unsigned short i = 0; i < PLAYER_NUM_MAX; ++i)
	{
		p_controllerInputs[i] = new ControllerInput{};
	}
	
	// 接続されているコントローラ数の取得
	m_connectedControllerNum = GetJoypadNum();

	// コントローラ数に合わせて仮の初期設定
	// DxLib上のコントローラ番号に合わせて1Pから順に設定
	for (unsigned short i = 0; i < m_connectedControllerNum; ++i)
	{
		if (i >= PLAYER_NUM_MAX) { break; }
		p_controllerInputs[i]->SetUp(i + DX_INPUT_PAD1);
	}
}

// デストラクタ
InputManager::~InputManager()
{
	for (unsigned short i = 0; i < PLAYER_NUM_MAX; ++i)
	{
		delete p_controllerInputs[i];
		p_controllerInputs[i] = nullptr;
	}
}

// 入力更新
void InputManager::Update()
{
	// コントローラの増減情報のリセット
	m_wasControllerAdded = false;
	m_wasControllerRemoved = false;

	// モードに合わせて分岐
	switch (m_inputMode)
	{
	case InputMode::Menu:
		UpdateModeMenu();
		break;
	case InputMode::Game:
		UpdateModeGame();
		break;
	default:
		break;
	}
}

// 入力モードの設定
void InputManager::SetInputMode(InputMode mode)
{
	m_inputMode = mode;
}

// 接続されているコントローラ数の取得
unsigned short InputManager::GetControllerNum()
{
	return m_connectedControllerNum;
}

// 想定されるコントローラ数を設定
void InputManager::SetExpectedControllerNum(unsigned short num)
{
	if (num > PLAYER_NUM_MAX)
	{
		num = PLAYER_NUM_MAX;
	}

	m_expectedControllerNum = num;
}

// 想定されるコントローラ数を取得
unsigned short InputManager::GetExpectedControllerNum() const
{
	return m_expectedControllerNum;
}

// コントローラ入力状態の取得
const ControllerInput* InputManager::GetInput(unsigned short player) const
{
	if (player >= m_connectedControllerNum) return nullptr;
	return p_controllerInputs[player];
}

// ボタン入力の取得
bool InputManager::GetButton(unsigned short player, Button button) const
{
	// プレイヤー番号が範囲外のときfalse
	if (player > m_connectedControllerNum || player > PLAYER_NUM_MAX)
	{
		return false;
	}

	switch (button)
	{
	case NORTH:
		return p_controllerInputs[player]->GetNorth();
		break;
	case EAST:
		return p_controllerInputs[player]->GetEast();
		break;
	case SOUTH:
		return p_controllerInputs[player]->GetSouth();
		break;
	case WEST:
		return p_controllerInputs[player]->GetWest();
		break;

	case L:
		return p_controllerInputs[player]->GetL();
		break;
	case R:
		return p_controllerInputs[player]->GetR();
		break;
	case ZL:
		return p_controllerInputs[player]->GetZL();
		break;
	case ZR:
		return p_controllerInputs[player]->GetZR();
		break;

	case START:
		return p_controllerInputs[player]->GetStart();
		break;
	case SELECT:
		return p_controllerInputs[player]->GetSelect();
		break;

	case UP:
		return p_controllerInputs[player]->GetArrowUp();
		break;
	case DOWN:
		return p_controllerInputs[player]->GetArrowDown();
		break;
	case LEFT:
		return p_controllerInputs[player]->GetArrowLeft();
		break;
	case RIGHT:
		return p_controllerInputs[player]->GetArrowRight();
		break;

	default:
		break;
	}

	return false;
}

// ボタン入力の取得 (押したとき)
bool InputManager::GetButtonDown(unsigned short player, Button button) const
{
	// プレイヤー番号が範囲外のときfalse
	if (player > m_connectedControllerNum || player > PLAYER_NUM_MAX)
	{
		return false;
	}

	switch (button)
	{
	case NORTH:
		return p_controllerInputs[player]->GetDownNorth();
		break;
	case EAST:
		return p_controllerInputs[player]->GetDownEast();
		break;
	case SOUTH:
		return p_controllerInputs[player]->GetDownSouth();
		break;
	case WEST:
		return p_controllerInputs[player]->GetDownWest();
		break;

	case L:
		return p_controllerInputs[player]->GetDownL();
		break;
	case R:
		return p_controllerInputs[player]->GetDownR();
		break;
	case ZL:
		return p_controllerInputs[player]->GetDownZL();
		break;
	case ZR:
		return p_controllerInputs[player]->GetDownZR();
		break;

	case START:
		return p_controllerInputs[player]->GetDownStart();
		break;
	case SELECT:
		return p_controllerInputs[player]->GetDownSelect();
		break;

	case UP:
		return p_controllerInputs[player]->GetDownArrowUp();
		break;
	case DOWN:
		return p_controllerInputs[player]->GetDownArrowDown();
		break;
	case LEFT:
		return p_controllerInputs[player]->GetDownArrowLeft();
		break;
	case RIGHT:
		return p_controllerInputs[player]->GetDownArrowRight();
		break;

	default:
		break;
	}

	return false;
}

// ボタン入力の取得 (離したとき)
bool InputManager::GetButtonUp(unsigned short player, Button button) const
{
	// プレイヤー番号が範囲外のときfalse
	if (player > m_connectedControllerNum || player > PLAYER_NUM_MAX)
	{
		return false;
	}

	switch (button)
	{
	case NORTH:
		return p_controllerInputs[player]->GetUpNorth();
		break;
	case EAST:
		return p_controllerInputs[player]->GetUpEast();
		break;
	case SOUTH:
		return p_controllerInputs[player]->GetUpSouth();
		break;
	case WEST:
		return p_controllerInputs[player]->GetUpWest();
		break;

	case L:
		return p_controllerInputs[player]->GetUpL();
		break;
	case R:
		return p_controllerInputs[player]->GetUpR();
		break;
	case ZL:
		return p_controllerInputs[player]->GetUpZL();
		break;
	case ZR:
		return p_controllerInputs[player]->GetUpZR();
		break;

	case START:
		return p_controllerInputs[player]->GetUpStart();
		break;
	case SELECT:
		return p_controllerInputs[player]->GetUpSelect();
		break;

	case UP:
		return p_controllerInputs[player]->GetUpArrowUp();
		break;
	case DOWN:
		return p_controllerInputs[player]->GetUpArrowDown();
		break;
	case LEFT:
		return p_controllerInputs[player]->GetUpArrowLeft();
		break;
	case RIGHT:
		return p_controllerInputs[player]->GetUpArrowRight();
		break;

	default:
		break;
	}

	return false;
}

// アナログ入力の取得
int InputManager::GetAnalog(unsigned short player, Analog analog) const
{
	// プレイヤー番号が範囲外のとき0
	if (player > m_connectedControllerNum || player > PLAYER_NUM_MAX)
	{
		return 0;
	}

	switch (analog)
	{
	case LX:
		return p_controllerInputs[player]->GetLeftX();
		break;
	case LY:
		return p_controllerInputs[player]->GetLeftY();
		break;

	case RX:
		return p_controllerInputs[player]->GetRightX();
		break;
	case RY:
		return p_controllerInputs[player]->GetRightY();
		break;

	case AX:
		return p_controllerInputs[player]->GetArrowX();
		break;
	case AY:
		return p_controllerInputs[player]->GetArrowY();
		break;

	default:
		break;
	}

	return 0;
}

// コントローラ種類の取得
unsigned int InputManager::GetController(unsigned short player) const
{
	// プレイヤー番号が範囲外のとき0
	if (player > m_connectedControllerNum || player > PLAYER_NUM_MAX)
	{
		return 0;
	}

	return p_controllerInputs[player]->GetControllerType();
}

// コントローラが追加接続されたかを返す
bool InputManager::WasControllerAdded() const
{
	return m_wasControllerAdded;
}

// コントローラが切断されたかを返す
bool InputManager::WasControllerRemoved() const
{
	return m_wasControllerRemoved;
}

// 入力モード:メニュー時の更新処理
void InputManager::UpdateModeMenu()
{
	// 接続されているコントローラ数の取得・更新
	unsigned short current_ctrl_num = GetJoypadNum();

	if (current_ctrl_num > m_connectedControllerNum)
	{
		// コントローラ数の増加
		IncrementController(current_ctrl_num);
	}

	if (current_ctrl_num < m_connectedControllerNum)
	{
		// コントローラ数の減少
		// 接続されているコントローラについて再設定
		for (unsigned short i = 0; i < current_ctrl_num; ++i)
		{
			if (i >= PLAYER_NUM_MAX) { break; }
			p_controllerInputs[i]->SetUp(i + DX_INPUT_PAD1);
		}
	}

	// コントローラ数更新
	m_connectedControllerNum = current_ctrl_num;

	// 入力状態の更新
	p_controllerInputs[0]->Update();
}

// 入力モード:ゲーム時の更新処理
void InputManager::UpdateModeGame()
{
	// 接続されているコントローラ数の取得・更新
	unsigned short current_ctrl_num = GetJoypadNum();

	if (current_ctrl_num > m_connectedControllerNum)
	{
		// コントローラ数の増加
		IncrementController(current_ctrl_num);
	}

	if (current_ctrl_num < m_connectedControllerNum)
	{
		// コントローラ数の減少
		DecreaseController(current_ctrl_num);
	}

	// コントローラ数更新
	m_connectedControllerNum = current_ctrl_num;

	// 入力状態の更新
	// コントローラ数が減っていた場合更新しない
	if (m_wasControllerRemoved) 
	{
		for (unsigned short i = 0; i < PLAYER_NUM_MAX; ++i)
		{
			p_controllerInputs[i]->ClearInput();
		}
		return;
	}
	for (unsigned short i = 0; i < m_connectedControllerNum; ++i)
	{
		if (i >= PLAYER_NUM_MAX) { break; }
		p_controllerInputs[i]->Update();
	}
}

// コントローラ数の増加
void InputManager::IncrementController(int current_num)
{
	// 増加した事を保持
	m_wasControllerAdded = true;

	// 増加前のデバイス情報を取得・保持
	// 同時に元々接続されていたXInputコントローラの数をカウント
	ControllerDeviceData previous_datas[PLAYER_NUM_MAX];
	unsigned short x_gamepad_cnt = 0;
	for (unsigned short i = 0; i < PLAYER_NUM_MAX; ++i)
	{
		previous_datas[i] = p_controllerInputs[i]->GetDeviceData();
		p_controllerInputs[i]->SetNonUse();
		if (p_controllerInputs[i]->GetInputType() == ControllerDeviceData::InputType::XBOX)
		{
			++x_gamepad_cnt;
		}
	}

	//printfDx("元のDirectコンは%d個\n", m_connectedControllerNum - x_gamepad_cnt);
	//printfDx("元のXBOXコンは%d個\n", x_gamepad_cnt);

	// 増加後、すなわち現在のデバイス情報を取得
	std::vector<ControllerDeviceData> current_datas;
	for (unsigned short i = 0; i < current_num; ++i)
	{
		current_datas.push_back(ControllerDeviceData{});
		current_datas[i].SetUp(i + DX_INPUT_PAD1);
	}

	// 既存のコントローラの情報からコントローラ番号を検索・再設定
	// この時、XInputのコントローラ番号を保持
	std::vector<int> x_gamepad_num;
	for (unsigned short i = 0; i < current_num; ++i)
	{
		if (current_datas[i].GetInputType() == ControllerDeviceData::InputType::XBOX) { x_gamepad_num.push_back(current_datas[i].GetGamepadNum()); }
		if (current_datas[i].GetInputType() != ControllerDeviceData::InputType::DIRECT) { continue; }

		for (unsigned short j = 0; j < m_connectedControllerNum; ++j)
		{
			if (j >= PLAYER_NUM_MAX) { break; }
			if (p_controllerInputs[j]->GetInputType() != ControllerDeviceData::InputType::DIRECT) { continue; }

			// デバイス情報が一致するかを判別
			if (IsDeviceDataEqual(&previous_datas[j], &current_datas[i]))
			{
				// 完全一致していたらコントローラ番号を更新
				p_controllerInputs[j]->SetGamepadNum(current_datas[i].GetGamepadNum());
				//printfDx("[%dP]Directコントローラ更新！\n", j + 1);
			}
		}
	}

	// XInputのコントローラ番号の再設定
	std::vector<int> use_x_gamepad_num;
	if (x_gamepad_cnt > 0)
	{
		int j = 0;
		for (unsigned short i = 0; i < PLAYER_NUM_MAX; ++i)
		{
			if (p_controllerInputs[i]->GetIsUse()) { continue; }
			if (p_controllerInputs[i]->GetInputType() != ControllerDeviceData::InputType::XBOX) { continue; }
			p_controllerInputs[i]->SetGamepadNum(x_gamepad_num[j]);
			use_x_gamepad_num.push_back(x_gamepad_num[j]);
			//printfDx("[%dP]XBOXコントローラ更新！\n", i + 1);
			++j;
			if (j >= x_gamepad_cnt) { break; }
		}
	}

	// まだプレイヤーの枠が空いていた場合、新規登録
	for (unsigned short i = 0; i < (current_num - m_connectedControllerNum); ++i)
	{
		// 空いているプレイヤー枠を検索
		unsigned short vacant_player = 0;
		for (vacant_player = 0; vacant_player <= PLAYER_NUM_MAX; ++vacant_player)
		{
			// 空き無し
			if (vacant_player >= PLAYER_NUM_MAX) { return; }

			if (!p_controllerInputs[vacant_player]->GetIsUse())
			{
				//printfDx("%dPが空いている！\n", vacant_player + 1);
				break;
			}
		}

		// 使用していないコントローラを検索
		unsigned short vacant_controller = 0;
		bool vacant = true;
		for (vacant_controller = 0; vacant_controller < current_num; ++vacant_controller)
		{
			vacant = true;
			for (unsigned short k = 0; k < PLAYER_NUM_MAX; ++k)
			{
				vacant = vacant && (!(p_controllerInputs[k]->GetIsUse() && (vacant_controller + DX_INPUT_PAD1 == p_controllerInputs[k]->GetDeviceData().GetGamepadNum())));
			}

			if (!vacant) { continue; }

			for (auto tmp : use_x_gamepad_num)
			{
				if (vacant_controller + DX_INPUT_PAD1 == tmp)
				{
					vacant = false;
					break;
				}
			}

			if (vacant) { break; }
		}

		if (vacant && vacant_player < PLAYER_NUM_MAX)
		{
			//printfDx("新規[%dP:%d]\n", vacant_player + 1, vacant_controller + DX_INPUT_PAD1);
			p_controllerInputs[vacant_player]->SetUp(vacant_controller + DX_INPUT_PAD1);
		}
	}

	//printfDx("\n");
}

// コントローラ数の減少
void InputManager::DecreaseController(int current_num)
{
	// 増加した事を保持
	m_wasControllerRemoved = true;
}

// ２つのコントローラのデバイス情報の一致不一致を判別する
bool InputManager::IsDeviceDataEqual(ControllerDeviceData* data1, ControllerDeviceData* data2)
{
	bool equal = true;
	equal = (equal && (data1->GetPID() == data2->GetPID()));
	equal = (equal && (data1->GetVID() == data2->GetVID()));

	// 同じ製品でなければ不一致
	if (equal == false) { return false; }

	// 同じ製品であれば判別継続
	GUID guid1 = data1->GetGuidInstance();
	GUID guid2 = data2->GetGuidInstance();

	equal = (equal && (guid1.Data1 == guid2.Data1));
	equal = (equal && (guid1.Data2 == guid2.Data2));
	equal = (equal && (guid1.Data3 == guid2.Data3));

	for (unsigned short i = 0; i < std::size(guid1.Data4); ++i)
	{
		equal = (equal && (guid1.Data4[i] == guid2.Data4[i]));
	}
	
	// 完全一致でtrue
	return equal;
}
