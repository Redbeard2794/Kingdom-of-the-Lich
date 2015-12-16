#ifndef DAMAGECALCULATOR_H
#define DAMAGECALCULATOR_H

class DamageCalculator
{
private:

public:
	DamageCalculator();

	~DamageCalculator();

	int CalculateDamage(int damageDealth, int healthToDecrease);
};

#endif