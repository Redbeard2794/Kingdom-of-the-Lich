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
	BloodParticle(float ttl, sf::Vector2f pos, int wType);

	void LoadTexture();

	void Update();
};

#endif
