#include "stdafx.h"
#include "PathFinder.h"

//PathFinder::PathFinder()
//{
//	initStartGoal = false;
//	reachedGoal = false;
//}
//
//PathFinder::~PathFinder()
//{
//}
//
//void PathFinder::FindPath(sf::Vector2f startPos, sf::Vector2f targetPos)
//{
//	if (!initStartGoal)
//	{
//		for (int i = 0; i < openList.size(); i++)
//		{
//			delete openList.at(i);
//		}
//		openList.clear();
//
//		for (int i = 0; i < closedList.size(); i++)
//		{
//			delete closedList.at(i);
//		}
//		closedList.clear();
//
//		//for (int i = 0; i < path.size(); i++)
//		//{
//		//	//delete path.at(i);
//		//}
//		path.clear();
//
//		//initialise start and end nodes
//		startNode = new Pnode(startPos, "s");
//		startNode->CalculateH(targetPos);
//		openList.push_back(startNode);
//
//		goalNode = new Pnode(targetPos, "g");
//
//		initStartGoal = true;
//	}
//	else
//	{
//		PathFind();
//	}
//}
//
//sf::Vector2f PathFinder::GetNextPathPos(sf::Vector2f pos, float radius)
//{
//	int index = 1;
//
//	sf::Vector2f nextPos;
//
//	nextPos.x = path.at(path.size() - index).x;
//	nextPos.y = path.at(path.size() - index).y;
//
//	sf::Vector2f dist = nextPos - pos;//npc pos
//
//	if (index < path.size())
//	{
//		float distLength = sqrtf((dist.x*dist.x) + (dist.y*dist.y));
//		if (distLength < radius)//ai radius
//		{
//			path.erase(path.end() - index);
//		}
//	}
//
//	return nextPos;
//}
//
//void PathFinder::ClearOpenList()
//{
//	openList.clear();
//}
//
//void PathFinder::ClearClosedList()
//{
//	closedList.clear();
//}
//
//void PathFinder::ClearPath()
//{
//	path.clear();
//}
//
//void PathFinder::CheckCurrentNodeInOpenList(float x, float y, float newCost, Pnode * parent)
//{
//	//if (obstructed)
//	//{
//	//	return;
//	//}
//
//	for (int i = 0; i < closedList.size(); i++)
//	{
//		//if the node is already in the closed list
//		if (x == closedList.at(i)->getPosition().x && y == closedList.at(i)->getPosition().y)
//		{
//			return;
//		}
//	}
//
//	Pnode* newChild = new Pnode(sf::Vector2f(x, y), "nc");
//	newChild->SetParent(parent);
//	newChild->SetG(newCost);
//	parent->CalculateH(goalNode->getPosition());
//	newChild->SetH(parent->GetH());
//
//	for (int i = 0; i < openList.size(); i++)
//	{
//		if (x == openList.at(i)->getPosition().x && y == openList.at(i)->getPosition().y)
//		{
//			float newF = newChild->GetG() + newCost + openList.at(i)->GetH();
//
//			if (openList.at(i)->GetF() > newF)
//			{
//				//replace with better F
//				openList.at(i)->SetG(newChild->GetG() + newCost);
//				openList.at(i)->SetParent(newChild);
//			}
//			else//if the f is not better
//			{
//				delete newChild;
//				return;
//			}
//		}
//	}
//
//	openList.push_back(newChild);
//}
//
//Pnode * PathFinder::GetNextNode()
//{
//	float bestF = 99999999999.f;
//	int index = -1;
//
//	Pnode* nextNode = NULL;
//
//	for (int i = 0; i < openList.size(); i++)
//	{
//		if (openList.at(i)->GetF() < bestF)
//		{
//			bestF = openList.at(i)->GetF();
//			index = i;
//		}
//	}
//
//	if (index >= 0)//if we found another node
//	{
//		nextNode = openList.at(index);
//		closedList.push_back(nextNode);
//		openList.erase(openList.begin() + index);
//	}
//
//	return nextNode;
//}
//
//void PathFinder::PathFind()
//{
//	if (openList.empty())//if open list is empty then don't bother
//		return;
//
//	Pnode* currentNode = GetNextNode();
//
//	if (currentNode->getPosition().x == goalNode->getPosition().x 
//		&& currentNode->getPosition().y == goalNode->getPosition().y)
//	{
//		goalNode->SetParent(currentNode->GetParent());
//
//		Pnode* getPath;
//
//		//build the path by working back through each nodes parent node
//		for (getPath = goalNode; getPath != NULL; getPath = getPath->GetParent())
//		{
//			path.push_back(getPath->getPosition());
//		}
//
//		reachedGoal = true;
//		return;
//	}
//	else
//	{
//		//right side
//		CheckCurrentNodeInOpenList(currentNode->getPosition().x + 1, currentNode->getPosition().y, currentNode->GetG() + 1, currentNode);
//		//left side
//		CheckCurrentNodeInOpenList(currentNode->getPosition().x - 1, currentNode->getPosition().y, currentNode->GetG() + 1, currentNode);
//		//up
//		CheckCurrentNodeInOpenList(currentNode->getPosition().x, currentNode->getPosition().y - 1, currentNode->GetG() + 1, currentNode);
//		//down
//		CheckCurrentNodeInOpenList(currentNode->getPosition().x, currentNode->getPosition().y + 1, currentNode->GetG() + 1, currentNode);
//
//		for (int i = 0; i < openList.size(); i++)
//		{
//			if (currentNode->getPosition().x == openList.at(i)->getPosition().x
//				&& currentNode->getPosition().y == openList.at(i)->getPosition().y)
//			{
//				openList.erase(openList.begin() + i);
//			}
//		}
//	}
//}

PathFinder::PathFinder()
{
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			graph[i][j] = new Pnode(sf::Vector2f((i * 50) + 25, (j * 50 + 25)));
		}
	}

	reachedGoal = false;
	startNode = NULL;
	goalNode = NULL;
}

PathFinder::~PathFinder()
{
}

void PathFinder::SetStartNodeByPosition(sf::Vector2f pos)
{
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (graph[i][j]->getPosition() == pos)
			{
				std::cout << "Start node located by passed in position " << pos.x << ", " << pos.y << std::endl;
				startNode = graph[i][j];
				graph[i][j]->setFillColor(sf::Color::Magenta);
				break;
			}
		}
	}
}

void PathFinder::SetGoalNodeByPosition(sf::Vector2f pos)
{
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (graph[i][j]->getPosition() == pos)
			{
				std::cout << "Goal node located by passed in position " << pos.x << ", " << pos.y << std::endl;
				goalNode = graph[i][j];
				graph[i][j]->setFillColor(sf::Color::Magenta);
				break;
			}
		}
	}
}

//http://www.policyalmanac.org/games/aStarTutorial.htm

void PathFinder::FindPath()
{
	//add start node to the open list
	openList.push_back(startNode);

	//add nodes adjacent to the start node to the open list
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (graph[i][j]->getGlobalBounds().intersects(startNode->getGlobalBounds()) 
				&& graph[i][j]->getPosition() != startNode->getPosition())//if a node touches the start node
			{
				std::cout << "+Found node adjacent to start node" << std::endl;
				graph[i][j]->SetParent(startNode);


				if (graph[i][j]->getPosition().x > startNode->getPosition().x
					&& graph[i][j]->getPosition().y < startNode->getPosition().y)//up right diagonal
				{
					graph[i][j]->SetG(startNode->GetG() + 75);
				}
				else if (graph[i][j]->getPosition().x > startNode->getPosition().x
					&& graph[i][j]->getPosition().y > startNode->getPosition().y)//down right diagonal
				{
					graph[i][j]->SetG(startNode->GetG() + 75);
				}
				else if (graph[i][j]->getPosition().x < startNode->getPosition().x
					&& graph[i][j]->getPosition().y > startNode->getPosition().y)//down left diagonal
				{
					graph[i][j]->SetG(startNode->GetG() + 75);
				}
				else if (graph[i][j]->getPosition().x < startNode->getPosition().x
					&& graph[i][j]->getPosition().y < startNode->getPosition().y)//up left diagonal
				{
					graph[i][j]->SetG(startNode->GetG() + 75);
				}
				else if (graph[i][j]->getPosition().x > startNode->getPosition().x)//right
				{
					graph[i][j]->SetG(startNode->GetG() + 50);
				}
				else if (graph[i][j]->getPosition().y > startNode->getPosition().y)//down
				{
					graph[i][j]->SetG(startNode->GetG() + 50);
				}
				else if (graph[i][j]->getPosition().x < startNode->getPosition().x)//left
				{
					graph[i][j]->SetG(startNode->GetG() + 50);
				}
				else if (graph[i][j]->getPosition().y < startNode->getPosition().y)//up
				{
					graph[i][j]->SetG(startNode->GetG() + 50);
				}


				graph[i][j]->setFillColor(sf::Color::Yellow);

				//float hx = goalNode->getPosition().x - graph[i][j]->getPosition().x;
				//float hy = goalNode->getPosition().y - graph[i][j]->getPosition().y;
				//float h = hx + hy;

				float h = sqrtf(((goalNode->getPosition().x - graph[i][j]->getPosition().x)*(goalNode->getPosition().x - graph[i][j]->getPosition().x)) + ((goalNode->getPosition().y - graph[i][j]->getPosition().y)*(goalNode->getPosition().y - graph[i][j]->getPosition().y)));


				graph[i][j]->SetH(h);

				graph[i][j]->SetF(graph[i][j]->GetG() + graph[i][j]->GetH());

				openList.push_back(graph[i][j]);
			}
		}
	}

	//move start node to the closed list
	openList.erase(openList.begin());
	closedList.push_back(startNode);
	//startNode->SetVisited(true);

	std::cout << "Open List size: " << openList.size() << std::endl;
	std::cout << "Closed List size: " << closedList.size() << std::endl;

	

	//for (int i = 0; i < 30; i++)
	//{

	/*continue searching*/

	//for (int k = 0; k < 30; k++)
	while(reachedGoal == false)
	{

		//find lowest f of squares on open list
		float bestF = FLT_MAX;
		int bestIndex = 0;
		for (int i = 0; i < openList.size(); i++)
		{
			if (openList.at(i)->GetF() < bestF)
			{
				bestF = openList.at(i)->GetF();
				bestIndex = i;
			}
		}

		//add to closed list and remove from open list
		Pnode* currentNode = openList.at(bestIndex);

		closedList.push_back(openList.at(bestIndex));
		openList.erase(openList.begin() + bestIndex);


		for (int ass = 0; ass < openList.size(); ass++)
		{
			if (openList.at(ass) == goalNode)
			{
				std::cout << "Found goal!" << std::endl;

				reachedGoal = true;
			}
		}

		//if (reachedGoal == false)
		//{
			for (int i = 0; i < 40; i++)
			{
				for (int j = 0; j < 40; j++)
				{
					if (graph[i][j]->getGlobalBounds().intersects(currentNode->getGlobalBounds()))
					{
						bool notInClosed = false;
						for (int i = 0; i < closedList.size(); i++)
						{
							if (closedList.at(i) == graph[i][j])
								notInClosed = true;
						}

						if (notInClosed == false)
						{
							if (graph[i][j]->IsObstructed() == false)
							{
								bool notInOpen = false;
								for (int i = 0; i < openList.size(); i++)
								{
									if (openList.at(i) == graph[i][j])
										notInOpen = false;
								}

								if (notInOpen == false)
								{
									graph[i][j]->SetParent(currentNode);

									if (graph[i][j]->getPosition().x > currentNode->getPosition().x
										&& graph[i][j]->getPosition().y < currentNode->getPosition().y)//up right diagonal
									{
										graph[i][j]->SetG(currentNode->GetG() + 75);
									}
									else if (graph[i][j]->getPosition().x > currentNode->getPosition().x
										&& graph[i][j]->getPosition().y > currentNode->getPosition().y)//down right diagonal
									{
										graph[i][j]->SetG(currentNode->GetG() + 75);
									}
									else if (graph[i][j]->getPosition().x < currentNode->getPosition().x
										&& graph[i][j]->getPosition().y > currentNode->getPosition().y)//down left diagonal
									{
										graph[i][j]->SetG(currentNode->GetG() + 75);
									}
									else if (graph[i][j]->getPosition().x < currentNode->getPosition().x
										&& graph[i][j]->getPosition().y < currentNode->getPosition().y)//up left diagonal
									{
										graph[i][j]->SetG(currentNode->GetG() + 75);
									}
									else if (graph[i][j]->getPosition().x > currentNode->getPosition().x)//right
									{
										graph[i][j]->SetG(currentNode->GetG() + 50);
									}
									else if (graph[i][j]->getPosition().y > currentNode->getPosition().y)//down
									{
										graph[i][j]->SetG(currentNode->GetG() + 50);
									}
									else if (graph[i][j]->getPosition().x < currentNode->getPosition().x)//left
									{
										graph[i][j]->SetG(currentNode->GetG() + 50);
									}
									else if (graph[i][j]->getPosition().y < currentNode->getPosition().y)//up
									{
										graph[i][j]->SetG(currentNode->GetG() + 50);
									}


									graph[i][j]->setFillColor(sf::Color::Yellow);

									//float hx = goalNode->getPosition().x - graph[i][j]->getPosition().x;
									//float hy = goalNode->getPosition().y - graph[i][j]->getPosition().y;
									//float h = hx + hy;

									float h = sqrtf(((goalNode->getPosition().x - graph[i][j]->getPosition().x)*(goalNode->getPosition().x - graph[i][j]->getPosition().x)) + ((goalNode->getPosition().y - graph[i][j]->getPosition().y)*(goalNode->getPosition().y - graph[i][j]->getPosition().y)));


									graph[i][j]->SetH(h);

									graph[i][j]->SetF(graph[i][j]->GetG() + graph[i][j]->GetH());

									openList.push_back(graph[i][j]);
								}

								else
								{
									std::cout << "Checking an already open node for better path." << std::endl;

									float currentG = graph[i][j]->GetG();
									float possibleG = 0;


									if (graph[i][j]->getPosition().x > currentNode->getPosition().x
										&& graph[i][j]->getPosition().y < currentNode->getPosition().y)//up right diagonal
									{
										//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 14);
										possibleG = currentNode->GetG() + 75;
									}
									else if (graph[i][j]->getPosition().x > currentNode->getPosition().x
										&& graph[i][j]->getPosition().y > currentNode->getPosition().y)//down right diagonal
									{
										//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 14);
										possibleG = currentNode->GetG() + 75;
									}
									else if (graph[i][j]->getPosition().x < currentNode->getPosition().x
										&& graph[i][j]->getPosition().y > currentNode->getPosition().y)//down left diagonal
									{
										//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 14);
										possibleG = currentNode->GetG() + 75;
									}
									else if (graph[i][j]->getPosition().x < currentNode->getPosition().x
										&& graph[i][j]->getPosition().y < currentNode->getPosition().y)//up left diagonal
									{
										//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 14);
										possibleG = currentNode->GetG() + 75;
									}
									else if (graph[i][j]->getPosition().x > currentNode->getPosition().x)//right
									{
										//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 10);
										possibleG = currentNode->GetG() + 50;
									}
									else if (graph[i][j]->getPosition().y > currentNode->getPosition().y)//down
									{
										//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 10);
										possibleG = currentNode->GetG() + 50;
									}
									else if (graph[i][j]->getPosition().x < currentNode->getPosition().x)//left
									{
										//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 10);
										possibleG = currentNode->GetG() + 50;
									}
									else if (graph[i][j]->getPosition().y < currentNode->getPosition().y)//up
									{
										//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 10);
										possibleG = currentNode->GetG() + 50;
									}


									if (possibleG < currentG)
									{
										graph[i][j]->SetParent(currentNode);
										graph[i][j]->SetG(possibleG);
										graph[i][j]->SetF(graph[i][j]->GetG() + graph[i][j]->GetH());
									}
								}
							}
						}
					}
				}
			}
		//}


	}

	if (reachedGoal == true)
	{
		Pnode* node = goalNode;

		bool pathEnd = false;

		/*while (pathEnd == false)
		{
			if (node->getPosition() != startNode->getPosition())
			{
				path.push_back(node->getPosition());
				node = node->GetParent();
			}
			else
			{
				pathEnd = true;
			}
		}*/

		//while (node->getPosition() != startNode->getPosition())
		//{
		//	path.push_back(node->getPosition());
		//	node = node->GetParent();
		//}
	}

	std::cout << std::endl;

	//	//check for goal node
	//	for (int i = 0; i < openList.size(); i++)
	//	{
	//		if (openList.at(i)->getPosition() == goalNode->getPosition())
	//		{
	//			reachedGoal = true;
	//		}
	//	}


	//	if (reachedGoal == false || openList.size() != 0)
	//	{
	//		for (int i = 0; i < 40; i++)
	//		{
	//			for (int j = 0; j < 40; j++)
	//			{
	//				if (graph[i][j]->getGlobalBounds().intersects(closedList.at(closedList.size() - 1)->getGlobalBounds())
	//					&& graph[i][j]->getPosition() != closedList.at(closedList.size() - 1)->getPosition())//if a node touches the current node
	//				{
	//					bool alreadyClosed = false;
	//					for (int i = 0; i < closedList.size(); i++)
	//					{
	//						if (closedList.at(i) == graph[i][j])
	//						{
	//							alreadyClosed = true;
	//						}
	//					}

	//					if (!alreadyClosed && !graph[i][j]->IsObstructed())//not already closed and not obstructed
	//					{
	//						bool alreadyInOpenList = false;
	//						for (int i = 0; i < openList.size(); i++)
	//						{
	//							if (openList.at(i) == graph[i][j])
	//							{
	//								alreadyInOpenList = true;
	//							}
	//						}

	//						if (!alreadyInOpenList)//not already in open list
	//						{
	//							std::cout << "*Found adjacent node. Adding to open list." << std::endl;
	//							graph[i][j]->SetParent(closedList.at(closedList.size() - 1));

	//							if (graph[i][j]->getPosition().x > closedList.at(closedList.size() - 1)->getPosition().x
	//								&& graph[i][j]->getPosition().y < closedList.at(closedList.size() - 1)->getPosition().y)//up right diagonal
	//							{
	//								graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 14);
	//							}
	//							else if (graph[i][j]->getPosition().x > closedList.at(closedList.size() - 1)->getPosition().x
	//								&& graph[i][j]->getPosition().y > closedList.at(closedList.size() - 1)->getPosition().y)//down right diagonal
	//							{
	//								graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 14);
	//							}
	//							else if (graph[i][j]->getPosition().x < closedList.at(closedList.size() - 1)->getPosition().x
	//								&& graph[i][j]->getPosition().y > closedList.at(closedList.size() - 1)->getPosition().y)//down left diagonal
	//							{
	//								graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 14);
	//							}
	//							else if (graph[i][j]->getPosition().x < closedList.at(closedList.size() - 1)->getPosition().x
	//								&& graph[i][j]->getPosition().y < closedList.at(closedList.size() - 1)->getPosition().y)//up left diagonal
	//							{
	//								graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 14);
	//							}
	//							else if (graph[i][j]->getPosition().x > closedList.at(closedList.size() - 1)->getPosition().x)//right
	//							{
	//								graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 10);
	//							}
	//							else if (graph[i][j]->getPosition().y > closedList.at(closedList.size() - 1)->getPosition().y)//down
	//							{
	//								graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 10);
	//							}
	//							else if (graph[i][j]->getPosition().x < closedList.at(closedList.size() - 1)->getPosition().x)//left
	//							{
	//								graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 10);
	//							}
	//							else if (graph[i][j]->getPosition().y < closedList.at(closedList.size() - 1)->getPosition().y)//up
	//							{
	//								graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 10);
	//							}


	//							graph[i][j]->setFillColor(sf::Color::Yellow);

	//							float hx = goalNode->getPosition().x - graph[i][j]->getPosition().x;
	//							float hy = goalNode->getPosition().y - graph[i][j]->getPosition().y;
	//							float h = hx + hy;
	//							graph[i][j]->SetH(h);

	//							graph[i][j]->SetF(graph[i][j]->GetG() + graph[i][j]->GetH());

	//							openList.push_back(graph[i][j]);
	//						}
	//						else//already in open list
	//						{
	//							std::cout << "Checking an already open node for better path." << std::endl;

	//							float currentG = graph[i][j]->GetG();
	//							float possibleG = 0;// closedList.at(closedList.size() - 1)->getGlobalBounds + 10;


	//							if (graph[i][j]->getPosition().x > closedList.at(closedList.size() - 1)->getPosition().x
	//								&& graph[i][j]->getPosition().y < closedList.at(closedList.size() - 1)->getPosition().y)//up right diagonal
	//							{
	//								//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 14);
	//								possibleG = closedList.at(closedList.size() - 1)->GetG() + 14;
	//							}
	//							else if (graph[i][j]->getPosition().x > closedList.at(closedList.size() - 1)->getPosition().x
	//								&& graph[i][j]->getPosition().y > closedList.at(closedList.size() - 1)->getPosition().y)//down right diagonal
	//							{
	//								//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 14);
	//								possibleG = closedList.at(closedList.size() - 1)->GetG() + 14;
	//							}
	//							else if (graph[i][j]->getPosition().x < closedList.at(closedList.size() - 1)->getPosition().x
	//								&& graph[i][j]->getPosition().y > closedList.at(closedList.size() - 1)->getPosition().y)//down left diagonal
	//							{
	//								//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 14);
	//								possibleG = closedList.at(closedList.size() - 1)->GetG() + 14;
	//							}
	//							else if (graph[i][j]->getPosition().x < closedList.at(closedList.size() - 1)->getPosition().x
	//								&& graph[i][j]->getPosition().y < closedList.at(closedList.size() - 1)->getPosition().y)//up left diagonal
	//							{
	//								//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 14);
	//								possibleG = closedList.at(closedList.size() - 1)->GetG() + 14;
	//							}
	//							else if (graph[i][j]->getPosition().x > closedList.at(closedList.size() - 1)->getPosition().x)//right
	//							{
	//								//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 10);
	//								possibleG = closedList.at(closedList.size() - 1)->GetG() + 10;
	//							}
	//							else if (graph[i][j]->getPosition().y > closedList.at(closedList.size() - 1)->getPosition().y)//down
	//							{
	//								//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 10);
	//								possibleG = closedList.at(closedList.size() - 1)->GetG() + 10;
	//							}
	//							else if (graph[i][j]->getPosition().x < closedList.at(closedList.size() - 1)->getPosition().x)//left
	//							{
	//								//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 10);
	//								possibleG = closedList.at(closedList.size() - 1)->GetG() + 10;
	//							}
	//							else if (graph[i][j]->getPosition().y < closedList.at(closedList.size() - 1)->getPosition().y)//up
	//							{
	//								//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 10);
	//								possibleG = closedList.at(closedList.size() - 1)->GetG() + 10;
	//							}


	//							if (possibleG < currentG)
	//							{
	//								graph[i][j]->SetParent(closedList.at(closedList.size() - 1));
	//								//float hx = goalNode->getPosition().x - graph[i][j]->getPosition().x;
	//								//float hy = goalNode->getPosition().y - graph[i][j]->getPosition().y;
	//								//float h = hx + hy;
	//								//graph[i][j]->SetH(h);
	//								graph[i][j]->SetG(possibleG);
	//								graph[i][j]->SetF(graph[i][j]->GetG() + graph[i][j]->GetH());
	//							}

	//						}



	//					}




	//				}

	//			}

	//		}
	//	}

	//	else
	//	{
	//		if (reachedGoal == true)
	//		{
	//			Pnode* node = goalNode;
	//			while (node != NULL)
	//			{
	//				path.push_back(node->getPosition());
	//				node = node->GetParent();
	//			}
	//		}
	//		else std::cout << "The path is a lie." << std::endl;

	//		break;
	//	}
	//}
	//std::cout << "End" << std::endl;

	//while (reachedGoal == false)
	//{
	//	float bestF = 999999.f;
	//	int index = -1;

	//	for (int i = 0; i < openList.size(); i++)
	//	{
	//		if (openList.at(i)->GetF() < bestF)
	//		{
	//			bestF = openList.at(i)->GetF();//can optimise here if we end up with more than one node with the best f in regards to the one we pick
	//			index = i;
	//		}
	//	}


	//	//add node to closed list, remove from open list
	//	openList.at(index)->SetVisited(true);
	//	closedList.push_back(openList.at(index));
	//	openList.erase(openList.begin() + index);

	//	for (int i = 0; i < closedList.size(); i++)
	//	{
	//		if (closedList.at(i)->getPosition() == goalNode->getPosition())
	//			reachedGoal = true;
	//	}
	//	//if (closedList.at(closedList.size() - 1) == goalNode)
	//	//{
	//	//	reachedGoal = true;
	//	//}

	//	if(reachedGoal == false)
	//	{
	//		//find the adjacent squares
	//		//add nodes adjacent to the start node to the open list
	//		for (int i = 0; i < 40; i++)
	//		{
	//			for (int j = 0; j < 40; j++)
	//			{
	//				if (graph[i][j]->getGlobalBounds().intersects(closedList.at(closedList.size() - 1)->getGlobalBounds())
	//					&& graph[i][j]->getPosition() != closedList.at(closedList.size() - 1)->getPosition()
	//					&& !graph[i][j]->IsObstructed())//if a node touches the start node
	//				{
	//					std::cout << "*Found adjacent node" << std::endl;
	//					graph[i][j]->SetParent(closedList.at(closedList.size() - 1));

	//					float g = 0;

	//					if (graph[i][j]->getPosition().x > closedList.at(closedList.size() - 1)->getPosition().x
	//						&& graph[i][j]->getPosition().y < closedList.at(closedList.size() - 1)->getPosition().y)//up right diagonal
	//					{
	//						//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 14);
	//						g = closedList.at(closedList.size() - 1)->GetG() + 14;
	//					}
	//					else if (graph[i][j]->getPosition().x > closedList.at(closedList.size() - 1)->getPosition().x
	//						&& graph[i][j]->getPosition().y > closedList.at(closedList.size() - 1)->getPosition().y)//down right diagonal
	//					{
	//						//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 14);
	//						g = closedList.at(closedList.size() - 1)->GetG() + 14;
	//					}
	//					else if (graph[i][j]->getPosition().x < closedList.at(closedList.size() - 1)->getPosition().x
	//						&& graph[i][j]->getPosition().y > closedList.at(closedList.size() - 1)->getPosition().y)//down left diagonal
	//					{
	//						//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 14);
	//						g = closedList.at(closedList.size() - 1)->GetG() + 14;
	//					}
	//					else if (graph[i][j]->getPosition().x < closedList.at(closedList.size() - 1)->getPosition().x
	//						&& graph[i][j]->getPosition().y < closedList.at(closedList.size() - 1)->getPosition().y)//up left diagonal
	//					{
	//						//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 14);
	//						g = closedList.at(closedList.size() - 1)->GetG() + 14;
	//					}
	//					else if (graph[i][j]->getPosition().x > closedList.at(closedList.size() - 1)->getPosition().x)//right
	//					{
	//						//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 10);
	//						g = closedList.at(closedList.size() - 1)->GetG() + 10;
	//					}
	//					else if (graph[i][j]->getPosition().y > closedList.at(closedList.size() - 1)->getPosition().y)//down
	//					{
	//						//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 10);
	//						g = closedList.at(closedList.size() - 1)->GetG() + 10;
	//					}
	//					else if (graph[i][j]->getPosition().x < closedList.at(closedList.size() - 1)->getPosition().x)//left
	//					{
	//						//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 10);
	//						g = closedList.at(closedList.size() - 1)->GetG() + 10;
	//					}
	//					else if (graph[i][j]->getPosition().y < closedList.at(closedList.size() - 1)->getPosition().y)//up
	//					{
	//						//graph[i][j]->SetG(closedList.at(closedList.size() - 1)->GetG() + 10);
	//						g = closedList.at(closedList.size() - 1)->GetG() + 10;
	//					}

	//					if (g < graph[i][j]->GetG())
	//						graph[i][j]->SetG(g);

	//					graph[i][j]->setFillColor(sf::Color::Yellow);

	//					float hx = goalNode->getPosition().x - graph[i][j]->getPosition().x;
	//					float hy = goalNode->getPosition().y - graph[i][j]->getPosition().y;
	//					float h = hx + hy;
	//					graph[i][j]->SetH(h);

	//					graph[i][j]->SetF(graph[i][j]->GetG() + graph[i][j]->GetH());

	//					if(!graph[i][j]->WasVisited())
	//						openList.push_back(graph[i][j]);
	//				}
	//			}
	//		}
	//	}
	//}

	//if (reachedGoal == true)
	//{
	//	Pnode* node = goalNode;
	//	while (node != NULL)
	//	{
	//		path.push_back(node->getPosition());
	//		node = node->GetParent();
	//	}
	//}
	//else std::cout << "The path is a lie." << std::endl;
}

void PathFinder::Draw(sf::RenderTarget & window)
{
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			window.draw(*graph[i][j]);
		}
	}
}
