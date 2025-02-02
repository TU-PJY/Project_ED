#pragma once
#include "GameObject.h"

class HomeScreen : public GameObject {
private:
	TextUtil DiffText{};
	TextUtil Text{};

	std::string DiffString[5]{
		"EASY",
		"NORMAL",
		"HARD",
		"HARDER",
		"INSANE"
	};

	int CurrentPage{};

	PopBounce TitleBounce{};
	GLfloat TitleSize{};
	GLfloat TitleHeight{0.7};

	GLfloat ArrowPosition = WindowRect.rx + 0.2;
	GLfloat ArrowFeedback[2]{};
	bool CursorOnArrow[2]{};
	GLfloat ArrowOpacity[2]{};

	GLfloat GradationOpacity{};

	glm::vec2 TextPosition{ 0.0, -1.5 };

	GLfloat HighLightRotation{};

	SoundChannel Ch{};
	SoundChannel ChBGM{};

	TimerUtil DotGenTimer{};

	bool ExitState{};
	bool CutOffSet{};

	GLfloat KeyOpacity{};
	GLfloat Size{ 0.1 };

	bool TutorialScreen{};

	GameObject* TuPtr{};

public:
	HomeScreen();
	void UpdateFunc(float FrameTime);
	void RenderFunc();
	void UpdateArrow(float FrameTime);
	void EnterToGame(float FrameTime);
	void RenderKeyInfo();
	void InputKey(KeyEvent& Event);
};