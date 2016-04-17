#ifndef PNODE_H
#define PNODE_H

/* 
//	referenced from:
//		Oisin's pathfinding notes, 
//		my A* project from 3rd year,
//		http://www.bogotobogo.com/Algorithms/path_finding_algorithm.php,
//		http://code.activestate.com/recipes/577457-a-star-shortest-path-algorithm/
//*/
class Pnode : public sf::RectangleShape
{
private:
	float g;
	float f;
	float h;

	bool obstructed;
	bool visited;
	bool inPath;
	Pnode* parentNode;
	//std::string id;
//	float g;//total distance travelled to reach this node
//
//	float f;//total cost of path i.e g + h.
//
//	float h;//estimated remaining distance
//
//	sf::Texture texture;
//
//	bool obstructed;//is this node obstructed by something? e.g: a building 
//
//	Pnode* parentNode;
//
//	std::string id;
//
//	bool visited;
public:
	Pnode(sf::Vector2f pos);

	~Pnode();

	float GetG();
	void SetG(float newG);

	float GetF();
	void SetF(float newF);

	float GetH();
	void SetH(float newH);

	bool IsObstructed();
	void SetObstructed(bool o);

	bool WasVisited();
	void SetVisited(bool v);

	bool IsInPath();
	void SetInPath(bool ip);

	Pnode* GetParent();
	void SetParent(Pnode* p);
//	Pnode(sf::Vector2f pos, std::string i);
//
//	~Pnode();
//
//	void SetG(float pg);
//
//	//Calculate f. f = g + h. param is the position of the destination node position
//	void CalculateF(sf::Vector2f destPos);
//
//	//calculate the heuristic.(euclidean distance). param is the destination node position
//	void CalculateH(sf::Vector2f destPos);
//
//	float GetF();
//	float GetG();
//	float GetH();
//	//bool operator<(const Pnode& a, const Pnode& b)
//	//{
//	//	return a.GetF() > b.getF();
//	//}
//	bool IsVisited();
//	void SetVisited(bool v);
//
//	Pnode* GetParent();
//	void SetParent(Pnode* p);
//
//	void SetH(float  newH);
};

#endif
