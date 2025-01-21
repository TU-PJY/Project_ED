#include "PlayScore.h"

PlayScore::PlayScore() {
	Text.Init(L"Ronduit Capitals Light", FW_NORMAL);
	Text.SetColor(0.7, 0.7, 0.7);
	Text.SetAlign(ALIGN_MIDDLE);
	Text.SetHeightAlign(HEIGHT_ALIGN_MIDDLE);
	Text.SetRenderType(RENDER_TYPE_DEFAULT);
}

void PlayScore::PlusScore() {
	Score += 1;
	Feedback = 0.2;
}

void PlayScore::UpdateFunc(float FrameTime) {
	mathUtil.UpdateLerp(Feedback, 0.0, 5.0, FrameTime);
}

void PlayScore::RenderFunc() {
	if (OverHighScore)
		Text.Render(0.0, -0.4, 0.1 + Feedback * 0.25, L"HIGH SCORE!");
	Text.Render(0.0, -0.7, 0.2 + Feedback, L"%d", Score);
}
