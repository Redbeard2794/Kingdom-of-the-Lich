#ifndef FOOTPRINTPARTICLE_H
#define FOOTPRINTPARTICLE_H

class FootprintParticle : public Particle
{
private:
	enum PrintType
	{
		LEFT,
		RIGHT,
	};
	int type;
public:
	/*constructor. params: time to live, position to spawn at, type(left or right i.e 0 or 1) and rotation*/
	FootprintParticle(float ttl, sf::Vector2f pos, int t, float r);

	/*Load the correct texture*/
	void LoadTexture();

	/*Update the particle*/
	void Update();

};

#endif
