#include "CameraController.h"
#include "CameraUtil.h"
#include "TransformUtil.h"
#include "Scene.h"

void CameraController::InputKey(KeyEvent& Event) {

}

void CameraController::UpdateFunc(float FT){
	if (scene.Mode() == "PlayMode") {
		if (Global.GameOverState) {
			if (!ZoomCompleted) {
				ZoomValue += FT * 40.0;
				ChangeCameraZoom(ZoomValue);
				if (EX.CheckClampValue(ZoomValue, 6.5, CLAMP_GREATER)) 
					ZoomCompleted = true;
			}
			else {
				ZoomValue -= FT * 40.0;
				EX.ClampValue(ZoomValue, 4.0, CLAMP_LESS);
				ChangeCameraZoom(ZoomValue);
			}
		}

		else {
			mathUtil.UpdateLerp(ZoomValue, 1.0, 10.0, FT * Global.PlaySpeed);
			ChangeCameraZoom(ZoomValue);
			Rotation += Global.CameraRotateSpeed * RotateDirection * FT * Global.PlaySpeed;
			if (Rotation > 360.0 || Rotation < -360.0)
				Rotation = 0.0;
		}
	}

	else {
		mathUtil.UpdateLerp(ZoomValue, 1.0, 10.0, FT);
		ChangeCameraZoom(ZoomValue);
		ZoomCompleted = false;
	}
	
	ComputeCameraMatrix();
}

void CameraController::AddShakeValue(GLfloat Value) {
	ShakeValue += Value;
}

void CameraController::ShakeCamera(float FrameTime) {
	ShakePosition.x = Random.Gen(RANDOM_TYPE_REAL, -ShakeValue, ShakeValue);
	ShakePosition.y = Random.Gen(RANDOM_TYPE_REAL, -ShakeValue, ShakeValue);
	ShakeValue -= FrameTime * 0.2;
	EX.ClampValue(ShakeValue, 0.0, CLAMP_LESS);
}

void CameraController::MoveCamera(GLfloat X, GLfloat Y){
	Position.x = X;
	Position.y = Y;
}

void CameraController::MoveCamera(glm::vec2& PositionValue){
	Position = PositionValue;
}

void CameraController::RotateCamera(GLfloat Degree){
	Rotation = Degree;
}

void CameraController::CameraZoom(int ZoomType, GLfloat ZoomValue){
	switch (ZoomType) {
	case ZOOM_IN:
		camera.ZoomValue = camera.ZoomValue / (1.0f - ZoomValue);
		break;

	case ZOOM_OUT:
		camera.ZoomValue = camera.ZoomValue * (1.0f - ZoomValue);
		break;
	}
}

void CameraController::ChangeCameraZoom(GLfloat ZoomValue){
	camera.ZoomValue = ZoomValue;
}

GLfloat CameraController::ComputeNextZoom(int ZoomType, GLfloat ZoomValue) {
	if (ZoomType == ZOOM_IN)
		return camera.ZoomValue / (1.0f - ZoomValue);
	else if (ZoomType == ZOOM_OUT)
		return camera.ZoomValue * (1.0f - ZoomValue);
	else
		return camera.ZoomValue;
}

void CameraController::ChangeRotateDirection() {
	RotateDirection *= -1;
}

GLfloat CameraController::GetRotation() {
	return Rotation;
}

void CameraController::ChangeRotation(GLfloat Value) {
	Rotation = Value;
}

void CameraController::ResetRotateDirection() {
	RotateDirection = 1;
}

glm::vec2 CameraController::GetShakePosition() {
	return ShakePosition;
}

///////////////////////////////////////// private

void CameraController::ComputeCameraMatrix(){
	transform.Identity(camera.RotateMatrix);
	transform.Identity(camera.TranslateMatrix);
	transform.Move(camera.TranslateMatrix, Position.x, Position.y);
	transform.Rotate(camera.RotateMatrix, Rotation);
}