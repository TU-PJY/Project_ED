#include "ED.h"
#include "Scene.h"

void ClassED::UpdateFunc(float FrameTime) {
	if (scene.Mode() == "HomeMode") {
		BlinkTimer.Update(FrameTime);
		if (!BlinkState && BlinkTimer.CheckSec(2, CHECK_AND_INTERPOLATE)) {
			EDIndex = 1;
			if (Global.NewHighScore[Global.Diff])
				EDIndex = 2;
		}
		else if (BlinkState && BlinkTimer.CheckMiliSec(0.2, 1, CHECK_AND_INTERPOLATE)) {
			EDIndex = 0;
			if (Global.NewHighScore[Global.Diff])
				EDIndex = 3;
		}

		MachinePosition.y = HeightLoop.Update(0.1, 2.0, FrameTime);
	}

	else if (scene.Mode() == "PlayMode" && Global.GameOverState)
		EDIndex = 4;
}

void ClassED::RenderFunc() {
	//Machine Back
	BeginRender(RENDER_TYPE_STATIC);
	transform.Move(TranslateMatrix, MachinePosition);
	transform.Scale(ScaleMatrix, Size, Size);
	RenderSprite(Sprite.MachineBack);

	// ED
	BeginRender(RENDER_TYPE_STATIC);
	transform.Move(TranslateMatrix, MachinePosition);
	transform.Scale(ScaleMatrix, Size, Size);
	RenderSprite(Sprite.ED[EDIndex]);

	// Machine Front
	BeginRender(RENDER_TYPE_STATIC);
	transform.Move(TranslateMatrix, MachinePosition);
	transform.Scale(ScaleMatrix, Size, Size);
	RenderSprite(Sprite.MachineFront);
}
