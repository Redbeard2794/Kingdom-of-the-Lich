#include "stdafx.h"
#include "Npc.h"

//name, id, race, gender, texturePath, mapIconTexturePath, x, y, hasQuest, behaviour, show keyboard or controller hint
Npc::Npc(std::string n, int i, std::string texturePath, std::string mapIconTexturePath, sf::Vector2f pos, bool quest, std::string beh, bool controller)
	: name(n), id(i), hasQuest(quest), behaviour(beh)
{
	m_texture.loadFromFile(texturePath);
	setTexture(m_texture);
	setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
	setPosition(pos);

	if (npcMinimapIconTexture.loadFromFile(mapIconTexturePath)) {}
	else npcMinimapIconTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	npcMinimapIcon.setTexture(npcMinimapIconTexture);
	npcMinimapIcon.setOrigin(npcMinimapIconTexture.getSize().x / 2, npcMinimapIconTexture.getSize().y / 2);
	npcMinimapIcon.setPosition(pos);

	LoadInteractHintTexture(controller);
}

//Load the correct texture for the interact hint
void Npc::LoadInteractHintTexture(bool controllerHint)
{
	if (controllerHint == true)
	{
		if (interactHintTexture.loadFromFile("Assets/ControllerHints/pressAtoTalkHint.png")) {}
		else interactHintTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	}
	else
	{
		if (interactHintTexture.loadFromFile("Assets/KeyboardAndMouseHints/pressEtoTalkHint.png")) {}
		else interactHintTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	}
	interactHintSprite.setTexture(interactHintTexture);
	interactHintSprite.setOrigin(interactHintTexture.getSize().x / 2, interactHintTexture.getSize().y / 2);
	interactHintSprite.setPosition(sf::Vector2f(getPosition().x,getPosition().y+50));
}

Npc::~Npc()
{

}

void Npc::Update(sf::Vector2f playerPos)
{
	sf::Vector2f pos = getPosition();
	float distance = sqrtf((((pos.x - playerPos.x)*(pos.x - playerPos.x)) + ((pos.y - playerPos.y)*(pos.y - playerPos.y))));
	
	if(distance < 25)
		interactHintSprite.setColor(sf::Color::White);
	else interactHintSprite.setColor(sf::Color::Transparent);

	npcMinimapIcon.setPosition(getPosition());

	if (behaviour == "wander")
	{
		Wander();
	}

}

void Npc::Wander()
{
	if (behaviourClock.getElapsedTime().asSeconds() > 3)
	{
		wanderPos = sf::Vector2f(getPosition().x + (rand() % 30+10), getPosition().y + (rand() % 30 + 10));
		std::cout << name << " is wandering to " << wanderPos.x << ", " << wanderPos.y << std::endl;

		//now move to the postion(maybe a chance to go back to the previous position?)
		setPosition(wanderPos);
		behaviourClock.restart();
	}
}

void Npc::draw(sf::RenderTarget& window)
{
	window.draw(interactHintSprite);
}

void Npc::MinimapDraw(sf::RenderTarget& window)
{
	window.draw(npcMinimapIcon);
}

std::string Npc::getNpcName()
{
	return name;
}

int Npc::getNpcId()
{
	return id;
}

bool Npc::doesNpcHaveQuest()
{
	return hasQuest;
}

std::string Npc::getBehaviour()
{
	return behaviour;
}
