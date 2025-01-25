#include "ED.h"
#include "Scene.h"
#include "CameraController.h"

void ClassED::UpdateFunc(float FrameTime) {
	if (scene.Mode() == "HomeMode" || scene.Mode() == "OptionMode" || scene.Mode() == "CreditMode") {
		if (EDIndex == 4)
			EDIndex = 0;

		if (Global.NewHighScore[Global.Diff])
			SmileState = true;
		else
			SmileState = false;

		BlinkTimer.Update(FrameTime);
		// normal -> blink
		if ((EDIndex == 0) && BlinkTimer.CheckSec(3, CHECK_AND_INTERPOLATE)) 
			EDIndex = 1;

		// blink -> normal
		else if ((EDIndex == 1) && BlinkTimer.CheckMiliSec(0.3, 1, CHECK_AND_INTERPOLATE)) 
			EDIndex = 0;
		
		mathUtil.UpdateLerp(Size, 1.2, 5.0, FrameTime);
		mathUtil.UpdateLerp(MachinePosition.y, -0.1, 5.0, FrameTime);
		mathUtil.UpdateLerp(CamRotation, 0.0, 10.0, FrameTime);
		mathUtil.UpdateLerp(SmileRotation, DestSmileRotation, 10.0, FrameTime);
		mathUtil.UpdateLerp(MusicEffectValue, 0.0, 10.0, FrameTime);

		mathUtil.UpdateLerp(Position.y, MovePosition.y + MachinePosition.y, 3.0, FrameTime);
		mathUtil.UpdateLerp(EDRotation, DestSmileRotation, 3.0, FrameTime);

		MovePosition.y = HeightLoop.Update(0.03, 2.0, FrameTime);
		DestSmileRotation = RotationLoop.Update(6.0, 1.0, FrameTime);

		if (!SmileState)
			DestSmileRotation = 0.0;
	}

	else if (scene.Mode() == "PlayMode") {
		SmileState = false;
		RotationLoop.Reset();
		mathUtil.UpdateLerp(Position.y, MachinePosition.y, 10.0, FrameTime * Global.PlaySpeed);
		mathUtil.UpdateLerp(Size, 0.4, 10.0, FrameTime * Global.PlaySpeed);
		mathUtil.UpdateLerp(MachinePosition.y, 0.0, 10.0, FrameTime * Global.PlaySpeed);
		mathUtil.UpdateLerp(SmileRotation, 0.0, 10.0, FrameTime * Global.PlaySpeed);
		mathUtil.UpdateLerp(EDRotation, 0.0, 10.0, FrameTime * Global.PlaySpeed);
		mathUtil.UpdateLerp(MovePosition.y, 0.0, 10.0, FrameTime * Global.PlaySpeed);

		CamRotation = CameraControl->GetRotation();
		MusicEffectValue = Global.BeatDetectValue * 0.05;

		if (Global.GameOverState) 
			EDIndex = 4;
		else
			EDIndex = 1;
	}
}

void ClassED::RenderFunc() {
	ResetUnitTransform();
	transform.Move(UnitTranslateMatrix, MovePosition + MachinePosition);
	transform.Rotate(UnitRotateMatrix, CamRotation + SmileRotation); 
	transform.Scale(UnitScaleMatrix, Size + MusicEffectValue + (camera.ZoomValue - 1.0) * 0.5, Size + MusicEffectValue + (camera.ZoomValue - 1.0) * 0.5);
	{
		//Machine Back
		BeginRender(RENDER_TYPE_STATIC);
		RenderSprite(Sprite.MachineBack, 1.0, true);

		// ED, not apply unit transform
		BeginRender(RENDER_TYPE_STATIC);
		transform.Move(TranslateMatrix, Position);
		transform.Rotate(RotateMatrix, CamRotation + EDRotation);
		transform.Scale(ScaleMatrix, Size + MusicEffectValue + (camera.ZoomValue - 1.0) * 0.5, Size + MusicEffectValue + (camera.ZoomValue - 1.0) * 0.5);
		if(!SmileState)
			RenderSprite(Sprite.ED[EDIndex]);
		else
			RenderSprite(Sprite.ED[EDIndex + 2]);

		// Machine Front
		BeginRender(RENDER_TYPE_STATIC);
		RenderSprite(Sprite.MachineFront, 1.0, true);

		// Machine Light
		BeginRender(RENDER_TYPE_STATIC);
		RenderSprite(Sprite.MachineLight, Global.BeatDetectValue, true);
	}
}

glm::vec2 ClassED::GetPosition() {
	return MachinePosition + MovePosition;
}

GLfloat ClassED::GetSize() {
	return Size;
}