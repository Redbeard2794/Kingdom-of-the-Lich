#include "stdafx.h"
#include "AudioManager.h"

AudioManager::AudioManager()
{
	if (buffer.loadFromFile("Assets/Audio/SoundEffects/Unrolling Parchment.wav")) {}
	else std::cout << "Failed to load TestSound.wav" << std::endl;

	sound.setBuffer(buffer);
}

AudioManager::~AudioManager()
{

}

void AudioManager::PlaySoundEffect(std::string soundPath)
{
	if (buffer.loadFromFile(soundPath)) {}
	else std::cout << "Failed to load TestSound.wav" << std::endl;


	std::cout << "Playing sound effect: " << soundPath << std::endl;
	std::cout << "Volume: " << sound.getVolume() << std::endl;
	sound.play();
	std::cout << "Sound status: " << sound.getStatus() << std::endl;
}