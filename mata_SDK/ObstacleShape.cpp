#include "ObstacleShape.h"
#include "CameraController.h"

ObstacleShape::ObstacleShape(int Type) {
	SetColor(1.0, 1.0, 1.0);

	ShapeType = Type;

	// direction changer shape has low probability to spawn
	switch (Type) {
	case ObTriangle:
		Rotation = Random.Gen(RANDOM_TYPE_INT, 1, 2) * 120.0;
		ShapeIndex = Random.Gen(RANDOM_TYPE_INT, 0, 6);
		if (ShapeIndex < 6)
			ShapeIndex = Random.Gen(RANDOM_TYPE_INT, 0, 2);
		else {
			ShapeIndex = 2;
			RotateDirectionChanger = true;
		}
		break;

	case ObSquare:
		Rotation = Random.Gen(RANDOM_TYPE_INT, 1, 3) * 90.0;
		ShapeIndex = Random.Gen(RANDOM_TYPE_INT, 0, 10);
		if(ShapeIndex < 10)
			ShapeIndex = Random.Gen(RANDOM_TYPE_INT, 0, 4);
		else {
			ShapeIndex = 4;
			RotateDirectionChanger = true;
		}
		break;

	case ObPentagon:
		Rotation = Random.Gen(RANDOM_TYPE_INT, 1, 4) * 72.0;
		ShapeIndex = Random.Gen(RANDOM_TYPE_INT, 0, 10);
		if (ShapeIndex < 10)
			ShapeIndex = Random.Gen(RANDOM_TYPE_INT, 0, 4);
		else {
			ShapeIndex = 4;
			RotateDirectionChanger = true;
		}
		break;
	}
}

void ObstacleShape::UpdateFunc(float FrameTime) {
	CurrentSize -= Global.ShapeMoveSpeed * CurrentSize * FrameTime;

	if (CurrentSize <= 1.4) {
		if (RotateDirectionChanger)
			CameraControl->ChangeRotateDirection();
		scene.DeleteObject(this);
	}
}

void ObstacleShape::RenderFunc() {
	BeginRender();
	transform.Rotate(RotateMatrix, Rotation);

	switch (ShapeType) {
	case ObTriangle:
		transform.Scale(ScaleMatrix, CurrentSize + 0.1, CurrentSize + 0.1);
		RenderSprite(Sprite.Triangle[ShapeIndex]);
		break;

	case ObSquare:
		transform.Scale(ScaleMatrix, CurrentSize - 0.05, CurrentSize - 0.05);
		RenderSprite(Sprite.Square[ShapeIndex]);
		break;

	case ObPentagon:
		transform.Scale(ScaleMatrix, CurrentSize - 0.1, CurrentSize - 0.1);
		RenderSprite(Sprite.Pentagon[ShapeIndex]);
		break;
	}
}