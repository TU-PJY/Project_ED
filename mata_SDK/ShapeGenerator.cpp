#include "ShapeGenerator.h"
#include "ObstacleShape.h"

void ShapeGenerator::UpdateFunc(float FrameTime) {
	Timer.Update(FrameTime * Global.PlaySpeed);

	int RandomShape{};

	if (Timer.CheckMiliSec(Global.ShapeGenerateTime, 1, CHECK_AND_INTERPOLATE)) {
		if (!Created) {
			scene.AddObject(new ObstacleShape(ObTriangle), "obstacle_shape", LAYER2, OBJECT_TYPE_STATIC);
			Created = true;
			PrevShape = ObTriangle;
		}
		else {
			if (PrevShape == ObTriangle) {
				RandomShape = Random.Gen(RANDOM_TYPE_INT, ObTriangle, ObSquare);
				CheckSameShape(RandomShape, ObTriangle);
				scene.AddObject(new ObstacleShape(RandomShape), "obstacle_shape", LAYER2, OBJECT_TYPE_STATIC);
			}

			else if (PrevShape == ObSquare) {
				RandomShape = Random.Gen(RANDOM_TYPE_INT, ObTriangle, ObPentagon);
				CheckSameShape(RandomShape, ObSquare);
				scene.AddObject(new ObstacleShape(RandomShape), "obstacle_shape", LAYER2, OBJECT_TYPE_STATIC);
			}

			else if (PrevShape == ObPentagon) {
				RandomShape = Random.Gen(RANDOM_TYPE_INT, ObSquare, ObPentagon);
				CheckSameShape(RandomShape, ObPentagon);
				scene.AddObject(new ObstacleShape(RandomShape), "obstacle_shape", LAYER2, OBJECT_TYPE_STATIC);
			}

			PrevShape = RandomShape;
		}
	}
}

void ShapeGenerator::CheckSameShape(int& RandomType, int PrevShape) {
	if (RandomType == PrevShape) {
		if (Random.Gen(RANDOM_TYPE_INT, 0, 1) == 0)
			++SameShapeCount;
		else
			SameShapeCount = 3;

		if (SameShapeCount > 2) {
			switch (PrevShape) {
			case ObTriangle:
				++RandomType;
				break;

			case ObSquare:
				if (Random.Gen(RANDOM_TYPE_INT, 0, 1) == 0)
					--RandomType;
				else
					++RandomType;
				break;

			case ObPentagon:
				--RandomType;
				break;
			}

			SameShapeCount = 0;
		}
	}
	else
		SameShapeCount = 0;
}
