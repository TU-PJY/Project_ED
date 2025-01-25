#pragma once
#include "GameObject.h"

class IntroScreen : public GameObject {
private:
	TimerUtil    timer;
	TimerUtil    WarningTimer{};
	TextUtil     Text{};
#ifdef USE_SOUND_SYSTEM
	SoundChannel IntroChannel{};
#endif

	GLfloat      LogoSize        = 1.0;
	GLfloat      LogoOpacity = 0.0;
	GLfloat      LogoPosition    = -0.3;
	GLfloat      AnimationSpeed  = 0.5;

	SinLerp      Slerp{};

	int          Scene{}; 
	bool         ScenePlay{};

public:
	IntroScreen() {
		Text.Init(L"에스코어 드림 3 Light", FW_DONTCARE);
		Text.SetAlign(ALIGN_MIDDLE);
		Text.SetHeightAlign(HEIGHT_ALIGN_MIDDLE);
		Text.SetFixMiddle(true);
	}

	void InputKey(KeyEvent& Event) {
		if (Event.Type == NORMAL_KEY_DOWN) {
			switch (Event.NormalKey) {
			case NK_ENTER:
#ifdef USE_SOUND_SYSTEM
				soundUtil.StopSound(IntroChannel);
#endif
				scene.SwitchMode(START_MODE);
				break;

#ifdef ENABLE_DEV_EXIT
			case NK_ESCAPE:
				System.Exit();
				break;
#endif
			}
		}
	}

	void UpdateFunc(float FrameTime) {
		WarningTimer.Update(FrameTime);
		if (!ScenePlay && WarningTimer.CheckSec(10, CHECK_AND_STOP))
			ScenePlay = true;

		if (ScenePlay) {
			timer.Update(FrameTime);
			switch (Scene) {
			case 0:
				if (timer.CheckMiliSec(1.0, 1, CHECK_AND_INTERPOLATE)) {
#ifdef USE_SOUND_SYSTEM
					soundUtil.PlaySound(SysRes.INTRO_SOUND, IntroChannel);
#endif
					++Scene;
				}
				break;


			case 1:
				if (timer.MiliSec() < 2.5) {
					LogoPosition = Slerp.Update(LogoPosition, 0.0, AnimationSpeed, FrameTime);
					LogoOpacity = Slerp.Update(LogoOpacity, 1.0, AnimationSpeed, FrameTime);
				}

				if (timer.CheckMiliSec(2.5, 1, CHECK_AND_RESUME)) {
					LogoOpacity -= FrameTime * 2;
					EX.ClampValue(LogoOpacity, 0.0, CLAMP_LESS);
				}

				if (timer.CheckMiliSec(4.0, 1, CHECK_AND_INTERPOLATE)) {
					LogoPosition = -0.3;
					Slerp.Reset();
					++Scene;
				}
				break;


			case 2:
				if (timer.MiliSec() < 2.5) {
					LogoPosition = Slerp.Update(LogoPosition, 0.0, AnimationSpeed, FrameTime);
					LogoOpacity = Slerp.Update(LogoOpacity, 1.0, AnimationSpeed, FrameTime);
				}

				if (timer.CheckMiliSec(2.5, 1, CHECK_AND_RESUME)) {
					LogoOpacity -= FrameTime * 2;
					EX.ClampValue(LogoOpacity, 0.0, CLAMP_LESS);
				}

				if (timer.CheckMiliSec(4.0, 1, CHECK_AND_RESUME))
					scene.SwitchMode(START_MODE);

				break;
			}
		}
	}

	void RenderFunc() {
		if (!ScenePlay) {
			Text.Render(0.0, 0.0, 0.1, L"알림\n\n 본 게임은 '트릭컬:리바이브'의 팬게임으로,\n해당 게임의 캐릭터에 대한 모든 권한은\nEPIDGames가 소유함을 알립니다.\n\n(C)2024 EPIDGames. All Rights Reserved.");
		}

		BeginRender(RENDER_TYPE_STATIC);
		transform.Move(TranslateMatrix, 0.0, LogoPosition);

		switch (Scene) {
		case 1:
			RenderSprite(SysRes.SDK_LOGO, LogoOpacity);
			break;

		case 2: case 3:
			RenderSprite(SysRes.FMOD_LOGO, LogoOpacity);
			break;
		}
	}
};