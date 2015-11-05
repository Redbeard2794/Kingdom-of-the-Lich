#include "stdafx.h"
#include "Npc.h"

Npc::Npc(std::string n, int i, sf::Vector2f pos) : name(n), id(i)
{
	m_texture.loadFromFile("Assets/npcTemp.png");
	setTexture(m_texture);
	setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
	setPosition(pos);
}

Npc::~Npc()
{

}

void Npc::Update()
{

}
