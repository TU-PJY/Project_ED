#pragma once
#include "GameObject.h"

class PlayScore : public GameObject {
private:
	TextUtil Text{};
	int HighScore{};
	int Score{};

	bool OverHighScore{};

public:
	PlayScore();
	void PlusScore();
	void RenderFunc();
};