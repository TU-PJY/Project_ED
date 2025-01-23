#include "PlayScore.h"

PlayScore::PlayScore() {
	Text.Init(L"Ronduit Capitals Light", FW_NORMAL);
	Text.SetAlign(ALIGN_MIDDLE);
	Text.SetHeightAlign(HEIGHT_ALIGN_MIDDLE);
	Text.SetRenderType(RENDER_TYPE_DEFAULT);

	HighScore = Global.HighScore[Global.Diff];
}

void PlayScore::PlusScore() {
	Score += 1;
	if (HighScore > 0 && Score > HighScore)
		OverHighScore = true;
}

void PlayScore::UpdateFunc(float FrameTime) {
	mathUtil.UpdateLerp(Feedback, Global.BeatDetectValue * 0.05, 40.0, FrameTime * Global.PlaySpeed);
	mathUtil.UpdateLerp(Opacity, 1.0, 5.0, FrameTime * Global.PlaySpeed);
	mathUtil.UpdateLerp(Size, 1.0, 5.0, FrameTime * Global.PlaySpeed);
}

void PlayScore::RenderFunc() {
	Text.SetColor(Global.ObjectColor.x, Global.ObjectColor.y, Global.ObjectColor.z);
	if (OverHighScore)
		Text.Render(0.0, -0.4, Size * 0.1 + Feedback * 0.25, L"HIGH SCORE!");
	Text.Render(0.0, -0.7, Size * 0.2 + Feedback, L"%d", Score);
}
