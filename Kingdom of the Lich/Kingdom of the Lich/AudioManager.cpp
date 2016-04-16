#include "stdafx.h"
#include "AudioManager.h"

bool AudioManager::instanceFlag = false;
AudioManager* AudioManager::instance = NULL;

AudioManager* AudioManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new AudioManager();
		instanceFlag = true;
		return instance;
	}
	else return instance;
}

//destructor
AudioManager::~AudioManager()
{
	//delete all sounds and sound buffers here in future
	instanceFlag = false;
}

//play a music file, param is the index of the sound in the vector
void AudioManager::PlayMusicById(int musicId)
{
	if (musicTracks.at(musicId)->getStatus() != PLAYING)//if the piece of music is not playing
		musicTracks.at(musicId)->play();
}

//play a sound effect, params are the index of the sound in the sounds vector and whether the sound can be played multiple times in one go
void AudioManager::PlaySoundEffectById(int soundId, bool delay)
{
	if(delay == false)//if it is ok for the sound to play multiple times
		soundEffects.at(soundId)->play();
	else
	{
		if (soundEffects.at(soundId)->getStatus() != PLAYING)//if the sound is not playing
			soundEffects.at(soundId)->play();
	}
}

//Fade out a piece of music and stop it from playing when volume is 0. Param is the index of the piece of music in the vector
void AudioManager::FadeOutMusic(int musicId)
{
	if (musicTracks.at(musicId)->getStatus() != STOPPED)//if the music is not already stopped
	{
		if (musicTracks.at(musicId)->getVolume() > 0)//check the volume is greater than 0
		{
			int prevVol = openingMusic.getVolume();
			int newVol = prevVol - 1;
			musicTracks.at(musicId)->setVolume(newVol);
		}
		else musicTracks.at(musicId)->stop();
	}
}

//Fade out a sound effect and stop it from playing when volume is 0. Param is the index of the sound in the vector
void AudioManager::FadeOutSound(int soundId)
{
	if (soundEffects.at(soundId)->getStatus() != STOPPED)//if the sound is not already stopped
	{
		if (soundEffects.at(soundId)->getVolume() > 0)//check the volume is greater than 0
		{
			int prevVol = soundEffects.at(soundId)->getVolume();
			int newVol = prevVol - 1;
			soundEffects.at(soundId)->setVolume(newVol);
		}
		else soundEffects.at(soundId)->stop();
	}
}

void AudioManager::StopMusic(int musicId)
{
	musicTracks.at(musicId)->stop();
}

void AudioManager::StopSfx(int soundId)
{
	soundEffects.at(soundId)->stop();
}

//set the global music volume
void AudioManager::SetMusicVolume(int vol)
{
	for (int i = 0; i < musicTracks.size(); i++)
	{
		musicTracks.at(i)->setVolume(vol);
	}
}

//set the global sfx volume
void AudioManager::SetSfxVolume(int vol)
{
	for (int i = 0; i < soundEffects.size(); i++)
	{
		soundEffects.at(i)->setVolume(vol);
	}
}

/*Audio Spatialization methods*/

//set the sf listeners position. params: x co-ord, y co-ord, z co-ord. z defaults to zero as this is a 2d game
void AudioManager::SetListenersPosition(float x, float y, float z)
{
	sf::Listener::setPosition(x, y, z);
}

//set the sf listeners direction. params are x direction, y direction, z direction. z defaults to 0
void AudioManager::SetListenersDirection(float x, float y, float z)
{
	sf::Listener::setDirection(x, y, z);
}

//set the sf listeners global volume of the scene. param is the volume
void AudioManager::SetListenerGlobalVolume(float vol)
{
	sf::Listener::setGlobalVolume(vol);
}

/*play a spatialised sound effect. params:  index of the sound in the vector, is the sound relative to the listener,
minimum distance, attenuation value, x co-ord, y co-ord, z co-ord. z defaults to 0*/
void AudioManager::PlaySpatializedSoundEffect(bool loop, int soundId, bool relListener, float minDistance, float attenuation, float x, float y, float z)
{
	soundEffects.at(soundId)->setPosition(x, y, z);
	soundEffects.at(soundId)->setRelativeToListener(relListener);
	soundEffects.at(soundId)->setMinDistance(minDistance);
	soundEffects.at(soundId)->setAttenuation(attenuation);
	soundEffects.at(soundId)->setLoop(loop);
	if(soundEffects.at(soundId)->getStatus() != PLAYING)
		soundEffects.at(soundId)->play();
	std::cout << "Position: " << soundEffects.at(soundId)->getPosition().x << ", " << soundEffects.at(soundId)->getPosition().y << ", " << soundEffects.at(soundId)->getPosition().z << std::endl;
	std::cout << "MinDistance: " << soundEffects.at(soundId)->getMinDistance() << std::endl;
	std::cout << "Attenuation: " << soundEffects.at(soundId)->getAttenuation() << std::endl;
	std::cout << "Volume: " << soundEffects.at(soundId)->getVolume() << std::endl;
	std::cout << "Status: " << soundEffects.at(soundId)->getStatus() << std::endl;
}
