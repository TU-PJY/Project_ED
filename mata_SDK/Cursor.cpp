#include "Cursor.h"
#include "MouseUtil.h"

Cursor::Cursor() {
	SetColor(1.0, 1.0, 1.0);
}

// mouse cursor appear when cursor moves
void Cursor::UpdateFunc(float FrameTime) {
	if (PrevPosition != glm::vec2(mouse.x, mouse.y)) {
		VisibleTimer.Reset();
		PrevPosition = glm::vec2(mouse.x, mouse.y);
		VisibleState = true;
	}

	if (VisibleState) {
		mathUtil.UpdateLerp(Opacity, 1.0, 10.0, FrameTime);

		VisibleTimer.Update(FrameTime);
		if (VisibleTimer.Sec() >= 2)
			VisibleState = false;
	}

	else
		mathUtil.UpdateLerp(Opacity, 0.0, 10.0, FrameTime);
}

void Cursor::RenderFunc() {
	BeginRender(RENDER_TYPE_STATIC);
	transform.Move(TranslateMatrix, mouse.x, mouse.y);
	transform.Scale(ScaleMatrix, 0.2, 0.2);
	RenderSprite(Sprite.Cursor, Opacity);
}
