#pragma once
#include "GameObject.h"

enum shapeenum {
	Triangle,
	Square,
	Pentagon
};

class PlayerShape : public GameObject {
private:
	int CurrentShape{}; // 0: triangle, 1: sauqre, 2: pentagon
	GLfloat ShapeRotation{};
	GLfloat ShapeSize{ 1.2 };

public:
	PlayerShape();
	void InputKey(KeyEvent& Event);
	void UpdateFunc(float FrameTime);
	void RenderFunc();
};