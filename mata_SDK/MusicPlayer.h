#pragma once
#include "GameObject.h"

class MusicPlayer : public GameObject {
private:
	int CurrentMusicIndex{};
	GLfloat PlaySpeed{ 1.0 };
	SoundChannel Ch{};

public:
	MusicPlayer();
	void PlayMusic(Sound& SoundRes, int Index);
	void PauseMusic();
	void StopMusic();
	void SetPlaySpeed(GLfloat SpeedValue);
	void EnableMuffle();
	void DisableMuffle();
};