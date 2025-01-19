#include "PlayerShape.h"

PlayerShape::PlayerShape() {
	SetColor(1.0, 1.0, 1.0);
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
	mathUtil.UpdateLerp(ShapeRotation, RotationDest, 35.0, FrameTime);
}

void PlayerShape::RenderFunc() {
	BeginRender();
	transform.Rotate(RotateMatrix, ShapeRotation);
	transform.Scale(ScaleMatrix, ShapeSize, ShapeSize);
	RenderSprite(Sprite.ImagePlayerShape[CurrentShape]);
}