#ifndef QUESTSTAGE_H
#define QUESTSTAGE_H

class QuestStage
{
private:
	std::string objective;
	int stageNumber;
	sf::Vector2f objectiveLocation;
	bool completed;

public:
	QuestStage(std::string obj, int num, sf::Vector2f pos);

	~QuestStage();

	/*Gets the objective assigned to this stage*/
	std::string getObjective();

	/*Get this stages identifying number*/
	int getStageNumber();

	/*Get the objectives location*/
	sf::Vector2f getObjectiveLocation();

	/*Get the completion status of this stage. 
	False means not completed and True means completed*/
	bool getCompletionStatus();

	void setObjective(std::string obj);

	void setStageNumber(int n);

	void setObjectiveLocation(sf::Vector2f pos);

	void setCompletionStatus(bool c);
};

#endif
