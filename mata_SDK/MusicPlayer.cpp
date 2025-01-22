#include "MusicPlayer.h"

MusicPlayer::MusicPlayer() {
	
}

void MusicPlayer::PlayMusic(Sound& SoundRes, int Index) {
	soundUtil.PlaySound(SoundRes, Ch);
}

void MusicPlayer::PauseMusic() {
	soundUtil.PauseSound(Ch, true);
}

void MusicPlayer::SetPlaySpeed(GLfloat SpeedValue) {

}

void MusicPlayer::EnableMuffle() {
	
}

void MusicPlayer::DisableMuffle() {

}
