#include "stdafx.h"
#include "AudioManager.h"

//constructor
AudioManager::AudioManager()
{

	//load music, well partial load I suppose....
	if (openingMusic.openFromFile("Assets/Audio/Music/Horror Game Menu.ogg")) {}
	else std::cout << "Failed to open 'Assets/Audio/Music/Horror Game Menu.ogg'" << std::endl;
	openingMusic.setLoop(true);
	openingMusic.setVolume(75);//60

	if (tutorialAreaMusic.openFromFile("Assets/Audio/Music/Harp.ogg")) {}
	else std::cout << "Failed to open 'Assets/Audio/Music/Harp.ogg'" << std::endl;
	tutorialAreaMusic.setLoop(true);
	tutorialAreaMusic.setVolume(75);//70

	if (sewerAreaMusic.openFromFile("Assets/Audio/Music/magical_theme.ogg")) {}
	else std::cout << "Failed to open 'Assets/Audio/Music/magical_theme.ogg'" << std::endl;
	sewerAreaMusic.setLoop(true);
	sewerAreaMusic.setVolume(75);//70

	if (battleMusic.openFromFile("Assets/Audio/Music/Battle.ogg")) {}
	else std::cout << "Failed to open 'Assets/Audio/Music/Battle.ogg'" << std::endl;
	battleMusic.setLoop(true);
	battleMusic.setVolume(75);

	//vector of music
	musicTracks.push_back(&openingMusic);//0
	musicTracks.push_back(&tutorialAreaMusic);//1
	musicTracks.push_back(&sewerAreaMusic);//2
	musicTracks.push_back(&battleMusic);//3

	//load sound effects
	if (charCreationOpeningSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/Unrolling ParchmentMono.wav")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/Unrolling Parchment.wav'" << std::endl;
	charCreationOpeningSound.setBuffer(charCreationOpeningSoundBuffer);

	if (menuNavSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/menuSounds/interface6Mono.wav")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/menuSounds/interface6.wav'" << std::endl;
	menuNavSound.setBuffer(menuNavSoundBuffer);

	if (menuConfirmSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/menuSounds/sword-unsheathe4newMono.wav")) {}
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

	if (crunchSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/impactcrunch03Mono.wav")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/impactcrunch03.wav'" << std::endl;
	crunchSound.setBuffer(crunchSoundBuffer);

	if (thunderClapSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/rock_breakingMono.wav")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/rock_breaking.wav'" << std::endl;
	thunderClap.setBuffer(thunderClapSoundBuffer);

	if (drinkSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/bottleMono.wav")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/bottle.wav'" << std::endl;
	drinkSound.setBuffer(drinkSoundBuffer);

	if (doorSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/doorMono.wav")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/door.wav'" << std::endl;
	doorSound.setBuffer(doorSoundBuffer);

	if (stabSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/battleSounds/sword-clash-01.wav")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/battleSounds/sword-clash-01.wav'" << std::endl;
	stabSound.setBuffer(stabSoundBuffer);

	if (chopAttackSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/battleSounds/metal-knife-scrape-03.wav")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/battleSounds/metal-knife-scrape-03'" << std::endl;
	chopAttackSound.setBuffer(chopAttackSoundBuffer);

	if (sliceSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/battleSounds/sword-clash-03.wav")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/battleSounds/sword-clash-03.wav'" << std::endl;
	sliceSound.setBuffer(sliceSoundBuffer);

	if (playerCombatDealthSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/battleSounds/qubodup-PowerDrain.ogg")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/battleSounds/qubodup-PowerDrain.ogg'" << std::endl;
	playerCombatDeathSound.setBuffer(playerCombatDealthSoundBuffer);

	if (stoneGolemHitSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/battleSounds/qubodupImpactMeat02.ogg")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/battleSounds/qubodupImpactMeat02.ogg'" << std::endl;
	stoneGolemHitSound.setBuffer(stoneGolemHitSoundBuffer);

	if (stoneGolemPunchSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/battleSounds/qubodupPunch01.ogg")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/battleSounds/qubodupPunch01.ogg'" << std::endl;
	stoneGolemPunchSound.setBuffer(stoneGolemPunchSoundBuffer);

	if (achievementUnlockedSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/achievementUnlockSounds/Metal Hit.wav")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/achievementUnlockSounds/Metal Hit.wav'" << std::endl;
	achievementUnlockedSound.setBuffer(achievementUnlockedSoundBuffer);

	if (blacksmithSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/Pick Hitting RockMono.wav")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/Pick Hitting RockMono.wav'" << std::endl;
	blacksmithSound.setBuffer(blacksmithSoundBuffer);

	if (blacksmithForgeSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/fire-1Mono.wav")) {}
	else std::cout << "Failed to load 'Assets/Audio/SoundEffects/fire-1Mono.wav'" << std::endl;
	blacksmithForgeSound.setBuffer(blacksmithForgeSoundBuffer);

	//vector of sound effects
	soundEffects.push_back(&charCreationOpeningSound);//0
	soundEffects.push_back(&menuNavSound);//1
	soundEffects.push_back(&menuConfirmSound);//2
	soundEffects.push_back(&inventoryOpenSound);//3
	soundEffects.push_back(&chestOpenSound);//4
	soundEffects.push_back(&chestLockedSound);//5
	soundEffects.push_back(&crunchSound);//6
	soundEffects.push_back(&thunderClap);//7
	soundEffects.push_back(&drinkSound);//8
	soundEffects.push_back(&doorSound);//9
	soundEffects.push_back(&stabSound);//10
	soundEffects.push_back(&chopAttackSound);//11
	soundEffects.push_back(&sliceSound);//12
	soundEffects.push_back(&playerCombatDeathSound);//13
	soundEffects.push_back(&stoneGolemHitSound);//14
	soundEffects.push_back(&stoneGolemPunchSound);//15
	soundEffects.push_back(&achievementUnlockedSound);//16
	soundEffects.push_back(&blacksmithSound);//17
	soundEffects.push_back(&blacksmithForgeSound);//18
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

void AudioManager::StopMusic(int musicId)
{
	musicTracks.at(musicId)->stop();
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
	soundEffects.at(soundId)->play();
	std::cout << "Position: " << soundEffects.at(soundId)->getPosition().x << ", " << soundEffects.at(soundId)->getPosition().y << ", " << soundEffects.at(soundId)->getPosition().z << std::endl;
	std::cout << "MinDistance: " << soundEffects.at(soundId)->getMinDistance() << std::endl;
	std::cout << "Attenuation: " << soundEffects.at(soundId)->getAttenuation() << std::endl;
	std::cout << "Volume: " << soundEffects.at(soundId)->getVolume() << std::endl;
	std::cout << "Status: " << soundEffects.at(soundId)->getStatus() << std::endl;
}
