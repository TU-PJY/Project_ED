#pragma once
#include "GameObject.h"
#include "Scene.h"

class Tutorial : public GameObject {
private:
	GLfloat Opacity{};
	bool ExitState{};
	TextUtil Text{};
	
	GLfloat TutorialOpacity[5]{};
	bool TutorialOpacityWork[5]{};

	TimerUtil Timer{};
	int TutorialIndex{};

	bool ContinueAble{};

public:
	Tutorial() {
		Text.Init(L"�����ھ� �帲 3 Light", FW_DONTCARE);
		Text.SetColor(1.0, 1.0, 1.0);
		Text.SetAlign(ALIGN_MIDDLE);
		Text.SetHeightAlign(HEIGHT_ALIGN_MIDDLE);
	}

	void UpdateFunc(float FrameTime) {
		if (!ExitState) {
			mathUtil.UpdateLerp(Opacity, 1.0, 10.0, FrameTime);
			Timer.Update(FrameTime);

			if (TutorialIndex < 5 && Timer.CheckSec(2, CHECK_AND_INTERPOLATE)) {
				TutorialOpacityWork[TutorialIndex] = true;
				++TutorialIndex;
			}

			for (int i = 0; i < 5; ++i) {
				if (TutorialOpacityWork[i]) {
					TutorialOpacity[i] += FrameTime * 1.5;
					EX.ClampValue(TutorialOpacity[i], 1.0, CLAMP_GREATER);
				}
			}

			if (TutorialOpacity[3] >= 1.0) 
				ContinueAble = true;
		}
		else {
			mathUtil.UpdateLerp(Opacity, 0.0, 10.0, FrameTime);
			if (Opacity <= 0.0001)
				scene.DeleteObject(this);
		}
	}

	void RenderFunc() {
		SetColor(0.1, 0.1, 0.1);
		BeginRender(RENDER_TYPE_STATIC);
		transform.Scale(ScaleMatrix, WindowRect.rx - WindowRect.lx, WindowRect.ry - WindowRect.ly);
		RenderSprite(SysRes.COLOR_TEXTURE, Opacity);

		Text.SetOpacity(TutorialOpacity[0] * Opacity);
		Text.Render(0.0, 0.8, 0.15, L"���� ���� �����ؿ�.");

		Text.SetOpacity(TutorialOpacity[1] * Opacity);
		Text.Render(-0.5, 0.6, 0.07, L"�ٰ����� ������ �ε����� ����\n���� �������� ���߸� �ſ�.");

		Text.SetOpacity(TutorialOpacity[2] * Opacity);
		Text.Render(0.5, 0.6, 0.07, L"���� �ٸ� ������ �ε����� �Ǹ�\n�޿��� ���� �ɰſ���.");

		SetColor(0.0, 0.0, 0.0);
		BeginRender(RENDER_TYPE_STATIC);
		transform.Scale(ScaleMatrix, 1.0, 1.0);
		transform.Move(TranslateMatrix, -0.5, 0.0);
		RenderSprite(Sprite.TutorialImage[0], TutorialOpacity[1] * Opacity);

		BeginRender(RENDER_TYPE_STATIC);
		transform.Scale(ScaleMatrix, 1.0, 1.0);
		transform.Move(TranslateMatrix, 0.5, 0.0);
		RenderSprite(Sprite.TutorialImage[1], TutorialOpacity[2] * Opacity);

		Text.SetOpacity(TutorialOpacity[3] * Opacity);
		Text.Render(0.0, -0.6, 0.1, L"���� �ٲٱ�");

		SetColor(1.0, 1.0, 1.0);

		ResetUnitTransform();
		transform.Move(UnitTranslateMatrix, -0.5, -0.8);

		BeginRender(RENDER_TYPE_STATIC);
		transform.Move(TranslateMatrix, -0.1, 0.0);
		transform.Scale(ScaleMatrix, 0.2, 0.2);
		RenderSprite(Sprite.ArrowIconLeft, TutorialOpacity[3] * Opacity, true);

		transform.Move(TranslateMatrix, 0.2, 0.0);
		RenderSprite(Sprite.ArrowIconRight, TutorialOpacity[3] * Opacity, true);

		Text.Render(0.0, -0.8, 0.1, L"�Ǵ�");


		ResetUnitTransform();
		transform.Move(UnitTranslateMatrix, 0.5, -0.8);

		BeginRender(RENDER_TYPE_STATIC);
		transform.Move(TranslateMatrix, -0.1, 0.0);
		transform.Scale(ScaleMatrix, 0.2, 0.2);
		RenderSprite(Sprite.ShiftIcon, TutorialOpacity[3] * Opacity, true);

		transform.Move(TranslateMatrix, 0.2, 0.0);
		RenderSprite(Sprite.ShiftIcon, TutorialOpacity[3] * Opacity, true);

		BeginRender(RENDER_TYPE_STATIC);
		transform.Move(TranslateMatrix, WindowRect.rx - 0.2, -0.8);
		transform.Scale(ScaleMatrix, 0.2, 0.2);
		RenderSprite(Sprite.EnterIcon, TutorialOpacity[4] * Opacity);

		Text.SetAlign(ALIGN_LEFT);
		Text.SetOpacity(TutorialOpacity[4] * Opacity);
		Text.Render(WindowRect.rx - 0.35, -0.8, 0.07, L"�� ������ �������");
		Text.SetAlign(ALIGN_MIDDLE);
	}

	void SetExitState() {
		ExitState = true;
		ObjectTag = "";
	}

	bool GetContinueAble() {
		return ContinueAble;
	}
};