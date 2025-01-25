#pragma once
#include "GameObject.h"
#include "Scene.h"

class Credit : public GameObject {
private:
	TextUtil Text{};
	GLfloat Opacity{};
	std::string CreditString{};

	bool ExitState{};

public:
	Credit() {
		Text.Init(L"에스코어 드림 3 Light", FW_DONTCARE);
		Text.SetColor(1.0, 1.0, 1.0);
		Text.SetAlign(ALIGN_MIDDLE);
		Text.SetHeightAlign(HEIGHT_ALIGN_MIDDLE);
		Text.SetFixMiddle(true);

		CreditString = Global.CreditData.LoadStringData("credit", "data");
	}

	void InputKey(KeyEvent& Event) {
		if (Event.Type == NORMAL_KEY_DOWN) {
			switch (Event.NormalKey) {
			case NK_ENTER: case NK_ESCAPE:
				ExitState = true;
				ObjectTag = "";
				scene.EndFloatingMode();
				break;
			}
		}
	}

	void UpdateFunc(float FrameTime) {
		if (!ExitState)
			mathUtil.UpdateLerp(Opacity, 1.0, 20.0, FrameTime);
		else {
			mathUtil.UpdateLerp(Opacity, 1.0, 20.0, FrameTime);
			if (Opacity <= 0.0001)
				scene.DeleteObject(this);
		}
	}

	void RenderFunc() {
		BeginRender(RENDER_TYPE_STATIC);
		transform.Scale(ScaleMatrix, WindowRect.rx - WindowRect.lx, WindowRect.ry - WindowRect.ly);
		RenderSprite(SysRes.COLOR_TEXTURE, Opacity * 0.8);

		Text.SetOpacity(Opacity);
		Text.Render(0.0, 0.0, 0.2, stringUtil.Wstring(CreditString).c_str());
	}
};