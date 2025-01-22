#include "PlayerShape.h"
#include "Scene.h"
#include "PauseMode.h"

PlayerShape::PlayerShape() {
	SetColor(1.0, 1.0, 1.0);

	switch (Global.MusicPlayOption) {
	case 0:
		soundUtil.PlaySound(Audio.Track[Global.Diff], Global.TrackChannel, Global.PrevPlayTime[Global.Diff]);
		soundUtil.PlaySound(Audio.Beat[Global.Diff], Global.BeatChannel, Global.PrevPlayTime[Global.Diff]);
		break;

	case 1:
		soundUtil.PlaySound(Audio.Track[Global.Diff], Global.TrackChannel, Global.PrevPlayTime[Global.Diff]);
		soundUtil.PlaySound(Audio.Beat[Global.Diff], Global.BeatChannel, Global.PrevPlayTime[Global.Diff]);
		break;

	case 2:
		Global.PrevPlayTime[Global.Diff] = 0;
		soundUtil.PlaySound(Audio.Track[Global.Diff], Global.TrackChannel);
		soundUtil.PlaySound(Audio.Beat[Global.Diff], Global.BeatChannel, Global.PrevPlayTime[Global.Diff]);
		break;
	}

	soundUtil.SetBeatDetect(Global.BeatChannel);

	switch (Global.Diff) {
	case 0:
		Global.EffectStrength = 1.0;
		break;
	case 1:
		Global.EffectStrength = 1.0;
		break;
	case 2:
		Global.EffectStrength = 1.0;
		break;
	case 3:
		Global.EffectStrength = 1.0;
		break;
	case 4:
		Global.EffectStrength = 1.0;
		break;
	}
}

void PlayerShape::InputKey(KeyEvent& Event) {
	if (Event.Type == SPECIAL_KEY_DOWN) {
		switch (Event.SpecialKey) {
		case SK_ARROW_RIGHT:
			CurrentShape += 1;
			EX.ClampValue(CurrentShape, 2, CLAMP_GREATER);
			ChangeShapeRotationDest();
			break;

		case SK_ARROW_LEFT:
			CurrentShape -= 1;
			EX.ClampValue(CurrentShape, 0, CLAMP_LESS);
			ChangeShapeRotationDest();
			break;
		}
	}

	else if (Event.Type == NORMAL_KEY_DOWN && Event.NormalKey == NK_ESCAPE) {
		Global.PlaySpeed = 0.0;
		soundUtil.PauseSound(Global.TrackChannel, true);
		soundUtil.PauseSound(Global.BeatChannel, true);
		scene.StartFloatingMode(PauseMode.Start);
	}
}

void PlayerShape::ChangeShapeRotationDest() {
	if (PrevShape != CurrentShape) {
		ShapeRotation += (ShapeRotationValue[CurrentShape] - ShapeRotationValue[PrevShape]) * 0.5;
		RotationDest = ShapeRotationValue[CurrentShape];
		PrevShape = CurrentShape;
	}
}

void PlayerShape::UpdateFunc(float FrameTime) {
	// Shape Rotation
	mathUtil.UpdateLerp(ShapeRotation, RotationDest, 35.0, FrameTime * Global.PlaySpeed);

	if (scene.Mode() == "PlayMode") {
		Global.PlaySpeed += FrameTime * 0.5;
		soundUtil.SetPlaySpeed(Global.TrackChannel, Global.PlaySpeed);
		soundUtil.SetPlaySpeed(Global.BeatChannel, Global.PlaySpeed);
		EX.ClampValue(Global.PlaySpeed, 1.0, CLAMP_GREATER);

		Global.PrevPlayTime[Global.Diff] = soundUtil.GetPlayTime(Global.TrackChannel);

		if (Global.UseMusicEffect)
			mathUtil.UpdateLerp(Global.BeatDetectValue, soundUtil.DetectBeat(0.4, 10) * Global.MusicEffectValue * 2.0, 20.0 * Global.PlaySpeed, FrameTime);
	}
}

void PlayerShape::RenderFunc() {
	BeginRender();
	transform.Rotate(RotateMatrix, ShapeRotation);
	transform.Scale(ScaleMatrix, ShapeSize, ShapeSize);
	RenderSprite(Sprite.ImagePlayerShape[CurrentShape]);
	RenderSprite(Sprite.ImagePlayerShapeLight[CurrentShape], 0.8);

	if (Global.UseMusicEffect)
		RenderSprite(Sprite.ImagePlayerShapeLight[CurrentShape], Global.BeatDetectValue);
}