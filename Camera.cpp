#include "Camera.h"

Camera::Camera(){

	// カメラの初期水平角度は１８０度
	AngleH = DX_PI_F;

	// 垂直角度は０度
	AngleV = 0.0f;

	input = Input();
	chara = Chara();
}

Camera::~Camera(){}

void Camera::Update() {

	// パッドの３ボタンか、シフトキーが押されている場合のみ角度変更操作を行う
	if (CheckHitKey(KEY_INPUT_LSHIFT) || (input.nowInput() & PAD_INPUT_C))
	{
		// 「←」ボタンが押されていたら水平角度をマイナスする
		if (input.nowInput() & PAD_INPUT_LEFT)
		{
			AngleH -= CAMERA_ANGLE_SPEED;

			// −１８０度以下になったら角度値が大きくなりすぎないように３６０度を足す
			if (AngleH < -DX_PI_F)
			{
				AngleH += DX_TWO_PI_F;
			}
		}

		// 「→」ボタンが押されていたら水平角度をプラスする
		if (input.nowInput() & PAD_INPUT_RIGHT)
		{
			AngleH += CAMERA_ANGLE_SPEED;

			// １８０度以上になったら角度値が大きくなりすぎないように３６０度を引く
			if (AngleH > DX_PI_F)
			{
				AngleH -= DX_TWO_PI_F;
			}
		}

		// 「↑」ボタンが押されていたら垂直角度をマイナスする
		if (input.nowInput() & PAD_INPUT_UP)
		{
			AngleV -= CAMERA_ANGLE_SPEED;

			// ある一定角度以下にはならないようにする
			if (AngleV < -DX_PI_F / 2.0f + 0.6f)
			{
				AngleV = -DX_PI_F / 2.0f + 0.6f;
			}
		}

		// 「↓」ボタンが押されていたら垂直角度をプラスする
		if (input.nowInput() & PAD_INPUT_DOWN)
		{
			AngleV += CAMERA_ANGLE_SPEED;

			// ある一定角度以上にはならないようにする
			if (AngleV > DX_PI_F / 2.0f - 0.6f)
			{
				AngleV = DX_PI_F / 2.0f - 0.6f;
			}
		}
	}

	// カメラの注視点はプレイヤー座標から規定値分高い座標
	Target = VAdd(chara.getPos(), VGet(0.0f, CAMERA_PLAYER_TARGET_HEIGHT, 0.0f));

	// カメラの座標を決定する
	{
		MATRIX RotZ, RotY;
		float Camera_Player_Length;
		MV1_COLL_RESULT_POLY_DIM HRes;
		int HitNum;

		// 水平方向の回転はＹ軸回転
		RotY = MGetRotY(AngleH);

		// 垂直方向の回転はＺ軸回転 )
		RotZ = MGetRotZ(AngleV);

		// カメラからプレイヤーまでの初期距離をセット
		Camera_Player_Length = CAMERA_PLAYER_LENGTH;

		// カメラの座標を算出
		// Ｘ軸にカメラとプレイヤーとの距離分だけ伸びたベクトルを
		// 垂直方向回転( Ｚ軸回転 )させたあと水平方向回転( Ｙ軸回転 )して更に
		// 注視点の座標を足したものがカメラの座標
		Eye = VAdd(VTransform(VTransform(VGet(-Camera_Player_Length, 0.0f, 0.0f), RotZ), RotY), Target);

		// 注視点からカメラの座標までの間にステージのポリゴンがあるか調べる
		HRes = MV1CollCheck_Capsule(chara.getModelHandle(), -1, Target, Eye, CAMERA_COLLISION_SIZE);
		HitNum = HRes.HitNum;
		MV1CollResultPolyDimTerminate(HRes);
		if (HitNum != 0)
		{
			float NotHitLength;
			float HitLength;
			float TestLength;
			VECTOR TestPosition;

			// あったら無い位置までプレイヤーに近づく

			// ポリゴンに当たらない距離をセット
			NotHitLength = 0.0f;

			// ポリゴンに当たる距離をセット
			HitLength = Camera_Player_Length;
			do
			{
				// 当たるかどうかテストする距離をセット( 当たらない距離と当たる距離の中間 )
				TestLength = NotHitLength + (HitLength - NotHitLength) / 2.0f;

				// テスト用のカメラ座標を算出
				TestPosition = VAdd(VTransform(VTransform(VGet(-TestLength, 0.0f, 0.0f), RotZ), RotY), Target);

				// 新しい座標で壁に当たるかテスト
				HRes = MV1CollCheck_Capsule(chara.getModelHandle(), -1, Target, TestPosition, CAMERA_COLLISION_SIZE);
				HitNum = HRes.HitNum;
				MV1CollResultPolyDimTerminate(HRes);
				if (HitNum != 0)
				{
					// 当たったら当たる距離を TestLength に変更する
					HitLength = TestLength;
				}
				else
				{
					// 当たらなかったら当たらない距離を TestLength に変更する
					NotHitLength = TestLength;
				}

				// HitLength と NoHitLength が十分に近づいていなかったらループ
			} while (HitLength - NotHitLength > 0.1f);
			
			// カメラの座標をセット
			Eye = TestPosition;
		}
	}
	
	// カメラの情報をライブラリのカメラに反映させる
	SetEye = VAdd(SetEye, VScale(VSub(Eye, SetEye), 0.2f));
	SetTarget = VAdd(SetTarget, VScale(VSub(Target, SetTarget), 0.2f));
	//SetCameraPositionAndTarget_UpVecY(SetEye, SetTarget);
	
}