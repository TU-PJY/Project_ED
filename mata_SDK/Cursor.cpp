#include "Cursor.h"
#include "MouseUtil.h"

Cursor::Cursor() {
	SetColor(1.0, 1.0, 1.0);
}

void Cursor::UpdateFunc(float FrameTime) {
}

void Cursor::RenderFunc() {
	BeginRender(RENDER_TYPE_STATIC);
	transform.Move(TranslateMatrix, mouse.x, mouse.y);
	transform.Scale(ScaleMatrix, 0.2, 0.2);
	RenderSprite(Sprite.Cursor);
}
