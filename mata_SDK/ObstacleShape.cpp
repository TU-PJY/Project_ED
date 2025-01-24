#include "ObstacleShape.h"
#include "CameraController.h"
#include "PlayerFeedback.h"
#include "ShapeGenerator.h"
#include "HomeMode.h"
#include "PlayerShape.h"

ObstacleShape::ObstacleShape(int Type) {
	SetColor(1.0, 1.0, 1.0);

	ShapeType = Type;

	bool VariationGenerate{};

	if (Global.Diff == 1 && Global.ElapsedTime >= 20.0) 
		VariationGenerate = true;
	
	else if (Global.Diff > 1)
		VariationGenerate = true;

	// direction changer shape has low probability to spawn
	// if direction changer shape destroied, it changes camera rotate direction
	switch (Type) {
	case ObTriangle:
		if (VariationGenerate) {
			Rotation = Random.Gen(RANDOM_TYPE_INT, 1, 2) * 120.0;
			ShapeIndex = Random.Gen(RANDOM_TYPE_INT, 0, 7);
			if (ShapeIndex < 7)
				ShapeIndex = Random.Gen(RANDOM_TYPE_INT, 0, 1);
			else {
				ShapeIndex = 2;
				RotateDirectionChanger = true;
			}
		}
		break;

	case ObSquare:
		if (VariationGenerate) {
			Rotation = Random.Gen(RANDOM_TYPE_INT, 1, 3) * 90.0;
			ShapeIndex = Random.Gen(RANDOM_TYPE_INT, 0, 7);
			if (ShapeIndex < 7)
				ShapeIndex = Random.Gen(RANDOM_TYPE_INT, 0, 3);
			else {
				ShapeIndex = 4;
				RotateDirectionChanger = true;
			}
		}
		break;

	case ObPentagon:
		if (VariationGenerate) {
			Rotation = Random.Gen(RANDOM_TYPE_INT, 1, 4) * 72.0;
			ShapeIndex = Random.Gen(RANDOM_TYPE_INT, 0, 7);
			if (ShapeIndex < 7)
				ShapeIndex = Random.Gen(RANDOM_TYPE_INT, 0, 3);
			else {
				ShapeIndex = 4;
				RotateDirectionChanger = true;
			}
		}
		break;
	}
}

void ObstacleShape::UpdateFunc(float FrameTime) {
	if (!ExitReady) {
		if (!DestroyState) {
			CurrentSize -= Global.ShapeMoveSpeed * CurrentSize * FrameTime * Global.PlaySpeed;
			mathUtil.UpdateLerp(Opacity, 1.0, Global.ShapeMoveSpeed * 5.0, FrameTime * Global.PlaySpeed);

			if (CurrentSize <= 1.15) {
				if (PlayerShapePtr) {
					if (PlayerShapePtr->GetCurrentShape() != ShapeType) {
						//CameraControl->AddShakeValue(0.1);

						Global.GameOverState = true;
						Focused = true;
						ExitReady = true;

						Global.PlaySpeed = 0.0;
						scene.SwapLayer(this, LAYER3);

						for (int i = 0; i < scene.LayerSize(LAYER2); ++i) {
							if (auto Object = scene.FindMulti("obstacle_shape", LAYER2, i); Object)
								Object->SetExitReady();
						}

						soundUtil.PlaySound(Audio.GameOverSound, Ch);

						Global.PrevPlayTime[Global.Diff] = soundUtil.GetPlayTime(Global.TrackChannel);
						soundUtil.StopSound(Global.TrackChannel);
						soundUtil.StopSound(Global.BeatChannel);
						return;
					}
				}

				if (RotateDirectionChanger)
					CameraControl->ChangeRotateDirection();

				scene.AddObject(new PlayerFeedback, "player_feedback", LAYER1);

				if (auto PlayScore = scene.Find("play_score"); PlayScore)
					PlayScore->PlusScore();

				DestroyState = true;
			}
		}

		else {
			mathUtil.UpdateLerp(CurrentSize, 0.0, 10.0, FrameTime * Global.PlaySpeed);
			mathUtil.UpdateLerp(Opacity, 0.0, 10.0, FrameTime * Global.PlaySpeed);
			if (Opacity <= 0.01)
				scene.DeleteObject(this);
		}
	}

	// game over
	else {
		if (Focused) {
			GameOverTimer.Update(FrameTime);
			if (GameOverTimer.Sec() >= 1 && !ExitState) {
				if (PlayerShapePtr)
					PlayerShapePtr->SetExitState();

				for (int i = 0; i < scene.LayerSize(LAYER2); ++i) {
					if (auto Object = scene.FindMulti("obstacle_shape", LAYER2, i); Object)
						Object->SetExitState();
				}

				SetExitState();
				scene.SwitchMode(HomeMode.Start);
			}

			if (FlickerCount < 6) {
				FlickerTimer.Update(FrameTime);
				if (FlickerTimer.CheckMiliSec(0.1, 1, CHECK_AND_INTERPOLATE)) {
					EX.SwitchBool(Flicker);
					++FlickerCount;
				}
			}
		}
	}

	if (ExitState)
		ExitToHome(FrameTime);
}

void ObstacleShape::RenderFunc() {
	if (Focused) {
		if(Flicker)
			if(Global.Diff == 2)
				SetColor(1.0, 1.0, 0.0);
			else
				SetColor(1.0, 0.0, 0.0);
		else
			SetColor(Global.ObjectColor);
	}

	else 
		SetColor(Global.ObjectColor);

	BeginRender();
	transform.Rotate(RotateMatrix, Rotation);

	switch (ShapeType) {
	case ObTriangle:
		transform.Scale(ScaleMatrix, CurrentSize + 0.3, CurrentSize + 0.3);
		RenderSprite(Sprite.Triangle[ShapeIndex], Opacity);
		break;

	case ObSquare:
		transform.Scale(ScaleMatrix, CurrentSize + 0.15, CurrentSize + 0.15);
		RenderSprite(Sprite.Square[ShapeIndex], Opacity);
		break;

	case ObPentagon:
		transform.Scale(ScaleMatrix, CurrentSize + 0.1, CurrentSize + 0.1);
		RenderSprite(Sprite.Pentagon[ShapeIndex], Opacity);
		break;
	}
}

void ObstacleShape::ExitToHome(float FrameTime) {
	CurrentSize += CurrentSize * FrameTime * 4.0;
	Opacity -= FrameTime * 3.0;
	if (Opacity <= 0.0)
		scene.DeleteObject(this);
}

void ObstacleShape::SetExitState() {
	ObjectTag = "";
	ExitState = true;
}

void ObstacleShape::SetExitReady() {
	ExitReady = true;
}
