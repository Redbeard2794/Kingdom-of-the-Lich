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

	sf::RectangleShape clockTextBackground;
public:
	WorldClock(sf::Font f, int screenW, int screenH);
	~WorldClock();

	void Update();

	void UpdateSeconds();
	void UpdateMinutes();
	void UpdateHours();

	

	int GetCurrentHours();
	int GetCurrentMinutes();
	int GetCurrentSeconds();

	void DrawClockText(sf::RenderTarget& window);
};

#endif
