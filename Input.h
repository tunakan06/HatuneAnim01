#ifndef _INPUT_H
#define _INPUT_H

#include "DxLib.h"

class Input {

public:

	Input();

	~Input();

	void Update();

	int nowInput();

	// 入力情報構造体
	struct PADINPUT
	{
		int		NowInput;				// 現在の入力
		int		EdgeInput;				// 現在のフレームで押されたボタンのみビットが立っている入力値
	};

	PADINPUT inp;		// 入力情報の実体宣言
};

#endif