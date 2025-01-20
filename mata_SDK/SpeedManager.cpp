#include "SpeedManager.h"

void SpeedManager::Stop() {
	RunningState = false;
}

void SpeedManager::Resume() {
	RunningState = true;
}

void SpeedManager::UpdateFunc(float FrameTime){
	if (RunningState) {
		Global.ElapsedTime += FrameTime;

		switch (Global.Diff) {
		case 1:
			Global.ShapeGenerateTime = 1.0 - (Global.ElapsedTime * 0.005);
			Global.ShapeMoveSpeed = 1.6 + (Global.ElapsedTime * TimeElapsRatio1 * 0.005);
			Global.CameraRotateSpeed = (Global.ElapsedTime * TimeElapsRatio2 * 0.005);
			break;

		case 2:
			Global.ShapeGenerateTime = 1.0 - (Global.ElapsedTime * 0.005) * 1.8;
			Global.ShapeMoveSpeed = 1.6 + (Global.ElapsedTime * TimeElapsRatio1 * 0.005) * 1.8;
			Global.CameraRotateSpeed = (Global.ElapsedTime * TimeElapsRatio2 * 0.005) * 1.8;
			break;

		case 3:
			Global.ShapeGenerateTime = 1.0 - (Global.ElapsedTime * 0.005) * 4.0;
			Global.ShapeMoveSpeed = 1.6 + (Global.ElapsedTime * TimeElapsRatio1 * 0.005) * 4.0;
			Global.CameraRotateSpeed = (Global.ElapsedTime * TimeElapsRatio2 * 0.005) * 4.0;
			break;

		case 4:
			Global.ShapeGenerateTime = 1.0 -( Global.ElapsedTime * 0.005) * 10.0;
			Global.ShapeMoveSpeed = 1.6 + (Global.ElapsedTime * TimeElapsRatio1 * 0.005) * 10.0;
			Global.CameraRotateSpeed = (Global.ElapsedTime * TimeElapsRatio2 * 0.005) * 10.0;
			break;

		case 5:
			Global.ShapeGenerateTime = 1.0 - (Global.ElapsedTime * 0.005) * 40.0;
			Global.ShapeMoveSpeed = 1.6 + (Global.ElapsedTime * TimeElapsRatio1 * 0.005) * 40.0;
			Global.CameraRotateSpeed = (Global.ElapsedTime * TimeElapsRatio2 * 0.005) * 40.0;
			break;
		}

		EX.ClampValue(Global.ShapeMoveSpeed, 2.6, CLAMP_GREATER);
		EX.ClampValue(Global.ShapeGenerateTime, 0.4, CLAMP_LESS);
		EX.ClampValue(Global.CameraRotateSpeed, 100.0, CLAMP_GREATER);

		std::cout << Global.CameraRotateSpeed << " " << Global.ShapeMoveSpeed << " " << Global.ShapeGenerateTime << std::endl;
	}
}

void SpeedManager::UpdateGenerateSpeed() {
	//if(Global.ElapsedTime < 20.0)
	//	Global.ShapeGenerateTime = 1.0;

	/*else if (20.0 <= Global.ElapsedTime && Global.ElapsedTime < 60.0)
		Global.ShapeGenerateTime = 0.7;

	else if (60.0 <= Global.ElapsedTime && Global.ElapsedTime < 100.0)
		Global.ShapeGenerateTime = 0.45;

	else if (100.0 <= Global.ElapsedTime && Global.ElapsedTime < 140.0)
		Global.ShapeGenerateTime = 0.35;

	else if (140.0 <= Global.ElapsedTime && Global.ElapsedTime < 180.0)
		Global.ShapeGenerateTime = 0.3;

	else if (180.0 <= Global.ElapsedTime)
		Global.ShapeGenerateTime = 0.25;*/

}

void SpeedManager::UpdateRotateSpeed() {
	/*
	if (Global.ElapsedTime < 20.0)
		Global.CameraRotateSpeed = 0.0;

	else if (20.0 <= Global.ElapsedTime && Global.ElapsedTime < 40.0)
		Global.CameraRotateSpeed = 20.0;

	else if (40.0 <= Global.ElapsedTime && Global.ElapsedTime < 60.0)
		Global.CameraRotateSpeed = 35.0;

	else if (60.0 <= Global.ElapsedTime && Global.ElapsedTime < 80.0)
		Global.CameraRotateSpeed = 45.0;

	else if (80.0 <= Global.ElapsedTime && Global.ElapsedTime < 100.0)
		Global.CameraRotateSpeed = 55.0;

	else if (100.0 <= Global.ElapsedTime && Global.ElapsedTime < 140.0)
		Global.CameraRotateSpeed = 65.0;

	else if (140.0 <= Global.ElapsedTime && Global.ElapsedTime < 180.0)
		Global.CameraRotateSpeed = 80.0;

	else if (180.0 <= Global.ElapsedTime)
		Global.CameraRotateSpeed = 100.0;*/
}
