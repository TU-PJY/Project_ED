#pragma once
#include "GameObject.h"

class HomeScreen : public GameObject {
private:
	FileUtil HighScoreData{};
	TextUtil Text{};
	AABB ArrowAABB[2]{};

	int CurrentPage{ 0 };
	int HighScore[5]{}; // 0: easy, 1: normal, 2: hard, 3: harder, 4: hardest
	bool NewHighScore[5]{};

	std::string DiffString[5]{
		"EASY",
		"NORMAL",
		"HARD",
		"HARDER",
		"INSANE"
	};

public:
	HomeScreen();
	void UpdateFunc(float FrameTime);
	void RenderFunc();
	void InputKey(KeyEvent& Event);
	void InputMouse(int Type);
};