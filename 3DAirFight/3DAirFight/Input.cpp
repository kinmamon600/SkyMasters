// ライブラリ・ヘッダ
#include "Input.h"

void GameInput::SetGamepad(int pad)
{
	gamepadNum = pad;

	// デッドゾーンを設定
	SetJoypadDeadZone(gamepadNum, JOYPAD_DEADZONE);
}

void GameInput::Update()
{
	// 方角ボタン
	north = (GetJoypadInputState(gamepadNum) & PAD_INPUT_4) ? true : false;
	east  = (GetJoypadInputState(gamepadNum) & PAD_INPUT_2) ? true : false;
	south = (GetJoypadInputState(gamepadNum) & PAD_INPUT_1) ? true : false;
	west  = (GetJoypadInputState(gamepadNum) & PAD_INPUT_3) ? true : false;

	// L, R
	l = (GetJoypadInputState(gamepadNum) & PAD_INPUT_5) ? true : false;
	r = (GetJoypadInputState(gamepadNum) & PAD_INPUT_6) ? true : false;

	// start
	start = (GetJoypadInputState(gamepadNum) & PAD_INPUT_12) ? true : false;

	// ジョイスティック
	GetJoypadAnalogInput(&x, &y, gamepadNum);
	y = -y;

	//printfDx("北:%d　東:%d　南:%d　西:%d　", north, east, south, west);
	//printfDx("L:%d　R:%d　Start:%d　", l, r, start);
	//printfDx("X:%d　Y:%d\n", x, y);
}

bool GameInput::GetNorth() const { return north; }
bool GameInput::GetEast() const { return east; }
bool GameInput::GetSouth() const { return south; }
bool GameInput::GetWest() const { return west; }
bool GameInput::GetL() const { return l; }
bool GameInput::GetR() const { return r; }
//bool GameInput::GetStart() const { return start; }
int GameInput::GetX() const { return x; }
int GameInput::GetY() const { return y; }

short GameInput::GetDigitalX() const
{
	if (x > 0)
	{
		return 1;
	}
	else if (x < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

short GameInput::GetDigitalY() const
{
	if (y > 0)
	{
		return 1;
	}
	else if (y < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
