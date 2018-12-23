#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include	<iostream>
#include	<string>
#include	<map>
#include	<SDL.h>
#include	<SDL_image.h>
#include	<SDL_ttf.h>
#include	<SDL_mixer.h>

using namespace std;

class AudioManager
{
public:

	static AudioManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new AudioManager();
		}

		return s_pInstance;
	}

	bool loadAudio(const char* fileName, string id);
	bool loadMusic(const char* fileName);
	void playAudio(string id);
	void playMusic();
	void clearFromAudioMap(string id); //delete audio from the map
	void clearMusic();
private:
	map<string, Mix_Chunk*>		m_audioMap;
	Mix_Music*					m_backgroundMusic;
	static AudioManager*		s_pInstance;
	AudioManager() {};
	~AudioManager();
};

#endif // AUDIOMANAGER_H