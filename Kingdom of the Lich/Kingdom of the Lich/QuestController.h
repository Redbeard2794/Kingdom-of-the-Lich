#ifndef QUESTCONTROLLER
#define QUESTCONTROLLER
#include "Quest.h"
class QuestController
{
private:
	std::vector<Quest> activeQuests;//Quests that the player has found but has not completed
	std::vector<Quest> completedQuests;//Quests that the player has completed
	std::vector<Quest> undiscoveredQuests;//Quests that the player has not discovered yet

	Quest currentQuest;//Quest that the player is currently doing

public:
	/*Constructor*/
	QuestController();

	/*Destructor*/
	~QuestController();

	/*Load all undiscovered quests*/
	void LoadUndiscoveredQuests();

	/*Add an undiscovered quest to active quests vector when it is discovered
	Parameter is the id of the quest you want to add to active*/
	void AddUndiscoveredQuestToActiveQuests(int qId);

	/*Add an active quest to completed quests vector when it is completed
	Parameter is the id of the quest you want to add to completed*/
	void AddActiveQuestToCompletedQuests(int qId);

	//void SetCurrentQuest();


};

#endif;
