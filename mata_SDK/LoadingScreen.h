#pragma once
#include "Scene.h"
#include "ImageUtil.h"
#include "SoundUtil.h"
#include "IntroMode.h"
#include "CameraUtil.h"
#include "FontUtil.h"
#include "FPSInd.h"

class LoadingScreen : public GameObject {
private:
	HANDLE  ThreadHandle{};
	GLfloat Rotation{};
	GLfloat SpinnerOpacity{1.0};
	bool    LoadCommand{};
	bool    ThreadEnd{};

public:
	void InputKey(KeyEvent& Event) {
#ifdef ENABLE_DEV_EXIT
		if (Event.Type == NORMAL_KEY_DOWN) {
			if (Event.NormalKey == NK_ESCAPE)
				System.Exit();
		}
#endif
	}

	void UpdateFunc(float FrameTime) {
		if (LoadCommand) {
			Rotation -= 200 * FrameTime;

			if (!threadUtil.IsRunning(ThreadHandle) && !ThreadEnd) {
				threadUtil.Close(ThreadHandle);
				ThreadEnd = true;
			}

			if(ThreadEnd) {
				imageUtil.Map();

				if (!ENABLE_INTRO_SCREEN) {
#ifdef USE_SOUND_SYSTEM
					soundUtil.Release(SysRes.INTRO_SOUND);
#endif				
					if (SHOW_FPS) {
						scene.AddObject(new FPS_Indicator, "SDK_OBJECT_FPS_INDICATOR", EOL - 1, OBJECT_TYPE_STATIC);
						Indicator = scene.Find("SDK_OBJECT_FPS_INDICATOR");
					}
					scene.SwitchMode(START_MODE);
				}

				else {
					SpinnerOpacity -= FrameTime * 2.0;
					if (EX.CheckClampValue(SpinnerOpacity, 0.0, CLAMP_LESS)) {
						if (SHOW_FPS) {
							scene.AddObject(new FPS_Indicator, "SDK_OBJECT_FPS_INDICATOR", EOL - 1, OBJECT_TYPE_STATIC);
							Indicator = scene.Find("SDK_OBJECT_FPS_INDICATOR");
						}
						scene.SwitchMode(IntroMode.Start);
					}
				}
			}
		}

		else {
			camera.Init();
			imageUtil.Init();
#ifdef USE_SOUND_SYSTEM
			soundUtil.Init();
#endif
			imageUtil.Load(SysRes.LOADING_SPINNER, SysRes.SDK_LOADING_SPINNER_DIRECTORY, IMAGE_TYPE_LINEAR);
			threadUtil.Create(ThreadHandle, SystemResourceCreateThread);

			LoadCommand = true;
		}
	}

	void RenderFunc() {
		BeginRender(RENDER_TYPE_STATIC);
		transform.Move(TranslateMatrix, WindowRect.rx - 0.15, -0.85);
		transform.Scale(ScaleMatrix, 0.25, 0.25);
		transform.Rotate(RotateMatrix, Rotation);
		RenderSprite(SysRes.LOADING_SPINNER, SpinnerOpacity);
	}

	static DWORD WINAPI SystemResourceCreateThread(LPVOID Param) {
#ifdef USE_SOUND_SYSTEM
		soundUtil.Load(SysRes.INTRO_SOUND, SysRes.SDK_LOGO_SOUND_DIRECTORY, FMOD_DEFAULT);
#endif

		imageUtil.PreLoad(SysRes.SDK_LOGO, SysRes.SDK_LOGO_IMAGE_DIRECTORY, IMAGE_TYPE_LINEAR);
		imageUtil.PreLoad(SysRes.SDK_LOGO_ERROR, SysRes.SDK_LOGO_ERROR_IMAGE_DIRECTORY, IMAGE_TYPE_LINEAR);
		imageUtil.PreLoad(SysRes.FMOD_LOGO, SysRes.FMOD_LOGO_DIRECTORY, IMAGE_TYPE_LINEAR);
		imageUtil.PreLoad(SysRes.COLOR_TEXTURE, SysRes.COLOR_TEXTURE_DIRECTORY);

		// game resoueces
		for (int i = 0; i < 3; ++i) {
			std::string FileName = "Assets//Image//Shapes//Triangle//obstacle_triangle_";
			FileName += std::to_string(i + 1);
			FileName += ".png";
			imageUtil.PreLoad(Sprite.Triangle[i], FileName);
		}

		for (int i = 0; i < 5; ++i) {
			std::string FileName = "Assets//Image//Shapes//Square//obstacle_square_";
			FileName += std::to_string(i + 1);
			FileName += ".png";
			imageUtil.PreLoad(Sprite.Square[i], FileName);
		}

		for (int i = 0; i < 5; ++i) {
			std::string FileName = "Assets//Image//Shapes//Pentagon//obstacle_pentagon_";
			FileName += std::to_string(i + 1);
			FileName += ".png";
			imageUtil.PreLoad(Sprite.Pentagon[i], FileName);
		}

		Global.UserSettingData.Load("GameData//UserSetting", Format.UsetSettingDataFormat);
		Global.FullscreenMode = Global.UserSettingData.LoadDigitData("Option", "FullscreenMode");
		Global.MusicPlayOption = Global.UserSettingData.LoadDigitData("Option", "MusicPlayOption");
		Global.UseMusicEffect = Global.UserSettingData.LoadDigitData("Option", "UseMusicEffect");
		Global.MusicEffectValue = Global.UserSettingData.LoadDigitData("Option", "MusicEffectValue");

		soundUtil.Load(Audio.KeyMoveSound, "Assets//Sound//key_click.wav");
		soundUtil.Load(Audio.KeySelectSound, "Assets//Sound//key_select.wav");
		soundUtil.Load(Audio.OptionSelectSound, "Assets//Sound//option_select.wav");
		soundUtil.Load(Audio.GameStartSound, "Assets//Sound//game_start.wav");

		imageUtil.PreLoad(Sprite.ImagePlayerShape[0], "Assets//Image//Player//triangle.png", IMAGE_TYPE_LINEAR);
		imageUtil.PreLoad(Sprite.ImagePlayerShape[1], "Assets//Image//Player//square.png", IMAGE_TYPE_LINEAR);
		imageUtil.PreLoad(Sprite.ImagePlayerShape[2], "Assets//Image//Player//pentagon.png", IMAGE_TYPE_LINEAR);

		imageUtil.PreLoad(Sprite.ImagePlayerFeedBack, "Assets//Image//Player//feedback.png");

		imageUtil.PreLoad(Sprite.Title, "Assets//Image//UI//title.png", IMAGE_TYPE_LINEAR);

		imageUtil.PreLoad(Sprite.ArrowLeft, "Assets//Image//UI//arrow_left.png", IMAGE_TYPE_LINEAR);
		imageUtil.PreLoad(Sprite.ArrowRight, "Assets//Image//UI//arrow_right.png", IMAGE_TYPE_LINEAR);

		imageUtil.PreLoad(Sprite.Cursor, "Assets//Image//UI//cursor.png", IMAGE_TYPE_LINEAR);

		SysRes.GLU_CIRCLE = gluNewQuadric();
		SysRes.GLU_LINE_CIRCLE = gluNewQuadric();
		gluQuadricDrawStyle(SysRes.GLU_CIRCLE, GLU_FILL);
		gluQuadricDrawStyle(SysRes.GLU_LINE_CIRCLE, GLU_FILL);

		fontUtil.Load(SysRes.SYSTEM_FONT_DIRECTORY, true);

#ifdef USE_CUSTOM_FONT
		int TotalSize = sizeof(FONT_PATH);
		int ElementSize = sizeof(FONT_PATH[0]);
		int Length = TotalSize / ElementSize;
		for (int i = 0; i < Length; ++i)
			fontUtil.Load(FONT_PATH[i], true);
#endif

		return 0;
	}
};

