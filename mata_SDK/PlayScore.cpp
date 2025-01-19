#include "PlayScore.h"

PlayScore::PlayScore() {
	Text.Init(L"Exo", FW_BOLD);
	Text.SetColor(0.7, 0.7, 0.7);
	Text.SetAlign(ALIGN_MIDDLE);
	Text.SetHeightAlign(HEIGHT_ALIGN_MIDDLE);
	Text.SetRenderType(RENDER_TYPE_DEFAULT);
}

void PlayScore::PlusScore() {
	Score += 1;
}

void PlayScore::RenderFunc() {
	//if(OverHighScore)
		Text.Render(0.0, -0.5, 0.1, L"HIGH SCORE!");
	//else
		Text.Render(0.0, -0.6, 0.3, L"%d", Score);
}//
