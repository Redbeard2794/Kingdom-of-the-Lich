#include "stdafx.h"
#include "PopupMessageController.h"

/*
Constructor.
param is the font for custom messages to use
*/
PopupMessageHandler::PopupMessageHandler(sf::Font f) : font(f)
{
	activeMessages = 0;
}

//destructor
PopupMessageHandler::~PopupMessageHandler()
{
	//blank for the moment
}

//Update all active messages
void PopupMessageHandler::UpdateMessages()
{
	activeMessages = messages.size();

	for (int i = 0; i < messages.size(); i++)
	{
		messages.at(i)->Update();
	}

	RemoveMessage();
}

/*
Add a new custom text message.
params: message text, position to draw it at, how long the message will be displayed for
*/
void PopupMessageHandler::AddCustomMessage(std::string message, sf::Vector2f position, float displayTime, sf::Color col)
{
	PopupMessage* p = new PopupMessage(font, message, position, displayTime, col);
	messages.push_back(p);
}

/*
Add a new pre-built picture message.
params: pre-built message type, position to draw it at, how long the message will be displayed for
*/
void PopupMessageHandler::AddPreBuiltMessage(int type, sf::Vector2f position, float displayTime)
{
	PopupMessage* p = new PopupMessage(1, position, displayTime);
	messages.push_back(p);
}

//Remove messages that have finished fading out and are safe to remove
void PopupMessageHandler::RemoveMessage()
{
	for (auto it = messages.begin(); it != messages.end();)
	{
		if ((*it)->IsRemoveable())//if the explosion can be removed
		{
			delete * it;//delete the pointer
			it = messages.erase(it);//erase the object(calls the objects destructor)
			std::cout << "Removed a message." << std::endl;
		}
		else ++it;
	}
}

//draw all active messages
void PopupMessageHandler::DrawMessages(sf::RenderTarget & window)
{
	for (int i = 0; i < messages.size(); i++)
	{
		messages.at(i)->Draw(window);
	}
}

int PopupMessageHandler::GetActiveMessageCount()
{
	return activeMessages;
}
