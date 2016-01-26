#include "stdafx.h"
#include "AudioManager.h"

//constructor
AudioManager::AudioManager()
{

	//load music, well partial load I suppose....
	if (openingMusic.openFromFile("Assets/Audio/Music/Horror Game Menu.ogg")) {}
	else std::cout << "Failed to open 'Assets/Audio/Music/Horror Game Menu.ogg'" << std::endl;
	openingMusic.setLoop(true);
	openingMusic.setVolume(100);

	if (tutorialAreaMusic.openFromFile("Assets/Audio/Music/Harp.ogg")) {}
	else std::cout << "Failed to open 'Assets/Audio/Music/Harp.ogg'" << std::endl;
	tutorialAreaMusic.setLoop(true);
	tutorialAreaMusic.setVolume(100);

	//vector of music
	musicTracks.push_back(&openingMusic);//0
	musicTracks.push_back(&tutorialAreaMusic);//1

	//load sound effects
	if (charCreationOpeningSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/Unrolling Parchment.wav")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/Unrolling Parchment.wav'" << std::endl;
	charCreationOpeningSound.setBuffer(charCreationOpeningSoundBuffer);

	if (menuNavSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/menuSounds/interface6.wav")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/menuSounds/interface6.wav'" << std::endl;
	menuNavSound.setBuffer(menuNavSoundBuffer);

	if (menuConfirmSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/menuSounds/sword-unsheathe4new.wav")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/menuSounds/sword-unsheathe4new.wav'" << std::endl;
	menuConfirmSound.setBuffer(menuConfirmSoundBuffer);

	if (inventoryOpenSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/inventorySounds/cloth-heavy1.wav")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/inventorySounds/cloth-heavy1.wav'" << std::endl;
	inventoryOpenSound.setBuffer(inventoryOpenSoundBuffer);

	if (chestOpenSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/interactionSounds/chestSounds/altChestOpenSound.wav")) {}
	else std::cout << "Failed to load ''Assets/Audio/SoundEffects/interactionSounds/chestSounds/altChestOpenSound.wav'" << std::endl;
	chestOpenSound.setBuffer(chestOpenSoundBuffer);

	if (chestLockedSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/interactionSounds/chestSounds/Key Jiggle.wav")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/interactionSounds/chestSounds/Key Jiggle.wav'" << std::endl;
	chestLockedSound.setBuffer(chestLockedSoundBuffer);

	if (crunchSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/impactcrunch03.wav")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/impactcrunch03.wav'" << std::endl;
	crunchSound.setBuffer(crunchSoundBuffer);

	if (thunderClapSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/rock_breaking.wav")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/rock_breaking.wav'" << std::endl;
	thunderClap.setBuffer(thunderClapSoundBuffer);

	//vector of sound effects
	soundEffects.push_back(&charCreationOpeningSound);//0
	soundEffects.push_back(&menuNavSound);//1
	soundEffects.push_back(&menuConfirmSound);//2
	soundEffects.push_back(&inventoryOpenSound);//3
	soundEffects.push_back(&chestOpenSound);//4
	soundEffects.push_back(&chestLockedSound);//5
	soundEffects.push_back(&crunchSound);//6
	soundEffects.push_back(&thunderClap);//7
}

//destructor
AudioManager::~AudioManager()
{
	//delete all sounds and sound buffers here in future
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
