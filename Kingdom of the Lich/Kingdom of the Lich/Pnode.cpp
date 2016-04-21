#include "stdafx.h"
#include "pNode.h"

//Pnode::Pnode(sf::Vector2f pos, std::string i) : parentNode(0)
//{
//	//initialise f, g and h values to 0
//	f = 0;
//	g = 0;
//	h = 0;
//
//	//load the texture to represent the node
//	if (texture.loadFromFile("Assets/Pathfinding/node.png")) {}
//	else texture.loadFromFile("Assets/Debug.png");
//	setTexture(texture);
//	setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
//	setPosition(pos);
//
//	obstructed = false;
//
//	id = i;
//
//	visited = false;
//}
//
//Pnode::~Pnode()
//{
//}
//
//void Pnode::SetG(float pg)
//{
//	g += pg;
//}
//
////Calculate f. f = g + h. param is the position of the destination node
//void Pnode::CalculateF(sf::Vector2f destPos)
//{
//	CalculateH(destPos);
//	f = g + h;//heuristic is 100% accurate for now
//}
//
////calculate the heuristic. param is the destination node position
//void Pnode::CalculateH(sf::Vector2f destPos)
//{
//	//euclidean distance
//	//h = sqrtf((destPos.x - getPosition().x * destPos.x - getPosition().x) + ((destPos.y - getPosition().y) * (destPos.y - getPosition().y)));
//
//	//manhattan distance
//	float x = getPosition().x - destPos.x;
//	float y = getPosition().y - destPos.y;
//	h = x + y;
//}
//
//float Pnode::GetF()
//{
//	return f;
//}
//
//float Pnode::GetG()
//{
//	return g;
//}
//
//float Pnode::GetH()
//{
//	return h;
//}
//
//bool Pnode::IsVisited()
//{
//	return visited;
//}
//
//void Pnode::SetVisited(bool v)
//{
//	visited = v;
//}
//
//Pnode * Pnode::GetParent()
//{
//	return parentNode;
//}
//
//void Pnode::SetParent(Pnode * p)
//{
//	parentNode = p;
//}
//
//void Pnode::SetH(float newH)
//{
//	h = newH;
//}

Pnode::Pnode(sf::Vector2f pos)
{
	setSize(sf::Vector2f(50, 50));
	setOrigin(getSize().x / 2, getSize().y / 2);
	setFillColor(sf::Color::Transparent);
	setOutlineColor(sf::Color::Blue);
	setOutlineThickness(2);
	setPosition(pos);

	g = 0;
	f = 0;
	h = 0;
	parentNode = NULL;
	obstructed = false;
	visited = false;
	inPath = false;
}

Pnode::~Pnode()
{
	//blank for the moment
}

float Pnode::GetG()
{
	return g;
}

void Pnode::SetG(float newG)
{
	g = newG;
}

float Pnode::GetF()
{
	return f;
}

void Pnode::SetF(float newF)
{
	f = newF;
}

float Pnode::GetH()
{
	return h;
}

void Pnode::SetH(float newH)
{
	h = newH;
}

bool Pnode::IsObstructed()
{
	return obstructed;
}

void Pnode::SetObstructed(bool o)
{
	obstructed = o;
}

bool Pnode::WasVisited()
{
	return visited;
}

void Pnode::SetVisited(bool v)
{
	visited = v;
}

bool Pnode::IsInPath()
{
	return inPath;
}

void Pnode::SetInPath(bool ip)
{
	inPath = ip;
}

Pnode * Pnode::GetParent()
{
	return parentNode;
}

void Pnode::SetParent(Pnode * p)
{
	parentNode = p;
}
