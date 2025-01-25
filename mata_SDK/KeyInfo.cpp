#include "KeyInfo.h"

KeyInfo::KeyInfo(int Type) {
	Text.Init(L"에스코어 드림 3 Light", FW_DONTCARE);
	Text.SetColor(1.0, 1.0, 1.0);
	Text.SetHeightAlign(HEIGHT_ALIGN_MIDDLE);

	InfoType = TypeMenuScreen;

	switch (Type) {
	case TypeHomeScreen:
		Speed = 10.0;
		break;

	case TypeMenuScreen:
		Speed = 20.0;
		break;
	}
}

void KeyInfo::UpdateFunc(float FrameTime) {
	if (!ExitState)
		mathUtil.UpdateLerp(Opacity, 1.0, Speed, FrameTime);
	else {
		mathUtil.UpdateLerp(Opacity, 0.0, Speed, FrameTime);
		if (Opacity <= 0.0001)
			scene.DeleteObject(this);
	}
}

void KeyInfo::RenderFunc() {
	SetColor(1.0, 1.0, 1.0);
	Text.SetOpacity(Opacity);

	switch (InfoType) {
	case TypeHomeScreen:
		if (scene.Mode() == "OptionMode")
			break;

		BeginRender(RENDER_TYPE_STATIC);
		transform.Move(TranslateMatrix, WindowRect.lx + 0.15, -0.65);
		transform.Scale(ScaleMatrix, Size, Size);
		RenderSprite(Sprite.ArrowIconLeft, Opacity);

		transform.Move(TranslateMatrix, Size, 0.0);
		RenderSprite(Sprite.ArrowIconRight, Opacity);

		transform.Move(TranslateMatrix, -Size * 0.5, -Size);
		RenderSprite(Sprite.EnterIcon, Opacity);

		transform.Move(TranslateMatrix, 0.0, -Size);
		RenderSprite(Sprite.EscapeIcon, Opacity);

		Text.Render(WindowRect.lx + 0.15 + Size * 2.0, -0.65 + 0.01, 0.05, L"난이도 선택");
		Text.Render(WindowRect.lx + 0.15 + Size * 2.0, -0.65 - Size + 0.01, 0.05, L"잠들기");
		Text.Render(WindowRect.lx + 0.15 + Size * 2.0, -0.65 - Size * 2.0 + 0.01, 0.05, L"메인메뉴");
		break;

	case TypeMenuScreen:
		BeginRender(RENDER_TYPE_STATIC);
		transform.Move(TranslateMatrix, WindowRect.lx + 0.15, -0.65);
		transform.Scale(ScaleMatrix, Size, Size);
		RenderSprite(Sprite.ArrowIconUp, Opacity);

		transform.Move(TranslateMatrix, Size, 0.0);
		RenderSprite(Sprite.ArrowIconDown, Opacity);

		transform.Move(TranslateMatrix, Size, 0.0);
		RenderSprite(Sprite.ArrowIconLeft, Opacity);

		transform.Move(TranslateMatrix, Size, 0.0);
		RenderSprite(Sprite.ArrowIconRight, Opacity);

		transform.Move(TranslateMatrix, -Size * 1.5, -Size);
		RenderSprite(Sprite.EnterIcon, Opacity);

		transform.Move(TranslateMatrix, 0.0, -Size);
		RenderSprite(Sprite.EscapeIcon, Opacity);

		Text.Render(WindowRect.lx + 0.15 + Size * 4.0, -0.65 + 0.01, 0.05, L"이동");
		Text.Render(WindowRect.lx + 0.15 + Size * 2.5, -0.65 - Size + 0.01, 0.05, L"선택");
		Text.Render(WindowRect.lx + 0.15 + Size * 2.5, -0.65 - Size * 2.0 + 0.01, 0.05, L"홈으로 돌아가기");
		break;
	}
}



void KeyInfo::SetExitState() {
	ExitState = true;
	ObjectTag = "";
}
