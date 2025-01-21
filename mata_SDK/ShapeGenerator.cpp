#include "ShapeGenerator.h"
#include "ObstacleShape.h"

void ShapeGenerator::UpdateFunc(float FrameTime) {
	Timer.Update(FrameTime * Global.PlaySpeed);

	if (Timer.CheckMiliSec(Global.ShapeGenerateTime, 1, CHECK_AND_INTERPOLATE)) {
		switch (PrevShape) {
		case -1:
			scene.AddObject(new ObstacleShape(ObTriangle), "obstacle_shape", LAYER2);
			PrevShape = ObTriangle;
			break;

		case ObSquare:
		{
			int RandomType = Random.Gen(RANDOM_TYPE_INT, ObTriangle, ObPentagon);
			if (RandomType == ObSquare)
				++SameShapeCount;
			else
				SameShapeCount = 0;

			if (SameShapeCount == 2) {
				int RandomNum = Random.Gen(RANDOM_TYPE_INT, 0, 1);
				if (RandomNum == 0)
					--RandomType;
				else if (RandomNum == 1)
					++RandomType;

				SameShapeCount = 0;
			}

			scene.AddObject(new ObstacleShape(RandomType), "obstacle_shape", LAYER2);
			PrevShape = RandomType;
		}
		break;

		case ObTriangle:
		{
			int RandomType = Random.Gen(RANDOM_TYPE_INT, ObTriangle, ObSquare);
			if (RandomType == ObTriangle)
				++SameShapeCount;
			else
				SameShapeCount = 0;

			if (SameShapeCount == 2) {
				++RandomType;
				SameShapeCount = 0;
			}

			scene.AddObject(new ObstacleShape(RandomType), "obstacle_shape", LAYER2);
			PrevShape = RandomType;
		}
		break;

		case ObPentagon:
		{
			int RandomType = Random.Gen(RANDOM_TYPE_INT, ObSquare, ObPentagon);

			if (RandomType == ObPentagon)
				++SameShapeCount;
			else
				SameShapeCount = 0;

			if (SameShapeCount == 2) {
				--RandomType;
				SameShapeCount = 0;
			}

			scene.AddObject(new ObstacleShape(RandomType), "obstacle_shape", LAYER2);
			PrevShape = RandomType;
		}
		break;
		}
	}
}