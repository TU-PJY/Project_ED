#pragma once
#include "GameObject.h"

class CameraController : public GameObject {
public:
	glm::vec2 Position{};
	GLfloat Rotation{};
	glm::vec2 ShakePosition{};
	GLfloat ShakeValue{};

	RandomUtil Random{};

	GLfloat ZoomValue{1.0};
	bool ZoomCompleted{};

	void InputKey(KeyEvent& Event);
	void UpdateFunc(float FT);
	void AddShakeValue(GLfloat Value);
	void ShakeCamera(float FrameTime);
	void MoveCamera(GLfloat X, GLfloat Y);
	void MoveCamera(glm::vec2& PositionValue);
	void RotateCamera(GLfloat Degree);
	void CameraZoom(int ZoomType, GLfloat ZoomValue);
	void ChangeCameraZoom(GLfloat ZoomValue);
	GLfloat ComputeNextZoom(int ZoomType, GLfloat ZoomValue);

	void ChangeRotateDirection();
	GLfloat GetRotation();
	void ChangeRotation(GLfloat Value);
	void ResetRotateDirection();
	glm::vec2 GetShakePosition();

	int RotateDirection{ 1 };

private:
	void ComputeCameraMatrix();
};

extern GameObject* CameraControl;