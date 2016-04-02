#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

class AudioManager
{
private:
	static bool instanceFlag;
	static AudioManager* instance;

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

	sf::SoundBuffer buySellSoundBuffer;
	sf::Sound buySellSound;

	sf::SoundBuffer notEnoughGemsSoundBuffer;
	sf::Sound notEnoughGemsSound;

	sf::SoundBuffer golemPosSoundBuffer;
	sf::Sound golemPosSound;

	sf::SoundBuffer collideSoundBuffer;
	sf::Sound collideSound;

	sf::SoundBuffer pauseSoundBuffer;
	sf::Sound pauseSound;

	//vector of sound effects
	std::vector<sf::Sound*> soundEffects;

	//possible states for a sound/piece of music
	enum PlayStatuses
	{
		STOPPED,
		PAUSED,
		PLAYING
	};

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

		if (menuNavSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/menuSounds/menuMoveSoundNew1Stereo.wav")) {}
		else std::cout << "Failed to load 'Assets/Audio/SoundEffects/menuSounds/menuMoveSoundNew1Stereo.wav'" << std::endl;
		menuNavSound.setBuffer(menuNavSoundBuffer);

		if (menuConfirmSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/menuSounds/menuConfirmStereo.wav")) {}
		else std::cout << "Failed to load 'Assets/Audio/SoundEffects/menuSounds/menuConfirmStereo.wav'" << std::endl;
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

		if (drinkSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/bottle.wav")) {}
		else std::cout << "Failed to load 'Assets/Audio/SoundEffects/bottle.wav'" << std::endl;
		drinkSound.setBuffer(drinkSoundBuffer);

		if (doorSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/door.wav")) {}
		else std::cout << "Failed to load 'Assets/Audio/SoundEffects/door.wav'" << std::endl;
		doorSound.setBuffer(doorSoundBuffer);

		if (stabSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/battleSounds/sword-clash-01.wav")) {}
		else std::cout << "Failed to load 'Assets/Audio/SoundEffects/battleSounds/sword-clash-01.wav'" << std::endl;
		stabSound.setBuffer(stabSoundBuffer);

		if (chopAttackSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/battleSounds/metal-knife-scrape-03.wav")) {}
		else std::cout << "Failed to load 'Assets/Audio/SoundEffects/battleSounds/metal-knife-scrape-03'" << std::endl;
		chopAttackSound.setBuffer(chopAttackSoundBuffer);

		if (sliceSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/battleSounds/Socapex - new_hits_1F.wav")) {}
		else std::cout << "Failed to load 'Assets/Audio/SoundEffects/battleSounds/Socapex - new_hits_1F.wav'" << std::endl;
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

		if (achievementUnlockedSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/achievementUnlockSounds/achievementSoundStereo.wav")) {}
		else std::cout << "Failed to load 'Assets/Audio/SoundEffects/achievementUnlockSounds/achievementSoundStereo.wav'" << std::endl;
		achievementUnlockedSound.setBuffer(achievementUnlockedSoundBuffer);

		if (blacksmithSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/Pick Hitting RockMono.wav")) {}
		else std::cout << "Failed to load 'Assets/Audio/SoundEffects/Pick Hitting RockMono.wav'" << std::endl;
		blacksmithSound.setBuffer(blacksmithSoundBuffer);

		if (blacksmithForgeSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/fireplaceA.wav")) {}
		else std::cout << "Failed to load 'Assets/Audio/SoundEffects/fireplaceA.wav'" << std::endl;
		blacksmithForgeSound.setBuffer(blacksmithForgeSoundBuffer);

		if (buySellSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/133008__cosmicd__annulet-of-absorptionE.wav")) {}
		else std::cout << "Failed to load 'Assets/Audio/SoundEffects/133008__cosmicd__annulet-of-absorptionE.wav'" << std::endl;
		buySellSound.setBuffer(buySellSoundBuffer);

		if (notEnoughGemsSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/gongStereo.wav")) {}
		else std::cout << "Failed to load 'Assets/Audio/SoundEffects/gongStereo.wav'" << std::endl;
		notEnoughGemsSound.setBuffer(notEnoughGemsSoundBuffer);

		if (golemPosSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/Goblin ScreamM.wav")) {}
		else std::cout << "Failed to load 'Assets/Audio/SoundEffects/Goblin ScreamM.wav'" << std::endl;
		golemPosSound.setBuffer(golemPosSoundBuffer);

		if (collideSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/CollideSoundS.wav")) {}
		else std::cout << "Failed to load 'Assets/Audio/SoundEffects/CollideSoundS.wav'" << std::endl;
		collideSound.setBuffer(collideSoundBuffer);

		if (pauseSoundBuffer.loadFromFile("Assets/Audio/SoundEffects/PauseGameSoundS.wav")) {}
		else std::cout << "Failed to load 'Assets/Audio/SoundEffects/PauseGameSoundS.wav'" << std::endl;
		pauseSound.setBuffer(pauseSoundBuffer);

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
		soundEffects.push_back(&buySellSound);//19
		soundEffects.push_back(&notEnoughGemsSound);//20
		soundEffects.push_back(&golemPosSound);//21
		soundEffects.push_back(&collideSound);//22
		soundEffects.push_back(&pauseSound);//23
	}

public:
	static AudioManager* GetInstance();

	//constructor
	//AudioManager();

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

	void StopSfx(int soundId);

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
