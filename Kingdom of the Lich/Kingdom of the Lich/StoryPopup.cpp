#include "stdafx.h"
#include "StoryPopup.h"

//constructor. Params: screen width and height
StoryPopup::StoryPopup(int sw, int sh) : screenW(sw), screenH(sh)
{
	allInfoRevealed = false;
	infoRevealClock.restart();
}

//destructor
StoryPopup::~StoryPopup()
{
	texture.~Texture();
}

/*
set the story to display.
Load the correct texture and reset texture rectangle
*/
void StoryPopup::SetStory(int story)
{
	currentStory = story;//set the current story

	//load the correct texture for the current story
	if (currentStory == INTRO)
	{
		if (texture.loadFromFile("Assets/StoryScreens/intro/storyIntro" + std::to_string(screenW) + "x" + std::to_string(screenH) + ".png")) {}
		else texture.loadFromFile("Assets/Debug.png");

		setTexture(texture);
		textureRect = sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(screenW, screenH / 8));
		setTextureRect(textureRect);
	}
	else if (currentStory == SEWER)
	{
		if (texture.loadFromFile("Assets/StoryScreens/")) {}
		else texture.loadFromFile("Assets/Debug.png");
	}

	infoRevealClock.restart();//restart the clock
}

//Check if it is time to show more information/end
void StoryPopup::Update()
{
	if (infoRevealClock.getElapsedTime().asSeconds() > 3.5)
	{
		if (!allInfoRevealed)//if not all the information has been revealed
		{
			IncreaseTextureRect();
			infoRevealClock.restart();
		}
	}
}

//increase how much of the texture we want to show
void StoryPopup::IncreaseTextureRect()
{
	if (textureRect.height >= screenH)//check to see if full texture displayed
	{
		allInfoRevealed = true;
	}
	else//if not then show more
	{
		textureRect.height += screenH / 8;
		setTextureRect(textureRect);
	}
}

bool StoryPopup::IsAllInfoRevealed()
{
	return allInfoRevealed;
}
