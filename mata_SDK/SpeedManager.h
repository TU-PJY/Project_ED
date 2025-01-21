#pragma once
#include "GameObject.h"
#include "Scene.h"

class SpeedManager : public GameObject {
private:
	// ratio of generate speed and shape move speed
	GLfloat TimeElapsRatio1{ 2.2 };

	//ratio of generate speed and camera rotate speed
	GLfloat TimeElapsRatio2{ 242.85 };

	GLfloat IncreaseSpeed{};
	GLfloat MaxRotateSpeed{};
	GLfloat LessGenerateTime{};
	GLfloat MaxMoveSpeed{};

public:
	SpeedManager();
	void UpdateFunc(float FrameTime);
};