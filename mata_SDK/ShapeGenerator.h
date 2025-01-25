#pragma once
#include "GameObject.h"
#include "Scene.h"

enum GenerateTypeEnum {
	ObTriangle,
	ObSquare,
	ObPentagon
};

class ShapeGenerator : public GameObject {
private:
	TimerUtil Timer{};
	RandomUtil Random{};
	GLfloat GenerateTime{ 1.0 };

	int PrevShape{-1};
	int SameShapeCount{};
	bool Created{};

public:
	void UpdateFunc(float FrameTime);
	void CheckSameShape(int& RandomType, int PrevShape);
};