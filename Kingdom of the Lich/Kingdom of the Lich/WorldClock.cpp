#include "stdafx.h"
#include "WorldClock.h"

WorldClock::WorldClock(sf::Font f, int screenW, int screenH) : font(f)
{
	secondClock.restart();
	currentSeconds = 0;
	currentMinutes = 59;
	currentHours = 11;

	timeMultiplier = 0.15;

	timeText.setFont(font);
	timeText.setCharacterSize(20);
	timeText.setPosition(screenW / 1.297, 75);
	timeText.setColor(sf::Color::White);

	clockTextBackground.setSize(sf::Vector2f(260, 25));
	clockTextBackground.setFillColor(sf::Color::Blue);
	clockTextBackground.setOutlineColor(sf::Color::Black);
	clockTextBackground.setOutlineThickness(2);
	clockTextBackground.setPosition(screenW / 1.3, 75);

}

WorldClock::~WorldClock()
{
}

void WorldClock::Update()
{
	int prevS = currentSeconds;
	UpdateSeconds();

	if (currentSeconds != prevS)
	{
		//std::cout << "Current Time: " << currentHours << "::" << currentMinutes << "::" << currentSeconds << std::endl;
		std::string t = "Current Time: ";
		if(currentHours > 10)
			t += std::to_string(currentHours) + "::";
		else t += "0" + std::to_string(currentHours) + "::";
		if (currentMinutes < 10)
			t += "0" + std::to_string(currentMinutes) + "::";
		else t += std::to_string(currentMinutes) + "::";
		if (currentSeconds < 10)
			t += "0" + std::to_string(currentSeconds);
		else t += std::to_string(currentSeconds);
		timeText.setString(t);
		//timeText.setString("Current Time: " + std::to_string(currentHours) + "::" + std::to_string(currentMinutes) + "::" + std::to_string(currentSeconds));
	}
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

int WorldClock::GetCurrentHours()
{
	return currentHours;
}

int WorldClock::GetCurrentMinutes()
{
	return currentMinutes;
}

int WorldClock::GetCurrentSeconds()
{
	return currentSeconds;
}

void WorldClock::SetCurrentHours(int h)
{
	currentHours = h;
}

void WorldClock::SetCurrentMinutes(int m)
{
	currentMinutes = m;
}

void WorldClock::SetCurrentSecs(int s)
{
	currentSeconds = s;
}

void WorldClock::DrawClockText(sf::RenderTarget & window)
{
	window.draw(clockTextBackground);
	window.draw(timeText);
}
