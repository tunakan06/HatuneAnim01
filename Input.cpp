#include "Input.h"

Input::Input(){}

Input::~Input(){}

void Input::Update() {

	int Old;

	// ひとつ前のフレームの入力を変数にとっておく
	Old = inp.NowInput;

	// 現在の入力状態を取得
	inp.NowInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// 今のフレームで新たに押されたボタンのビットだけ立っている値を EdgeInput に代入する
	inp.EdgeInput = inp.NowInput & ~Old;

}

int Input::nowInput() {

	return inp.NowInput;

}