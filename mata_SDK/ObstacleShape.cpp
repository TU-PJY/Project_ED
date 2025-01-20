#include "ObstacleShape.h"
#include "CameraController.h"
#include "PlayerFeedback.h"
#include "ShapeGenerator.h"

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
	if (!DestroyState) {
		CurrentSize -= Global.ShapeMoveSpeed * CurrentSize * FrameTime;
		mathUtil.UpdateLerp(Opacity, 1.0, Global.ShapeMoveSpeed * 5.0, FrameTime);

		if (CurrentSize <= 1.15) {
			if (RotateDirectionChanger)
				CameraControl->ChangeRotateDirection();

			scene.AddObject(new PlayerFeedback, "player_feedback", LAYER1);

			if (auto PlayScore = scene.Find("play_score"); PlayScore)
				PlayScore->PlusScore();

			DestroyState = true;
		}
	}

	else {
		mathUtil.UpdateLerp(CurrentSize, 0.0, 10.0, FrameTime);
		mathUtil.UpdateLerp(Opacity, 0.0, 10.0, FrameTime);
		if (Opacity <= 0.01)
			scene.DeleteObject(this);
	}
}

void ObstacleShape::RenderFunc() {
	BeginRender();
	transform.Rotate(RotateMatrix, Rotation);

	switch (ShapeType) {
	case ObTriangle:
		transform.Scale(ScaleMatrix, CurrentSize + 0.1, CurrentSize + 0.1);
		RenderSprite(Sprite.Triangle[ShapeIndex], Opacity);
		break;

	case ObSquare:
		transform.Scale(ScaleMatrix, CurrentSize - 0.05, CurrentSize - 0.05);
		RenderSprite(Sprite.Square[ShapeIndex], Opacity);
		break;

	case ObPentagon:
		transform.Scale(ScaleMatrix, CurrentSize - 0.1, CurrentSize - 0.1);
		RenderSprite(Sprite.Pentagon[ShapeIndex], Opacity);
		break;
	}
}