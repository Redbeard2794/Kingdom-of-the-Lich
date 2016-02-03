#include "stdafx.h"
#include "Attack.h"

//constructor. params are attack name and damage value
Attack::Attack(std::string n, int dv)
{
	name = n;
	damageValue = dv;
}

//destructor
Attack::~Attack()
{
	//blank for the moment
}

//retrieve the attack name
std::string Attack::GetName()
{
	return name;
}

//retrieve the damage value
int Attack::GetDamageValue()
{
	return damageValue;
}
