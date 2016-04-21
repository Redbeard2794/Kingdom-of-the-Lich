#ifndef PLAYER_H
#define PLAYER_H
#include "Compass.h"
#include "Npc.h"
#include "Subject.h"
class Player : public sf::Sprite, public Subject
{
private:
	sf::Vector2f velocity;
	sf::Sprite mSprite;

	sf::Texture mTexture;

	//for representing the player on the minimap
	sf::Texture minimapTexture;
	sf::Sprite minimapSprite;

	float speed;

	float health;

	sf::Vector2f direction;

	//character info
	int race;
	int gender;
	int playerClass;

	bool isRunning;

	sf::Font font;

	enum Race
	{
		HUMAN,
		ELF,
		Dwarf
	};

	enum Gender
	{
		MALE,
		FEMALE
	};

	enum Class
	{
		ARCHER,
		KNIGHT,
		SPELLBLADE
	};

	enum Directions
	{
		NORTH,//0
		SOUTH,//1
		EAST,//2
		WEST,//3
		NOTMOVING//4
	};
	int currentDirection;
	int previousDirection;
	int lockedDirection;

	sf::RectangleShape boundingBox;
	sf::Vector2f preCollisionPosition;
	bool colliding;
	sf::Vector2f collisionSeparation;

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

	/*The total number of frames in the sheet*/
	int numFrames;

	/*How long does it take to move through each frame*/
	float animationTime;

	/*clock for moving through the sheet*/
	sf::Clock animationClock;

	int openedChests;
	int potionsUsed;
	bool enteredPubFirstTime;
	bool enteredSewerFirstTime;
	int combatsComplete;
	bool stoleStuffBack;
	bool hasPlayerBoughtSomething;
	bool hasPlayerSoldSomething;
	int numPeopleTalkedTo;
	int numGems;

public:
	//constructor(param is a font)
	Player(sf::Font f);
	//destructor
	~Player();

	void Update();//sf::Vector2f objectivePos, std::string currentQuestName);

	//Set the player's texture based on their chosen race
	void setTextures();

	/*Move the player in the direction they are travelling in
	Don't allow them to move if that direction is locked due to collision with another object*/
	void Move(int newDir);

	void Animate();

	/*Check to see if the player is colliding with a chest*/
	bool CollisionWithChest(sf::Sprite chestSprite);

	void DrawBoundingBox(sf::RenderTarget& window);

	/*draw the player on the minimap*/
	void MinimapDraw(sf::RenderTarget& window);

#pragma region Properties
	//start gets
	sf::Vector2f getVelocity() { return velocity; }
	sf::Sprite getSprite() { return mSprite; }
	float getSpeed() { return speed; }
	float getHealth() { return health; }
	bool getIsRunning() { return isRunning; }

	int getRace() { return race; }
	int getGender() { return gender; }
	int getClass() { return playerClass; }
	int getCurrentDirection() { return currentDirection; }

	int getPreviousDirection() { return previousDirection; }

	bool IsColliding() { return colliding; }
	sf::Vector2f GetPreCollisionPosition() { return preCollisionPosition; }
	int GetOpenedChests() { return openedChests; }
	int GetPotionsDrank() { return potionsUsed; }
	bool HasPlayerGonePub() { return enteredPubFirstTime; }
	bool HasPlayerGoneSewers() { return enteredSewerFirstTime; }
	int GetNumberCompletedCombats() { return combatsComplete; }
	bool HasPlayerStoleStuffBack() { return stoleStuffBack; }
	bool HasPlayerBoughtSomething() { return hasPlayerBoughtSomething; }
	bool HasPlayerSoldSomething() { return hasPlayerSoldSomething; }
	int GetNumPeopleTalkedTo() { return numPeopleTalkedTo; }
	int GetGems() {return numGems; }
	//end gets
	//start sets
	void setHealth(float h) { health = h; }
	void setVelocity(sf::Vector2f vel) { velocity = vel; }
	void setSpeed(float s) { speed = s; }
	void setIsRunning(bool r) { isRunning = r; }

	void setRace(int r) { race = r; }
	void setGender(int g) { gender = g; }
	void setClass(int c) { playerClass = c; }

	void setCurrentDirection(int currDir) { currentDirection = currDir; }
	void setPreviousDirection(int pDir) { previousDirection = pDir; }

	void setCollidingStatus(bool c) { colliding = c; }
	void setCollisionSeparation(sf::Vector2f sep) { collisionSeparation = sep; }
	void IncreaseOpenedChests(int c) { openedChests += c; }
	void IncreasePotionsDrank(int p) { potionsUsed += p; }
	void SetPlayerGonePub(bool pub) { enteredPubFirstTime = pub; }
	void SetPlayerGoneSewer(bool sewer) { enteredSewerFirstTime = sewer; }
	void IncreaseCombatsComplete(int c) { combatsComplete += c; }
	void SetStoleStuffBack(bool s) { stoleStuffBack = s; }
	void SetPlayerBoughtSomething(bool b) { hasPlayerBoughtSomething = b; }
	void SetPlayerSellSomething(bool b) { hasPlayerSoldSomething = b; }
	void IncreaseNumPeopleTalkedTo(int t) { numPeopleTalkedTo += t; }
	void SetGems(int g) { numGems = g; }
	//end sets
#pragma endregion

};

#endif