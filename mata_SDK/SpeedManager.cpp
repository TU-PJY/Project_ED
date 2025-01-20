#include "SpeedManager.h"

SpeedManager::SpeedManager(){
	Global.ElapsedTime = 0.0;
	Global.RunningState = true;

	switch (Global.Diff) {
	case 1:
		IncreaseSpeed = 0.5; break;
	case 2:
		IncreaseSpeed = 1.8; break;
	case 3:
		IncreaseSpeed = 5.0; break;
	case 4:
		IncreaseSpeed = 10.0; break;
	case 5:
		IncreaseSpeed = 40.0; break;
	}
}

void SpeedManager::UpdateFunc(float FrameTime){
	if (Global.RunningState) {
		Global.ElapsedTime += FrameTime;

		Global.ShapeGenerateTime = 1.0 - (Global.ElapsedTime * 0.005) * IncreaseSpeed;
		Global.ShapeMoveSpeed = 1.6 + (Global.ElapsedTime * TimeElapsRatio1 * 0.005) * IncreaseSpeed;
		Global.CameraRotateSpeed = (Global.ElapsedTime * TimeElapsRatio2 * 0.005) * IncreaseSpeed;

		EX.ClampValue(Global.ShapeMoveSpeed, 2.6, CLAMP_GREATER);
		EX.ClampValue(Global.ShapeGenerateTime, 0.4, CLAMP_LESS);
		EX.ClampValue(Global.CameraRotateSpeed, 150.0, CLAMP_GREATER);
	}
}