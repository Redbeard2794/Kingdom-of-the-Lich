#ifndef QUEST_H	
#define QUEST_H

class Quest
{
public:
	Quest(int id, std::string qName, sf::Vector2f startPos, std::string giverName, std::string objective, sf::Vector2f objectivePos, bool combat, int gems, int xp);
	~Quest();

	//start gets
	int getQuestId() { return questId; }
	std::string getQuestName(){return questName;}
	sf::Vector2f getQuestStartingPosition(){ return questStartingPosition; }
	std::string getQuestGiverName() { return questGiverName; }
	std::string getQuestObjective() { return questObjective; }
	sf::Vector2f getObjectiveLocation() { return objectiveLocation; }
	bool getIsCombatBased() { return isCombatBased; }
	int getQuestGemReward() { return questGemReward; }
	//Item getRewardItem(){return rewardItem;}
	int getXpReward() { return xpReward; }
	bool getIsCompleted() { return completed; }
	//end gets

	//start sets
	void setQuestId(int id) { questId = id; }
	void setQuestName(std::string qName) { questName = qName; }
	void setQuestStartingPosition(sf::Vector2f qsp) { questStartingPosition = qsp; }
	void setQuestGiverName(std::string qgn) { questGiverName = qgn; }
	void setQuestObjective(std::string qo) { questObjective = qo; }
	void setObjectiveLocation(sf::Vector2f ol) { objectiveLocation = ol; }
	void setIsCombatBased(bool cb) { isCombatBased = cb; }
	void setQuestGemReward(int qgr) { questGemReward = qgr; }
	//void setRewardItem(Item i){rewardItem = i;}
	void setXpReward(int xpr) { xpReward = xpr; }
	void setIsCompleted(bool c) { completed = c; }
	//end sets

private:
	int questId;//id for the quest

	std::string questName;

	sf::Vector2f questStartingPosition;//where does the quest start(the quest givers position)

	std::string questGiverName;//who gives the quest

	struct Objective
	{
		std::string objectiveDescription;
		sf::Vector2f objectiveLocation;
		bool completed;
	};

	std::string questObjective;//what the player needs to do

	sf::Vector2f objectiveLocation;//the location where the objective will be carried out

	bool isCombatBased;//is there combat involved?

	int questGemReward;//number of gems to be awarded for completing the quest(if no gems are to be awarded then pass 0)

	//Item rewardItem;//the item to be awarded

	int xpReward;//amount of xp to be awarded.(if no xp is to be awarded then pass 0)

	bool completed;//is the quest completed?

};

#endif
