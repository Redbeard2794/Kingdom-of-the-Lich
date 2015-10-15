#ifndef QUEST_H	
#define QUEST_H

class Quest
{
public:
	Quest();
	~Quest();

	//start gets
	sf::Vector2f getQuestStartingPosition(){ return questStartingPosition; }
	sf::String getQuestGiverName() { return questGiverName; }
	sf::String getQuestObjective() { return questObjective; }
	sf::Vector2f getObjectiveLocation() { return objectiveLocation; }
	bool getIsCombatBased() { return isCombatBased; }
	int getQuestGemReward() { return questGemReward; }
	//Item getRewardItem(){return rewardItem;}
	int getXpReward() { return xpReward; }
	//end gets

	//start sets
	void setQuestStartingPosition(sf::Vector2f qsp) { questStartingPosition = qsp; }
	void setQuestGiverName(sf::String qgn) { questGiverName = qgn; }
	void setQuestObjective(sf::String qo) { questObjective = qo; }
	void setObjectiveLocation(sf::Vector2f ol) { objectiveLocation = ol; }
	void setIsCombatBased(bool cb) { isCombatBased = cb; }
	void setQuestGemReward(int qgr) { questGemReward = qgr; }
	//void setRewardItem(Item i){rewardItem = i;}
	void setXpReward(int xpr) { xpReward = xpr; }
	//end sets

private:
	sf::Vector2f questStartingPosition;//where does the quest start(the quest givers position)

	sf::String questGiverName;//who gives the quest

	sf::String questObjective;//what the player needs to do

	sf::Vector2f objectiveLocation;//the location where the objective will be carried out

	bool isCombatBased;//is there combat involved?

	int questGemReward;//number of gems to be awarded for completing the quest

	//Item rewardItem;//the item to be awarded

	int xpReward;//amount of xp to be awarded.

};

#endif
