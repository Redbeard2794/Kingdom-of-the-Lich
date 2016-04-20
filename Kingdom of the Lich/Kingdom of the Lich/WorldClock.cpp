#include "stdafx.h"
#include "WorldClock.h"

WorldClock::WorldClock(sf::Font f, int screenW, int screenH) : font(f)
{
	secondClock.restart();
	currentSeconds = 0;
	currentMinutes = 0;
	currentHours = 9;

	timeMultiplier = 0.5;

	timeText.setFont(font);
	timeText.setCharacterSize(20);
	timeText.setPosition(screenW -275, 175);
	timeText.setColor(sf::Color::White);

	clockTextBackground.setSize(sf::Vector2f(260, 25));
	clockTextBackground.setFillColor(sf::Color::Blue);
	clockTextBackground.setOutlineColor(sf::Color::Black);
	clockTextBackground.setOutlineThickness(2);
	clockTextBackground.setPosition(screenW -275, 175);


	setPosition(screenW - 150, 80);
	setRadius(60);
	setFillColor(sf::Color(sf::Color(212, 175, 55, 255)));
	setOutlineColor(sf::Color(30,144,255,255));
	setOutlineThickness(3);
	setPointCount(120);
	setOrigin(getGlobalBounds().width / 2, getGlobalBounds().height / 2);

	secondHand.setSize(sf::Vector2f(2, 60));
	secondHand.setOrigin(secondHand.getSize().x / 2, secondHand.getSize().y);
	secondHand.setFillColor(sf::Color::Red);
	secondHand.setPosition(getPosition());

	minuteHand.setSize(sf::Vector2f(4, 60));
	minuteHand.setOrigin(minuteHand.getSize().x / 2, minuteHand.getSize().y);
	minuteHand.setFillColor(sf::Color::Black);
	minuteHand.setPosition(getPosition());

	hourHand.setSize(sf::Vector2f(6, 60));
	hourHand.setOrigin(hourHand.getSize().x / 2, hourHand.getSize().y);
	hourHand.setFillColor(sf::Color::Black);
	hourHand.setPosition(getPosition());
	hourHand.setRotation(270);

	if (backgroundTexture.loadFromFile("Assets/newClockBackground.png")) {}
	else backgroundTexture.loadFromFile("Assets/Debug.png");
	setTexture(&backgroundTexture);
	//backgroundSprite.setTexture(backgroundTexture);
	//backgroundSprite.setOrigin(backgroundTexture.getSize().x / 2, backgroundTexture.getSize().y / 2);
	//backgroundSprite.setPosition(getPosition());
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
		if (currentSeconds < 58)
		{
			currentSeconds += 1;
			secondHand.rotate(6);
		}
		else
		{
			secondHand.setRotation(0);
			currentSeconds = 0;
			UpdateMinutes();
		}
	}
}

void WorldClock::UpdateMinutes()
{
	if (currentMinutes < 58)
	{
		currentMinutes += 1;
		minuteHand.rotate(6);
	}
	else
	{
		secondHand.setRotation(0);
		currentMinutes = 0;
		UpdateHours();
	}
}

void WorldClock::UpdateHours()
{
	if (currentHours < 23)
	{
		currentHours += 1;
		hourHand.rotate(30);
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
	//window.draw(backgroundSprite);
	window.draw(secondHand);
	window.draw(minuteHand);
	window.draw(hourHand);
	window.draw(clockTextBackground);
	window.draw(timeText);
}

void WorldClock::DrawBackground(sf::RenderTarget & window)
{
	//window.draw(backgroundSprite);
}
