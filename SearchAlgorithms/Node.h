#pragma once
#include <vector>

#include "Matrix.h"
#include <map>
#include <ctime>
#include <chrono>
#include <math.h>
#include <ctime>


class Node {
public:
	Matrix matrix;
	bool visitado;
	std::vector<Node*> children;
	static std::vector<Node*> visited;
	Node *parent;
	int f, g, h;
	int depth;
	bool inClosedSet, inOpenSet;
	typedef std::chrono::high_resolution_clock Clock;

	Node(Matrix m,Node *parent);
	std::vector<Node*> getChildren();
	bool dfs(Matrix finalMatrix, int& numMoves, int& numNodes, Node *n);
	bool bfs(Matrix finalMatrix, int &numMoves, int & numNodes, Node *n);
	bool IDDFS(Matrix finalMatrix, int &numMoves, int & numNodes, Node *n);
	bool DLS(Matrix finalMatrix, int & numMoves, int & numNodes, Node * node, int depth);
	bool Greedy(Matrix finalMatrix, int &numMoves, int & numNodes, Node *n);
	void Astar(Matrix finalMatrix, int &numMoves, int &numNodes, Node *n);
	bool thereisCycle(Matrix m3);
	bool thereisCycle2(Node * n,Matrix m3);
	void numberOfMoves(Node *n,int &numMoves);
	int heuristic(Node * n, Node * u);
	static bool compare(std::pair<Node*, int> i, std::pair<Node*, int> j);
	static std::pair<Node*, int> getMin(std::map<Node*, int> mymap);
};
//std::vector<Node*> Node::visited;