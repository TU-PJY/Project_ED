#pragma once
#include "GameObject.h"

class Cursor : public GameObject {
private:
	TimerUtil VisibleTimer{};
	GLfloat Opacity{};
	glm::vec2 PrevPosition{};
	bool VisibleState{};

public:
	Cursor();
	void UpdateFunc(float FrameTime);
	void RenderFunc();
};