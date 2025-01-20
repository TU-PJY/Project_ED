#pragma once
#include "GameObject.h"
#include "Scene.h"

class SpeedManager : public GameObject {
private:
	bool RunningState{ true };
	// ratio of generate speed and shape move speed
	GLfloat TimeElapsRatio1{ 1.66 };

	//ratio of generate speed and camera rotate speed
	GLfloat TimeElapsRatio2{ 142.8 };

public:
	void Stop();
	void Resume();
	void UpdateFunc(float FrameTime);
	void UpdateGenerateSpeed();
	void UpdateRotateSpeed();
};