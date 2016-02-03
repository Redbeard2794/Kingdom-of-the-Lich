#ifndef ATTACK_H
#define ATTACK_H

class Attack
{
private:
	std::string name;//attack name

	int damageValue;//how much damage the attack does

public:
	//constructor. params are attack name and damage value
	Attack(std::string n, int dv);

	//destructor
	~Attack();

	//retrieve the attack name
	std::string GetName();

	//retrieve the damage value
	int GetDamageValue();
};

#endif