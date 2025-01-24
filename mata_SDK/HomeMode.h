﻿#pragma once
#include "Scene.h"
#include "MouseUtil.h"
#include "CameraController.h"

#include "HomeScreen.h"
#include "ColorChanger.h"
#include "ED.h"
#include "Nata.h"

class Home_Mode {
public:
	std::string ModeName{ "HomeMode" };
	int         ModeType{ MODE_TYPE_DEFAULT };

	bool        UseCameraController{ false };

	std::vector<std::string> InputObjectTag
	{
		"home_screen"
	};

	std::vector<GameObject*> InputObject{};

	/////////////////////////////////////////////////////////////

	static void Start() {
		System.HideCursor();

		if(auto Changer = scene.Find("color_changer"); !Changer)
			scene.AddObject(new ColorChanger, "color_changer", LAYER1, OBJECT_TYPE_STATIC);

		if (auto ED = scene.Find("ED"); !ED)
			scene.AddObject(new ClassED, "ED", LAYER2, OBJECT_TYPE_STATIC);

		if (auto Nata = scene.Find("Nata"); !Nata)
			scene.AddObject(new ClassNata, "Nata", LAYER4, OBJECT_TYPE_STATIC);

		scene.AddObject(new HomeScreen, "home_screen", LAYER5, OBJECT_TYPE_STATIC);
		SetUp();
	}

	static void Destructor() {

	}

	/////////////////////////////////////////////////////////////

	void AddControlObject(GameObject* Object) {
		InputObject.emplace_back(Object);
	}

	void DeleteControlObject(GameObject* Object) {
		auto Target = std::find(begin(InputObject), end(InputObject), Object);
		if (Target != end(InputObject))
			InputObject.erase(Target);
	}

	/////////////////////////////////////////////////////////////
	// Fold here
#pragma region FoldRegion 
	static Home_Mode* M_Inst;

	Home_Mode() {
		M_Inst = this;
	}

	static void SetUp() {
		M_Inst->InputObject.clear();

		for (auto const& Tag : M_Inst->InputObjectTag) {
			if (auto Object = scene.Find(Tag); Object)
				M_Inst->InputObject.emplace_back(Object);
		}

		if (M_Inst->UseCameraController)
			M_Inst->InputObject.emplace_back(CameraControl);

		scene.RegisterModeName(M_Inst->ModeName);
		scene.RegisterDestructor(Destructor);
		scene.RegisterController(Controller, M_Inst->ModeType);
	}

	static void ProcessKeyEvent(KeyEvent& Event) {
		for (auto const& Object : M_Inst->InputObject)
			if (Object)  Object->InputKey(Event);
	}

	static void KeyDown(unsigned char KEY, int X, int Y) {
#ifdef ENABLE_DEV_EXIT
		if (KEY == NK_ESCAPE)
			System.Exit();
#endif
		KeyEvent Event{ NORMAL_KEY_DOWN, KEY, NULL };
		ProcessKeyEvent(Event);
	}

	static void KeyUp(unsigned char KEY, int X, int Y) {
		KeyEvent Event{ NORMAL_KEY_UP, KEY, NULL };
		ProcessKeyEvent(Event);
	}

	static void SpecialKeyDown(int KEY, int X, int Y) {
		KeyEvent Event{ SPECIAL_KEY_DOWN, NULL, KEY };
		ProcessKeyEvent(Event);
	}

	static void SpecialKeyUp(int KEY, int X, int Y) {
		KeyEvent Event{ SPECIAL_KEY_UP, NULL, KEY };
		ProcessKeyEvent(Event);
	}

	static void MouseMotion(int X, int Y) {
		mouse.ConvertPosition(X, Y);
	}

	static void MousePassiveMotion(int X, int Y) {
		mouse.ConvertPosition(X, Y);
	}

	static void MouseWheel(int Button, int Wheel, int X, int Y) {
		int WheelEvent{};

		if (Wheel > 0)
			WheelEvent = WHEEL_UP;
		else if (Wheel < 0)
			WheelEvent = WHEEL_DOWN;

		for (auto const& Object : M_Inst->InputObject)
			if (Object)  Object->InputScroll(WheelEvent);
	}

	static void MouseButton(int Button, int State, int X, int Y) {
		int ButtonEvent{};

		switch (State) {
		case GLUT_DOWN:
			switch (Button) {
			case GLUT_LEFT_BUTTON:
				ButtonEvent = LEFT_BUTTON_DOWN;   break;
			case GLUT_RIGHT_BUTTON:
				ButtonEvent = RIGHT_BUTTON_DOWN;  break;
			case GLUT_MIDDLE_BUTTON:
				ButtonEvent = MIDDLE_BUTTON_DOWN; break;
			}
			break;

		case GLUT_UP:
			switch (Button) {
			case GLUT_LEFT_BUTTON:
				ButtonEvent = LEFT_BUTTON_UP;   break;
			case GLUT_RIGHT_BUTTON:
				ButtonEvent = RIGHT_BUTTON_UP;  break;
			case GLUT_MIDDLE_BUTTON:
				ButtonEvent = MIDDLE_BUTTON_UP; break;
			}
			break;
		}

		for (auto const& Object : M_Inst->InputObject)
			if (Object)  Object->InputMouse(ButtonEvent);
	}

	static void Controller() {
		glutMotionFunc(MouseMotion);
		glutPassiveMotionFunc(MousePassiveMotion);
		glutKeyboardFunc(KeyDown);
		glutKeyboardUpFunc(KeyUp);
		glutMouseWheelFunc(MouseWheel);
		glutMouseFunc(MouseButton);
		glutSpecialFunc(SpecialKeyDown);
		glutSpecialUpFunc(SpecialKeyUp);
	}
#pragma endregion
};
extern Home_Mode HomeMode;