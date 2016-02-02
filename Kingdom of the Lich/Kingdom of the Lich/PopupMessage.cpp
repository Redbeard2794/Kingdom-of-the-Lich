#include "stdafx.h"
#include "PopupMessage.h"

/*
Use this constructor if you want to display a custom message with just text.
params: font, your message, position to draw at, how long it is displayed for.
*/
PopupMessage::PopupMessage(sf::Font f, std::string m, sf::Vector2f pos, float fTime) : font(f)
{
	customMessage = true;
	removeable = false;

	message = m;

	position = pos;

	displayTime = fTime;

	fadeClock.restart();

	text.setFont(font);
	text.setString(message);
	text.setColor(sf::Color::Black);
	text.setCharacterSize(30);
	text.setPosition(position);
}

/*
Use this constructor if you want to use a pre-built message that use's a texture(e.g: press 'A' to open).
params: type of pre-built message, position to draw it at, how long it is displayed for.
*/
PopupMessage::PopupMessage(int type, sf::Vector2f pos, float fTime)
{
	customMessage = false;
	removeable = false;
	fadeClock.restart();
	displayTime = fTime;

	if (type == 1)//use dpad to move
	{
		texture.loadFromFile("Assets/ControllerHints/useLeftStickToMoveHint.png");
	}

	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	sprite.setPosition(pos);

}

//destructor
PopupMessage::~PopupMessage()
{
	if (customMessage)
	{

	}
	else
	{

	}
}

/*
Update the message(fade it out)
*/
void PopupMessage::Update()
{
	if (fadeClock.getElapsedTime().asSeconds() > displayTime)
	{
		if(customMessage)
			text.setColor(sf::Color(text.getColor().r, text.getColor().g, text.getColor().b, text.getColor().a - 1));
		else
			sprite.setColor(sf::Color(sprite.getColor().r, sprite.getColor().g, sprite.getColor().b, sprite.getColor().a - 1));
	}

	//decide if the message can be removed
	if (customMessage)
	{
		if (text.getColor().a <= 0)
			removeable = true;
	}
	else
	{
		if (sprite.getColor().a <= 0)
			removeable = true;
	}
}

/*
Draw the message
*/
void PopupMessage::Draw(sf::RenderTarget & window)
{
	if (customMessage)
	{
		window.draw(text);
	}
	else
	{
		window.draw(sprite);
	}
}

bool PopupMessage::IsRemoveable()
{
	return removeable;
}
