#include "Nata.h"
#include "CameraController.h"

void ClassNata::UpdateFunc(float FrameTime) {
	if (auto Ptr = scene.Find("ED"); Ptr)
		ED = Ptr;

	if (scene.Mode() == "HomeMode" || scene.Mode() == "OptionMode") {
		mathUtil.UpdateLerp(Position.y, ED->GetPosition().y + 0.4, 3.0, FrameTime);
		mathUtil.UpdateLerp(Position.x, -0.5, 5.0, FrameTime);
		mathUtil.UpdateLerp(MovePosition.y, 0.0, 10.0, FrameTime);

		if (!Global.NewHighScore[Global.Diff])
			Index = 0;
		else
			Index = 1;
	}

	else if (scene.Mode() == "PlayMode") {
		mathUtil.UpdateLerp(Position.x, -2.5, 10.0, FrameTime * Global.PlaySpeed);
		mathUtil.UpdateLerp(Position.y, ED->GetPosition().y + 1.5, 10.0, FrameTime * Global.PlaySpeed);
		MovePosition.y = MoveLoop.Update(0.5, 1.0, FrameTime * Global.PlaySpeed);

		if (Global.GameOverState) {
			ShakePosition = -CameraControl->GetShakePosition();
			Index = 2;
		}
	}
}

void ClassNata::RenderFunc() {
	BeginRender(RENDER_TYPE_STATIC);
	if (scene.Mode() == "OptionMode" || scene.Mode() == "PauseMode")
		SetBlur(2.0);
	transform.Scale(TranslateMatrix, ED->GetSize() * 0.4 + (camera.ZoomValue - 1.0) * 0.5, ED->GetSize() * 0.4 + (camera.ZoomValue - 1.0) * 0.5);
	transform.Move(TranslateMatrix, Position + MovePosition + ShakePosition);
	RenderSprite(Sprite.Nata[Index]);
}
