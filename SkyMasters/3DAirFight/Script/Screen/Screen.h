#ifndef _SCREEN_H
#define _SCREEN_H

/// <summary>
/// 画面設定
/// </summary>
class Screen
{
public:
	static const int Width = 1920 / 2;	// 画面幅
	static const int Height = 1080 / 2;	// 画面高さ

	// フレームレート
	static const int FPS = 60;

	// 1フレームの時間(ミリ秒)
	static constexpr float OneFrameTime_ms = 1000.0f / (float)FPS;

	// 1フレームの時間(秒)
	static constexpr float OneFrameTime_sec = 1.0f / (float)FPS;
};
#endif