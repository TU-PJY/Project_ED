#include "HomeScreen.h"
#include "Scene.h"

#include "PlayMode.h"

HomeScreen::HomeScreen() {
	// text init
	Text.Init(L"Ronduit Capitals Light", FW_NORMAL);
	Text.SetColor(1.0, 1.0, 1.0);
	Text.SetAlign(ALIGN_MIDDLE);
	Text.SetHeightAlign(HEIGHT_ALIGN_MIDDLE);

	// HighScore Data Load
	HighScoreData.Load("GameData//Data", Format.HighScoreDataFormat);
	DigitDataSet HighScoreDataSet = HighScoreData.LoadCategoryDigitData("HighScore");
	size_t Size = HighScoreDataSet.size();
	for (int i = 0; i < Size; ++i)
		HighScore[i] = HighScoreDataSet[i];

	SetColor(1.0, 1.0, 1.0);
}

void HomeScreen::InputKey(KeyEvent& Event) {
	if (Event.Type == SPECIAL_KEY_DOWN) {
		switch (Event.SpecialKey) {
		case SK_ARROW_LEFT:
			--CurrentPage;
			EX.ClampValue(CurrentPage, 0, CLAMP_LESS);
			break;

		case SK_ARROW_RIGHT:
			++CurrentPage;
			EX.ClampValue(CurrentPage, 4, CLAMP_GREATER);
			break;
		}
	}

	// enter to play
	else if (Event.Type == NORMAL_KEY_DOWN) {
		switch (Event.NormalKey) {
		case NK_ENTER:
			Global.Diff = CurrentPage + 1;
			scene.SwitchMode(PlayMode.Start);
			break;
		}
	}
}

void HomeScreen::InputMouse(int Type) {
	switch (Type) {
	case LEFT_BUTTON_DOWN:
		// left arrow click
		if (ArrowAABB[0].CheckCollisionPoint(mouse.x, mouse.y)) {
			--CurrentPage;
			EX.ClampValue(CurrentPage, 0, CLAMP_LESS);
		}

		// right arrow click
		else if (ArrowAABB[1].CheckCollisionPoint(mouse.x, mouse.y)) {
			++CurrentPage;
			EX.ClampValue(CurrentPage, 0, CLAMP_LESS);
		}
		break;
	}
}

void HomeScreen::UpdateFunc(float FrameTime) {
	// left arrow
	ArrowAABB[0].Update(glm::vec2(WindowRect.lx + 0.12, 0.0), 0.2, 0.25);

	// right arrow
	ArrowAABB[1].Update(glm::vec2(WindowRect.rx - 0.12, 0.0), 0.2, 0.25);
}

void HomeScreen::RenderFunc() {
	// diff text
	Text.RenderStr(0.0, -0.7, 0.2, DiffString[CurrentPage]);

	// title
	BeginRender();
	transform.Move(TranslateMatrix, 0.0, 0.6);
	transform.Scale(ScaleMatrix, 1.5, 1.5);
	RenderSprite(Sprite.Title);

	// arrow left
	BeginRender();
	transform.Move(TranslateMatrix, WindowRect.lx + 0.15, 0.0);
	transform.Scale(ScaleMatrix, 0.3, 0.3);
	RenderSprite(Sprite.ArrowLeft);

	// arrow right
	BeginRender();
	transform.Move(TranslateMatrix, WindowRect.rx - 0.15, 0.0);
	transform.Scale(ScaleMatrix, 0.3, 0.3);
	RenderSprite(Sprite.ArrowRight);
	for (int i = 0; i < 2; ++i)
		ArrowAABB[i].Render();
}