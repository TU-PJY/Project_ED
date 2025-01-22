#include "GameResource.h"
#include "ImageUtil.h"
#include "SoundUtil.h"
#include "FileUtil.h"
#include "ScriptUtil.h"

DWORD WINAPI ResourceLoader(LPVOID Param) {
	// game resoueces
	for (int i = 0; i < 3; ++i) {
		std::string FileName = "Assets//Image//Shapes//Triangle//obstacle_triangle_";
		FileName += std::to_string(i + 1);
		FileName += ".png";
		imageUtil.PreLoad(Sprite.Triangle[i], FileName);
	}

	for (int i = 0; i < 5; ++i) {
		std::string FileName = "Assets//Image//Shapes//Square//obstacle_square_";
		FileName += std::to_string(i + 1);
		FileName += ".png";
		imageUtil.PreLoad(Sprite.Square[i], FileName);
	}

	for (int i = 0; i < 5; ++i) {
		std::string FileName = "Assets//Image//Shapes//Pentagon//obstacle_pentagon_";
		FileName += std::to_string(i + 1);
		FileName += ".png";
		imageUtil.PreLoad(Sprite.Pentagon[i], FileName);
	}

	for (int i = 0; i < 3; ++i) {
		std::string FileName = "Assets//Image//Shapes//Triangle//obstacle_triangle_light_";
		FileName += std::to_string(i + 1);
		FileName += ".png";
		imageUtil.PreLoad(Sprite.TriangleLight[i], FileName);
	}

	for (int i = 0; i < 5; ++i) {
		std::string FileName = "Assets//Image//Shapes//Square//obstacle_square_light_";
		FileName += std::to_string(i + 1);
		FileName += ".png";
		imageUtil.PreLoad(Sprite.SquareLight[i], FileName);
	}

	for (int i = 0; i < 5; ++i) {
		std::string FileName = "Assets//Image//Shapes//Pentagon//obstacle_pentagon_light_";
		FileName += std::to_string(i + 1);
		FileName += ".png";
		imageUtil.PreLoad(Sprite.PentagonLight[i], FileName);
	}


	Global.UserSettingData.Load("GameData//UserSetting", Format.UsetSettingDataFormat);
	Global.FullscreenMode = Global.UserSettingData.LoadDigitData("Option", "FullscreenMode");
	Global.MusicPlayOption = Global.UserSettingData.LoadDigitData("Option", "MusicPlayOption");
	Global.UseMusicEffect = Global.UserSettingData.LoadDigitData("Option", "UseMusicEffect");
	Global.MusicEffectValue = Global.UserSettingData.LoadDigitData("Option", "MusicEffectValue");



	imageUtil.PreLoad(Sprite.ImagePlayerShape[0], "Assets//Image//Player//triangle.png", IMAGE_TYPE_LINEAR);
	imageUtil.PreLoad(Sprite.ImagePlayerShape[1], "Assets//Image//Player//square.png", IMAGE_TYPE_LINEAR);
	imageUtil.PreLoad(Sprite.ImagePlayerShape[2], "Assets//Image//Player//pentagon.png", IMAGE_TYPE_LINEAR);

	imageUtil.PreLoad(Sprite.ImagePlayerShapeLight[0], "Assets//Image//Player//triangle_light.png", IMAGE_TYPE_LINEAR);
	imageUtil.PreLoad(Sprite.ImagePlayerShapeLight[1], "Assets//Image//Player//square_light.png", IMAGE_TYPE_LINEAR);
	imageUtil.PreLoad(Sprite.ImagePlayerShapeLight[2], "Assets//Image//Player//pentagon_light.png", IMAGE_TYPE_LINEAR);

	imageUtil.PreLoad(Sprite.ImagePlayerFeedBack, "Assets//Image//Player//feedback.png");

	imageUtil.PreLoad(Sprite.Title, "Assets//Image//UI//title.png", IMAGE_TYPE_LINEAR);

	imageUtil.PreLoad(Sprite.ArrowLeft, "Assets//Image//UI//arrow_left.png", IMAGE_TYPE_LINEAR);
	imageUtil.PreLoad(Sprite.ArrowRight, "Assets//Image//UI//arrow_right.png", IMAGE_TYPE_LINEAR);



	soundUtil.Load(Audio.KeyMoveSound, "Assets//Sound//key_click.wav");
	soundUtil.Load(Audio.KeySelectSound, "Assets//Sound//key_select.wav");
	soundUtil.Load(Audio.OptionSelectSound, "Assets//Sound//option_select.wav");
	soundUtil.Load(Audio.GameStartSound, "Assets//Sound//game_start.wav");
	soundUtil.Load(Audio.GameExitSound, "Assets//Sound//game_exit.wav");

	soundUtil.Load(Audio.Track[0], "Assets//Sound//Track//track_easy.mp3", FMOD_LOOP_NORMAL);
	soundUtil.Load(Audio.Track[1], "Assets//Sound//Track//track_normal.mp3", FMOD_LOOP_NORMAL);
	soundUtil.Load(Audio.Track[2], "Assets//Sound//Track//track_hard.mp3", FMOD_LOOP_NORMAL);
	soundUtil.Load(Audio.Track[3], "Assets//Sound//Track//track_harder.mp3", FMOD_LOOP_NORMAL);
	soundUtil.Load(Audio.Track[4], "Assets//Sound//Track//track_insane.mp3", FMOD_LOOP_NORMAL);

	soundUtil.Load(Audio.HomeBGM, "Assets//Sound//Track//track_home.mp3", FMOD_LOOP_NORMAL);

#ifdef USE_CUSTOM_FONT
	fontUtil.LoadUserFont();
#endif

	return 0;
}