#include "stdafx.h"
#include "Npc.h"

Npc::Npc(std::string n, int i, sf::Vector2f pos) : name(n), id(i)
{
	m_texture.loadFromFile("Assets/npcTemp.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
	setPosition(pos);
}

Npc::~Npc()
{

}

void Npc::Update()
{

}

void Npc::draw(sf::RenderTarget& window, sf::RenderStates state) const {}

void Npc::draw(sf::RenderTarget& window)
{
	window.draw(m_sprite, getTransform());
}