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

	GLfloat KeyOpacity{};
	GLfloat Size{ 0.1 };

	bool ExitScreenState{};

	SoundChannel Ch{};

public:
	PauseScreen() {
		Text.Init(L"에스코어 드림 3 Light", FW_DONTCARE);
		Text.SetAlign(ALIGN_MIDDLE);
		Text.SetHeightAlign(HEIGHT_ALIGN_MIDDLE);
		Text.SetColor(1.0, 1.0, 1.0);
		soundUtil.PlaySound(Audio.GameExitSound, Ch);
	}

	void InputKey(KeyEvent& Event) {
		if (Event.Type == NORMAL_KEY_DOWN) {
			switch (Event.NormalKey) {
			case NK_ESCAPE:
				if (!ExitToHome && !ExitToDesktop)
					ExitToGameMode();
				
				else if (ExitToHome || ExitToDesktop) {
					soundUtil.PlaySound(Audio.KeySelectSound, Ch);
					ExitToHome = false;
					ExitToDesktop = false;
				}
				break;

			case NK_ENTER:
				if (!ExitToHome && !ExitToDesktop) {
					if (CurrentPauseIndex == 0) 
						ExitToGameMode();
					
					else if (CurrentPauseIndex == 1) {
						soundUtil.PlaySound(Audio.KeySelectSound, Ch);
						ExitToHome = true;
						CurrentQuestionIndex = 0;
						DestQuestionTextHeight = 0.0;
						QuestionTextHeight = 0.0;
					}
					else if (CurrentPauseIndex == 2) {
						soundUtil.PlaySound(Audio.KeySelectSound, Ch);
						ExitToDesktop = true;
						CurrentQuestionIndex = 0;
						DestQuestionTextHeight = 0.0;
						QuestionTextHeight = 0.0;
					}
				}

				else if (ExitToHome && !ExitToDesktop) {
					soundUtil.PlaySound(Audio.KeySelectSound, Ch);

					if (CurrentQuestionIndex == 0) 
						ExitToHomeMode();
					
					else if (CurrentQuestionIndex == 1)
						ExitToHome = false;
				}

				else if (!ExitToHome && ExitToDesktop) {
					soundUtil.PlaySound(Audio.KeySelectSound, Ch);

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
				soundUtil.PlaySound(Audio.KeyMoveSound, Ch);

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
				soundUtil.PlaySound(Audio.KeyMoveSound, Ch);

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
			mathUtil.UpdateLerp(KeyOpacity, 1.0, 20.0, FrameTime);
		}

		else {
			mathUtil.UpdateLerp(BackOpacity, 0.0, 20.0, FrameTime);
			mathUtil.UpdateLerp(BlockOpacity, 0.0, 20.0, FrameTime);
			mathUtil.UpdateLerp(PauseTextOpacity, 0.0, 20.0, FrameTime);
			mathUtil.UpdateLerp(QuestionTextOpacity, 0.0, 20.0, FrameTime);
			mathUtil.UpdateLerp(KeyOpacity, 0.0, 20.0, FrameTime);

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

		RenderKeyInfo();
	}

	void ExitToHomeMode() {
		Global.PrevPlayTime[Global.Diff] = soundUtil.GetPlayTime(Global.TrackChannel);
		soundUtil.StopSound(Global.TrackChannel);
		soundUtil.StopSound(Global.BeatChannel);

		Global.GameOverState = true;
		size_t Size = scene.LayerSize(LAYER2);
		for (int i = 0; i < Size; ++i) {
			if (auto Object = scene.FindMulti("obstacle_shape", LAYER2, i); Object)
				Object->SetExitState();
		}

		if (auto Object = scene.Find("player_shape"); Object)
			Object->SetExitState();

		scene.SwitchMode(HomeMode.Start);
		ObjectTag = "";
		ExitScreenState = true;
	}

	void ExitToGameMode() {
		soundUtil.PlaySound(Audio.GameStartSound, Ch);
		scene.EndFloatingMode();
		ObjectTag = "";
		ExitScreenState = true;
		soundUtil.PauseSound(Global.TrackChannel, false);
		soundUtil.PauseSound(Global.BeatChannel, false);
	}

	void RenderKeyInfo() {
		Text.SetOpacity(KeyOpacity);
		Text.SetAlign(ALIGN_DEFAULT);
		BeginRender(RENDER_TYPE_STATIC);
		SetColor(1.0, 1.0, 1.0);
		transform.Move(TranslateMatrix, WindowRect.lx + 0.15, -0.65);
		transform.Scale(ScaleMatrix, Size, Size);
		RenderSprite(Sprite.ArrowIconLeft, KeyOpacity);

		transform.Move(TranslateMatrix, Size, 0.0);
		RenderSprite(Sprite.ArrowIconRight, KeyOpacity);

		transform.Move(TranslateMatrix, -Size * 0.5, -Size);
		RenderSprite(Sprite.EnterIcon, KeyOpacity);

		transform.Move(TranslateMatrix, 0.0, -Size);
		RenderSprite(Sprite.EscapeIcon, KeyOpacity);

		Text.Render(WindowRect.lx + 0.15 + Size * 2.0, -0.65 + 0.01, 0.05, L"이동");
		Text.Render(WindowRect.lx + 0.15 + Size * 2.0, -0.65 - Size + 0.01, 0.05, L"선택");

		if (ExitToHome || ExitToDesktop)
			Text.Render(WindowRect.lx + 0.15 + Size * 2.0, -0.65 - Size * 2.0 + 0.01, 0.05, L"뒤로가기");
		else
			Text.Render(WindowRect.lx + 0.15 + Size * 2.0, -0.65 - Size * 2.0 + 0.01, 0.05, L"게임으로 돌아가기");

		Text.SetAlign(ALIGN_MIDDLE);
	}
};