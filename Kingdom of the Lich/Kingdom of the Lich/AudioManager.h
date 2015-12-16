#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

class AudioManager
{
private:
	//music
	sf::Music openingMusic;
	sf::Music tutorialAreaMusic;

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
};

#endif
