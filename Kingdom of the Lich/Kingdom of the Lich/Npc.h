#ifndef NPC_H
#define NPC_H

#include "Emitter.h"
#include "FootprintEmitter.h"

class Npc : public sf::Sprite
{
private:
	std::string name;

	int id;

	sf::Texture m_texture;

	sf::Texture npcMinimapIconTexture;

	sf::Sprite npcMinimapIcon;

	bool hasQuest;

	std::string behaviour;
	std::string behaviour2;
	std::string behaviour3;
	std::string behaviour4;


	sf::Sprite interactHintSprite;
	sf::Texture interactHintTexture;

	sf::Clock behaviourClock;

	//for wandering
	sf::Vector2f wanderPos;
	sf::Vector2f prevWanderPos;
	sf::Vector2f prevPos;
	int timeBetweenWander;

	//for walkPattern
	std::vector<sf::Vector2f> patternPoints;
	int currentPointIndex;
	int prevPointIndex;
	sf::Vector2f direction;

	//for spritesheet handling
	sf::Vector2i framePosition;
	sf::Vector2i frameSize;
	sf::IntRect frame;

	sf::Texture upIdleTexture;
	sf::Texture downIdleTexture;
	sf::Texture rightIdleTexture;
	sf::Texture leftIdleTexture;

	sf::Texture upWalkTexture;
	sf::Texture downWalkTexture;
	sf::Texture rightWalkTexture;
	sf::Texture leftWalkTexture;

	enum Directions
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	int currentDirection;
	int prevDirection;
	bool idle;

	sf::Clock animationClock;

	int numberOfFrames;

	bool colliding;

	sf::RectangleShape boundingBox;

	float distanceToPlayer;

	bool showHint;

	bool interactable;

	FootprintEmitter* footprintEmitter;

	int bedId;
	int bedtimeH;
	int bedtimeM;
	int bedtimeS;

	int wakeTimeH;
	int wakeTimeM;
	int wakeTimeS;

	bool timeForBed;
	sf::Vector2f bedPos;

	bool inBed;

	sf::Texture bedTexture;
	sf::Sprite bedSprite;

	sf::Vector2f patrolPoint1;
	sf::Vector2f patrolPoint2;
	sf::Vector2f patrolPoint3;
	sf::Vector2f patrolPoint4;
	bool patrolPointsPicked;
	sf::Clock patrolWanderClock;
	bool patrolPointReached;
	int currentPatrolPoint;

public: 
	//name, id, race, gender, texturePath, mapIconTexturePath, x, y, hasQuest, behaviour, show keyboard or controller hint
	Npc(std::string n, int i, std::string idleUpPath, std::string idleDownPath, std::string idleLeftPath, std::string idleRightPath, int numFrames, 
		std::string walkUpPath, std::string walkDownPath, std::string walkLeftPath, std::string walkRightPath, std::string mapIconTexturePath
		, sf::Vector2f pos, std::string quest, std::string interact, std::string beh, bool controller);

	//Load the correct texture for the interact hint
	void LoadInteractHintTexture(bool controllerHint);

	~Npc();

	void Update(sf::Vector2f playerPos);
	
	/*Wander to random points within 100 pixels on either the x or y and then stand there for up to 7 seconds.
	If we collide with something, move out of collision and choose a new place to wander to*/
	void Wander();

	/*Walk around in a rectangle from the points set in the constructor*/
	void walkPattern();

	/*Follow the position that is passed in. This is a modified Seek algorithm
	(it can only move up, down, left orright but not at the same time). Only allows 4 directions of movement*/
	void Follow(sf::Vector2f positionToFollow);

	void GoToBed(sf::Vector2f bedPos);

	void WakeUp();

	void Patrol();

	/*Draw the interaction hint sprite*/
	void draw(sf::RenderTarget& window);
	
	void DrawBedCovers(sf::RenderTarget& window);

	/*Draw the npc on the minimap as an icon*/
	void MinimapDraw(sf::RenderTarget& window);

	void DrawBoundingBox(sf::RenderTarget& window);

	//gets

	//name
	std::string getNpcName();
	//id
	int getNpcId();
	//hasQuest
	bool doesNpcHaveQuest();
	//behaviour
	std::string getBehaviour();

	bool IsColliding();

	void setColliding(bool c);

	float CheckDistanceToPlayer();

	void setShowHint(bool s);

	void SetBedId(int id);
	int GetBedId();

	void SetBedtimeH(int h);
	int GetBedtimeH();

	void SetBedtimeM(int m);
	int GetBedtimeM();

	void SetBedtimeS(int s);
	int GetBedtimeS();

	bool IsTimeForBed();
	void SetIsTimeForBed(bool b);

	void SetBedPos(sf::Vector2f bpos);

	bool IsInBed();
	void SetInBed(bool b);

	int GetWakeTH();
	void SetWakeTH(int h);
	void SetWakeTM(int m);
	int GetWakeTM();
	void SetWakeTS(int s);
	int GetWakeTS();
};

#endif
