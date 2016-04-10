#ifndef WORLDCLOCK_H
#define WORLDCLOCK_H

class WorldClock : public sf::Sprite
{
private:
	sf::Clock secondClock;//clock for counting seconds

	int currentSeconds;//current number of seconds
	int currentMinutes;//current number of minutes
	int currentHours;//current number of hours

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

	void DrawText();
};

#endif
