#include "stdafx.h"
#include "AchievementTracker.h"

AchievementTracker::AchievementTracker(Player* p, sf::Font f, int sw, int sh, AudioManager* am) : player(p), font(f), screenW(sw), screenH(sh)
{
	player->addObserver(this);
	LoadAchievements();
	displayClock.restart();

	unlockText.setFont(font);
	unlockText.setString("Achievement unlocked: ");
	unlockText.setColor(sf::Color(255, 215, 0, 255));
	unlockText.setCharacterSize(30);
	unlockText.setPosition(screenW/3, 25);
	audioManager = am;

	messageBackground.setPosition(sf::Vector2f(unlockText.getPosition().x, unlockText.getPosition().y + 6));
	messageBackground.setSize(sf::Vector2f(unlockText.getGlobalBounds().width, unlockText.getGlobalBounds().height));
	messageBackground.setFillColor(sf::Color::Black);
}

AchievementTracker::~AchievementTracker()
{
}

void AchievementTracker::LoadAchievements()
{
	xml_document<> doc;
	std::ifstream file("Assets/Icons/Achievements/AchievementList.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	xml_node<> *pRoot = doc.first_node();

	xml_node<>* achievementList = doc.first_node("AchievementList");
	xml_node<>* achievement = achievementList->first_node("Achievement");

	//load in each npc's information and then create them
	while (achievement != NULL)
	{
		//name, id, race, gender, texturePath, mapIconTexturePath, x, y, hasQuest, behaviour
		std::string name = "";
		int id = 0;
		bool locked = true;
		std::string texturePath;

		/*Get the name*/
		name = achievement->first_attribute("name")->value();

		/*Get the id*/
		id = atoi(achievement->first_node("id")->value());

		locked = std::atoi(achievement->first_node("locked")->value());

		texturePath = achievement->first_node("iconTexturePath")->value();

		/*Create the npc*/
		Achievement* n = new Achievement(name, id, locked, texturePath, screenW, screenH);
		lockedAchievements.push_back(n);

		/*Move onto the next achievement tag*/
		achievement = achievement->next_sibling("Achievement");
	}
	std::cout << "Achievements loaded" << std::endl;
}

void AchievementTracker::Update()
{
	for (int i = 0; i < lockedAchievements.size(); i++)
	{
		//if it is the 'Open the Chest!' achievement and it hasn't already been unlocked
		if (lockedAchievements.at(i)->GetName() == "Open the chest!" && lockedAchievements.at(i)->GetLockedStatus())
		{
			if (player->GetOpenedChests() == 1)
			{
				std::cout << "Player unlocked the 'Open the Chest!' achievement." << std::endl;
				lockedAchievements.at(i)->Unlock();
				unlockedAchievements.push_back(lockedAchievements.at(i));
				displayClock.restart();
				audioManager->PlaySoundEffectById(16, false);
				break;
			}
		}
		//else if it is the 'A refreshing drink' achievement and it hasn't already been unlocked
		else if (lockedAchievements.at(i)->GetName() == "A refreshing drink" && lockedAchievements.at(i)->GetLockedStatus())
		{
			if (player->GetPotionsDrank() == 1)
			{
				std::cout << "Player has unlocked the 'A refreshing drink' achievement." << std::endl;
				lockedAchievements.at(i)->Unlock();
				unlockedAchievements.push_back(lockedAchievements.at(i));
				displayClock.restart();
				audioManager->PlaySoundEffectById(16, false);
			}
		}
		//if it is the 'Fight!' achievement and it hasn't already been unlocked
		else if (lockedAchievements.at(i)->GetName() == "Fight!" && lockedAchievements.at(i)->GetLockedStatus())
		{
			if (player->GetNumberCompletedCombats() == 1)
			{
				std::cout << "Player has unlocked the 'Fight!' achievement." << std::endl;
				lockedAchievements.at(i)->Unlock();
				unlockedAchievements.push_back(lockedAchievements.at(i));
				displayClock.restart();
				audioManager->PlaySoundEffectById(16, false);
			}
		}
		//else if it is the 'To the sewers!' achievement and it hasn't already been unlocked
		else if (lockedAchievements.at(i)->GetName() == "To the sewers!" && lockedAchievements.at(i)->GetLockedStatus())
		{
			if (player->HasPlayerGoneSewers() == true)
			{
				std::cout << "Player has unlocked the 'To the sewers!' achievement." << std::endl;
				lockedAchievements.at(i)->Unlock();
				unlockedAchievements.push_back(lockedAchievements.at(i));
				displayClock.restart();
				audioManager->PlaySoundEffectById(16, false);
			}
		}
		//else if it is the 'Pub?' achievement and it hasn't already been unlocked
		else if (lockedAchievements.at(i)->GetName() == "Pub?" && lockedAchievements.at(i)->GetLockedStatus())
		{
			if (player->HasPlayerGonePub() == true)
			{
				std::cout << "Player has unlocked the 'Pub?' achievement." << std::endl;
				lockedAchievements.at(i)->Unlock();
				unlockedAchievements.push_back(lockedAchievements.at(i));
				displayClock.restart();
				audioManager->PlaySoundEffectById(16, false);
			}
		}
		//else if it is the 'Steal from a Thief' achievement and it hasn't already been unlocked
		else if (lockedAchievements.at(i)->GetName() == "Steal from a Thief" && lockedAchievements.at(i)->GetLockedStatus())
		{
			if (player->HasPlayerStoleStuffBack() == true)
			{
				std::cout << "Player has unlocked the 'Steal from a Thief' achievement." << std::endl;
				lockedAchievements.at(i)->Unlock();
				unlockedAchievements.push_back(lockedAchievements.at(i));
				displayClock.restart();
				audioManager->PlaySoundEffectById(16, false);
			}
		}
		//else if it is the 'Capitalism' achievement and it hasn't already been unlocked
		else if (lockedAchievements.at(i)->GetName() == "Capitalism" && lockedAchievements.at(i)->GetLockedStatus())
		{
			if (player->HasPlayerBoughtSomething() == true && player->HasPlayerSoldSomething() == true)
			{
				std::cout << "Player has unlocked the 'Capitalism' achievement." << std::endl;
				lockedAchievements.at(i)->Unlock();
				unlockedAchievements.push_back(lockedAchievements.at(i));
				displayClock.restart();
				audioManager->PlaySoundEffectById(16, false);
			}
		}
		//else if it is the 'Chatterbox' achievement and it hasn't already been unlocked
		else if (lockedAchievements.at(i)->GetName() == "Chatterbox" && lockedAchievements.at(i)->GetLockedStatus())
		{
			if (player->GetNumPeopleTalkedTo() >= 5)
			{
				std::cout << "Player has unlocked the 'Chatterbox' achievement." << std::endl;
				lockedAchievements.at(i)->Unlock();
				unlockedAchievements.push_back(lockedAchievements.at(i));
				displayClock.restart();
				audioManager->PlaySoundEffectById(16, false);
			}
		}
		//else if it is the 'A weeks wages' achievement and it hasn't already been unlocked
		else if (lockedAchievements.at(i)->GetName() == "A weeks wages" && lockedAchievements.at(i)->GetLockedStatus())
		{
			if (player->GetGems() >= 20)
			{
				std::cout << "Player has unlocked the 'A weeks wages' achievement." << std::endl;
				lockedAchievements.at(i)->Unlock();
				unlockedAchievements.push_back(lockedAchievements.at(i));
				displayClock.restart();
				audioManager->PlaySoundEffectById(16, false);
			}
		}
	}
}

void AchievementTracker::DisplayAchievement(sf::RenderTarget & window)
{
	for (int i = 0; i < unlockedAchievements.size(); i++)
	{
		if (unlockedAchievements.at(i)->HasBeenDisplayed() == false && displayClock.getElapsedTime().asSeconds() < 5)
		{
			unlockText.setString("Achievement unlocked: " + unlockedAchievements.at(i)->GetName());
			messageBackground.setSize(sf::Vector2f(unlockText.getGlobalBounds().width, unlockText.getGlobalBounds().height));
			window.draw(messageBackground);
			window.draw(unlockText);
			window.draw(*unlockedAchievements.at(i));
		}

		if (displayClock.getElapsedTime().asSeconds() >= 5 && unlockedAchievements.at(i)->HasBeenDisplayed() == false)
		{
			unlockedAchievements.at(i)->SetDisplayStatus(true);
		}
	}
}

//make achievements unlocked in a saved game not pop up again when the game is loaded
void AchievementTracker::LoadPrevUnlockedAchievements()
{
	for (int i = 0; i < unlockedAchievements.size(); i++)
	{
		unlockedAchievements.at(i)->SetDisplayStatus(true);
	}
}
