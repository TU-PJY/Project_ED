#include "HomeScreen.h"
#include "Scene.h"

#include "PlayMode.h"
#include "OptionMode.h"

HomeScreen::HomeScreen() {
	// text init
	DiffText.Init(L"Ronduit Capitals Light", FW_NORMAL);
	DiffText.SetColor(1.0, 1.0, 1.0);
	DiffText.SetAlign(ALIGN_MIDDLE);
	DiffText.SetHeightAlign(HEIGHT_ALIGN_MIDDLE);

	// HighScore Data Load
	Global.HighScoreData.Load("GameData//Data", Format.HighScoreDataFormat);
	DigitDataSet HighScoreDataSet = Global.HighScoreData.LoadCategoryDigitData("HighScore");
	size_t Size = HighScoreDataSet.size();
	for (int i = 0; i < Size; ++i)
		Global.PrevHighScore[i] = HighScoreDataSet[i];

	CurrentPage = Global.Diff;

	SetColor(1.0, 1.0, 1.0);
}

void HomeScreen::InputKey(KeyEvent& Event) {
	if (Event.Type == SPECIAL_KEY_DOWN) {
		switch (Event.SpecialKey) {
		case SK_ARROW_LEFT:
			if (CurrentPage == 0) break;
			soundUtil.PlaySound(Audio.KeyMoveSound, Ch);
			--CurrentPage;
			TextPosition.x = 0.5;
			ArrowFeedback[0] = -0.1;
			break;

		case SK_ARROW_RIGHT:
			if (CurrentPage == 4) break;
			soundUtil.PlaySound(Audio.KeyMoveSound, Ch);
			++CurrentPage;
			TextPosition.x = -0.5;
			ArrowFeedback[1] = 0.1;
			break;
		}
	}

	// enter to play
	else if (Event.Type == NORMAL_KEY_DOWN) {
		switch (Event.NormalKey) {
		case NK_ENTER:
			soundUtil.PlaySound(Audio.GameStartSound, Ch);
			Global.Diff = CurrentPage;
			scene.SwitchMode(PlayMode.Start);
			break;

		case NK_ESCAPE:
			soundUtil.PlaySound(Audio.KeySelectSound, Ch);
			scene.StartFloatingMode(OptionMode.Start);
			break;
		}
	}
}

void HomeScreen::UpdateFunc(float FrameTime) {
	TitleSize = TitleBounce.Update(1.5, 2.0, 20.0, 20.0, 10.0, FrameTime);

	mathUtil.UpdateLerp(TextPosition.x, 0.0, 10.0, FrameTime);
	mathUtil.UpdateLerp(TextPosition.y, -0.7, 10.0, FrameTime);

	UpdateArrow(FrameTime);
}

void HomeScreen::RenderFunc() {
	// diff text
	DiffText.RenderStr(TextPosition.x, TextPosition.y, 0.2, DiffString[CurrentPage]);

	// title
	BeginRender();
	transform.Move(TranslateMatrix, 0.0, 0.6);
	transform.Scale(ScaleMatrix, TitleSize, TitleSize);
	RenderSprite(Sprite.Title);

	// arrow left
	BeginRender();
	transform.Move(TranslateMatrix, -ArrowPosition + ArrowFeedback[0], 0.0);
	transform.Scale(ScaleMatrix, 0.3, 0.3);
	RenderSprite(Sprite.ArrowLeft, ArrowOpacity[0]);
	

	// arrow right
	BeginRender();
	transform.Move(TranslateMatrix, ArrowPosition + ArrowFeedback[1], 0.0);
	transform.Scale(ScaleMatrix, 0.3, 0.3);
	RenderSprite(Sprite.ArrowRight, ArrowOpacity[1]);
}

void HomeScreen::UpdateArrow(float FrameTime) {
	if (CurrentPage == 0) {
		mathUtil.UpdateLerp(ArrowOpacity[0], 0.0, 20.0, FrameTime);
		mathUtil.UpdateLerp(ArrowOpacity[1], 1.0, 20.0, FrameTime);
	}
	else if (CurrentPage == 4) {
		mathUtil.UpdateLerp(ArrowOpacity[0], 1.0, 20.0, FrameTime);
		mathUtil.UpdateLerp(ArrowOpacity[1], 0.0, 20.0, FrameTime);
	}
	else {
		mathUtil.UpdateLerp(ArrowOpacity[0], 1.0, 20.0, FrameTime);
		mathUtil.UpdateLerp(ArrowOpacity[1], 1.0, 20.0, FrameTime);
	}

	mathUtil.UpdateLerp(ArrowPosition, WindowRect.rx - 0.2, 10.0, FrameTime);
	// arrow feedback
	for (int i = 0; i < 2; ++i)
		mathUtil.UpdateLerp(ArrowFeedback[i], 0.0, 10.0, FrameTime);
}