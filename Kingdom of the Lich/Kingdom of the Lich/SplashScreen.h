#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

class SplashScreen
{
private:
	//summoning circle
	sf::Texture summoningCircleTexture;
	sf::Sprite summoningCircleSprite;

	//decide whether to show game's name or not
	bool summoned;

	//game's name
	sf::Texture nameTexture;
	sf::Sprite nameSprite;

	//fireball texture, sprite and animation stuff
	sf::Texture fireballTexture;
	sf::Sprite fireballSprite;
	sf::Clock fireballAnimationClock;
	double fireballAnimationTime;
	sf::Vector2i fireballFramePosition;
	sf::Vector2i fireballFrameSize;
	sf::IntRect fireballFrame;

	//candle texture, sprite and animation stuff
	sf::Texture candleTexture;
	sf::Sprite candles[4];
	sf::Clock candlesAnimationClock;
	double candlesAnimationTime;
	sf::Vector2i candlesFramePosition;
	sf::Vector2i candlesFrameSize;
	sf::IntRect candlesFrame;

public:
	/*constructor*/
	SplashScreen();

	/*destructor*/
	~SplashScreen();

	/*Update, used to animate the candles and fireball*/
	void Update();

	//draw, requires a render target
	void Draw(sf::RenderTarget& window);

	//check the summoning status
	bool isSummoned();
};

#endif
