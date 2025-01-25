#pragma once
#include "GameObject.h"
#include "Scene.h"

enum InfoTypeEnum {
	TypeHomeScreen,
	TypeMenuScreen,
	TypeOptionScreen
};

class KeyInfo : public GameObject {
private:
	int InfoType{};
	GLfloat Opacity{};
	bool ExitState{};
	TextUtil Text{};

	GLfloat Size = 0.1;
	GLfloat Speed{};

public:
	KeyInfo(int Type);
	void UpdateFunc(float FrameTime);
	void RenderFunc();
	void SetExitState();
};