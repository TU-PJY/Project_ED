#pragma once
#include "GameObject.h"

class Cursor : public GameObject {
private:
	TimerUtil VisibleTimer{};
	GLfloat Opacity{};

public:
	Cursor();
	void UpdateFunc(float FrameTime);
	void RenderFunc();
};