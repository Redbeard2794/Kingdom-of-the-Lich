#ifndef POPUPMESSAGECONTROLLER_H
#define POPUPMESSAGECONTROLLER_H

#include "PopupMessage.h"

class PopupMessageHandler
{
private:
	sf::Font font;

	std::vector<PopupMessage*> messages;

	int activeMessages;
public:
	/*
	Constructor.
	param is the font for custom messages to use
	*/
	PopupMessageHandler(sf::Font f);

	//destructor
	~PopupMessageHandler();

	//Update all active messages
	void UpdateMessages();

	/*
	Add a new custom text message.
	params: message text, position to draw it at, how long the message will be displayed for
	*/
	void AddCustomMessage(std::string message, sf::Vector2f position, float displayTime, sf::Color col);

	/*
	Add a new pre-built picture message.
	params: pre-built message type, position to draw it at, how long the message will be displayed for
	*/
	void AddPreBuiltMessage(int type, sf::Vector2f position, float displayTime);

	//Remove messages that have finished fading out and are safe to remove
	void RemoveMessage();

	//draw all active messages
	void DrawMessages(sf::RenderTarget& window);

	int GetActiveMessageCount();
};

#endif
