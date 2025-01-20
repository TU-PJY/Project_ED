#pragma once
#include "GameObject.h"
#include "Scene.h"

class OptionWindow : public GameObject {
private:
	GLfloat BackOpacity{};

	TextUtil Text{};
	GLfloat TextHeight[3]{ 0.16, 0.0, -0.16 };
	GLfloat TextOpacity{};
	GLfloat TextBackOpacity[3]{};
	GLfloat TextFeedback[3]{};
	bool TextSelected[3]{};

	int KeyboardCursor{};

	bool ExitOption{};

public:
	OptionWindow() {
		Text.Init(L"에스코어 드림 3 Light", FW_DONTCARE);
		Text.SetColor(1.0, 1.0, 1.0);
		Text.SetAlign(ALIGN_MIDDLE);
		Text.SetHeightAlign(HEIGHT_ALIGN_MIDDLE);

		TextSelected[0] = true;
	}

	void UpdateFunc(float FrameTime) {
		if (!ExitOption) {
			mathUtil.UpdateLerp(BackOpacity, 0.6, 20.0, FrameTime);
			mathUtil.UpdateLerp(TextOpacity, 1.0, 20.0, FrameTime);

			for (int i = 0; i < 3; ++i) {
				if (TextSelected[i]) {
					mathUtil.UpdateLerp(TextFeedback[i], 0.02, 10.0, FrameTime);
					mathUtil.UpdateLerp(TextBackOpacity[i], 0.4, 10.0, FrameTime);
				}
				else {
					mathUtil.UpdateLerp(TextFeedback[i], 0.0, 10.0, FrameTime);
					mathUtil.UpdateLerp(TextBackOpacity[i], 0.0, 10.0, FrameTime);
				}
			}
		}

		else {
			for(int i = 0; i < 3; ++i)
				mathUtil.UpdateLerp(TextBackOpacity[i], 0.0, 20.0, FrameTime);
			mathUtil.UpdateLerp(BackOpacity, 0.0, 20.0, FrameTime);
			mathUtil.UpdateLerp(TextOpacity, 0.0, 20.0, FrameTime);

			if (BackOpacity <= 0.0001)
				scene.DeleteObject(this);
		}
	}

	void InputKey(KeyEvent& Event) {
		if (Event.Type == NORMAL_KEY_DOWN) {
			switch (Event.NormalKey) {
			case NK_ESCAPE:
				scene.EndFloatingMode();
				ExitOption = true;
				ObjectTag = "";
				break;

			case NK_ENTER:
				if (TextSelected[2])
					System.Exit();

				else if (TextSelected[1]) {
					scene.EndFloatingMode();
					ExitOption = true;
					ObjectTag = "";
				}
				break;
			}
		}

		else if (Event.Type == SPECIAL_KEY_DOWN) {
			switch (Event.SpecialKey) {
			case SK_ARROW_UP:
				if (KeyboardCursor == 0) break;

				else
				--KeyboardCursor;

				TextSelected[KeyboardCursor + 1] = false;
				TextSelected[KeyboardCursor] = true;
				break;

			case SK_ARROW_DOWN:
				if (KeyboardCursor == 2) break;

				else
					++KeyboardCursor;

				TextSelected[KeyboardCursor - 1] = false;
				TextSelected[KeyboardCursor] = true;
				break;
			}
		}
	}

	void RenderFunc() {
		// background
		BeginRender(RENDER_TYPE_STATIC);
		SetColor(0.0, 0.0, 0.0);
		transform.Scale(ScaleMatrix, WindowRect.rx - WindowRect.lx, WindowRect.ry - WindowRect.ly);
		RenderSprite(SysRes.COLOR_TEXTURE, BackOpacity);

		// Text back
		for (int i = 0; i < 3; ++i) {
			BeginRender(RENDER_TYPE_STATIC);
			SetColor(1.0, 1.0, 1.0);
			transform.Move(TranslateMatrix, 0.0, TextHeight[i] - 0.02);
			transform.Scale(ScaleMatrix, 0.8, 0.15);
			RenderSprite(SysRes.COLOR_TEXTURE, TextBackOpacity[i]);
		}

		// Text
		Text.SetOpacity(TextOpacity);
		Text.Render(0.0, 0.16, 0.1 + TextFeedback[0], L"환경설정");
		Text.Render(0.0, 0.0, 0.1 + TextFeedback[1], L"홈으로 돌아가기");
		Text.Render(0.0, -0.16, 0.1 + TextFeedback[2], L"바탕화면으로 나가기");
	}
};