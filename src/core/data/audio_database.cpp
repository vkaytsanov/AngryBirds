#include "include/audio_database.h"
#include "include/lib.h"

#define AUDIO 1

AudioDatabase::AudioDatabase() {
	const std::string soundNames[] = {
		"bird 01 collision a1.wav",
		"bird 01 flying.wav",
		"bird 01 select.wav",
		"redbird_yell01.wav",
		"piglette destroyed.wav",
		"wood destroyed a1.wav"
	};

	const std::string musicNames[] = {
		"Angry-Birds-Theme-Song.mp3",
		"level clear military a1.mp3",
		"level failed piglets a2.mp3",
		"level start military a1.mp3"
	};

	for (unsigned i = 0; i < m_sounds.size(); i++) {
		m_sounds[i].loadSound(AUDIO_LOCATION + "sfx/" + soundNames[i]);
	}

	for (unsigned i = 0; i < m_musics.size(); i++) {
		m_musics[i].loadMusic(AUDIO_LOCATION + "music/" + musicNames[i]);
	}

}

void AudioDatabase::play(SoundType type) {
#if AUDIO
	m_sounds[type].play(type);
#endif
}

void AudioDatabase::play(MusicType type, bool loopable) {
#if AUDIO
	m_musics[type].play(loopable);
#endif
}

void AudioDatabase::stop(SoundType type) {
	m_sounds[type].stop();
}

void AudioDatabase::stop(MusicType type) {
	Lib::audio->stopMusic();
}

bool AudioDatabase::isPlaying(SoundType type) {
	return m_sounds[type].isPlaying(type);
}

AudioDatabase& AudioDatabase::getInstance() {
	static AudioDatabase database;
	return database;
}

void AudioDatabase::free() {
	for (unsigned i = 0; i < m_sounds.size(); i++) {
		m_sounds[i].free();
	}
	for (unsigned i = 0; i < m_musics.size(); i++) {
		m_musics[i].free();
	}
}
