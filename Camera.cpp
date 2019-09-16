#include "Camera.h"

Camera::Camera(){

	// �J�����̏��������p�x�͂P�W�O�x
	AngleH = DX_PI_F;

	// �����p�x�͂O�x
	AngleV = 0.0f;

	input = Input();
	chara = Chara();
}

Camera::~Camera(){}

void Camera::Update() {

	// �p�b�h�̂R�{�^�����A�V�t�g�L�[��������Ă���ꍇ�̂݊p�x�ύX������s��
	if (CheckHitKey(KEY_INPUT_LSHIFT) || (input.nowInput() & PAD_INPUT_C))
	{
		// �u���v�{�^����������Ă����琅���p�x���}�C�i�X����
		if (input.nowInput() & PAD_INPUT_LEFT)
		{
			AngleH -= CAMERA_ANGLE_SPEED;

			// �|�P�W�O�x�ȉ��ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x�𑫂�
			if (AngleH < -DX_PI_F)
			{
				AngleH += DX_TWO_PI_F;
			}
		}

		// �u���v�{�^����������Ă����琅���p�x���v���X����
		if (input.nowInput() & PAD_INPUT_RIGHT)
		{
			AngleH += CAMERA_ANGLE_SPEED;

			// �P�W�O�x�ȏ�ɂȂ�����p�x�l���傫���Ȃ肷���Ȃ��悤�ɂR�U�O�x������
			if (AngleH > DX_PI_F)
			{
				AngleH -= DX_TWO_PI_F;
			}
		}

		// �u���v�{�^����������Ă����琂���p�x���}�C�i�X����
		if (input.nowInput() & PAD_INPUT_UP)
		{
			AngleV -= CAMERA_ANGLE_SPEED;

			// ������p�x�ȉ��ɂ͂Ȃ�Ȃ��悤�ɂ���
			if (AngleV < -DX_PI_F / 2.0f + 0.6f)
			{
				AngleV = -DX_PI_F / 2.0f + 0.6f;
			}
		}

		// �u���v�{�^����������Ă����琂���p�x���v���X����
		if (input.nowInput() & PAD_INPUT_DOWN)
		{
			AngleV += CAMERA_ANGLE_SPEED;

			// ������p�x�ȏ�ɂ͂Ȃ�Ȃ��悤�ɂ���
			if (AngleV > DX_PI_F / 2.0f - 0.6f)
			{
				AngleV = DX_PI_F / 2.0f - 0.6f;
			}
		}
	}

	// �J�����̒����_�̓v���C���[���W����K��l���������W
	Target = VAdd(chara.getPos(), VGet(0.0f, CAMERA_PLAYER_TARGET_HEIGHT, 0.0f));

	// �J�����̍��W�����肷��
	{
		MATRIX RotZ, RotY;
		float Camera_Player_Length;
		MV1_COLL_RESULT_POLY_DIM HRes;
		int HitNum;

		// ���������̉�]�͂x����]
		RotY = MGetRotY(AngleH);

		// ���������̉�]�͂y����] )
		RotZ = MGetRotZ(AngleV);

		// �J��������v���C���[�܂ł̏����������Z�b�g
		Camera_Player_Length = CAMERA_PLAYER_LENGTH;

		// �J�����̍��W���Z�o
		// �w���ɃJ�����ƃv���C���[�Ƃ̋����������L�т��x�N�g����
		// ����������]( �y����] )���������Ɛ���������]( �x����] )���čX��
		// �����_�̍��W�𑫂������̂��J�����̍��W
		Eye = VAdd(VTransform(VTransform(VGet(-Camera_Player_Length, 0.0f, 0.0f), RotZ), RotY), Target);

		// �����_����J�����̍��W�܂ł̊ԂɃX�e�[�W�̃|���S�������邩���ׂ�
		HRes = MV1CollCheck_Capsule(chara.getModelHandle(), -1, Target, Eye, CAMERA_COLLISION_SIZE);
		HitNum = HRes.HitNum;
		MV1CollResultPolyDimTerminate(HRes);
		if (HitNum != 0)
		{
			float NotHitLength;
			float HitLength;
			float TestLength;
			VECTOR TestPosition;

			// �������疳���ʒu�܂Ńv���C���[�ɋ߂Â�

			// �|���S���ɓ�����Ȃ��������Z�b�g
			NotHitLength = 0.0f;

			// �|���S���ɓ����鋗�����Z�b�g
			HitLength = Camera_Player_Length;
			do
			{
				// �����邩�ǂ����e�X�g���鋗�����Z�b�g( ������Ȃ������Ɠ����鋗���̒��� )
				TestLength = NotHitLength + (HitLength - NotHitLength) / 2.0f;

				// �e�X�g�p�̃J�������W���Z�o
				TestPosition = VAdd(VTransform(VTransform(VGet(-TestLength, 0.0f, 0.0f), RotZ), RotY), Target);

				// �V�������W�ŕǂɓ����邩�e�X�g
				HRes = MV1CollCheck_Capsule(chara.getModelHandle(), -1, Target, TestPosition, CAMERA_COLLISION_SIZE);
				HitNum = HRes.HitNum;
				MV1CollResultPolyDimTerminate(HRes);
				if (HitNum != 0)
				{
					// ���������瓖���鋗���� TestLength �ɕύX����
					HitLength = TestLength;
				}
				else
				{
					// ������Ȃ������瓖����Ȃ������� TestLength �ɕύX����
					NotHitLength = TestLength;
				}

				// HitLength �� NoHitLength ���\���ɋ߂Â��Ă��Ȃ������烋�[�v
			} while (HitLength - NotHitLength > 0.1f);
			
			// �J�����̍��W���Z�b�g
			Eye = TestPosition;
		}
	}
	
	// �J�����̏������C�u�����̃J�����ɔ��f������
	SetEye = VAdd(SetEye, VScale(VSub(Eye, SetEye), 0.2f));
	SetTarget = VAdd(SetTarget, VScale(VSub(Target, SetTarget), 0.2f));
	//SetCameraPositionAndTarget_UpVecY(SetEye, SetTarget);
	
}