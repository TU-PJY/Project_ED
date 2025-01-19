#include "ShapeGenerator.h"
#include "ObstacleShape.h"

void ShapeGenerator::UpdateFunc(float FrameTime) {
	if (RunningState) {
		Timer.Update(FrameTime);
		if (Timer.CheckMiliSec(GenerateTime, 1, CHECK_AND_INTERPOLATE)) {
			int RandomType = Random.Gen(RANDOM_TYPE_INT, 0, 2);
			scene.AddObject(new ObstacleShape(RandomType), "obstacle_shape", LAYER2);
		}
	}
}

void ShapeGenerator::Stop() {
	RunningState = false;
}
