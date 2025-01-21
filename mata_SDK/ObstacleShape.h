#pragma once
#include "GameObject.h"
#include "Scene.h"

class ObstacleShape : public GameObject {
private:
	RandomUtil Random{};

	int ShapeType{}; // 0: triangle, 1: square, 2: pentagon
	int ShapeIndex{}; // shape's variation number
	GLfloat Rotation{}; // random rotation
	GLfloat CurrentSize{ 16.0 }; // shape's size
	GLfloat Opacity{};

	bool RotateDirectionChanger{};
	bool DestroyState{};
	bool MoveState{ true };

public:
	ObstacleShape(int Type);
	void UpdateFunc(float FrameTime);
	void RenderFunc();
	void Stop();
};