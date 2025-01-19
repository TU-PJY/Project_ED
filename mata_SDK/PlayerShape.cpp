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
			break;

		case SK_ARROW_LEFT:
			CurrentShape -= 1;
			EX.ClampValue(CurrentShape, 0, CLAMP_LESS);
			break;
		}
	}
}

void PlayerShape::UpdateFunc(float FrameTime) {

}

void PlayerShape::RenderFunc() {
	BeginRender();
	transform.Scale(ScaleMatrix, ShapeSize, ShapeSize);

	switch (CurrentShape) {
	case Triangle:
		RenderSprite(Sprite.Triangle[0]);
		break;

	case Square:
		RenderSprite(Sprite.Square[0]);
		break;

	case Pentagon:
		RenderSprite(Sprite.Pentagon[0]);
		break;
	}
}
