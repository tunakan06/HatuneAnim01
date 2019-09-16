#ifndef _CAMERA_H
#define _CAMERA_H

#include "DxLib.h"

#include "Input.h"
#include "Chara.h"

class Camera {

public:

	Camera();

	~Camera();

	void Update();

	float AngleH, AngleV;
	VECTOR		Eye;					// �J�������W
	VECTOR		Target;				// �����_���W

	VECTOR		SetEye;
	VECTOR		SetTarget;

	// �J�����֌W�̒�`
	#define CAMERA_ANGLE_SPEED			0.05f		// ���񑬓x
	#define CAMERA_PLAYER_TARGET_HEIGHT		20.0f		// �v���C���[���W����ǂꂾ�������ʒu�𒍎��_�Ƃ��邩
	#define CAMERA_PLAYER_LENGTH			50.0f		// �v���C���[�Ƃ̋���
	#define CAMERA_COLLISION_SIZE			30.0f		// �J�����̓����蔻��T�C�Y

	Input input;
	Chara chara;

};

#endif