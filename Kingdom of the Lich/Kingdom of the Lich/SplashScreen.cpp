#include "stdafx.h"
#include "SplashScreen.h"

/*constructor*/
SplashScreen::SplashScreen()
{
	summoned = false;

	//game's name
	nameTexture.loadFromFile("Assets/Splash Screen/startScreenIcon.png");
	nameSprite.setTexture(nameTexture);
	nameSprite.setScale(sf::Vector2f(.5f, .5f));
	nameSprite.setPosition(85, 250);

	//summoning circle
	summoningCircleTexture;
	summoningCircleTexture.loadFromFile("Assets/Splash Screen/circle5a.png");
	summoningCircleSprite.setTexture(summoningCircleTexture);
	summoningCircleSprite.setOrigin(summoningCircleTexture.getSize().x / 2, summoningCircleTexture.getSize().y / 2);
	summoningCircleSprite.setScale(0.5f, 0.5f);
	summoningCircleSprite.setPosition(SCREENWIDTH / 2, 275);

	//fireball
	fireballTexture.loadFromFile("Assets/Splash Screen/VioletFireBallSheet.png");
	fireballSprite.setTexture(fireballTexture);
	fireballSprite.setOrigin(fireballTexture.getSize().x / 2, fireballTexture.getSize().y / 2);
	
	fireballSprite.setPosition(675, 275);
	fireballSprite.setScale(4, 4);

	//set up the fireball texture rectangle
	fireballFramePosition = sf::Vector2i(0, 0);
	fireballFrameSize = sf::Vector2i(46, 46);
	fireballFrame = sf::IntRect(fireballFramePosition, fireballFrameSize);
	fireballSprite.setTextureRect(fireballFrame);

	fireballAnimationTime = 0.5;
	fireballAnimationClock.restart();

	//candles
	candlesAnimationClock.restart();
	candlesAnimationTime = 0.4;

	candleTexture.loadFromFile("Assets/Splash Screen/CandlesSheet.png");

	//set up the candle texture rectangle
	candlesFramePosition = sf::Vector2i(0, 0);
	candlesFrameSize = sf::Vector2i(7, 21);
	candlesFrame = sf::IntRect(candlesFramePosition, candlesFrameSize);

	//set up the candle sprites
	for (int i = 0; i < 4; i++)
	{
		candles[i].setTexture(candleTexture);
		candles[i].setOrigin(candleTexture.getSize().x / 2, candleTexture.getSize().y / 2);
		candles[i].setScale(7, 7);
		candles[i].setTextureRect(candlesFrame);
	}
	candles[0].setPosition(200, 100);
	candles[1].setPosition(650, 100);
	candles[2].setPosition(200, 400);
	candles[3].setPosition(650, 400);
}

/*destructor*/
SplashScreen::~SplashScreen()
{

}

/*Update, used to animate the candles and fireball*/
void SplashScreen::Update()
{
	if (!summoned)//if the game's name has not yet been summoned
	{
		//animate the fireball
		if (fireballAnimationClock.getElapsedTime().asSeconds() > fireballAnimationTime)
		{
			if (fireballFramePosition.x < fireballTexture.getSize().x - fireballFrameSize.x)
				fireballFramePosition.x += fireballFrameSize.x;//move the frame forward

			else
			{
				fireballFramePosition.x = 0;
				if (fireballAnimationTime > -0.5)
				{
					fireballAnimationTime -= 0.05;
				}
				else
				{
					summoned = true;//the game's name has now been summoned! dun dun dun
					summoningCircleSprite.setColor(sf::Color(summoningCircleSprite.getColor().r, summoningCircleSprite.getColor().g, summoningCircleSprite.getColor().b, 127));
				}
			}

			fireballAnimationClock.restart();
		}

		//reset the fireball texture rectangle
		fireballFrameSize = sf::Vector2i(fireballTexture.getSize().x / 4, fireballTexture.getSize().y);
		fireballFrame = sf::IntRect(fireballFramePosition, fireballFrameSize);
		fireballSprite.setTextureRect(fireballFrame);
	}

	//animate the candles
	if (candlesAnimationClock.getElapsedTime().asSeconds() > candlesAnimationTime)
	{
		if (candlesFramePosition.x < candleTexture.getSize().x - candlesFrameSize.x)
			candlesFramePosition.x += candlesFrameSize.x;//move the frame forward

		else candlesFramePosition.x = 0;

		candlesAnimationClock.restart();
	}

	//reset the candles texture rectangle
	candlesFrameSize = sf::Vector2i(candleTexture.getSize().x / 2, candleTexture.getSize().y);
	candlesFrame = sf::IntRect(candlesFramePosition, candlesFrameSize);
	for (int i = 0; i < 4; i++)
	{
		candles[i].setTextureRect(candlesFrame);
	}
	
}

//draw, requires a render target
void SplashScreen::Draw(sf::RenderTarget& window)
{
	//draw the summoning circle
	window.draw(summoningCircleSprite);

	//draw the candles
	for (int i = 0; i < 4; i++)
	{
		window.draw(candles[i]);
	}

	if(!summoned)//if the game's name has not been summoned yet
		window.draw(fireballSprite);//draw the fireball
	else if(summoned)//else if the game's name has been summoned
		window.draw(nameSprite);//draw the game's name
}

//check the summoning status
bool SplashScreen::isSummoned()
{
	return summoned;
}
