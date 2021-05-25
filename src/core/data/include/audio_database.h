#pragma once

#include <array>

#include "include/audio.h"


const std::string AUDIO_LOCATION = __FILE__ "/../../../../assets/audio/";

enum MusicType {
	MUSIC_MENU,
	MUSIC_LEVEL_CLEAR,
	MUSIC_LEVEL_FAILED,
	MUSIC_LEVEL_START
};

enum SoundType {
	SOUND_BIRD_COLLISION,
	SOUND_BIRD_FLYING,
	SOUND_BIRD_SELECT,
	SOUND_BIRD_YELL,
	SOUND_PIG_DESTROYED,
	SOUND_WOOD_DESTROYED
};

class AudioDatabase {
private:
	std::array<Sound, 6> m_sounds;
	std::array<Music, 4> m_musics;
public:
	AudioDatabase();
	~AudioDatabase() = default;
public:
	void play(SoundType type);
	void play(MusicType type, bool loopable = false);
	void stop(SoundType type);
	void stop(MusicType type);
	bool isPlaying(SoundType type);
	static AudioDatabase& getInstance();
	void free();

};
