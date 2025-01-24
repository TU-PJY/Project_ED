#pragma once
#include "GameObject.h"

class ClassED : public GameObject {
private:
	glm::vec2 MachinePosition{};
	glm::vec2 EDPosition{};

	GLfloat Size{};
	GLfloat Rotation{};

	int EDIndex{};
	TimerUtil BlinkTimer{};
	bool BlinkState{};

	int NataIndex{};

	SinLoop HeightLoop{};

public:
	void UpdateFunc(float FrameTime);
	void RenderFunc();
};