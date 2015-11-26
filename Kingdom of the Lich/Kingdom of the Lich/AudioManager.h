#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

class AudioManager
{
private:
	sf::SoundBuffer buffer;

	sf::Sound sound;

	enum PlayStatus
	{
		STOPPED,
		PAUSED,
		PLAYING
	};
public:
	AudioManager();

	~AudioManager();

	void PlaySoundEffect(std::string soundPath);
};

#endif
