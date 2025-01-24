#pragma once
#include "GameObject.h"

class ClassED : public GameObject {
private:
	glm::vec2 MachinePosition{0.0, -0.1};
	glm::vec2 MovePosition{};
	glm::vec2 Position{ 0.0, -0.1 };

	GLfloat Size{ 0.0 };
	GLfloat CamRotation{};
	GLfloat SmileRotation{};
	GLfloat DestSmileRotation{};
	GLfloat EDRotation{};

	GLfloat MusicEffectValue{};

	bool SmileState{};
	int EDIndex{};
	TimerUtil BlinkTimer{};

	SinLoop HeightLoop{};
	SinLoop RotationLoop{};

public:
	void UpdateFunc(float FrameTime);
	void RenderFunc();
	glm::vec2 GetPosition();
	GLfloat GetSize();
};