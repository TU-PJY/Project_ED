#pragma once
#include "GameObject.h"

class PlayScore : public GameObject {
private:
	TextUtil Text{};
	int HighScore{};

	GLfloat Feedback{};
	GLfloat Size{};
	GLfloat Opacity{};

	bool OverHighScore{};

public:
	PlayScore();
	void PlusScore();
	void UpdateFunc(float FrameTime);
	void RenderFunc();
};