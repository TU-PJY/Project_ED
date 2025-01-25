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

	// user data load
	Global.UserSettingData.Load("GameData//UserSetting", Format.UsetSettingDataFormat);
	Global.FullscreenMode = Global.UserSettingData.LoadDigitData("Option", "FullscreenMode");
	Global.MusicPlayOption = Global.UserSettingData.LoadDigitData("Option", "MusicPlayOption");
	Global.UseMusicEffect = Global.UserSettingData.LoadDigitData("Option", "UseMusicEffect");
	Global.MusicEffectValue = Global.UserSettingData.LoadDigitData("Option", "MusicEffectValue");

	// HighScore Data Load
	Global.HighScoreData.Load("GameData//Data", Format.HighScoreDataFormat);
	DigitDataSet HighScoreDataSet = Global.HighScoreData.LoadCategoryDigitData("HighScore");
	size_t Size = HighScoreDataSet.size();
	for (int i = 0; i < Size; ++i) 
		Global.HighScore[i] = HighScoreDataSet[i];
	

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
	imageUtil.PreLoad(Sprite.HighLight, "Assets//Image//UI//fanfare.png", IMAGE_TYPE_LINEAR);

	imageUtil.PreLoad(Sprite.ED[0], "Assets//Image//Player//ED//normal_1.png", IMAGE_TYPE_LINEAR);
	imageUtil.PreLoad(Sprite.ED[1], "Assets//Image//Player//ED//normal_2.png", IMAGE_TYPE_LINEAR);
	imageUtil.PreLoad(Sprite.ED[2], "Assets//Image//Player//ED//highscore_1.png", IMAGE_TYPE_LINEAR);
	imageUtil.PreLoad(Sprite.ED[3], "Assets//Image//Player//ED//highscore_2.png", IMAGE_TYPE_LINEAR);
	imageUtil.PreLoad(Sprite.ED[4], "Assets//Image//Player//ED//gameover.png", IMAGE_TYPE_LINEAR);

	imageUtil.PreLoad(Sprite.Nata[0], "Assets//Image//Player//Nata//normal.png", IMAGE_TYPE_LINEAR);
	imageUtil.PreLoad(Sprite.Nata[1], "Assets//Image//Player//Nata//highscore.png", IMAGE_TYPE_LINEAR);
	imageUtil.PreLoad(Sprite.Nata[2], "Assets//Image//Player//Nata//GameOver.png", IMAGE_TYPE_LINEAR);

	imageUtil.PreLoad(Sprite.MachineFront, "Assets//Image//Player//ED//machine_front.png", IMAGE_TYPE_LINEAR);
	imageUtil.PreLoad(Sprite.MachineBack, "Assets//Image//Player//ED//machine_back.png", IMAGE_TYPE_LINEAR);
	imageUtil.PreLoad(Sprite.MachineLight, "Assets//Image//Player//ED//machine_front_light.png", IMAGE_TYPE_LINEAR);

	imageUtil.PreLoad(Sprite.Gradation, "Assets//Image//UI//gradation.png");
	imageUtil.PreLoad(Sprite.Dot, "Assets//Image//UI//dot.png");

	imageUtil.PreLoad(Sprite.MataLogo, "Assets//Image//UI//mata_logo.png");

	imageUtil.PreLoad(Sprite.ArrowIconRight, "Assets//Image//UI//key//arrow-right.png");
	imageUtil.PreLoad(Sprite.ArrowIconLeft, "Assets//Image//UI//key//arrow-left.png");
	imageUtil.PreLoad(Sprite.ArrowIconUp, "Assets//Image//UI//key//arrow-up.png");
	imageUtil.PreLoad(Sprite.ArrowIconDown, "Assets//Image//UI//key//arrow-down.png");
	imageUtil.PreLoad(Sprite.EnterIcon, "Assets//Image//UI//key//enter.png");
	imageUtil.PreLoad(Sprite.ShiftIcon, "Assets//Image//UI//key//shift.png");
	imageUtil.PreLoad(Sprite.EscapeIcon, "Assets//Image//UI//key//esc.png");

	soundUtil.Load(Audio.KeyMoveSound, "Assets//Sound//UI//key_click.wav");
	soundUtil.Load(Audio.KeySelectSound, "Assets//Sound//UI//key_select.wav");
	soundUtil.Load(Audio.OptionSelectSound, "Assets//Sound//UI//option_select.wav");
	soundUtil.Load(Audio.GameStartSound, "Assets//Sound//UI//game_start.wav");
	soundUtil.Load(Audio.GameExitSound, "Assets//Sound//UI//game_exit.wav");
	soundUtil.Load(Audio.GameOverSound, "Assets//Sound//UI//game_over.mp3");

	soundUtil.Load(Audio.Track[0], "Assets//Sound//Track//track_easy.mp3", FMOD_LOOP_NORMAL);
	soundUtil.Load(Audio.Track[1], "Assets//Sound//Track//track_normal.mp3", FMOD_LOOP_NORMAL);
	soundUtil.Load(Audio.Track[2], "Assets//Sound//Track//track_hard.mp3", FMOD_LOOP_NORMAL);
	soundUtil.Load(Audio.Track[3], "Assets//Sound//Track//track_harder.mp3", FMOD_LOOP_NORMAL);
	soundUtil.Load(Audio.Track[4], "Assets//Sound//Track//track_insane.mp3", FMOD_LOOP_NORMAL);

	soundUtil.Load(Audio.Beat[0], "Assets//Sound//Beat//track_easy_beat.mp3", FMOD_LOOP_NORMAL);
	soundUtil.Load(Audio.Beat[1], "Assets//Sound//Beat//track_normal_beat.mp3", FMOD_LOOP_NORMAL);
	soundUtil.Load(Audio.Beat[2], "Assets//Sound//Beat//track_hard_beat.mp3", FMOD_LOOP_NORMAL);
	soundUtil.Load(Audio.Beat[3], "Assets//Sound//Beat//track_harder_beat.mp3", FMOD_LOOP_NORMAL);
	soundUtil.Load(Audio.Beat[4], "Assets//Sound//Beat//track_insane_beat.mp3", FMOD_LOOP_NORMAL);

	soundUtil.Load(Audio.HomeBGM, "Assets//Sound//Track//track_home.mp3", FMOD_LOOP_NORMAL);

#ifdef USE_CUSTOM_FONT
	fontUtil.LoadUserFont();
#endif

	return 0;
}