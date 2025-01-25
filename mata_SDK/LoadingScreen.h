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
	HANDLE  SystemResourceLoadHandle{};
	HANDLE  UserResourceLoadHandle{};
	GLfloat Rotation{};
	GLfloat SpinnerOpacity{1.0};
	bool    LoadStartCommand{};
	bool    SystemResourceLoadEnd{};
	bool    UserResourceLoadEnd{};

	TextUtil Text{};

	GLfloat Position{};

public:
	LoadingScreen() {
		Text.Init(L"에스코어 드림 3 Light", FW_DONTCARE);
		Text.SetAlign(ALIGN_MIDDLE);
		Text.SetHeightAlign(HEIGHT_ALIGN_MIDDLE);
		Text.SetColor(1.0, 1.0, 1.0);

		Position = WindowRect.lx - 0.75;
	}

	void InputKey(KeyEvent& Event) {
#ifdef ENABLE_DEV_EXIT
		if (Event.Type == NORMAL_KEY_DOWN) {
			if (Event.NormalKey == NK_ESCAPE)
				System.Exit();
		}
#endif
	}

	void UpdateFunc(float FrameTime) {
		if (LoadStartCommand) {
			Rotation -= 200 * FrameTime;
			Position += FrameTime * 2.0;
			if (Position >= WindowRect.rx + 0.75)
				Position = WindowRect.lx - 0.75;

			if (!threadUtil.IsRunning(SystemResourceLoadHandle) && !SystemResourceLoadEnd) {
				threadUtil.Close(SystemResourceLoadHandle);
				threadUtil.Create(UserResourceLoadHandle, ResourceLoader);
				SystemResourceLoadEnd = true;
			}

			if (!threadUtil.IsRunning(UserResourceLoadHandle) && !UserResourceLoadEnd) {
				threadUtil.Close(UserResourceLoadHandle);
				UserResourceLoadEnd = true;
			}

			if(SystemResourceLoadEnd && UserResourceLoadEnd) {
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
					SpinnerOpacity -= FrameTime;

					if (EX.CheckClampValue(SpinnerOpacity, 0.0, CLAMP_LESS)) {
						Global.FullscreenMode = (int)Global.UserSettingData.LoadDigitData("Option", "FullscreenMode");
						if (Global.FullscreenMode == 1)
							System.SwitchScreenState();

						else {
							RECT WorkArea;

							if (SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkArea, 0)) {
								int AREA_H = WorkArea.right - WorkArea.left;
								int AREA_V = WorkArea.bottom - WorkArea.top;
								WIDTH = AREA_H;
								HEIGHT = AREA_V;
								glutReshapeWindow(WIDTH, HEIGHT);
								glutPositionWindow(0, 0);
							}
						}

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
			threadUtil.Create(SystemResourceLoadHandle, SystemResourceCreateThread);

			LoadStartCommand = true;
		}
	}

	void RenderFunc() {
		SetColor(0.0, 0.0, 0.0);
		BeginRender(RENDER_TYPE_STATIC);
		transform.Move(TranslateMatrix, Position, 0.0);
		transform.Scale(ScaleMatrix, 1.5, 1.5);
		transform.Rotate(RotateMatrix, Rotation);
		RenderSprite(SysRes.LOADING_SPINNER, SpinnerOpacity);

		Text.SetOpacity(SpinnerOpacity);
		Text.Render(0.0, -0.9, 0.1, L"리소스 로드 중... 데굴데굴 데구르르....");
	}

	static DWORD WINAPI SystemResourceCreateThread(LPVOID Param) {
#ifdef USE_SOUND_SYSTEM
		soundUtil.Load(SysRes.INTRO_SOUND, SysRes.SDK_LOGO_SOUND_DIRECTORY, FMOD_DEFAULT);
#endif

		imageUtil.PreLoad(SysRes.SDK_LOGO, SysRes.SDK_LOGO_IMAGE_DIRECTORY, IMAGE_TYPE_LINEAR);
		imageUtil.PreLoad(SysRes.SDK_LOGO_ERROR, SysRes.SDK_LOGO_ERROR_IMAGE_DIRECTORY, IMAGE_TYPE_LINEAR);
		imageUtil.PreLoad(SysRes.FMOD_LOGO, SysRes.FMOD_LOGO_DIRECTORY, IMAGE_TYPE_LINEAR);
		imageUtil.PreLoad(SysRes.COLOR_TEXTURE, SysRes.COLOR_TEXTURE_DIRECTORY);

		SysRes.GLU_CIRCLE = gluNewQuadric();
		SysRes.GLU_LINE_CIRCLE = gluNewQuadric();
		gluQuadricDrawStyle(SysRes.GLU_CIRCLE, GLU_FILL);
		gluQuadricDrawStyle(SysRes.GLU_LINE_CIRCLE, GLU_FILL);

		fontUtil.Load(SysRes.SYSTEM_FONT_DIRECTORY, true);

		return 0;
	}
};

