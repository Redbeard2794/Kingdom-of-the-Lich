#ifndef POPUPMESSAGE_H
#define POPUPMESSAGE_H

class PopupMessage
{
private:

	//is the message a custom text message or a pre-built image message
	bool customMessage;

	//font to use for the message text
	sf::Font font;

	//the message itself(for custom messages only)
	std::string message;

	//the type of prebuilt message
	int preBuiltType;

	//the position to draw the message at
	sf::Vector2f position;

	//the text used to display the custom message
	sf::Text text;

	//the texture for the pre-built message
	sf::Texture texture;

	//the sprite for the pre-built message
	sf::Sprite sprite;

	//how long the message will be displayed for
	float displayTime;

	//clock used to figure out when the message should be removed
	sf::Clock fadeClock;

	//can the message be safely removed
	bool removeable;

	sf::RectangleShape messageBackground;

public:

	/*
	Use this constructor if you want to display a custom message with just text.
	params: font, your message, position to draw at, how long it is displayed for.
	*/
	PopupMessage(sf::Font f, std::string m, sf::Vector2f pos, float fTime, sf::Color col);

	/*
	Use this constructor if you want to use a pre-built message that use's a texture(e.g: press 'A' to open).
	params: type of pre-built message, position to draw it at, how long it is displayed for.
	*/
	PopupMessage(int type, sf::Vector2f pos, float fTime);

	//destructor
	~PopupMessage();

	/*
	Update the message(fade it out)
	*/
	void Update();

	/*
	Draw the message
	*/
	void Draw(sf::RenderTarget& window);

	bool IsRemoveable();
};

#endif
