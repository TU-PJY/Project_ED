#include "ShapeGenerator.h"
#include "ObstacleShape.h"

void ShapeGenerator::UpdateFunc(float FrameTime) {
	if (RunningState) {
		Timer.Update(FrameTime);
		if (Timer.CheckMiliSec(GenerateTime, 1, CHECK_AND_INTERPOLATE)) {
			switch (PrevShape) {
			case -1: 
				scene.AddObject(new ObstacleShape(ObTriangle), "obstacle_shape", LAYER2);
				PrevShape = ObTriangle;
				break;
			
			case ObSquare:
			{
				int RandomType = Random.Gen(RANDOM_TYPE_INT, ObTriangle, ObPentagon);
				scene.AddObject(new ObstacleShape(RandomType), "obstacle_shape", LAYER2);
				PrevShape = RandomType;
			}
			break;

			case ObTriangle:
			{
				int RandomType = Random.Gen(RANDOM_TYPE_INT, ObTriangle, ObSquare);
				scene.AddObject(new ObstacleShape(RandomType), "obstacle_shape", LAYER2);
				PrevShape = RandomType;
			}
			break;

			case ObPentagon:
			{
				int RandomType = Random.Gen(RANDOM_TYPE_INT, ObSquare, ObPentagon);
				scene.AddObject(new ObstacleShape(RandomType), "obstacle_shape", LAYER2);
				PrevShape = RandomType;
			}
			break;
			}
		}
	}
}

void ShapeGenerator::Stop() {
	RunningState = false;
}
