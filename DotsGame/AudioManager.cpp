#include "AudioManager.h"

AudioManager* AudioManager::s_pInstance = 0;

bool AudioManager::loadAudio(const char* fileName, string id)
{
	Mix_Chunk* audio;
	audio = Mix_LoadWAV(fileName);
	if (audio == nullptr)
		return false;

	m_audioMap[id] = audio; //save audio.
	return true;
}
bool AudioManager::loadMusic(const char* fileName)
{
	m_backgroundMusic = Mix_LoadMUS(fileName);
	if (m_backgroundMusic == nullptr)
		return false;

	return true;
}

void AudioManager::playMusic() 
{
	if (m_backgroundMusic)
	{
		Mix_PlayMusic(m_backgroundMusic, -1);
		Mix_VolumeMusic(30);
	}
}

void AudioManager::playAudio(string id) 
{
	if(m_audioMap[id])
		Mix_PlayChannel(-1, m_audioMap[id], 0);
}

void AudioManager::clearFromAudioMap(string id)
{
	Mix_FreeChunk(m_audioMap[id]);
	m_audioMap.erase(id);
	
}
void AudioManager::clearMusic()
{
	Mix_FreeMusic(m_backgroundMusic);
}

AudioManager::~AudioManager() 
{
	if (m_audioMap.size() > 0)
	{
		for (auto const& x : m_audioMap)
		{
			Mix_FreeChunk(x.second);
		}
	}
	Mix_FreeMusic(m_backgroundMusic);
}
