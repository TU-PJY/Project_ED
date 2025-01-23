#pragma once
#include "Scene.h"
#include "MouseUtil.h"
#include "CameraController.h"

#include "SpeedManager.h"
#include "ShapeGenerator.h"
#include "PlayScore.h"
#include "PlayerShape.h"

class Play_Mode {
public:
	// define mode name and mode type here
	std::string ModeName { "PlayMode" };
	int         ModeType { MODE_TYPE_DEFAULT };

	// when you activate this option, you can access the camera controller.
	bool        UseCameraController{ true };

	// type object tag to input device event
	std::vector<std::string> InputObjectTag
	{
		"player_shape"
	};

	// this is a container that stores object pointers for accessing object controllers.
	// a pointer to the object corresponding to the tag entered in InputObjectTag is added when the mode starts.
	std::vector<GameObject*> InputObject{};

	/////////////////////////////////////////////////////////////

	static void Start() {
		Global.ElapsedTime = 0.0;
		Global.GameOverState = false;
		Global.PlaySpeed = 1.0;
		CameraControl->ChangeRotation(0.0);
		CameraControl->ResetRotateDirection();

		scene.AddObject(new PlayerShape, "player_shape", LAYER3, OBJECT_TYPE_STATIC);
		scene.AddObject(new SpeedManager, "speed_manager", LAYER1);
		scene.AddObject(new ShapeGenerator, "shape_generator", LAYER1);
		scene.AddObject(new PlayScore, "play_score", LAYER1);
		SetUp();
	}

	static void Destructor() {
	}

    /////////////////////////////////////////////////////////////
	// Adds a control object to the mode.
	void AddControlObject(GameObject* Object) {
		InputObject.emplace_back(Object);
	}

	// Deletes a control object from mode.
	void DeleteControlObject(GameObject* Object) {
		auto Target = std::find(begin(InputObject), end(InputObject), Object);
		if (Target != end(InputObject))
			InputObject.erase(Target);
	}

	/////////////////////////////////////////////////////////////
	// Fold here
#pragma region FoldRegion 
	static Play_Mode* M_Inst;

	Play_Mode() {
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
extern Play_Mode PlayMode;