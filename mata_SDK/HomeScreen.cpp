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
		Global.HighScore[i] = HighScoreDataSet[i];

	CurrentPage = Global.Diff;

	SetColor(1.0, 1.0, 1.0);

	soundUtil.PlaySound(Audio.HomeBGM, ChBGM);
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
			Global.Diff = CurrentPage;
			break;

		case SK_ARROW_RIGHT:
			if (CurrentPage == 4) break;
			soundUtil.PlaySound(Audio.KeyMoveSound, Ch);
			++CurrentPage;
			TextPosition.x = -0.5;
			ArrowFeedback[1] = 0.1;
			Global.Diff = CurrentPage;
			break;
		}
	}

	// enter to play
	else if (Event.Type == NORMAL_KEY_DOWN) {
		switch (Event.NormalKey) {
		case NK_ENTER:
			soundUtil.StopSound(ChBGM);
			soundUtil.PlaySound(Audio.GameStartSound, Ch);
			ExitState = true;
			ObjectTag = "";
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
	if (!ExitState) {
		TitleSize = TitleBounce.Update(1.5, 2.0, 20.0, 20.0, 10.0, FrameTime);

		mathUtil.UpdateLerp(TextPosition.x, 0.0, 10.0, FrameTime);
		mathUtil.UpdateLerp(TextPosition.y, -0.8, 10.0, FrameTime);

		UpdateArrow(FrameTime);
	}
	else
		EnterToGame(FrameTime);
}

void HomeScreen::RenderFunc() {
	// diff text
	DiffText.SetColor(Global.ObjectColor.x, Global.ObjectColor.y, Global.ObjectColor.z);
	DiffText.RenderStr(TextPosition.x, TextPosition.y, 0.2, DiffString[CurrentPage]);
	DiffText.Render(TextPosition.x, TextPosition.y + 0.1, 0.1, L"HIGH SCORE %d", Global.HighScore[CurrentPage]);

	SetColor(Global.ObjectColor);

	// arrow left
	BeginRender(RENDER_TYPE_STATIC);
	transform.Move(TranslateMatrix, -ArrowPosition + ArrowFeedback[0], 0.0);
	transform.Scale(ScaleMatrix, 0.3, 0.3);
	RenderSprite(Sprite.ArrowLeft, ArrowOpacity[0]);

	// arrow right
	BeginRender(RENDER_TYPE_STATIC);
	transform.Move(TranslateMatrix, ArrowPosition + ArrowFeedback[1], 0.0);
	transform.Scale(ScaleMatrix, 0.3, 0.3);
	RenderSprite(Sprite.ArrowRight, ArrowOpacity[1]);

	// title
	BeginRender(RENDER_TYPE_STATIC);
	transform.Move(TranslateMatrix, 0.0, TitleHeight);
	transform.Scale(ScaleMatrix, TitleSize, TitleSize);
	RenderSprite(Sprite.Title);
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

void HomeScreen::EnterToGame(float FrameTime) {
	mathUtil.UpdateLerp(TitleHeight, 1.5, 5.0, FrameTime);
	mathUtil.UpdateLerp(TextPosition.y, -1.5, 5.0, FrameTime);
	mathUtil.UpdateLerp(ArrowPosition, WindowRect.rx + 0.5, 5.0, FrameTime);

	if (TitleHeight >= 1.499)
		scene.DeleteObject(this);
}
