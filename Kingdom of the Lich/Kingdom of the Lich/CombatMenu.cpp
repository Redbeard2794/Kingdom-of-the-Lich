#include "stdafx.h"
#include "CombatMenu.h"

/*constructor. params: font, path for enemy texture, screen width, screen height*/
CombatMenu::CombatMenu(sf::Font f, std::string ePath, int sw, int sh) : font(f)
{
	playersTurn = false;
	turnCount = 0;

	turnText.setFont(font);
	turnText.setString("Completed turns: ");
	turnText.setColor(sf::Color::Black);
	turnText.setCharacterSize(20);
	turnText.setPosition(sf::Vector2f(25, 25));

	screenW = sw;
	screenH = sh;

	if (backgroundTexture.loadFromFile("Assets/Combat/moveSelectorBackground/combatMoveSelectorBackground" + std::to_string(screenW) + "x" + std::to_string(screenH) + ".png")) {}
	else backgroundTexture.loadFromFile("Assets/Combat/moveSelectorBackground/combatMoveSelectorBackground.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(0, screenH - backgroundTexture.getSize().y);

	menuItems[0].setFont(font);
	menuItems[0].setString("Fight");
	menuItems[0].setColor(sf::Color::Red);
	menuItems[0].setCharacterSize(40);
	menuItems[0].setPosition(sf::Vector2f(screenW / 8, screenH - 125));

	menuItems[1].setFont(font);
	menuItems[1].setString("Items");
	menuItems[1].setColor(sf::Color::Blue);
	menuItems[1].setCharacterSize(40);
	menuItems[1].setPosition(sf::Vector2f(screenW / 2.1, screenH - 125));

	menuItems[2].setFont(font);
	menuItems[2].setString("Flee");
	menuItems[2].setColor(sf::Color::Blue);
	menuItems[2].setCharacterSize(40);
	menuItems[2].setPosition(sf::Vector2f(screenW / 1.2, screenH - 125));

	selectorTexture.loadFromFile("Assets/combatUiSelector.png");
	selectorSprite.setTexture(selectorTexture);
	selectorSprite.setOrigin(selectorTexture.getSize().x / 2, selectorTexture.getSize().y / 2);
	selectorSprite.setPosition(screenW / 4.7, screenH - 100);//225

	//attack panel
	attackPanelTexture.loadFromFile("Assets/attackSelectionPanel.png");
	attackPanelSprite.setTexture(attackPanelTexture);
	attackPanelSprite.setOrigin(attackPanelTexture.getSize().x / 2, attackPanelTexture.getSize().y / 2);
	attackPanelSprite.setPosition(200, 200);

	//attack options
	sf::Text* attack1 = new sf::Text();
	attack1->setFont(font);
	attack1->setString("Stab");
	attack1->setColor(sf::Color::Red);
	attack1->setCharacterSize(25);
	attack1->setPosition(sf::Vector2f(75, 25));
	attackOptions.push_back(attack1);

	sf::Text* attack2 = new sf::Text();
	attack2->setFont(font);
	attack2->setString("Quick Chop");
	attack2->setColor(sf::Color::Blue);
	attack2->setCharacterSize(25);
	attack2->setPosition(sf::Vector2f(75, 75));
	attackOptions.push_back(attack2);

	sf::Text* attack3 = new sf::Text();
	attack3->setFont(font);
	attack3->setString("Slice");
	attack3->setColor(sf::Color::Blue);
	attack3->setCharacterSize(25);
	attack3->setPosition(sf::Vector2f(75, 125));
	attackOptions.push_back(attack3);

	//item panel
	itemPanelTexture.loadFromFile("Assets/itemSelectionPanel.png");
	itemPanelSprite.setTexture(itemPanelTexture);
	itemPanelSprite.setOrigin(itemPanelTexture.getSize().x / 2, itemPanelTexture.getSize().y / 2);
	itemPanelSprite.setPosition(400, 200);

	//item options
	sf::Text* item1 = new sf::Text();
	item1->setFont(font);
	item1->setString("Health Potion");
	item1->setColor(sf::Color::Red);
	item1->setCharacterSize(25);
	item1->setPosition(sf::Vector2f(260, 25));
	itemOptions.push_back(item1);

	sf::Text* item2 = new sf::Text();
	item2->setFont(font);
	item2->setString("Bottle of Ale");
	item2->setColor(sf::Color::Blue);
	item2->setCharacterSize(25);
	item2->setPosition(sf::Vector2f(260, 75));
	itemOptions.push_back(item2);

	sf::Text* item3 = new sf::Text();
	item3->setFont(font);
	item3->setString("Apple");
	item3->setColor(sf::Color::Blue);
	item3->setCharacterSize(25);
	item3->setPosition(sf::Vector2f(260, 125));
	itemOptions.push_back(item3);

	playerHealthText.setFont(font);
	playerHealthText.setString("Player Health: ");
	playerHealthText.setColor(sf::Color::Blue);
	playerHealthText.setCharacterSize(30);
	playerHealthText.setPosition(30, screenH/1.6);

	enemyTexture.loadFromFile(ePath);
	enemySprite.setTexture(enemyTexture);

	enemyFramePosition = sf::Vector2i(0, 0);
	numFrames = 4;
	enemyFrameSize.x = enemyTexture.getSize().x / numFrames;
	enemyFrameSize.y = enemyTexture.getSize().y;
	enemyFrame = sf::IntRect(enemyFramePosition, enemyFrameSize);
	enemyAnimationTime = 0.2f;
	enemySprite.setTextureRect(enemyFrame);


	enemySprite.setOrigin(enemyFrameSize.x / 2, enemyFrameSize.y / 2);


	//enemySprite.setOrigin(enemyTexture.getSize().x, enemyTexture.getSize().y);
	enemySprite.setScale(8, 8);
	enemySprite.setPosition(screenW/ 1.2, screenH/4); 
	
	enemyHealthText.setFont(font);
	enemyHealthText.setString("Stone Golem Health: ");
	enemyHealthText.setColor(sf::Color::Red);
	enemyHealthText.setCharacterSize(30);
	enemyHealthText.setPosition(screenW/1.5, screenH/3);

	enemyName = "Stone Golem";

	currentOption = 0;
	currentAction = 0;
	canMove = true;

	combatOver = false;

	if(combatBackgroundTexture.loadFromFile("Assets/Combat/backgrounds/grass/grass" + std::to_string(screenW) + "x" + std::to_string(screenH) + ".png")){}
	else combatBackgroundTexture.loadFromFile("Assets/Combat/backgrounds/grass/grass_template2.jpg");
	combatBackgroundSprite.setTexture(combatBackgroundTexture);
	combatBackgroundSprite.setPosition(0, 0);

	//hints
	moveSelectionHintTexture.loadFromFile("Assets/ControllerHints/useLeftStickToMoveHint.png");
	moveSelectionHintSprite.setTexture(moveSelectionHintTexture);
	//moveSelectionHintSprite.setScale(0.8, 0.4);
	moveSelectionHintSprite.setPosition(50, screenH/ 1.42);

	selectHintTexture.loadFromFile("Assets/ControllerHints/pressAtoSelectHint.png");
	selectHintSprite.setTexture(selectHintTexture);
	//selectHintSprite.setScale(0.8, 0.7);
	selectHintSprite.setPosition(screenW/2.5, screenH / 1.38);

	goBackHintTexture.loadFromFile("Assets/ControllerHints/pressBtoGoBack.png");
	goBackHintSprite.setTexture(goBackHintTexture);
	//goBackHintSprite.setScale(0.8, 0.7);
	goBackHintSprite.setPosition(screenW / 1.4, screenH / 1.38);

	canSelect = false;

	finishedAttackAnim = false;
	enemyFinishedAttackAnim = false;
}

/*destructor*/
CombatMenu::~CombatMenu()
{

}

//set the correct texture for the player based on race and gender. params: player race, player gender
void CombatMenu::SetPlayerRepSprite(int race, int gender)
{
	std::string filePath = "Assets/Player/";

	if (race == 0)//Human
		filePath+="Human/";
	else if (race == 1)//Elf
		filePath+="Elf/";
	else if (race == 2)//Dwarf
		filePath+="Dwarf/";

	if (gender == 0)//male
		filePath += "Male/";
	else if (gender == 1)//female
		filePath += "Female/";

	filePath += "Combat/upAttackSheet.png";


	playerRepTexture.loadFromFile(filePath);
	playerRepSprite.setTexture(playerRepTexture);

	//set up for animation
	framePosition = sf::Vector2i(0, 0);
	numFrames = 4;
	frameSize.x = playerRepTexture.getSize().x / numFrames;
	frameSize.y = playerRepTexture.getSize().y;
	frame = sf::IntRect(framePosition, frameSize);
	animationTime = 0.2f;

	playerRepSprite.setTextureRect(frame);

	
	playerRepSprite.setOrigin(frameSize.x / 2, frameSize.y / 2);
	playerRepSprite.setScale(8, 8);
	playerRepSprite.setPosition(screenW / 6, screenH / 1.9);

}

//move right through the menu(for choosing action)
void CombatMenu::MoveSelectionRight()
{
	if (canMove == true)
	{
		if (currentAction == 2)
			currentAction = 0;
		else currentAction += 1;

		for (int i = 0; i < 3; i++)
		{
			menuItems[i].setColor(sf::Color::Blue);
		}
		menuItems[currentAction].setColor(sf::Color::Red);
	}
}

//move left through the menu(for choosing action)
void CombatMenu::MoveSelectionLeft()
{
	if (canMove == true)
	{
		if (currentAction == 0)
			currentAction = 2;
		else currentAction -= 1;

		for (int i = 0; i < 3; i++)
		{
			menuItems[i].setColor(sf::Color::Blue);
		}
		menuItems[currentAction].setColor(sf::Color::Red);
	}
}

//move up through the menu(for choosing attack/item)
void CombatMenu::MoveSelectionUp()
{
	int size = 0;
	if (currentState == SelectAttack)
		size = attackOptions.size();
	else if (currentState == SelectItem)
		size = itemOptions.size();

	if (canMove == true)
	{
		if (currentOption == 0)
		{
			currentOption = size - 1;

			//if(currentState == SelectAttack)
			//	selectorSprite.setPosition(sf::Vector2f(325, 135));
			//else if (currentState == SelectItem)
			//	selectorSprite.setPosition(sf::Vector2f(525, 135));
		}
		else
		{
			currentOption -= 1;
			//selectorSprite.setPosition(selectorSprite.getPosition().x, selectorSprite.getPosition().y - 45);
		}

		for (int i = 0; i < size; i++)
		{
			if(currentState == SelectAttack)
				attackOptions.at(i)->setColor(sf::Color::Blue);
			else if(currentState == SelectItem)
				itemOptions.at(i)->setColor(sf::Color::Blue);
		}

		if (currentState == SelectAttack)
			attackOptions.at(currentOption)->setColor(sf::Color::Red);
		else if (currentState == SelectItem)
			itemOptions.at(currentOption)->setColor(sf::Color::Red);
	}
}

//move down through the menu(for choosing attack/item)
void CombatMenu::MoveSelectionDown()
{
	int size = 0;
	if (currentState == SelectAttack)
		size = attackOptions.size();
	else if (currentState == SelectItem)
		size = itemOptions.size();

	if (canMove == true)
	{
		if (currentOption == size - 1)
		{
			currentOption = 0;

			//if (currentState == SelectAttack)
			//	selectorSprite.setPosition(sf::Vector2f(325, 45));
			//else if(currentState == SelectItem)
			//	selectorSprite.setPosition(sf::Vector2f(525, 45));
		}
		else
		{
			currentOption += 1;
			//selectorSprite.setPosition(selectorSprite.getPosition().x, selectorSprite.getPosition().y + 45);
		}

		for (int i = 0; i < size; i++)
		{
			if (currentState == SelectAttack)
				attackOptions.at(i)->setColor(sf::Color::Blue);
			else if (currentState == SelectItem)
				itemOptions.at(i)->setColor(sf::Color::Blue);
		}

		if (currentState == SelectAttack)
			attackOptions.at(currentOption)->setColor(sf::Color::Red);
		else if (currentState == SelectItem)
			itemOptions.at(currentOption)->setColor(sf::Color::Red);
	}
}

//set the player and enemy health. params: player health, enemy health
void CombatMenu::Update(int playerHealth, int enemyHealth)
{
	playerCurrentHealth = playerHealth;
	enemyCurrentHealth = enemyHealth;
}

/*Draw all elements of the menu*/
void CombatMenu::Draw(sf::RenderTarget & window)
{
	window.draw(combatBackgroundSprite);
	window.draw(backgroundSprite);
	for (int i = 0; i < 3; i++)
	{
		window.draw(menuItems[i]);
	}
	window.draw(moveSelectionHintSprite);
	window.draw(selectHintSprite);
	window.draw(goBackHintSprite);

	turnText.setString("Completed turns: " + std::to_string(turnCount));
	window.draw(turnText);

	window.draw(enemySprite);
	enemyHealthText.setString(enemyName + "Health: " + std::to_string(enemyCurrentHealth));
	window.draw(enemyHealthText);
	window.draw(playerRepSprite);
	playerHealthText.setString("Player Health: " + std::to_string(playerCurrentHealth));
	window.draw(playerHealthText);


	if (currentState == SelectAction)
	{
		window.draw(selectorSprite);
		if (currentAction == 0)
			selectorSprite.setPosition(screenW / 4.7, selectorSprite.getPosition().y);
		else if(currentAction == 1)
			selectorSprite.setPosition(screenW / 1.8, selectorSprite.getPosition().y);//475
		else if(currentAction == 2)
			selectorSprite.setPosition(screenW / 1.1, selectorSprite.getPosition().y);//750
	}

	else if (currentState == SelectAttack)
	{
		window.draw(attackPanelSprite);
		window.draw(selectorSprite);
		for (int i = 0; i < attackOptions.size(); i++)
		{
			window.draw(*attackOptions.at(i));
		}
		if (screenW == 1366 && screenH == 768)
		{
			if (currentOption == 0)
				selectorSprite.setPosition(selectorSprite.getPosition().x, screenH / 16.3);
			else if (currentOption == 1)
				selectorSprite.setPosition(selectorSprite.getPosition().x, screenH / 8);//475
			else if (currentOption == 2)
				selectorSprite.setPosition(selectorSprite.getPosition().x, screenH / 5.4);//750
		}
		else if (screenW == 1600 && screenH == 900)
		{
			if (currentOption == 0)
				selectorSprite.setPosition(selectorSprite.getPosition().x, screenH / 19);
			else if (currentOption == 1)
				selectorSprite.setPosition(selectorSprite.getPosition().x, screenH / 9.3);//475
			else if (currentOption == 2)
				selectorSprite.setPosition(selectorSprite.getPosition().x, screenH / 6.4);//750
		}
	}
	else if (currentState == SelectItem)
	{
		window.draw(itemPanelSprite);
		window.draw(selectorSprite);
		for (int i = 0; i < itemOptions.size(); i++)
		{
			window.draw(*itemOptions.at(i));
		}
		if (screenW == 1366 && screenH == 768)
		{
			if (currentOption == 0)
				selectorSprite.setPosition(selectorSprite.getPosition().x, screenH / 16.3);
			else if (currentOption == 1)
				selectorSprite.setPosition(selectorSprite.getPosition().x, screenH / 8);//475
			else if (currentOption == 2)
				selectorSprite.setPosition(selectorSprite.getPosition().x, screenH / 5.4);//750
		}
		else if (screenW == 1600 && screenH == 900)
		{
			if (currentOption == 0)
				selectorSprite.setPosition(selectorSprite.getPosition().x, screenH / 19);
			else if (currentOption == 1)
				selectorSprite.setPosition(selectorSprite.getPosition().x, screenH / 9.3);//475
			else if (currentOption == 2)
				selectorSprite.setPosition(selectorSprite.getPosition().x, screenH / 6.4);//750
		}
	}
	else if (currentState == FleeAttempt)
	{

	}
}

//move th eplayer sprite in front of the enemy so it can attack
void CombatMenu::MovePlayerToAttack()
{
	if (playerRepSprite.getPosition().x < enemySprite.getPosition().x-100)
		playerRepSprite.setPosition(playerRepSprite.getPosition().x + 1, playerRepSprite.getPosition().y);
	if (playerRepSprite.getPosition().y > enemySprite.getPosition().y + 100)
		playerRepSprite.setPosition(playerRepSprite.getPosition().x, playerRepSprite.getPosition().y - 1);
}

//set up attack animation for player or enemy based on parameter passed in. true = player, false = enemy
void CombatMenu::SetUpAttackAnimations(bool player)
{
	if (player)
	{
		animationClock.restart();
		finishedAttackAnim = false;
		playerRepSprite.setPosition(screenW / 1.3, screenH / 4);
	}
	else
	{
		enemyAnimationClock.restart();
		enemyFinishedAttackAnim = false;
		enemySprite.setPosition(screenW / 6, screenH / 2.1);
	}
}

//animate the players attack
void CombatMenu::PlayerAttackAnimation()
{
	if (!finishedAttackAnim)//if animation not finished
	{
		if (animationClock.getElapsedTime().asSeconds() > animationTime)
		{
			if (framePosition.x < playerRepTexture.getSize().x - frameSize.x)
				framePosition.x += frameSize.x;//move the frame forward

			else
			{
				framePosition.x = 0;
				finishedAttackAnim = true;
				playerRepSprite.setPosition(screenW / 6, screenH / 1.9);
			}

			animationClock.restart();
		}

		//reset the texture rectangle
		frameSize = sf::Vector2i(playerRepTexture.getSize().x / numFrames, playerRepTexture.getSize().y);
		frame = sf::IntRect(framePosition, frameSize);
		playerRepSprite.setTextureRect(frame);
		playerRepSprite.setOrigin(frameSize.x / 2, frameSize.y / 2);
	}
}

//animate the enemies attack
void CombatMenu::EnemyAttackAnimation()
{
	if (!enemyFinishedAttackAnim)//if animation not finished
	{
		if (enemyAnimationClock.getElapsedTime().asSeconds() > enemyAnimationTime)
		{
			if (enemyFramePosition.x < enemyTexture.getSize().x - enemyFrameSize.x)
				enemyFramePosition.x += enemyFrameSize.x;//move the frame forward

			else
			{
				enemyFramePosition.x = 0;
				enemyFinishedAttackAnim = true;
				
				enemySprite.setPosition(screenW / 1.2, screenH / 4);
			}

			enemyAnimationClock.restart();
		}

		//reset the texture rectangle
		enemyFrameSize = sf::Vector2i(enemyTexture.getSize().x / numFrames, enemyTexture.getSize().y);
		enemyFrame = sf::IntRect(enemyFramePosition, enemyFrameSize);
		enemySprite.setTextureRect(enemyFrame);
		enemySprite.setOrigin(enemyFrameSize.x / 2, enemyFrameSize.y / 2);
	}
}

//reset textures and turn values etc to be ready for the next combat. params: path to enemy texture, enemy name
void CombatMenu::ResetForNextCombat(std::string ePath, std::string eName)
{
	//reset enemy sprite and texture
	enemyTexture.loadFromFile(ePath);
	enemySprite.setTexture(enemyTexture);
	enemyFramePosition = sf::Vector2i(0, 0);
	numFrames = 4;
	enemyFrameSize.x = enemyTexture.getSize().x / numFrames;
	enemyFrameSize.y = enemyTexture.getSize().y;
	enemyFrame = sf::IntRect(enemyFramePosition, enemyFrameSize);
	enemyAnimationTime = 0.2f;
	enemySprite.setTextureRect(enemyFrame);
	enemySprite.setOrigin(enemyFrameSize.x / 2, enemyFrameSize.y / 2);
	enemySprite.setScale(8, 8);
	enemySprite.setPosition(screenW / 1.2, screenH / 4);
	//reset text for enemy health
	enemyHealthText.setString(eName+ "Health: ");

	combatOver = false;
	currentOption = 0;
	currentAction = 0;
	canMove = true;
	canSelect = false;
	finishedAttackAnim = false;
	enemyFinishedAttackAnim = false;
	playersTurn = true;
	turnCount = 0;
	enemyName = eName;

	if (combatBackgroundTexture.loadFromFile("Assets/Combat/backgrounds/brick/brickBack" + std::to_string(screenW) + "x" + std::to_string(screenH) + ".png")) {}
	else combatBackgroundTexture.loadFromFile("Assets/Combat/backgrounds/grass/grass_template2.jpg");
	combatBackgroundSprite.setTexture(combatBackgroundTexture);
}

/*gets & sets start*/

int CombatMenu::getCurrentAction()
{
	return currentAction;
}

int CombatMenu::getCurrentOption()
{
	return currentOption;
}

void CombatMenu::setCurrentOption(int o)
{
	currentOption = 0;
}

bool CombatMenu::getCanMove()
{
	return canMove;
}

void CombatMenu::setCanMove(bool cm)
{
	canMove = cm;
}

int CombatMenu::GetCurrentMenuState()
{
	return currentState;
}

void CombatMenu::SetCurrentMenuState(int newState)
{
	currentState = newState;
}

void CombatMenu::SetSelectorPosition(sf::Vector2f pos)
{
	selectorSprite.setPosition(pos);
}

sf::Vector2f CombatMenu::GetSelectorPosition()
{
	return selectorSprite.getPosition();
}

bool CombatMenu::IsCombatOver()
{
	return combatOver;
}

void CombatMenu::setCombatOver(bool co)
{
	combatOver = co;
}

bool CombatMenu::IsPlayersTurn()
{
	return playersTurn;
}

void CombatMenu::SetPlayersTurn(bool t)
{
	playersTurn = t;
	if(playersTurn == true)
		std::cout << "It is the players turn" << std::endl;
	else if(playersTurn == false)
		std::cout << "It is not the players turn" << std::endl;
}

int CombatMenu::GetTurnCount()
{
	return turnCount;
}

void CombatMenu::IncrementTurnCount()
{
	turnCount += 1;
}

std::string CombatMenu::GetEnemyName()
{
	return enemyName;
}

/*gets & sets end*/
