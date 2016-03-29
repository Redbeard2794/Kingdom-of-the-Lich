#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

class AudioManager
{
private:
	//music
	sf::Music openingMusic;
	sf::Music tutorialAreaMusic;
	sf::Music sewerAreaMusic;
	sf::Music battleMusic;

	//vector of music tracks
	std::vector<sf::Music*> musicTracks;

	//sounds and sound buffers
	sf::SoundBuffer charCreationOpeningSoundBuffer;
	sf::Sound charCreationOpeningSound;

	sf::SoundBuffer menuNavSoundBuffer;
	sf::Sound menuNavSound;

	sf::SoundBuffer menuConfirmSoundBuffer;
	sf::Sound menuConfirmSound;

	sf::SoundBuffer inventoryOpenSoundBuffer;
	sf::Sound inventoryOpenSound;

	sf::SoundBuffer chestOpenSoundBuffer;
	sf::Sound chestOpenSound;

	sf::SoundBuffer chestLockedSoundBuffer;
	sf::Sound chestLockedSound;

	sf::SoundBuffer crunchSoundBuffer;
	sf::Sound crunchSound;

	sf::SoundBuffer thunderClapSoundBuffer;
	sf::Sound thunderClap;

	sf::SoundBuffer drinkSoundBuffer;
	sf::Sound drinkSound;

	sf::SoundBuffer doorSoundBuffer;
	sf::Sound doorSound;

	sf::SoundBuffer stabSoundBuffer;
	sf::Sound stabSound;

	sf::SoundBuffer chopAttackSoundBuffer;
	sf::Sound chopAttackSound;

	sf::SoundBuffer sliceSoundBuffer;
	sf::Sound sliceSound;

	sf::SoundBuffer playerCombatDealthSoundBuffer;
	sf::Sound playerCombatDeathSound;

	sf::SoundBuffer stoneGolemHitSoundBuffer;
	sf::Sound stoneGolemHitSound;

	sf::SoundBuffer stoneGolemPunchSoundBuffer;
	sf::Sound stoneGolemPunchSound;

	sf::SoundBuffer achievementUnlockedSoundBuffer;
	sf::Sound achievementUnlockedSound;

	sf::SoundBuffer blacksmithSoundBuffer;
	sf::Sound blacksmithSound;

	sf::SoundBuffer blacksmithForgeSoundBuffer;
	sf::Sound blacksmithForgeSound;

	//vector of sound effects
	std::vector<sf::Sound*> soundEffects;

	//possible states for a sound/piece of music
	enum PlayStatuses
	{
		STOPPED,
		PAUSED,
		PLAYING
	};

public:
	//constructor
	AudioManager();

	//destructor
	~AudioManager();

	//play a music file, param is the index of the sound in the vector
	void PlayMusicById(int musicId);

	//play a sound effect, params are the index of the sound in the sounds vector and whether the sound can be played multiple times in one go
	void PlaySoundEffectById(int soundId, bool delay);

	//Fade out a piece of music and stop it from playing when volume is 0. Param is the index of the piece of music in the vector
	void FadeOutMusic(int musicId);

	//Fade out a sound effect and stop it from playing when volume is 0. Param is the index of the sound in the vector
	void FadeOutSound(int soundId);

	void StopMusic(int musicId);

	//set the global music volume
	void SetMusicVolume(int vol);

	//set the global sfx volume
	void SetSfxVolume(int vol);

	/*Audio Spatialization methods*/

	//set the sf listeners position. params: x co-ord, y co-ord, z co-ord. z defaults to zero as this is a 2d game
	void SetListenersPosition(float x, float y, float z = 0);

	//set the sf listeners direction. params are x direction, y direction, z direction. z defaults to 0
	void SetListenersDirection(float x, float y, float z = 0);

	//set the sf listeners global volume of the scene. param is the volume
	void SetListenerGlobalVolume(float vol);

	/*play a spatialised sound effect. params:  index of the sound in the vector, is the sound relative to the listener, 
		minimum distance, attenuation value, x co-ord, y co-ord, z co-ord. z defaults to 0*/
	void PlaySpatializedSoundEffect(bool loop, int soundId, bool relListener, float minDistance, float attenuation, float x, float y, float z = 0);
};

#endif
