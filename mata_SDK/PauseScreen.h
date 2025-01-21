#pragma once
#include "GameObject.h"
#include "Scene.h"

#include "HomeMode.h"

class PauseScreen : public GameObject {
private:
	GLfloat BackOpacity{};
	GLfloat BlockOpacity{};

	TextUtil Text{};
	bool Question{};
	bool ExitToHome{};
	bool ExitToDesktop{};

	GLfloat PauseTextOpacity{};
	GLfloat PauseTextHeight{};
	GLfloat DestPauseTextHeight{};

	GLfloat QuestionTextOpacity{};
	GLfloat QuestionTextHeight{};
	GLfloat DestQuestionTextHeight{};

	int CurrentPauseIndex{}, CurrentQuestionIndex{};

	bool ExitScreenState{};

	SoundChannel Ch{};

public:
	PauseScreen() {
		Text.Init(L"에스코어 드림 3 Light", FW_DONTCARE);
		Text.SetAlign(ALIGN_MIDDLE);
		Text.SetHeightAlign(HEIGHT_ALIGN_MIDDLE);
		Text.SetColor(1.0, 1.0, 1.0);
	}

	void InputKey(KeyEvent& Event) {
		if (Event.Type == NORMAL_KEY_DOWN) {
			switch (Event.NormalKey) {
			case NK_ESCAPE:
				if (!ExitToHome && !ExitToDesktop) {
					scene.EndFloatingMode();
					ObjectTag = "";
					Global.PlaySpeed = 1.0;
					ExitScreenState = true;
				}
				else if (ExitToHome || ExitToDesktop) {
					ExitToHome = false;
					ExitToDesktop = false;
				}
				break;

			case NK_ENTER:
				if (!ExitToHome && !ExitToDesktop) {
					if (CurrentPauseIndex == 0) {
						scene.EndFloatingMode();
						ObjectTag = "";
						Global.PlaySpeed = 1.0;
						ExitScreenState = true;
					}
					else if (CurrentPauseIndex == 1) {
						ExitToHome = true;
						CurrentQuestionIndex = 0;
						DestQuestionTextHeight = 0.0;
						QuestionTextHeight = 0.0;
					}
					else if (CurrentPauseIndex == 2) {
						ExitToDesktop = true;
						CurrentQuestionIndex = 0;
						DestQuestionTextHeight = 0.0;
						QuestionTextHeight = 0.0;
					}
				}

				else if (ExitToHome && !ExitToDesktop) {
					if (CurrentQuestionIndex == 0) {
						scene.SwitchMode(HomeMode.Start);
						ObjectTag = "";
						Global.PlaySpeed = 1.0;
						ExitScreenState = true;
					}
					else if (CurrentQuestionIndex == 1)
						ExitToHome = false;
				}

				else if (!ExitToHome && ExitToDesktop) {
					if (CurrentQuestionIndex == 0)
						System.Exit();
					else if (CurrentQuestionIndex == 1)
						ExitToDesktop = false;
				}
				break;
			}
		}

		else if (Event.Type == SPECIAL_KEY_DOWN) {
			switch (Event.SpecialKey) {
			case SK_ARROW_UP:
				if (!ExitToHome && !ExitToDesktop) {
					--CurrentPauseIndex;
					DestPauseTextHeight -= 0.16;
					if (CurrentPauseIndex < 0) {
						CurrentPauseIndex = 2;
						DestPauseTextHeight = 0.32;
					}
				}
				else if (ExitToHome || ExitToDesktop) {
					--CurrentQuestionIndex;
					DestQuestionTextHeight -= 0.16;
					if (CurrentQuestionIndex < 0) {
						CurrentQuestionIndex = 1;
						DestQuestionTextHeight = 0.16;
					}
				}
				break;

			case SK_ARROW_DOWN:
				if (!ExitToHome && !ExitToDesktop) {
					++CurrentPauseIndex;
					DestPauseTextHeight += 0.16;
					if (CurrentPauseIndex > 2) {
						CurrentPauseIndex = 0;
						DestPauseTextHeight = 0.0;
					}
				}
				else if (ExitToHome || ExitToDesktop) {
					++CurrentQuestionIndex;
					DestQuestionTextHeight += 0.16;
					if (CurrentQuestionIndex > 1) {
						CurrentQuestionIndex = 0;
						DestQuestionTextHeight = 0.0;
					}
				}
			}
		}
	}

	void UpdateFunc(float FrameTime) {
		if (!ExitScreenState) {
			mathUtil.UpdateLerp(BackOpacity, 0.8, 20.0, FrameTime);
			mathUtil.UpdateLerp(BlockOpacity, 0.2, 20.0, FrameTime);

			if (!ExitToHome && !ExitToDesktop) {
				mathUtil.UpdateLerp(PauseTextOpacity, 1.0, 20.0, FrameTime);
				mathUtil.UpdateLerp(QuestionTextOpacity, 0.0, 20.0, FrameTime);
			}
			else {
				mathUtil.UpdateLerp(PauseTextOpacity, 0.0, 20.0, FrameTime);
				mathUtil.UpdateLerp(QuestionTextOpacity, 1.0, 20.0, FrameTime);
			}

			mathUtil.UpdateLerp(PauseTextHeight, DestPauseTextHeight, 20.0, FrameTime);
			mathUtil.UpdateLerp(QuestionTextHeight, DestQuestionTextHeight, 20.0, FrameTime);
		}

		else {
			mathUtil.UpdateLerp(BackOpacity, 0.0, 20.0, FrameTime);
			mathUtil.UpdateLerp(BlockOpacity, 0.0, 20.0, FrameTime);
			mathUtil.UpdateLerp(PauseTextOpacity, 0.0, 20.0, FrameTime);
			mathUtil.UpdateLerp(QuestionTextOpacity, 0.0, 20.0, FrameTime);

			if (BackOpacity <= 0.0001)
				scene.DeleteObject(this);
		}
	}

	void RenderFunc() {
		// background
		BeginRender(RENDER_TYPE_STATIC);
		SetColor(0.0, 0.0, 0.0);
		transform.Scale(ScaleMatrix, WindowRect.rx - WindowRect.lx, WindowRect.ry - WindowRect.ly);
		RenderSprite(SysRes.COLOR_TEXTURE, BackOpacity);

		// block
		BeginRender(RENDER_TYPE_STATIC);
		SetColor(1.0, 1.0, 1.0);
		transform.Scale(ScaleMatrix, WindowRect.rx - WindowRect.lx, 0.15);
		RenderSprite(SysRes.COLOR_TEXTURE, BlockOpacity);

		// Text
		if (PauseTextOpacity > 0) {
			Text.SetOpacity(PauseTextOpacity);
			Text.SetAlign(ALIGN_DEFAULT);
			Text.Render(WindowRect.lx + 0.1, 0.02, 0.1, L"일시정지");

			Text.SetAlign(ALIGN_MIDDLE);
			Text.Render(0.0, 0.02 + PauseTextHeight, 0.1, L"계속하기");
			Text.Render(0.0, -0.16 + 0.02 + PauseTextHeight, 0.1, L"홈으로 나가기");
			Text.Render(0.0, -0.32 + 0.02 + PauseTextHeight, 0.1, L"바탕화면으로 나가기");
		}
		

		if (QuestionTextOpacity > 0) {
			Text.SetOpacity(QuestionTextOpacity);
			Text.SetAlign(ALIGN_DEFAULT);

			if (ExitToHome && !ExitToDesktop)
				Text.Render(WindowRect.lx + 0.1, 0.02, 0.1, L"홈으로 돌아갈까요?");
			else if (!ExitToHome && ExitToDesktop)
				Text.Render(WindowRect.lx + 0.1, 0.02, 0.1, L"바탕화면으로 나갈까요?");

			Text.SetAlign(ALIGN_MIDDLE);
			Text.Render(0.0, 0.02 + QuestionTextHeight, 0.1, L"예");
			Text.Render(0.0, -0.16 + 0.02 + QuestionTextHeight, 0.1, L"아니오");
		}
	}
};