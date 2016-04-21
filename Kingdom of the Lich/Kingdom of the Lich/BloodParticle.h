#ifndef BLOODPARTICLE_H
#define BLOODPARTICLE_H

class BloodParticle : public Particle
{
private:
	enum WoundTypes
	{
		MINOR,
		MAJOR,
		FATAL
	};
	int type;

	float speed;

public:
	/*constructor. params: time to live, start position, wound type*/
	BloodParticle(float ttl, sf::Vector2f pos, int wType);

	/*load correct texture*/
	void LoadTexture();

	/*update the particle*/
	void Update();
};

#endif
