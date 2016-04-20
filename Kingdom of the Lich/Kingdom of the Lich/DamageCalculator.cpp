#include "stdafx.h"
#include "DamageCalculator.h"

/*constructor*/
DamageCalculator::DamageCalculator()
{

}

//destructor
DamageCalculator::~DamageCalculator()
{

}

//calculate damage. params: damage, health
int DamageCalculator::CalculateDamage(int damageDealt, int healthToDecrease)
{
	return healthToDecrease - damageDealt;
}
