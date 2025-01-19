#include "PlayerFeedback.h"
#include "Scene.h"

PlayerFeedback::PlayerFeedback() {
	SetColor(1.0, 1.0, 1.0);
}

void PlayerFeedback::UpdateFunc(float FrameTime) {
	Opacity -= FrameTime * 3.0;
	if (Opacity <= 0.0)
		scene.DeleteObject(this);
}

void PlayerFeedback::RenderFunc() {
	BeginRender();
	transform.Scale(ScaleMatrix, 1.5, 1.5);
	RenderSprite(Sprite.ImagePlayerFeedBack, Opacity);
}