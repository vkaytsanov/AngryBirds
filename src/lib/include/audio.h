//
// Created by Viktor on 18.1.2021 г..
//

#ifndef AUDIO_H
#define AUDIO_H


#include "../utils/include/sound.h"
#include "../utils/include/music.h"

class Audio {
private:
public:
	Audio();
	~Audio();
	Sound newSound(const std::string& file_path);
	Music newMusic(const std::string& file_path);
	void stopMusic();
};


#endif //AUDIO_H
