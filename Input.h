#ifndef _INPUT_H
#define _INPUT_H

#include "DxLib.h"

class Input {

public:

	Input();

	~Input();

	void Update();

	int nowInput();

	// ���͏��\����
	struct PADINPUT
	{
		int		NowInput;				// ���݂̓���
		int		EdgeInput;				// ���݂̃t���[���ŉ����ꂽ�{�^���̂݃r�b�g�������Ă�����͒l
	};

	PADINPUT inp;		// ���͏��̎��̐錾
};

#endif