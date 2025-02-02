#pragma once
#include "GameObject.h"

enum ShapeEnum {
	Triangle,
	Square,
	Pentagon
};

extern GameObject* PlayerShapePtr;

class PlayerShape : public GameObject {
private:
	int CurrentShape{}; // 0: triangle, 1: sauqre, 2: pentagon
	int PrevShape{};

	GLfloat ShapeRotation{};
	GLfloat RotationDest{};

	// triangle, square, pentagon
	GLfloat ShapeRotationValue[3]{ 0.0, -90.0, -144.0 };

	GLfloat ShapeSize{ 5.0 };

	GLfloat ThreasHold{};

	GLfloat Opacity{};

	bool ExitState{};

	RandomUtil Random{};
	int RandomIndex{};
	unsigned int PlayLocation{};

public:
	PlayerShape();
	void InputKey(KeyEvent& Event);
	void ChangeShapeRotationDest();
	void UpdateFunc(float FrameTime);
	void RenderFunc();
	void ExitToHome(float FrameTime);
	void SetExitState();
	int GetCurrentShape();
};