#include "SpeedManager.h"

SpeedManager::SpeedManager(){
	Global.ElapsedTime = 0.0;
	Global.RunningState = true;
}

void SpeedManager::UpdateFunc(float FrameTime){
	if (Global.RunningState) {
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