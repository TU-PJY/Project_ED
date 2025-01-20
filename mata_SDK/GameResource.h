#pragma once
#include "SDKHeader.h"

// Declare the sprite resource or directory here. 
class SpriteResource {
public:
	Image Triangle[3]{};
	Image Square[5]{};
	Image Pentagon[5]{};

	Image ImagePlayerShape[3]{};
	Image ImagePlayerFeedBack{};
};

// Declare the sound resource or directory here. 
class AudioResource {
public:

};

// Data Format list
// Write your data format here.
// {  Data Type, Category Name, Data Name, Digit Value, String Value }
class DataFormatResource {
public:

};

// Declare the global value here.
class GlobalValue {
public:
	GLfloat ShapeMoveSpeed{};
	GLfloat ShapeGenerateTime{};
	GLfloat CameraRotateSpeed{};
	GLfloat ElapsedTime{};
	GLfloat PlaySpeed{ 1.0 };

	int Diff{5}; // 1: easy, 2: normal, 3: hard , 4: harder, 5: hardest
	bool RunningState{};
	bool GameOverState{};
};

// Load your custom font.
// USE_CUSTON_FONT must be enabled.
#define USE_CUSTOM_FONT
#ifdef USE_CUSTOM_FONT
constexpr const char* FONT_PATH[]
{
	"Assets//Font//Exo-Light.otf",
	"Assets//Font//Exo-Bold.otf",
	"Assets//Font//SCDream3.otf",
};
#endif

extern SpriteResource Sprite;
extern AudioResource Audio;
extern DataFormatResource Format;
extern GlobalValue Global;