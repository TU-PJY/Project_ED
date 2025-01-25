#pragma once
#include "GameObject.h"
#include "Scene.h"

class Tutorial : public GameObject {
private:
	GLfloat Opacity{};
	bool ExitState{};
	TextUtil Text{};
	
	GLfloat TutorialOpacity[4]{};
	bool TutortialOpacityWork[4]{};

	TimerUtil Timer{};
	int TutorialIndex{};

public:
	Tutorial() {
		Text.Init(L"에스코어 드림 3 Light", FW_DONTCARE);
		Text.SetColor(1.0, 1.0, 1.0);
		Text.SetAlign(ALIGN_MIDDLE);
		Text.SetHeightAlign(HEIGHT_ALIGN_MIDDLE);
	}

	void UpdateFunc(float FrameTime) {
		if (!ExitState) {
			mathUtil.UpdateLerp(Opacity, 1.0, 10.0, FrameTime);
			Timer.Update(FrameTime);

			if (TutorialIndex < 4 && Timer.CheckSec(2, CHECK_AND_INTERPOLATE)) {
				TutortialOpacityWork[TutorialIndex] = true;
				++TutorialIndex;
			}

			for (int i = 0; i < 4; ++i) {
				if (TutortialOpacityWork[i]) {
					TutorialOpacity[i] += FrameTime * 1.5;
					EX.ClampValue(TutorialOpacity[i], 1.0, CLAMP_GREATER);
				}
			}
		}
		else {
			mathUtil.UpdateLerp(Opacity, 0.0, 10.0, FrameTime);
			if (Opacity <= 0.0001)
				scene.DeleteObject(this);
		}
	}

	void RenderFunc() {
		SetColor(0.0, 0.0, 0.0);
		BeginRender(RENDER_TYPE_STATIC);
		transform.Scale(ScaleMatrix, WindowRect.rx - WindowRect.lx, WindowRect.ry - WindowRect.ly);
		RenderSprite(SysRes.COLOR_TEXTURE, Opacity);

		Text.SetOpacity(TutorialOpacity[0] * Opacity);
		Text.Render(0.0, 0.8, 0.15, L"꿈은 아주 간단해요.");

		Text.SetOpacity(TutorialOpacity[1] * Opacity);
		Text.Render(-0.5, 0.6, 0.07, L"다가오는 도형과 부딪히기 전에\n같은 도형으로 맞추면 돼요.");

		Text.SetOpacity(TutorialOpacity[2] * Opacity);
		Text.Render(0.5, 0.6, 0.07, L"만약 다른 도형과 부딪히게 되면\n꿈에서 깨게 될거예요.");

		BeginRender(RENDER_TYPE_STATIC);
		transform.Scale(ScaleMatrix, 1.0, 1.0);
		transform.Move(TranslateMatrix, -0.5, 0.0);
		RenderSprite(Sprite.TutorialImage[0], TutorialOpacity[1] * Opacity);

		BeginRender(RENDER_TYPE_STATIC);
		transform.Scale(ScaleMatrix, 1.0, 1.0);
		transform.Move(TranslateMatrix, 0.5, 0.0);
		RenderSprite(Sprite.TutorialImage[1], TutorialOpacity[2] * Opacity);

		Text.SetOpacity(TutorialOpacity[3] * Opacity);
		Text.Render(0.0, -0.6, 0.1, L"도형 바꾸기");

		SetColor(1.0, 1.0, 1.0);

		ResetUnitTransform();
		transform.Move(UnitTranslateMatrix, -0.5, -0.8);

		BeginRender(RENDER_TYPE_STATIC);
		transform.Move(TranslateMatrix, -0.1, 0.0);
		transform.Scale(ScaleMatrix, 0.2, 0.2);
		RenderSprite(Sprite.ArrowIconLeft, TutorialOpacity[3] * Opacity, true);

		transform.Move(TranslateMatrix, 0.2, 0.0);
		RenderSprite(Sprite.ArrowIconRight, TutorialOpacity[3] * Opacity, true);

		Text.Render(0.0, -0.8, 0.1, L"또는");


		ResetUnitTransform();
		transform.Move(UnitTranslateMatrix, 0.5, -0.8);

		BeginRender(RENDER_TYPE_STATIC);
		transform.Move(TranslateMatrix, -0.1, 0.0);
		transform.Scale(ScaleMatrix, 0.2, 0.2);
		RenderSprite(Sprite.ShiftIcon, TutorialOpacity[3] * Opacity, true);

		transform.Move(TranslateMatrix, 0.2, 0.0);
		RenderSprite(Sprite.ShiftIcon, TutorialOpacity[3] * Opacity, true);
	}

	void SetExitState() {
		ExitState = true;
		ObjectTag = "";
	}
};