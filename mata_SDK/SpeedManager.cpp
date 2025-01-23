#include "SpeedManager.h"

SpeedManager::SpeedManager(){
	switch (Global.Diff) {
	case 0: // easy
		IncreaseSpeed = 0.5; 
		LessGenerateTime = 0.45;
		MaxMoveSpeed = 2.4;
		MaxRotateSpeed = 60.0;
		break;

	case 1: // normal
		IncreaseSpeed = 1.0; 
		LessGenerateTime = 0.42;
		MaxMoveSpeed = 2.4;
		MaxRotateSpeed = 80.0;
		break;

	case 2: // hard
		IncreaseSpeed = 2.0; 
		LessGenerateTime = 0.4;
		MaxMoveSpeed = 2.5;
		MaxRotateSpeed = 100.0;
		break;

	case 3: // harder
		IncreaseSpeed = 5.0; 
		LessGenerateTime = 0.38;
		MaxMoveSpeed = 2.6;
		MaxRotateSpeed = 140.0;
		break;

	case 4:  // insane
		IncreaseSpeed = 50.0; 
		LessGenerateTime = 0.35;
		MaxMoveSpeed = 2.8;
		MaxRotateSpeed = 170.0;
		break;
	}

	TimeElapsRatio1 = (MaxMoveSpeed - 1.6) / (1.0 - LessGenerateTime);
	TimeElapsRatio2 = MaxRotateSpeed / (1.0 - LessGenerateTime);
}

void SpeedManager::UpdateFunc(float FrameTime){
	Global.ElapsedTime += FrameTime * Global.PlaySpeed;

	Global.ShapeGenerateTime = 1.0 - (Global.ElapsedTime * 0.005) * IncreaseSpeed;
	Global.ShapeMoveSpeed = 1.6 + (Global.ElapsedTime * TimeElapsRatio1 * 0.005) * IncreaseSpeed;
	Global.CameraRotateSpeed = (Global.ElapsedTime * TimeElapsRatio2 * 0.005) * IncreaseSpeed;

	EX.ClampValue(Global.ShapeMoveSpeed, MaxMoveSpeed, CLAMP_GREATER);
	EX.ClampValue(Global.ShapeGenerateTime, LessGenerateTime, CLAMP_LESS);
	EX.ClampValue(Global.CameraRotateSpeed, MaxRotateSpeed, CLAMP_GREATER);
}