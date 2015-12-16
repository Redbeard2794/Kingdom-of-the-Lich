#include "stdafx.h"
#include "DamageCalculator.h"

DamageCalculator::DamageCalculator()
{

}

DamageCalculator::~DamageCalculator()
{

}

int DamageCalculator::CalculateDamage(int damageDealt, int healthToDecrease)
{
	return healthToDecrease - damageDealt;
}
