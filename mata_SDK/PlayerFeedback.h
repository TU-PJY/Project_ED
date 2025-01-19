#pragma once
#include "GameObject.h"

class PlayerFeedback : public GameObject {
private:
	GLfloat Opacity{ 1.0 };

public:
	PlayerFeedback();
	void UpdateFunc(float FrameTIme);
	void RenderFunc();
};