#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(std::string assetPath, float h, float r, int t, sf::Vector2f pos)
{
	texture.loadFromFile(assetPath);
	setTexture(texture);
	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	setScale(5, 3);
	health = h;
	rarity = r;
	type = t;
	setPosition(pos);

	boundingBox.setOutlineThickness(2);
	boundingBox.setOutlineColor(sf::Color::White);
	boundingBox.setFillColor(sf::Color::Transparent);

	//set up enemies minimap icon
	if (minimapTexture.loadFromFile("Assets/enemyMinimapIcon.png")) {}
	else minimapTexture.loadFromFile("Assets/Debug.png");	//if it fails load placeholder
	minimapSprite.setTexture(minimapTexture);
	minimapSprite.setScale(5, 3);
	minimapSprite.setOrigin(minimapTexture.getSize().x / 2, minimapTexture.getSize().y / 2);
}

Enemy::~Enemy()
{

}

void Enemy::DrawBoundingBox(sf::RenderTarget & window)
{
	boundingBox.setPosition(sf::Vector2f(getGlobalBounds().left, getGlobalBounds().top));
	boundingBox.setSize(sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height));
	boundingBox.setRotation(getRotation());
	window.draw(boundingBox);
}

void Enemy::MinimapDraw(sf::RenderTarget & window)
{
	minimapSprite.setPosition(getPosition());
	window.draw(minimapSprite);
}
