#ifndef _CHARA_H
#define _CHARA_H

#include "DxLib.h"
#include "Input.h"

// �J�����֌W�̒�`
#define CAMERA_ANGLE_SPEED			0.05f		// ���񑬓x
#define CAMERA_PLAYER_TARGET_HEIGHT		20.0f		// �v���C���[���W����ǂꂾ�������ʒu�𒍎��_�Ƃ��邩
#define CAMERA_PLAYER_LENGTH			50.0f		// �v���C���[�Ƃ̋���
#define CAMERA_COLLISION_SIZE			30.0f		// �J�����̓����蔻��T�C�Y

class Chara {

public:

	Chara();

	~Chara();

	void Update();

	VECTOR getPos();
	int getModelHandle();

	int ModelHandle, AttachIndex, MapHandle;
	float TotalTime, PlayTime;
	int key;
	VECTOR pos = VGet(0.0f, 0.0f, 0.0f);
	enum Direction { DOWN, LEFT, UP, RIGHT }direction = DOWN;

	// �L�������s�t���O
	bool running = false;

	float AngleH, AngleV;
	VECTOR		Eye;					// �J�������W
	VECTOR		Target;				// �����_���W

	VECTOR		SetEye;
	VECTOR		SetTarget;

	Input* input;

};

#endif