#pragma once
#include "GameObject.h"
#include "Scene.h"

class Dot : public GameObject {
private:
	glm::vec2 Position{};
	GLfloat Opacity{1.5};
	GLfloat Speed{};
	bool ExitState{};

	RandomUtil Random{};

public:
	Dot() {
		Position.x = Random.Gen(RANDOM_TYPE_REAL, WindowRect.lx + 0.05, WindowRect.rx - 0.05);
		Position.y = -1.15;
		Speed = Random.Gen(RANDOM_TYPE_REAL, 0.3, 1.0);
	}

	void UpdateFunc(float FrameTime) {
		if (!ExitState) {
			Opacity -= FrameTime * 0.4;
			Position.y += FrameTime * Speed;
		}
		else 
			mathUtil.UpdateLerp(Opacity, 0.0, 5.0, FrameTime);
		
		if (Opacity <= 0.0001)
			scene.DeleteObject(this);
	}

	void RenderFunc() {
		SetColor(Global.ObjectColor);
		BeginRender(RENDER_TYPE_STATIC);
		transform.Move(TranslateMatrix, Position);
		transform.Scale(ScaleMatrix, 0.1, 0.1);
		RenderSprite(Sprite.Dot, Opacity);
	}

	void SetExitState() {
		ExitState = true;
		ObjectTag = "";
	}
};