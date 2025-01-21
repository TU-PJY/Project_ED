#pragma once
#include "GameObject.h"
#include "Scene.h"

class OptionWindow : public GameObject {
private:
	GLfloat BackOpacity{};
	TextUtil Text{};


	int CurrentIndex{};
	GLfloat TextOpacity{};
	GLfloat BlockOpacity{};
	GLfloat DestTextHeight{};
	GLfloat TextHeight{};

	bool SettingScreen{};
	int CurrentSettingIndex{};
	GLfloat SettingTextOpacity{};
	GLfloat SettingTextHeight{};
	GLfloat DestSettingTextHeight{};

	bool ExitOption{};

public:
	OptionWindow() {
		Text.Init(L"에스코어 드림 3 Light", FW_DONTCARE);
		Text.SetColor(1.0, 1.0, 1.0);
		Text.SetAlign(ALIGN_MIDDLE);
		Text.SetHeightAlign(HEIGHT_ALIGN_MIDDLE);
	}

	void UpdateFunc(float FrameTime) {
		UpdateMenu(FrameTime);
	}

	void InputKey(KeyEvent& Event) {
		if (Event.Type == NORMAL_KEY_DOWN) {
			switch (Event.NormalKey) {
			case NK_ESCAPE:
				if (!SettingScreen) {
					scene.EndFloatingMode();
					ExitOption = true;
					ObjectTag = "";
				}
				else {
					Global.UserSettingData.UpdateDigitData("Option", "FullscreenMode", Global.FullscreenMode);
					Global.UserSettingData.UpdateDigitData("Option", "MusicPlayOption", Global.MusicPlayOption);
					Global.UserSettingData.UpdateDigitData("Option", "UseMusicEffect", Global.UseMusicEffect);
					Global.UserSettingData.UpdateDigitData("Option", "MusicEffectValue", Global.MusicEffectValue);
					SettingScreen = false;
				}
				break;

			case NK_ENTER:
				if (!SettingScreen) {
					if (CurrentIndex == 2)
						System.Exit();

					else if (CurrentIndex == 1) {
						scene.EndFloatingMode();
						ExitOption = true;
						ObjectTag = "";
					}

					else if (CurrentIndex == 0) {
						SettingTextHeight = 0.0;
						DestSettingTextHeight = 0.0;
						CurrentSettingIndex = 0;
						SettingScreen = true;
					}
				}

				else {
					switch (CurrentSettingIndex) {
					case 0:
						Global.UserSettingData.UpdateDigitData("Option", "FullscreenMode", Global.FullscreenMode);
						Global.UserSettingData.UpdateDigitData("Option", "MusicPlayOption", Global.MusicPlayOption);
						Global.UserSettingData.UpdateDigitData("Option", "UseMusicEffect", Global.UseMusicEffect);
						Global.UserSettingData.UpdateDigitData("Option", "MusicEffectValue", Global.MusicEffectValue);
						SettingScreen = false;
						break;
					}
				}
				break;
			}
		}

		else if (Event.Type == SPECIAL_KEY_DOWN) {
			switch (Event.SpecialKey) {
			case SK_ARROW_UP:
				if (!SettingScreen) {
					if (CurrentIndex == 0) break;
					--CurrentIndex;
					DestTextHeight -= 0.16;
				}
				else {
					if (CurrentSettingIndex == 0) break;
					--CurrentSettingIndex;
					DestSettingTextHeight -= 0.16;
				}
				break;

			case SK_ARROW_DOWN:
				if (!SettingScreen) {
					if (CurrentIndex == 2) break;
					++CurrentIndex;
					DestTextHeight += 0.16;
				}
				else {
					if (CurrentSettingIndex == 4) break;
					++CurrentSettingIndex;
					DestSettingTextHeight += 0.16;
				}
				break;

			case SK_ARROW_RIGHT:
				if (SettingScreen) {
					switch (CurrentSettingIndex) {
					case 1:
						++Global.FullscreenMode;
						if (Global.FullscreenMode > 1)
							Global.FullscreenMode = 0;
						break;

					case 2:
						++Global.MusicPlayOption;
						if (Global.MusicPlayOption > 2)
							Global.MusicPlayOption = 0;
						break;

					case 3:
						++Global.UseMusicEffect;
						if (Global.UseMusicEffect > 1)
							Global.UseMusicEffect = 0;
						break;
					
					case 4:
						if (Global.UseMusicEffect == 1) 
							Global.MusicEffectValue += 0.1;
						break;
					}
				}
				break;

			case SK_ARROW_LEFT:
				if (SettingScreen) {
					switch (CurrentSettingIndex) {
					case 1:
						--Global.FullscreenMode;
						if (Global.FullscreenMode < 0)
							Global.FullscreenMode = 1;
						break;

					case 2:
						--Global.MusicPlayOption;
						if (Global.MusicPlayOption < 0)
							Global.MusicPlayOption = 2;
						break;

					case 3:
						--Global.UseMusicEffect;
						if (Global.UseMusicEffect < 0)
							Global.UseMusicEffect = 1;
						break;

					case 4:
						if (Global.UseMusicEffect == 1)
							Global.MusicEffectValue -= 0.1;
						break;
					}
				}
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

		// block
		BeginRender(RENDER_TYPE_STATIC);
		SetColor(1.0, 1.0, 1.0);
		transform.Scale(ScaleMatrix, WindowRect.rx - WindowRect.lx, 0.15);
		RenderSprite(SysRes.COLOR_TEXTURE, BlockOpacity);

		RenderMenu();
		RenderSettingMenu();
	}

	void UpdateMenu(float FrameTime) {
		if (!ExitOption) {
			mathUtil.UpdateLerp(BackOpacity, 0.7, 20.0, FrameTime);
			mathUtil.UpdateLerp(BlockOpacity, 0.2, 20.0, FrameTime);

			if (!SettingScreen) {
				mathUtil.UpdateLerp(TextOpacity, 1.0, 20.0, FrameTime);
				mathUtil.UpdateLerp(SettingTextOpacity, 0.0, 20.0, FrameTime);
			}
			else {
				mathUtil.UpdateLerp(TextOpacity, 0.0, 20.0, FrameTime);
				mathUtil.UpdateLerp(SettingTextOpacity, 1.0, 20.0, FrameTime);
			}
		}

		else {
			mathUtil.UpdateLerp(BackOpacity, 0.0, 20.0, FrameTime);
			mathUtil.UpdateLerp(BlockOpacity, 0.0, 20.0, FrameTime);
			mathUtil.UpdateLerp(TextOpacity, 0.0, 20.0, FrameTime);
			mathUtil.UpdateLerp(SettingTextOpacity, 0.0, 20.0, FrameTime);

			if (BackOpacity <= 0.0001)
				scene.DeleteObject(this);
		}

		mathUtil.UpdateLerp(TextHeight, DestTextHeight, 20.0, FrameTime);
		mathUtil.UpdateLerp(SettingTextHeight, DestSettingTextHeight, 20.0, FrameTime);
	}

	void RenderMenu() {
		Text.SetOpacity(TextOpacity);
		Text.Render(0.0, 0.0 + TextHeight + 0.02, 0.1, L"환경설정");
		Text.Render(0.0, -0.16 + TextHeight + 0.02, 0.1, L"홈으로 돌아가기");
		Text.Render(0.0, -0.32 + TextHeight + 0.02, 0.1, L"바탕화면으로 나가기");
	}

	void RenderSettingMenu() {
		if (CurrentSettingIndex > 0) {
			BeginRender(RENDER_TYPE_STATIC);
			transform.Move(TranslateMatrix, -0.7, 0.0);
			transform.Scale(ScaleMatrix, 0.1, 0.1);
			RenderSprite(Sprite.ArrowLeft, SettingTextOpacity);

			BeginRender(RENDER_TYPE_STATIC);
			transform.Move(TranslateMatrix, 0.7, 0.0);
			transform.Scale(ScaleMatrix, 0.1, 0.1);
			RenderSprite(Sprite.ArrowRight, SettingTextOpacity);
		}

		Text.SetOpacity(SettingTextOpacity);
		Text.Render(0.0, 0.0 + SettingTextHeight + 0.02, 0.1, L"저장하고 돌아가기");

		if(Global.FullscreenMode == 1)
			Text.Render(0.0, -0.16 + SettingTextHeight + 0.02, 0.1, L"스크린 설정: 전체화면");
		else
			Text.Render(0.0, -0.16 + SettingTextHeight + 0.02, 0.1, L"스크린 설정: 창");

		if(Global.MusicPlayOption == 0)
			Text.Render(0.0, -0.32 + SettingTextHeight + 0.02, 0.1, L"음악 재생 설정: 이어서 재생");
		else if(Global.MusicPlayOption == 1)
			Text.Render(0.0, -0.32 + SettingTextHeight + 0.02, 0.1, L"음악 재생 설정: 랜덤 지점 재생");
		else if (Global.MusicPlayOption == 2)
			Text.Render(0.0, -0.32 + SettingTextHeight + 0.02, 0.1, L"음악 재생 설정: 처음부터 재생");

		if (Global.UseMusicEffect == 1) {
			Text.Render(0.0, -0.48 + SettingTextHeight + 0.02, 0.1, L"음향 효과: 사용");
			Text.Render(0.0, -0.64 + SettingTextHeight + 0.02, 0.1, L"음향 효과 조정: %.1f", Global.MusicEffectValue);
		}
		else {
			Text.Render(0.0, -0.48 + SettingTextHeight + 0.02, 0.1, L"음향 효과: 사용 안 함");
			Text.SetOpacity(SettingTextOpacity - 0.7);
			Text.Render(0.0, -0.64 + SettingTextHeight + 0.02, 0.1, L"음향 효과 조정: %.1f", Global.MusicEffectValue);
		}
	}
};