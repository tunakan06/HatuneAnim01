#include "Input.h"

Input::Input(){}

Input::~Input(){}

void Input::Update() {

	int Old;

	// �ЂƂO�̃t���[���̓��͂�ϐ��ɂƂ��Ă���
	Old = inp.NowInput;

	// ���݂̓��͏�Ԃ��擾
	inp.NowInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ���̃t���[���ŐV���ɉ����ꂽ�{�^���̃r�b�g���������Ă���l�� EdgeInput �ɑ������
	inp.EdgeInput = inp.NowInput & ~Old;

}

int Input::nowInput() {

	return inp.NowInput;

}