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

	/*manually setting the clock is only used when loading a previous save*/
	void SetCurrentHours(int h);
	void SetCurrentMinutes(int m);
	void SetCurrentSecs(int s);

	void DrawClockText(sf::RenderTarget& window);
};

#endif
