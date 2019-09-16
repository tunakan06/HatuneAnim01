#include "Common.h"

Common::Common() {

	input = new Input();
	chara = new Chara();

}

Common::~Common(){}

void Common::Update() {

	input->Update();
	chara->Update();

}