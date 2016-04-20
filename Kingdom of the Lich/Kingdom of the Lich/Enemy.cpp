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

	currentState = Healthy;

	numHealingItems = 2;

	if (type == 0)
	{
		xml_document<> doc;
		std::ifstream file("Assets/AttackLists/stoneGolemAttacks.xml");
		std::stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		std::string content(buffer.str());
		doc.parse<0>(&content[0]);

		xml_node<> *pRoot = doc.first_node();
		std::cout << "Name of root node is: " << doc.first_node()->name() << "\n" << std::endl;

		xml_node<>* attackList = doc.first_node("AttackList");
		xml_node<>* attack = attackList->first_node("Attack");

		//load in each attacks's information and then create them
		while (attack != NULL)
		{
			std::string name = "";
			int damageValue = 0;

			/*Get the attacks's name*/
			std::cout << "Name: " << attack->first_attribute("name")->value() << std::endl;
			name = attack->first_attribute("name")->value();

			/*Get the attacks's damage value*/
			std::cout << "Damage Value: " << attack->first_node("damageValue")->value() << std::endl;
			damageValue = atoi(attack->first_node("damageValue")->value());

			std::cout << "------------------------------------------------------------" << std::endl;
			/*Move onto the next npc tag*/
			attack = attack->next_sibling("Attack");

			Attack* a = new Attack(name, damageValue);
			attacks.push_back(a);
		}
	}

	else if (type == 1)
	{
		xml_document<> doc;
		std::ifstream file("Assets/AttackLists/necromancerAttacks.xml");
		std::stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		std::string content(buffer.str());
		doc.parse<0>(&content[0]);

		xml_node<> *pRoot = doc.first_node();
		std::cout << "Name of root node is: " << doc.first_node()->name() << "\n" << std::endl;

		xml_node<>* attackList = doc.first_node("AttackList");
		xml_node<>* attack = attackList->first_node("Attack");

		//load in each attacks's information and then create them
		while (attack != NULL)
		{
			std::string name = "";
			int damageValue = 0;

			/*Get the attacks's name*/
			std::cout << "Name: " << attack->first_attribute("name")->value() << std::endl;
			name = attack->first_attribute("name")->value();

			/*Get the attacks's damage value*/
			std::cout << "Damage Value: " << attack->first_node("damageValue")->value() << std::endl;
			damageValue = atoi(attack->first_node("damageValue")->value());

			std::cout << "------------------------------------------------------------" << std::endl;
			/*Move onto the next npc tag*/
			attack = attack->next_sibling("Attack");

			Attack* a = new Attack(name, damageValue);
			attacks.push_back(a);
		}
	}
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	if (health > 40)
	{
		if (currentState != Healthy)
		{
			std::cout << "Changing state to Healthy." << std::endl;
			currentState = Healthy;
		}
	}
	else if (health < 40 && health > 15)
	{
		if (currentState != Hurt)
		{
			std::cout << "Changing state to Hurt." << std::endl;
			currentState = Hurt;
		}
	}
	else
	{
		if (currentState != HurtBadly)
		{
			std::cout << "Changing state to HurtBadly." << std::endl;
			currentState = HurtBadly;
		}
	}
}

std::string Enemy::TakeTurn(Player* p, bool crit)
{
	std::cout << "Taking my turn now." << std::endl;
	if (currentState == Healthy)
	{
		//attack the player with a random attack
		int max = attacks.size() - 1;
		int a = rand() % max;
		if (crit)
		{
			p->setHealth(p->getHealth() - (attacks.at(a)->GetDamageValue() + (attacks.at(a)->GetDamageValue()*.25)));
			return "Enemy attacked with a critical " + attacks.at(a)->GetName();
		}
		else
		{
			p->setHealth(p->getHealth() - attacks.at(a)->GetDamageValue());
			return "Enemy attacked with a " + attacks.at(a)->GetName();
		}
	}
	else if (currentState == Hurt)
	{
		//check for a healing item and use it if one exists
		if (numHealingItems > 0)
		{
			numHealingItems -= 1;
			health += 25;
			return "Enemy healed itself";
		}
		else
		{
			//attack the player with a stronger attack
			int max = attacks.size() - 1;
			int a = rand() % max;

			for (int i = 0; i < attacks.size(); i++)
			{
				if (attacks.at(i)->GetDamageValue() > attacks.at(a)->GetDamageValue())
				{
					a = i;
					break;
				}
			}

			if (crit)
			{
				p->setHealth(p->getHealth() - (attacks.at(a)->GetDamageValue() + (attacks.at(a)->GetDamageValue()*.25)));
				return "Enemy attacked with a critical " + attacks.at(a)->GetName();
			}
			else
			{
				p->setHealth(p->getHealth() - attacks.at(a)->GetDamageValue());
				return "Enemy attacked with a " + attacks.at(a)->GetName();
			}
			
		}
	}
	else if (currentState == HurtBadly)
	{
		//scream
		//check for a healing item and use it if one exists
		if (numHealingItems > 0)
		{
			numHealingItems -= 1;
			health += 25;
			return "Enemy healed itself";
		}
		else
		{
			//attack the player with strongest attack
			int dmg = attacks.at(0)->GetDamageValue();
			int strongestIndex = 0;

			for (int i = 0; i < attacks.size(); i++)
			{
				if (attacks.at(i)->GetDamageValue() > dmg)
				{
					dmg = attacks.at(i)->GetDamageValue();
					strongestIndex = i;
				}
			}
			if (crit)
			{
				p->setHealth(p->getHealth() - (attacks.at(strongestIndex)->GetDamageValue() + (attacks.at(strongestIndex)->GetDamageValue()*.25)));
				return "Enemy attacked with a critical " + attacks.at(strongestIndex)->GetName();
			}
			else
			{
				p->setHealth(p->getHealth() - attacks.at(strongestIndex)->GetDamageValue());
				return "Enemy attacked with a " + attacks.at(strongestIndex)->GetName();
			}
			
		}
	}
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
