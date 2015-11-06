#include "stdafx.h"
#include "Npc.h"

Npc::Npc(std::string n, int i, sf::Vector2f pos) : name(n), id(i)
{
	m_texture.loadFromFile("Assets/npcTemp.png");
	setTexture(m_texture);
	setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
	setPosition(pos);
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
	
	if(distance < 100)
		interactHintSprite.setColor(sf::Color::White);
	else interactHintSprite.setColor(sf::Color::Transparent);
}

void Npc::draw(sf::RenderTarget& window)
{
	window.draw(interactHintSprite);
}
