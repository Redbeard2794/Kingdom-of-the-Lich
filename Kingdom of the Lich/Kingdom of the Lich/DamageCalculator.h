#ifndef DAMAGECALCULATOR_H
#define DAMAGECALCULATOR_H

class DamageCalculator
{
private:

public:
	/*constructor*/
	DamageCalculator();

	//destructor
	~DamageCalculator();

	//calculate damage. params: damage, health
	int CalculateDamage(int damageDealt, int healthToDecrease);
};

#endif