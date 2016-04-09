#ifndef WORLDCLOCK_H
#define WORLDCLOCK_H

class WorldClock : public sf::Sprite
{
private:
	sf::Clock secondClock;

	int currentSeconds;

	int currentMinutes;
	int currentHours;

	float timeMultiplier;

	sf::Font font;
	sf::Text timeText;
public:
	WorldClock();
	~WorldClock();

	void Update();

	void UpdateSeconds();
	void UpdateMinutes();
	void UpdateHours();
};

#endif
