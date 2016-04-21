#include "stdafx.h"
#include "CampFire.h"

/*constructor. params: position and id*/
CampFire::CampFire(sf::Vector2f pos, int i) : id(i)
{
	if (texture.loadFromFile("Assets/Tiles/sewerLevel/clutterObjects/fire/campFireSheet.png")) {}
	else texture.loadFromFile("Assets/Debug.png");
	setTexture(texture);

	//set up the frame for the animation
	framePosition = sf::Vector2i(0, 0);
	numFrames = 3;
	frameSize.x = texture.getSize().x / numFrames;
	frameSize.y = texture.getSize().y;
	frame = sf::IntRect(framePosition, frameSize);
	animationTime = 0.2f;
	setTextureRect(frame);


	setOrigin(frameSize.x / 2, frameSize.y / 2);

	//scale(2, 2);

	animationClock.restart();

	setPosition(pos);
}

//destructor
CampFire::~CampFire()
{
}

//animate the fire
void CampFire::Update()
{
	if (animationClock.getElapsedTime().asSeconds() > animationTime)//time to move frame on
	{
		if (framePosition.x < texture.getSize().x - frameSize.x)
			framePosition.x += frameSize.x;//move the frame forward

		else
		{
			framePosition.x = 0;
		}

		animationClock.restart();
	}

	//reset the texture rectangle
	frameSize = sf::Vector2i(texture.getSize().x / numFrames, texture.getSize().y);
	frame = sf::IntRect(framePosition, frameSize);
	setTextureRect(frame);
	setOrigin(frameSize.x / 2, frameSize.y / 2);
}
