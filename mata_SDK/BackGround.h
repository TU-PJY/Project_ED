#pragma once
#include "GameObject.h"
#include "Scene.h"

class BackGround : public GameObject {
private:
	GLfloat Opacity{};
	bool ExitState{};

public:
	void UpdateFunc(float FrameTime) {
		if(!ExitState)
			mathUtil.UpdateLerp(Opacity, 1.0, 10.0, FrameTime);
		else {
			mathUtil.UpdateLerp(Opacity, 0.0, 5.0, FrameTime);
			if (Opacity <= 0.001)
				scene.DeleteObject(this);
		}
	}

	void RenderFunc() {
		SetColor(Global.ObjectColor);
		BeginRender(RENDER_TYPE_STATIC);
		transform.Move(TranslateMatrix, 0.0, -0.5);
		transform.Scale(ScaleMatrix, WindowRect.rx - WindowRect.lx, 2.0);
		RenderSprite(Sprite.Gradation, Opacity);
	}

	void SetExitState() {
		ExitState = true;
		ObjectTag = "";
	}
};
