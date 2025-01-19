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
	int PrevShape{};

	GLfloat ShapeRotation{};
	GLfloat CurrentRotationDest{};
	GLfloat ShapeRotationDest[3]{ 0.0, -90.0, -192.0 };

	GLfloat ShapeSize{ 1.2 };

public:
	PlayerShape();
	void InputKey(KeyEvent& Event);
	void ChangeShapeRotationDest();
	void UpdateFunc(float FrameTime);
	void RenderFunc();
};