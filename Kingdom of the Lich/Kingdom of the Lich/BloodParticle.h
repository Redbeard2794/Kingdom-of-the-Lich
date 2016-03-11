#ifndef BLOODPARTICLE_H
#define BLOODPARTICLE_H

class BloodParticle : public Particle
{
private:

public:
	BloodParticle(float ttl, sf::Vector2f pos);

	void LoadTexture();

	void Update();
};

#endif
