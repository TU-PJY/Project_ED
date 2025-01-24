#pragma once
#include "GameObject.h"
#include "Scene.h"

class ClassNata : public GameObject {
private:
	glm::vec2 Position{-0.5, 0.3};
	glm::vec2 MovePosition{};
	glm::vec2 ShakePosition{};
	SinLoop MoveLoop{};
	GameObject* ED{};
	int Index{};

public:
	void UpdateFunc(float FrameTime);
	void RenderFunc();
};