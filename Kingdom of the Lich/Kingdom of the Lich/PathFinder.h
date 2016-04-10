#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "Pnode.h"

class PathFinder
{
private:
	Pnode* graph[40][40];

	std::vector<Pnode*> openList;
	std::vector<Pnode*> closedList;
	std::vector<sf::Vector2f> path;

	bool reachedGoal;
	Pnode* startNode;
	Pnode* goalNode;

//	bool reachedGoal;//found goal
//
//	Pnode* startNode;
//	Pnode* goalNode;
//
//	std::vector<Pnode*> openList;
//	std::vector<Pnode*> closedList;//visited list
//	std::vector<sf::Vector2f> path;//pathtogoal
//
//	bool initStartGoal;//have the start and end nodes been initialised
//
public:
	PathFinder();
	~PathFinder();

	void SetStartNodeByPosition(sf::Vector2f pos);
	void SetGoalNodeByPosition(sf::Vector2f pos);

	void FindPath();

	void Draw(sf::RenderTarget& window);
//
//	//void SetStartAndGoal();
//	void FindPath(sf::Vector2f startPos, sf::Vector2f targetPos);
//	sf::Vector2f GetNextPathPos(sf::Vector2f pos, float radius);
//
//	//methods to clear lists
//	void ClearOpenList();
//	void ClearClosedList();
//	void ClearPath();
//
//	void SetStartAndGoalNodes(Pnode* start, Pnode* end);
//	void CheckCurrentNodeInOpenList(float x, float y, float newCost, Pnode* parent);//pathopened
//	Pnode* GetNextNode();
//	void PathFind();//continue path
};

#endif
