#pragma once
#include <iostream>
#include <map>
#include <SDL_mixer.h>
class audioManager 
{
public:
	audioManager();
	bool init();
	bool loadMusic(std::string filepaths[], std::string texturenames[], int count);
	bool loadChunks(std::string filepaths[], std::string texturenames[], int count);
	Mix_Music* getMusic(std::string name);
	Mix_Chunk* getChunk(std::string name);

	void playChunk(std::string chunk_name);
	void pauseMusic();
	void playMusic(std::string music_name);
	bool isMusicPlaying();
	void musicVolumeUp(bool up_or_down);
	void chunksVolumeUp(bool up_or_down);
	void exit();
	
private:
	std::map<std::string, Mix_Chunk* > chunks_map;
	std::map<std::string,Mix_Music*> music_map;
	std::string current_music;


};