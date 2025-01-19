#pragma once
#include "GameObject.h"
#include "Scene.h"

class ShapeGenerator : public GameObject {
private:
	TimerUtil Timer{};
	RandomUtil Random{};
	GLfloat GenerateTime{ 1.0 };
	bool RunningState{ true };

public:
	void UpdateFunc(float FrameTime);
	void Stop();
};