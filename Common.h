#ifndef _COMMON_H
#define _COMMON_H

#include "DxLib.h"

#include "Input.h"
#include "Chara.h"
#include "Camera.h"

class Common {

public:

	Common();

	~Common();

	void Update();

	Input* input;
	Chara* chara;
	Camera* camera;

};

#endif
