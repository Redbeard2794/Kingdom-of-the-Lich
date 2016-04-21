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

	std::string currentBehaviour;



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

	std::string greetingFilePath;
	std::vector<std::string> greetings;
	sf::Font font;
	sf::Text greetingText;

	bool displayGreeting;
	sf::Clock greetingClock;

	sf::Texture speechBubbleTexture;
	sf::Sprite speechBubbleSprite;

	bool atAnvil;
	bool atForge;
	float anvilAnimTime;
	float forgeAnimTime;
	int workPoint;
	sf::Texture workAnimTexture;
	sf::Clock workClock;

	bool itemStolen;

	bool reachedAppleStart;
	sf::Vector2f appleStartPoint;
	sf::Vector2f appleEndPoint;

	std::vector<sf::Vector2f> applePoints;
	int currentApplePoint;
	bool spotPicked;

	sf::Clock wanderClock;

	sf::Clock eatClock;
	sf::Texture foodTexture;
	sf::Sprite foodSprite;
	bool eating;

	sf::Vector2f preCollisionPos;

	int wanderCount;

public: 

	//fix these up later
	int behvaiour1H;
	int behvaiour1M;
	int behvaiour1S;
	int behvaiour2H;
	int behvaiour2M;
	int behvaiour2S;
	int behvaiour3H;
	int behvaiour3M;
	int behvaiour3S;
	int behvaiour4H;
	int behvaiour4M;
	int behvaiour4S;

	std::string behaviour1;
	std::string behaviour2;
	std::string behaviour3;
	std::string behaviour4;

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
	void Follow(sf::Vector2f positionToFollow, bool follow);

	void SetBehaviour(int behaviourNum);

	void GoToBed(sf::Vector2f bedPos);

	void WakeUp();

	//npcs with the forge behaviour will work at the blacksmiths forge and anvil
	void Forge();

	void Patrol();

	/*walk between apple trees*/
	void PickApples();

	void Eat();

	//actively avoid the player if they are close enough
	void AvoidPlayer(sf::Vector2f playerPos);

	//load greetings based on player race and gender
	void LoadGreetings(int pRace, int pGender);

	/*Draw the interaction hint sprite*/
	void draw(sf::RenderTarget& window);
	
	//choose a greeting to display
	void ChooseMessage();
	//draw a greeting if the npc is interacted with
	void DrawMessage(sf::RenderTarget& window);

	void DrawBedCovers(sf::RenderTarget& window);

	/*Draw the npc on the minimap as an icon*/
	void MinimapDraw(sf::RenderTarget& window);

	void DrawBoundingBox(sf::RenderTarget& window);

	void DrawFood(sf::RenderTarget& window);

	//gets

	//name
	std::string getNpcName();
	//id
	int getNpcId();
	//hasQuest
	bool doesNpcHaveQuest();
	//behaviour
	std::string getCurrentBehaviour();

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

	bool IsInteractable();

	bool HasStolenItem();
	void SetHasStolenItem(bool h);

	void SetPreCollisionPos(sf::Vector2f p);
	sf::Vector2f GetPreCollisionPos();
};

#endif
