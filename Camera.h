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
	VECTOR		Eye;					// カメラ座標
	VECTOR		Target;				// 注視点座標

	VECTOR		SetEye;
	VECTOR		SetTarget;

	// カメラ関係の定義
	#define CAMERA_ANGLE_SPEED			0.05f		// 旋回速度
	#define CAMERA_PLAYER_TARGET_HEIGHT		20.0f		// プレイヤー座標からどれだけ高い位置を注視点とするか
	#define CAMERA_PLAYER_LENGTH			50.0f		// プレイヤーとの距離
	#define CAMERA_COLLISION_SIZE			30.0f		// カメラの当たり判定サイズ

	Input input;
	Chara chara;

};

#endif