#include "stdafx.h"
#include "CampFire.h"

CampFire::CampFire(sf::Vector2f pos, int i) : id(i)
{
	if (texture.loadFromFile("Assets/Tiles/sewerLevel/clutterObjects/fire/campFireSheet.png")) {}
	else texture.loadFromFile("Assets/Debug.png");
	setTexture(texture);

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

CampFire::~CampFire()
{
}

void CampFire::Update()
{
	if (animationClock.getElapsedTime().asSeconds() > animationTime)
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
