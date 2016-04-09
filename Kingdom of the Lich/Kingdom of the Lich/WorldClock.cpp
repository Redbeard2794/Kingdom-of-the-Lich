#include "stdafx.h"
#include "WorldClock.h"

WorldClock::WorldClock()
{
	secondClock.restart();
	currentSeconds = 0;
	currentMinutes = 58;
	currentHours = 23;

	timeMultiplier = 0.5;
}

WorldClock::~WorldClock()
{
}

void WorldClock::Update()
{
	int prevS = currentSeconds;
	UpdateSeconds();

	if(currentSeconds!=prevS)
		std::cout << "Current Time: " << currentHours << "::" << currentMinutes << "::" << currentSeconds << std::endl;
}

void WorldClock::UpdateSeconds()
{
	if (secondClock.getElapsedTime().asSeconds() > timeMultiplier)
	{
		secondClock.restart();
		if (currentSeconds < 59)
		{
			currentSeconds += 1;
		}
		else
		{
			currentSeconds = 0;
			UpdateMinutes();
		}
	}
}

void WorldClock::UpdateMinutes()
{
	if (currentMinutes < 59)
	{
		currentMinutes += 1;
	}
	else
	{
		currentMinutes = 0;
		UpdateHours();
	}
}

void WorldClock::UpdateHours()
{
	if (currentHours < 23)
	{
		currentHours += 1;
	}
	else
	{
		currentHours = 0;
	}
}
