#pragma once
#include "GameObject.h"
#include "Scene.h"

enum GenerateTypeEnum {
	ObTriangle,
	ObSquare,
	ObPentagon
};

class ObstacleShape : public GameObject {
private:
	RandomUtil Random{};

	int ShapeType{}; // 0: triangle, 1: square, 2: pentagon
	int ShapeIndex{}; // shape's variation number
	GLfloat Rotation{}; // random rotation
	GLfloat CurrentSize{ 10.0 }; // shape's size

public:
	ObstacleShape(int Type);
	void UpdateFunc(float FrameTime);
	void RenderFunc();
};