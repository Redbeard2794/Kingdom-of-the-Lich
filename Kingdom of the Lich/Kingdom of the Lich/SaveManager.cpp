#include "stdafx.h"
#include "SaveManager.h"

SaveManager::SaveManager(sf::Font f, int sw, int sh) :font(f), screenW(sw), screenH(sh)
{
	savePath = "Saves/save";

	saveHeading.setFont(font);
	saveHeading.setString("Are you sure you want to save?");
	saveHeading.setPosition(screenW / 4, 50);
	saveHeading.setColor(sf::Color::White);

	menuItems[0].setFont(font);
	menuItems[0].setString("Yes");
	menuItems[0].setColor(sf::Color::Green);
	menuItems[0].setCharacterSize(50);
	menuItems[0].setPosition(sf::Vector2f(screenW / 2.36, screenH / 6.5));

	menuItems[1].setFont(font);
	menuItems[1].setString("No");
	menuItems[1].setColor(sf::Color::White);
	menuItems[1].setCharacterSize(50);
	menuItems[1].setPosition(sf::Vector2f(screenW / 2.33, screenH / 3.5));

	saveSlots[0].setFont(font);
	saveSlots[0].setString("Save 1");
	saveSlots[0].setColor(sf::Color::Green);
	saveSlots[0].setCharacterSize(50);
	saveSlots[0].setPosition(sf::Vector2f(screenW / 2.36, screenH / 5.7));
	slotImages[0].setPosition(sf::Vector2f(screenW / 2.36, screenH / 4));

	saveSlots[1].setFont(font);
	saveSlots[1].setString("Save 2");
	saveSlots[1].setColor(sf::Color::White);
	saveSlots[1].setCharacterSize(50);
	saveSlots[1].setPosition(sf::Vector2f(screenW / 2.36, screenH / 2.5));
	slotImages[1].setPosition(sf::Vector2f(screenW / 2.36, screenH / 2.1));

	saveSlots[2].setFont(font);
	saveSlots[2].setString("Save 3");
	saveSlots[2].setColor(sf::Color::White);
	saveSlots[2].setCharacterSize(50);
	saveSlots[2].setPosition(sf::Vector2f(screenW / 2.36, screenH / 1.6));
	slotImages[2].setPosition(sf::Vector2f(screenW / 2.36, screenH / 1.4));

	emptySlotTexture.loadFromFile("Saves/EmptySlotImage.png");

	for (int i = 0; i < 3; i++)
	{
		slotImages[i].setTexture(&emptySlotTexture);
		slotImages[i].setOutlineColor(sf::Color::White);
		slotImages[i].setSize(sf::Vector2f(150, 100));
		slotImages[i].setOutlineThickness(5);
	}

	if (slotOneTexture.loadFromFile("Saves/save1ScreenShot.png")) {}
	else slotOneTexture.loadFromFile("Saves/EmptySlotImage.png");
	slotImages[0].setTexture(&slotOneTexture);

	if (slotTwoTexture.loadFromFile("Saves/save2ScreenShot.png")) {}
	else slotTwoTexture.loadFromFile("Saves/EmptySlotImage.png");
	slotImages[1].setTexture(&slotTwoTexture);

	if (slotThreeTexture.loadFromFile("Saves/save3ScreenShot.png")) {}
	else slotThreeTexture.loadFromFile("Saves/EmptySlotImage.png");
	slotImages[2].setTexture(&slotThreeTexture);

	currentSelected = 0;

	canMove = true;

	currentState = NONE;
	saving = false;
}

SaveManager::~SaveManager()
{
	savePath.clear();
}

void SaveManager::SaveGame(int raceVal, int genderVal, int healthVal, int numChestsVal, int numPotionsVal, bool pubFirstVal, 
	bool sewerFirstVal, int combatsCompleteVal, sf::Vector2f pos, int areaVal, Inventory* playerInv, Quest* q1, WorldClock* clock)
{
	xml_document<> doc;
	std::ifstream file(savePath);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	//doc.parse<0>(&content[0]);
	doc.parse<rapidxml::parse_no_data_nodes>(&content[0]);

	xml_node<> *pRoot = doc.first_node();

	xml_node<>* save = doc.first_node("Save");

	/*race*/
	std::cout << "Previous Race: " << save->first_node("race")->value() << std::endl;
	std::string raceText;
	if (raceVal == 0)
		raceText = "human";
	else if (raceVal == 1)
		raceText = "elf";
	else if (raceVal == 2)
		raceText = "dwarf";
	const char * rt = doc.allocate_string(raceText.c_str(), strlen(raceText.c_str()));
	save->first_node("race")->value(rt);
	std::cout << "New Race: " << save->first_node("race")->value() << std::endl;

	/*gender*/
	std::cout << "Previous Gender: " << save->first_node("gender")->value() << std::endl;
	std::string genderText;
	if (genderVal == 0)
		genderText = "male";
	else if (genderVal == 1)
		genderText = "female";
	const char * gt = doc.allocate_string(genderText.c_str(), strlen(genderText.c_str()));
	save->first_node("gender")->value(gt);
	std::cout << "New Gender: " << save->first_node("gender")->value() << std::endl;

	/*health*/
	std::cout << "Previous Health: " << save->first_node("health")->value() << std::endl;
	std::string healthText = std::to_string(healthVal);
	const char * ht = doc.allocate_string(healthText.c_str(), strlen(healthText.c_str()));
	save->first_node("health")->value(ht);
	std::cout << "New Health: " << save->first_node("health")->value() << std::endl;

	/*number of chests opened*/
	std::cout << "Previous numChests: " << save->first_node("numChests")->value() << std::endl;
	std::string chestText = std::to_string(numChestsVal);
	const char * ct = doc.allocate_string(chestText.c_str(), strlen(chestText.c_str()));
	save->first_node("numChests")->value(ct);
	std::cout << "New numChests: " << save->first_node("numChests")->value() << std::endl;

	/*number of potions drank*/
	std::cout << "Previous numPotionsUsed: " << save->first_node("numPotionsUsed")->value() << std::endl;
	std::string potionsText = std::to_string(numPotionsVal);
	const char * pt = doc.allocate_string(potionsText.c_str(), strlen(potionsText.c_str()));
	save->first_node("numPotionsUsed")->value(pt);
	std::cout << "New numPotionsUsed: " << save->first_node("numPotionsUsed")->value() << std::endl;

	/*entered pub for first time*/
	std::cout << "Previous pubFirst: " << save->first_node("pubFirst")->value() << std::endl;
	std::string pubText = std::to_string(pubFirstVal);
	const char * pubt = doc.allocate_string(pubText.c_str(), strlen(pubText.c_str()));
	save->first_node("pubFirst")->value(pubt);
	std::cout << "New pubFirst: " << save->first_node("pubFirst")->value() << std::endl;

	/*entered sewers for first time*/
	std::cout << "Previous sewerFirst: " << save->first_node("sewerFirst")->value() << std::endl;
	std::string sewerText = std::to_string(sewerFirstVal);
	const char * sewt = doc.allocate_string(sewerText.c_str(), strlen(sewerText.c_str()));
	save->first_node("sewerFirst")->value(sewt);
	std::cout << "New sewerFirst: " << save->first_node("sewerFirst")->value() << std::endl;

	/*combats completed*/
	std::cout << "Previous numCombatsComplete: " << save->first_node("numCombatsComplete")->value() << std::endl;
	std::string combatText = std::to_string(combatsCompleteVal);
	const char * comt = doc.allocate_string(combatText.c_str(), strlen(combatText.c_str()));
	save->first_node("numCombatsComplete")->value(comt);
	std::cout << "New numCombatsComplete: " << save->first_node("numCombatsComplete")->value() << std::endl;

	/*position*/
	std::cout << "Previous Position: " << save->first_node("x")->value() << ", " << save->first_node("y")->value() << std::endl;
	std::string xText = std::to_string(pos.x);
	const char * posxt = doc.allocate_string(xText.c_str(), strlen(xText.c_str()));
	save->first_node("x")->value(posxt);
	std::string yText = std::to_string(pos.y);
	const char * posyt = doc.allocate_string(yText.c_str(), strlen(yText.c_str()));
	save->first_node("y")->value(posyt);
	std::cout << "New Position: " << save->first_node("x")->value() << ", " << save->first_node("y")->value() << std::endl;

	/*area*/
	std::cout << "Previous area: " << save->first_node("area")->value() << std::endl;
	std::string areaText = std::to_string(areaVal);
	const char * areat = doc.allocate_string(areaText.c_str(), strlen(areaText.c_str()));
	save->first_node("area")->value(areat);
	std::cout << "New area: " << save->first_node("area")->value() << std::endl;

	/*health potion quantity*/
	std::cout << "Previous Health Potion Quantity: " << save->first_node("healthPotionQuantity")->value() << std::endl;
	std::string healthPotionQText = std::to_string(playerInv->CheckQuantity(playerInv->i_healthPotion.key, false));
	const char * hpqText = doc.allocate_string(healthPotionQText.c_str(), strlen(healthPotionQText.c_str()));
	save->first_node("healthPotionQuantity")->value(hpqText);
	std::cout << "New Health Potion Quantity: " << save->first_node("healthPotionQuantity")->value() << std::endl;

	/*bottle of ale quantity*/
	std::cout << "Previous aleQuantity: " << save->first_node("aleQuantity")->value() << std::endl;
	std::string aleQText = std::to_string(playerInv->CheckQuantity(playerInv->i_ale.key, false));
	const char * aqText = doc.allocate_string(aleQText.c_str(), strlen(aleQText.c_str()));
	save->first_node("aleQuantity")->value(aqText);
	std::cout << "New aleQuantity: " << save->first_node("aleQuantity")->value() << std::endl;

	/*loaf of bread quantity*/
	std::cout << "Previous breadQuantity: " << save->first_node("breadQuantity")->value() << std::endl;
	std::string breadQText = std::to_string(playerInv->CheckQuantity(playerInv->i_bread.key, false));
	const char * bqText = doc.allocate_string(breadQText.c_str(), strlen(breadQText.c_str()));
	save->first_node("breadQuantity")->value(bqText);
	std::cout << "New breadQuantity: " << save->first_node("breadQuantity")->value() << std::endl;

	/*apple quantity*/
	std::cout << "Previous appleQuantity: " << save->first_node("appleQuantity")->value() << std::endl;
	std::string appleQText = std::to_string(playerInv->CheckQuantity(playerInv->i_apple.key, false));
	const char * appqText = doc.allocate_string(appleQText.c_str(), strlen(appleQText.c_str()));
	save->first_node("appleQuantity")->value(appqText);
	std::cout << "New appleQuantity: " << save->first_node("appleQuantity")->value() << std::endl;

	/*gem quantity*/
	std::cout << "Previous gemQuantity: " << save->first_node("gemQuantity")->value() << std::endl;
	std::string gemQText = std::to_string(playerInv->CheckQuantity(playerInv->i_gems.key, false));
	const char * gemqText = doc.allocate_string(gemQText.c_str(), strlen(gemQText.c_str()));
	save->first_node("gemQuantity")->value(gemqText);
	std::cout << "New gemQuantity: " << save->first_node("gemQuantity")->value() << std::endl;

	/*baracks key quantity*/
	std::cout << "Previous BaracksKeyQuantity: " << save->first_node("baracksKeyQuantity")->value() << std::endl;
	std::string bKeyText = std::to_string(playerInv->CheckQuantity(playerInv->i_baracksKey.key, false));
	const char * bkText = doc.allocate_string(bKeyText.c_str(), strlen(bKeyText.c_str()));
	save->first_node("baracksKeyQuantity")->value(bkText);
	std::cout << "New BaracksKeyQuantity: " << save->first_node("baracksKeyQuantity")->value() << std::endl;

	/*parchment quantity*/
	std::cout << "Previous parchmentQuantity: " << save->first_node("parchmentQuantity")->value() << std::endl;
	std::string parchmentText = std::to_string(playerInv->CheckQuantity(playerInv->i_parchment.key, false));
	const char * parText = doc.allocate_string(parchmentText.c_str(), strlen(parchmentText.c_str()));
	save->first_node("parchmentQuantity")->value(parText);
	std::cout << "New parchmentQuantity: " << save->first_node("parchmentQuantity")->value() << std::endl;

	/*ink bottle quantity*/
	std::cout << "Previous inkBottleQuantity: " << save->first_node("inkBottleQuantity")->value() << std::endl;
	std::string inkText = std::to_string(playerInv->CheckQuantity(playerInv->i_inkBottle.key, false));
	const char * inkBText = doc.allocate_string(inkText.c_str(), strlen(inkText.c_str()));
	save->first_node("inkBottleQuantity")->value(inkBText);
	std::cout << "New inkBottleQuantity: " << save->first_node("inkBottleQuantity")->value() << std::endl;

	/*quill quantity*/
	std::cout << "Previous quillQuantity: " << save->first_node("quillQuantity")->value() << std::endl;
	std::string quillText = std::to_string(playerInv->CheckQuantity(playerInv->i_quill.key, false));
	const char * qText = doc.allocate_string(quillText.c_str(), strlen(quillText.c_str()));
	save->first_node("quillQuantity")->value(qText);
	std::cout << "New quillQuantity: " << save->first_node("quillQuantity")->value() << std::endl;

	//quest 1 complete
	std::cout << "Previous quest1Complete: " << save->first_node("quest1Complete")->value() << std::endl;
	std::string quest1Text = std::to_string(q1->getCompletionStatus());
	const char * q1T = doc.allocate_string(quest1Text.c_str(), strlen(quest1Text.c_str()));
	save->first_node("quest1Complete")->value(q1T);
	std::cout << "New quest1Complete: " << save->first_node("quest1Complete")->value() << std::endl;

	//quest 1 stage
	std::cout << "Previous quest1CurrentStage: " << save->first_node("quest1CurrentStage")->value() << std::endl;
	std::string quest1StageText = std::to_string(q1->getCurrentStageIndex());
	const char * q1sT = doc.allocate_string(quest1StageText.c_str(), strlen(quest1StageText.c_str()));
	save->first_node("quest1CurrentStage")->value(q1sT);
	std::cout << "New quest1CurrentStage: " << save->first_node("quest1CurrentStage")->value() << std::endl;

	//clock
	std::string clockHText = std::to_string(clock->GetCurrentHours());
	const char * chT = doc.allocate_string(clockHText.c_str(), strlen(clockHText.c_str()));
	save->first_node("clockHours")->value(chT);
	std::string clockMText = std::to_string(clock->GetCurrentMinutes());
	const char * cmT = doc.allocate_string(clockMText.c_str(), strlen(clockMText.c_str()));
	save->first_node("clockMins")->value(cmT);
	std::string clockSText = std::to_string(clock->GetCurrentSeconds());
	const char * csT = doc.allocate_string(clockSText.c_str(), strlen(clockSText.c_str()));
	save->first_node("clockSecs")->value(csT);

	//// Convert doc to string if needed
	std::string xml_as_string;
	rapidxml::print(std::back_inserter(xml_as_string), doc);

	// Save to file
	std::ofstream file_stored(savePath);
	file_stored << doc;
	file_stored.close();
	doc.clear();

	saving = false;
}

//load a game. return true if the save is not empty. if it is then load a new game
bool SaveManager::LoadGame(Player* player, AchievementTracker* achievementTracker, AreaManager* areaManager, Inventory* playerInv, Quest* q1, WorldClock* clock)
{
	savePath = "Saves/save" + std::to_string(currentSelected + 1) + ".xml";

	xml_document<> doc;
	std::ifstream file(savePath);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	//doc.parse<0>(&content[0]);
	doc.parse<rapidxml::parse_no_data_nodes>(&content[0]);

	xml_node<> *pRoot = doc.first_node();

	xml_node<>* save = doc.first_node("Save");

	std::string race = save->first_node("race")->value();

	if (race == "unknown")//if race = unknown then the save is empty
		return false;

	std::string gender = save->first_node("gender")->value();
	int health = std::atoi(save->first_node("health")->value());
	int numChests = std::atoi(save->first_node("numChests")->value());
	int numPotionsUsed = std::atoi(save->first_node("numPotionsUsed")->value());
	bool pubFirst = std::atoi(save->first_node("pubFirst")->value());
	bool sewerFirst = std::atoi(save->first_node("sewerFirst")->value());
	int numCombatsComplete = std::atoi(save->first_node("numCombatsComplete")->value());
	float x = std::atof(save->first_node("x")->value());
	float y = std::atof(save->first_node("y")->value());
	int area = std::atoi(save->first_node("area")->value());
	int healthPotionQuantity = std::atoi(save->first_node("healthPotionQuantity")->value());
	int aleQuantity = std::atoi(save->first_node("aleQuantity")->value());
	int breadQuantity = std::atoi(save->first_node("breadQuantity")->value());
	int appleQuantity = std::atoi(save->first_node("appleQuantity")->value());
	int gemQuantity = std::atoi(save->first_node("gemQuantity")->value());
	int baracksKeyQuantity = std::atoi(save->first_node("baracksKeyQuantity")->value());
	int parchmentQuantity = std::atoi(save->first_node("parchmentQuantity")->value());
	int inkBottleQuantity = std::atoi(save->first_node("inkBottleQuantity")->value());
	int quillQuantity = std::atoi(save->first_node("quillQuantity")->value());
	bool quest1Complete = std::atoi(save->first_node("quest1Complete")->value());
	int quest1Stage = std::atoi(save->first_node("quest1CurrentStage")->value());
	int clockHours = std::atoi(save->first_node("clockHours")->value());
	int clockMins = std::atoi(save->first_node("clockMins")->value());
	int clockSecs = std::atoi(save->first_node("clockSecs")->value());

	//set the player's race
	if (race == "human")
		player->setRace(0);
	else if (race == "elf")
		player->setRace(1);
	else if (race == "dwarf")
		player->setRace(2);
	//set the player's gender
	if (gender == "male")
		player->setGender(0);
	else if (gender == "female")
		player->setGender(1);
	//set the player's health
	player->setHealth(health);
	//set the number of chests the player has opened
	player->IncreaseOpenedChests(numChests);
	//set the number of potions the player has drank
	player->IncreasePotionsDrank(numPotionsUsed);
	//set whether the player has visited a pub
	player->SetPlayerGonePub(pubFirst);
	//set whether the player has visited the sewers
	player->SetPlayerGoneSewer(sewerFirst);
	//set the number of combats the player has completed
	player->IncreaseCombatsComplete(numCombatsComplete);
	//set the player's position
	player->setPosition(x, y);
	//set the current area
	areaManager->SetCurrentArea(area);//////////////////not working properly??? a door is triggered?
	//set health potion quantity
	if (healthPotionQuantity != 0)
		playerInv->AddItemToInventory(playerInv->i_healthPotion.key, healthPotionQuantity);
	//set player bottle of ale quantity
	if (aleQuantity != 0)
		playerInv->AddItemToInventory(playerInv->i_ale.key, aleQuantity);
	//set the loaf of bread quantity
	if (breadQuantity != 0)
		playerInv->AddItemToInventory(playerInv->i_bread.key, breadQuantity);
	//set the apple quantity
	if (appleQuantity != 0)
		playerInv->AddItemToInventory(playerInv->i_apple.key, appleQuantity);
	//set the gem quantity
	if (gemQuantity != 0)
		playerInv->AddItemToInventory(playerInv->i_gems.key, gemQuantity);
	//set baracks key quantity
	if (baracksKeyQuantity != 0)
		playerInv->AddItemToInventory(playerInv->i_baracksKey.key, baracksKeyQuantity);
	//set parchment quantity
	if (parchmentQuantity != 0)
		playerInv->AddItemToInventory(playerInv->i_parchment.key, parchmentQuantity);
	//set ink bottle quantity
	if (inkBottleQuantity != 0)
		playerInv->AddItemToInventory(playerInv->i_inkBottle.key, inkBottleQuantity);
	//set the quill quantity
	if (quillQuantity != 0)
		playerInv->AddItemToInventory(playerInv->i_quill.key, quillQuantity);
	//quest 1 completion status
	q1->setCompletionStatus(quest1Complete);
	//quest 1 current stage
	q1->setCurrentStageIndex(quest1Stage);
	//set the time
	clock->SetCurrentHours(clockHours);
	clock->SetCurrentMinutes(clockMins);
	clock->SetCurrentSecs(clockSecs);

	for (int i = 0; i < 5; i++)
	{
		achievementTracker->Update();
	}
	achievementTracker->LoadPrevUnlockedAchievements();

	return true;
}

//clear all save slots of save data
void SaveManager::ClearAllSaveSlots()
{
	std::string path = "Saves/Save1.xml";
	std::string screenShotPath = "Saves/save1ScreenShot.png";

	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			path = "Saves/Save1.xml";
			screenShotPath = "Saves/save1ScreenShot.png";
		}
		else if (i == 1)
		{
			path = "Saves/Save2.xml";
			screenShotPath = "Saves/save2ScreenShot.png";
		}
		else if (i == 2)
		{
			path = "Saves/Save3.xml";
			screenShotPath = "Saves/save3ScreenShot.png";
		}

		xml_document<> doc;
		std::ifstream file(path);
		std::stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		std::string content(buffer.str());
		//doc.parse<0>(&content[0]);
		doc.parse<rapidxml::parse_no_data_nodes>(&content[0]);

		xml_node<> *pRoot = doc.first_node();

		xml_node<>* save = doc.first_node("Save");

		/*race*/
		std::string raceText = "unknown";
		const char * rt = doc.allocate_string(raceText.c_str(), strlen(raceText.c_str()));
		save->first_node("race")->value(rt);

		/*gender*/
		std::string genderText = "unknown";
		const char * gt = doc.allocate_string(genderText.c_str(), strlen(genderText.c_str()));
		save->first_node("gender")->value(gt);

		/*health*/
		std::string healthText = std::to_string(0);
		const char * ht = doc.allocate_string(healthText.c_str(), strlen(healthText.c_str()));
		save->first_node("health")->value(ht);

		/*number of chests opened*/
		std::string chestText = std::to_string(0);
		const char * ct = doc.allocate_string(chestText.c_str(), strlen(chestText.c_str()));
		save->first_node("numChests")->value(ct);

		/*number of potions drank*/
		std::string potionsText = std::to_string(0);
		const char * pt = doc.allocate_string(potionsText.c_str(), strlen(potionsText.c_str()));
		save->first_node("numPotionsUsed")->value(pt);

		/*entered pub for first time*/
		std::string pubText = std::to_string(0);
		const char * pubt = doc.allocate_string(pubText.c_str(), strlen(pubText.c_str()));
		save->first_node("pubFirst")->value(pubt);

		/*entered sewers for first time*/
		std::string sewerText = std::to_string(0);
		const char * sewt = doc.allocate_string(sewerText.c_str(), strlen(sewerText.c_str()));
		save->first_node("sewerFirst")->value(sewt);

		/*combats completed*/
		std::string combatText = std::to_string(0);
		const char * comt = doc.allocate_string(combatText.c_str(), strlen(combatText.c_str()));
		save->first_node("numCombatsComplete")->value(comt);

		/*position*/
		std::string xText = std::to_string(0);
		const char * posxt = doc.allocate_string(xText.c_str(), strlen(xText.c_str()));
		save->first_node("x")->value(posxt);
		std::string yText = std::to_string(0);
		const char * posyt = doc.allocate_string(yText.c_str(), strlen(yText.c_str()));
		save->first_node("y")->value(posyt);

		/*area*/
		std::string areaText = std::to_string(0);
		const char * areat = doc.allocate_string(areaText.c_str(), strlen(areaText.c_str()));
		save->first_node("area")->value(areat);

		/*health potion quantity*/
		std::string healthPotionQText = std::to_string(0);
		const char * hpqText = doc.allocate_string(healthPotionQText.c_str(), strlen(healthPotionQText.c_str()));
		save->first_node("healthPotionQuantity")->value(hpqText);

		/*bottle of ale quantity*/
		std::string aleQText = std::to_string(0);
		const char * aqText = doc.allocate_string(aleQText.c_str(), strlen(aleQText.c_str()));
		save->first_node("aleQuantity")->value(aqText);

		/*loaf of bread quantity*/
		std::string breadQText = std::to_string(0);
		const char * bqText = doc.allocate_string(breadQText.c_str(), strlen(breadQText.c_str()));
		save->first_node("breadQuantity")->value(bqText);

		/*apple quantity*/
		std::string appleQText = std::to_string(0);
		const char * appqText = doc.allocate_string(appleQText.c_str(), strlen(appleQText.c_str()));
		save->first_node("appleQuantity")->value(appqText);

		/*gem quantity*/
		std::string gemQText = std::to_string(0);
		const char * gemqText = doc.allocate_string(gemQText.c_str(), strlen(gemQText.c_str()));
		save->first_node("gemQuantity")->value(gemqText);

		/*baracks key quantity*/
		std::string bKeyText = std::to_string(0);
		const char * bkText = doc.allocate_string(bKeyText.c_str(), strlen(bKeyText.c_str()));
		save->first_node("baracksKeyQuantity")->value(bkText);

		/*parchment quantity*/
		std::string parchmentText = std::to_string(0);
		const char * parText = doc.allocate_string(parchmentText.c_str(), strlen(parchmentText.c_str()));
		save->first_node("parchmentQuantity")->value(parText);

		/*ink bottle quantity*/
		std::string inkText = std::to_string(0);
		const char * inkBText = doc.allocate_string(inkText.c_str(), strlen(inkText.c_str()));
		save->first_node("inkBottleQuantity")->value(inkBText);

		/*quill quantity*/
		std::string quillText = std::to_string(0);
		const char * qText = doc.allocate_string(quillText.c_str(), strlen(quillText.c_str()));
		save->first_node("quillQuantity")->value(qText);

		//quest 1 complete
		std::string quest1Text = std::to_string(0);
		const char * q1T = doc.allocate_string(quest1Text.c_str(), strlen(quest1Text.c_str()));
		save->first_node("quest1Complete")->value(q1T);

		//quest 1 stage
		std::cout << "Previous quest1CurrentStage: " << save->first_node("quest1CurrentStage")->value() << std::endl;
		std::string quest1StageText = std::to_string(0);
		const char * q1sT = doc.allocate_string(quest1StageText.c_str(), strlen(quest1StageText.c_str()));
		save->first_node("quest1CurrentStage")->value(q1sT);
		std::cout << "New quest1CurrentStage: " << save->first_node("quest1CurrentStage")->value() << std::endl;

		//clock
		std::string clockHText = std::to_string(0);
		const char * chT = doc.allocate_string(clockHText.c_str(), strlen(clockHText.c_str()));
		save->first_node("clockHours")->value(chT);
		std::string clockMText = std::to_string(0);
		const char * cmT = doc.allocate_string(clockMText.c_str(), strlen(clockMText.c_str()));
		save->first_node("clockMins")->value(cmT);
		std::string clockSText = std::to_string(0);
		const char * csT = doc.allocate_string(clockSText.c_str(), strlen(clockSText.c_str()));
		save->first_node("clockSecs")->value(csT);

		// Save to file
		std::ofstream file_stored(path);
		file_stored << doc;
		file_stored.close();
		doc.clear();

		if (remove(screenShotPath.c_str()) != 0)
			perror("Error deleting file");
		else
			puts("File successfully deleted");
	}
}

void SaveManager::UpdateState()
{
	if (currentState == SAVE && currentSelected == 0)
	{
		currentState = ChooseSaveSlot;
		saveHeading.setString("Choose a save slot");
		if (slotOneTexture.loadFromFile("Saves/save1ScreenShot.png")) {}
		else slotOneTexture.loadFromFile("Saves/EmptySlotImage.png");
		slotImages[0].setTexture(&slotOneTexture);
		if (slotTwoTexture.loadFromFile("Saves/save2ScreenShot.png")) {}
		else slotTwoTexture.loadFromFile("Saves/EmptySlotImage.png");
		slotImages[1].setTexture(&slotTwoTexture);
		if (slotThreeTexture.loadFromFile("Saves/save3ScreenShot.png")) {}
		else slotThreeTexture.loadFromFile("Saves/EmptySlotImage.png");
		slotImages[2].setTexture(&slotThreeTexture);
	}
	else if (currentState == SAVE && currentSelected == 1)
	{
		currentState = EXIT;
	}
	else if (currentState == ChooseSaveSlot)
	{
		saving = true;
		savePath = "Saves/save" + std::to_string(currentSelected + 1) + ".xml";
		currentState = EXIT;
	}
}

void SaveManager::NavUp()
{
	if (canMove == true)
	{
		if (currentState == SAVE)
		{
			if (currentSelected == 0)
				currentSelected = 1;
			else currentSelected -= 1;

			for (int i = 0; i < 2; i++)
			{
				menuItems[i].setColor(sf::Color::White);
			}
			menuItems[currentSelected].setColor(sf::Color::Green);
		}
		else if (currentState == ChooseSaveSlot)
		{
			if (currentSelected == 0)
				currentSelected = 2;
			else currentSelected -= 1;

			for (int i = 0; i < 3; i++)
			{
				saveSlots[i].setColor(sf::Color::White);
			}
			saveSlots[currentSelected].setColor(sf::Color::Green);
		}
	}
}

void SaveManager::NavDown()
{
	if (canMove == true)
	{
		if (currentState == SAVE)
		{
			if (currentSelected == 1)
				currentSelected = 0;
			else currentSelected += 1;

			for (int i = 0; i < 2; i++)
			{
				menuItems[i].setColor(sf::Color::White);
			}
			menuItems[currentSelected].setColor(sf::Color::Green);
		}
		else if (currentState == ChooseSaveSlot)
		{
			if (currentSelected == 2)
				currentSelected = 0;
			else currentSelected += 1;

			for (int i = 0; i < 3; i++)
			{
				saveSlots[i].setColor(sf::Color::White);
			}
			saveSlots[currentSelected].setColor(sf::Color::Green);
		}
	}
}

void SaveManager::Draw(sf::RenderTarget & window)
{
	if (currentState == SAVE)
	{
		window.draw(saveHeading);
		for (int i = 0; i < 2; i++)
		{
			window.draw(menuItems[i]);
		}
	}
	else if (currentState == ChooseSaveSlot)
	{
		window.draw(saveHeading);
		for (int i = 0; i < 3; i++)
		{
			window.draw(saveSlots[i]);
			window.draw(slotImages[i]);
		}
	}
}

int SaveManager::GetCurrentState()
{
	return currentState;
}

void SaveManager::SetCurrentState(int s)
{
	currentState = s;
}

bool SaveManager::GetCanMove()
{
	return canMove;
}

void SaveManager::SetCanMove(bool cm)
{
	canMove = cm;
}

bool SaveManager::GetCanSelect()
{
	return canSelect;
}

void SaveManager::SetCanSelect(bool cs)
{
	canSelect = cs;
}

bool SaveManager::IsSaving()
{
	return saving;
}

int SaveManager::GetCurrentSelected()
{
	return currentSelected;
}

void SaveManager::SetCurrentSelected(int sel)
{
	currentSelected = sel;
}
