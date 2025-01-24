#pragma once
#include "SDKHeader.h"
#include "FileUtil.h"
#include "SoundUtil.h"
#include "ImageUtil.h"
#include "FontUtil.h"

// Declare the sprite resource or directory here. 
class SpriteResource {
public:
	Image Triangle[3]{};
	Image Square[5]{};
	Image Pentagon[5]{};

	Image ImagePlayerShape[3]{};
	Image ImagePlayerShapeLight[3]{};
	Image ImagePlayerFeedBack{};

	Image Title{};
	Image ArrowRight{}, ArrowLeft{};

	Image HighLight{};

	Image ED[5]{};
	Image Nata[5]{};
	Image MachineFront{};
	Image MachineBack{};
	Image MachineLight{};
};

// Declare the sound resource or directory here. 
class AudioResource {
public:
	Sound KeyMoveSound{};
	Sound KeySelectSound{};
	Sound OptionSelectSound{};
	Sound GameStartSound{};
	Sound GameExitSound{};

	Sound Track[5]{};
	Sound Beat[5]{};
	Sound HomeBGM{};
	Sound GameOverSound{};
};

// Data Format list
// Write your data format here.
// {  Data Type, Category Name, Data Name, Digit Value, String Value }
class DataFormatResource {
public:
	DataFormat HighScoreDataFormat = {
		{DATA_TYPE_DIGIT, "HighScore", "EasyModeHighScore", 0.0, ""},
		{DATA_TYPE_DIGIT, "HighScore", "NormalModeHighScore", 0.0, ""},
		{DATA_TYPE_DIGIT, "HighScore", "HardModeHighScore", 0.0, ""},
		{DATA_TYPE_DIGIT, "HighScore", "HarderModeHighScore", 0.0, ""},
		{DATA_TYPE_DIGIT, "HighScore", "HardestModeHighScore", 0.0, ""},
	};

	DataFormat UsetSettingDataFormat = {
		{DATA_TYPE_DIGIT, "Option", "FullscreenMode", 1.0, ""},
		{DATA_TYPE_DIGIT, "Option", "MusicPlayOption", 0, ""},
		{DATA_TYPE_DIGIT, "Option", "UseMusicEffect", 1.0, ""},
		{DATA_TYPE_DIGIT, "Option", "MusicEffectValue", 1.0, ""},
	};
};

// Declare the global value here.
class GlobalValue {
public:
	GLfloat ShapeMoveSpeed{};
	GLfloat ShapeGenerateTime{};
	GLfloat CameraRotateSpeed{};
	GLfloat ElapsedTime{};
	GLfloat PlaySpeed{ 1.0 };

	// object color
	glm::vec3 ObjectColor{};

	// gmae
	int Diff{ 0 }; // 0: easy, 1: normal, 2: hard , 3: harder, 4: hardest
	bool GameOverState{};

	// score
	int CurrentScore{};
	bool NewHighScore[5]{};
	int HighScore[5]{}; // 0: easy, 1: normal, 2: hard, 3: harder, 4: hardest
	FileUtil HighScoreData{};

	// user settings
	int FullscreenMode{}; // 0: windowded, 1: fullscreen
	int MusicPlayOption{}; // 0: resume, 1: random point, 2: replay
	int UseMusicEffect{}; // 0: dont use, 1: use
	GLfloat MusicEffectValue{};
	FileUtil UserSettingData{};

	// music 
	SoundChannel TrackChannel{};
	SoundChannel BeatChannel{};
	int PrevPlayTime[5]{};
	GLfloat BeatDetectValue{};
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
	"Assets//Font//RondiutCapitalsLight-rPnO.otf"
};
#endif

extern SpriteResource Sprite;
extern AudioResource Audio;
extern DataFormatResource Format;
extern GlobalValue Global;
DWORD WINAPI ResourceLoader(LPVOID Param);