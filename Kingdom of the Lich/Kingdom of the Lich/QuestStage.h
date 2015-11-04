#ifndef QUESTSTAGE_H
#define QUESTSTAGE_H

class QuestStage
{
private:
	std::string objective;//this stages objective
	int stageNumber;//the identifying number for this stages
	sf::Vector2f objectiveLocation;//where the objective is
	bool completed;//is this stage completed?

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

	/*Set the objective for this stage*/
	void setObjective(std::string obj);

	/*Set this stage's identifying number*/
	void setStageNumber(int n);

	/*Set the location of the objective*/
	void setObjectiveLocation(sf::Vector2f pos);

	/*Set this stages completion status*/
	void setCompletionStatus(bool c);
};

#endif
