#include "SpeedManager.h"

SpeedManager::SpeedManager(){
	Global.ElapsedTime = 0.0;
	Global.RunningState = true;

	switch (Global.Diff) {
	case 0:
		IncreaseSpeed = 0.5; 
		MaxRotateSpeed = 80.0;
		LessGenerateTime = 0.45;
		MaxMoveSpeed = 2.6;
		break;

	case 1:
		IncreaseSpeed = 1.0; 
		MaxRotateSpeed = 80.0;
		LessGenerateTime = 0.4;
		MaxMoveSpeed = 2.6;
		break;

	case 2:
		IncreaseSpeed = 3.0; 
		MaxRotateSpeed = 100.0; 
		LessGenerateTime = 0.4;
		MaxMoveSpeed = 2.6;
		break;

	case 3:
		IncreaseSpeed = 5.0; 
		MaxRotateSpeed = 120.0;
		LessGenerateTime = 0.35;
		MaxMoveSpeed = 2.6;
		break;

	case 4:
		IncreaseSpeed = 50.0; 
		MaxRotateSpeed = 170.0;
		LessGenerateTime = 0.35;
		MaxMoveSpeed = 2.8;
		break;
	}
}

void SpeedManager::UpdateFunc(float FrameTime){
	if (Global.RunningState) {
		Global.ElapsedTime += FrameTime;

		Global.ShapeGenerateTime = 1.0 - (Global.ElapsedTime * 0.005) * IncreaseSpeed;
		Global.ShapeMoveSpeed = 1.6 + (Global.ElapsedTime * TimeElapsRatio1 * 0.005) * IncreaseSpeed;
		Global.CameraRotateSpeed = (Global.ElapsedTime * TimeElapsRatio2 * 0.005) * IncreaseSpeed;

		EX.ClampValue(Global.ShapeMoveSpeed, MaxMoveSpeed, CLAMP_GREATER);
		EX.ClampValue(Global.ShapeGenerateTime, LessGenerateTime, CLAMP_LESS);
		EX.ClampValue(Global.CameraRotateSpeed, MaxRotateSpeed, CLAMP_GREATER);
	}
}