#include "stdafx.h"
#include "AchievementTracker.h"

AchievementTracker::AchievementTracker(Player* p, sf::Font f) : player(p), font(f)
{
	player->addObserver(this);
	LoadAchievements();
	displayClock.restart();

	unlockText.setFont(font);
	unlockText.setString("Achievement unlocked: ");
	unlockText.setColor(sf::Color(255, 215, 0, 255));
	unlockText.setCharacterSize(30);
	unlockText.setPosition(400, 300);
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
		Achievement* n = new Achievement(name, id, locked, texturePath);
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
			}
		}
		//if it is the 'Fight!' achievement and it hasn't already been unlocked
		else if (lockedAchievements.at(i)->GetName() == "Fight!" && lockedAchievements.at(i)->GetLockedStatus())
		{

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
			window.draw(unlockText);
			window.draw(*unlockedAchievements.at(i));
		}

		if (displayClock.getElapsedTime().asSeconds() >= 5 && unlockedAchievements.at(i)->HasBeenDisplayed() == false)
		{
			unlockedAchievements.at(i)->SetDisplayStatus(true);
		}
	}
}
