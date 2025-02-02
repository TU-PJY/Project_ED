#pragma once
#include "GameObject.h"

class ColorChanger : public GameObject {
private:
	glm::vec3 BackgroundColor[5]{
		{0.02, 0.24, 0.41},
		{0.40, 0.02, 0.26},
		{0.38, 0.07, 0.00},
		{0.08, 0.11, 0.04},
		{0.22, 0.22, 0.22},
	};

	glm::vec3 ObjectColor[5]{
		{0.28, 0.73, 1.0},
		{0.88, 0.24, 0.66},
		{0.96, 0.28, 0.07},
		{0.51, 0.75, 0.26},
		{1.0, 1.0, 1.0}
	};

	glm::vec3 CurrentColor{};

public:
	void UpdateFunc(float FrameTime) {
		mathUtil.UpdateLerp(CurrentColor.x, BackgroundColor[Global.Diff].x, 5.0, FrameTime);
		mathUtil.UpdateLerp(CurrentColor.y, BackgroundColor[Global.Diff].y, 5.0, FrameTime);
		mathUtil.UpdateLerp(CurrentColor.z, BackgroundColor[Global.Diff].z, 5.0, FrameTime);
		System.SetBackColor(CurrentColor.x, CurrentColor.y, CurrentColor.z);

		mathUtil.UpdateLerp(Global.ObjectColor.x, ObjectColor[Global.Diff].x, 5.0, FrameTime);
		mathUtil.UpdateLerp(Global.ObjectColor.y, ObjectColor[Global.Diff].y, 5.0, FrameTime);
		mathUtil.UpdateLerp(Global.ObjectColor.z, ObjectColor[Global.Diff].z, 5.0, FrameTime);
	}
};