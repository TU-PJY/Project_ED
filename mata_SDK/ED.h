#pragma once
#include "GameObject.h"

class ClassED : public GameObject {
private:
	glm::vec2 MachinePosition{0.0, -0.1};
	glm::vec2 MovePosition{};
	glm::vec2 EDPosition{ 0.0, -0.1 };
	glm::vec2 ShakePosition{};

	GLfloat Size{ 0.0 };
	GLfloat Rotation{};
	GLfloat SmileRotation{};
	GLfloat DestSmileRotation{};
	GLfloat EDRotation{};

	GLfloat MusicEffectValue{};

	bool SmileState{};
	int EDIndex{};
	TimerUtil BlinkTimer{};

	int NataIndex{};

	SinLoop HeightLoop{};
	SinLoop RotationLoop{};

public:
	void UpdateFunc(float FrameTime);
	void RenderFunc();
};