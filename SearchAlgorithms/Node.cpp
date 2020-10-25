#include "Node.h"
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>

class mycomparison
{
	bool reverse;
public:
	mycomparison(const bool& revparam = false)
	{
		reverse = revparam;
	}
	bool operator() (const Node* lhs, const Node* rhs) const
	{
		if (reverse) return (lhs->f<rhs->f);
		else return (lhs->f>rhs->f);
	}
};

bool Node::compare(std::pair<Node*, int> i, std::pair<Node*, int> j)
{
	return i.second < j.second;
}

std::pair<Node*,int> Node::getMin(std::map<Node*, int> mymap)
{
	std::pair<Node*, int> min = *std::min_element(mymap.begin(), mymap.end(),
		&compare);
	return min;
}
Node::Node(Matrix m,Node *parent)
{

	this->matrix = m;
	this->parent = parent;
	visitado = false;
	if (parent != nullptr) {
		this->depth = this->parent->depth + 1;
	}
	else{
		this->depth = 0;
	}

	inClosedSet = false;
	inOpenSet = false;
}

std::vector<Node*> Node::getChildren()
{
	int xwhitespace, ywhitespace,tmp;
	Matrix m3;
	Node *node;
	if (children.size() == 0) {
		matrix.findWhitespace(xwhitespace,ywhitespace);
		// 0 up 1 right 2 down 3 left
		for (int i = 0; i < 4; i++) {
			if (i == 0 && ywhitespace != 0) {
				m3 = matrix;
				tmp = m3.get(xwhitespace, ywhitespace - 1);
				m3.set(xwhitespace, ywhitespace - 1, 0);
				m3.set(xwhitespace, ywhitespace, tmp);
				/*if (thereisCycle(m3)==true) { 
					node = new Node(m3, this);
					children.push_back(node);
				}*/
				if(thereisCycle2(this,m3)==true){
					node = new Node(m3, this);
					children.push_back(node);
				}
	
			}
			else if (i == 1 && xwhitespace != matrix.getSize()-1) {
				m3 = matrix;
				tmp = m3.get(xwhitespace +1, ywhitespace );
				m3.set(xwhitespace+1, ywhitespace, 0);
				m3.set(xwhitespace, ywhitespace, tmp);
				/*if (thereisCycle(m3) == true) {
					node = new Node(m3, this);
					children.push_back(node);
				}*/
					if(thereisCycle2(this,m3)==true){
					node = new Node(m3, this);
					children.push_back(node);
				}
			}
			else if (i == 2 && ywhitespace != matrix.getSize()-1) {
				m3 = matrix;
				tmp = m3.get(xwhitespace, ywhitespace + 1);
				m3.set(xwhitespace, ywhitespace + 1, 0);
				m3.set(xwhitespace, ywhitespace, tmp);
				/*if (thereisCycle(m3) == true) {
					node = new Node(m3, this);
					children.push_back(node);
				}*/
					if(thereisCycle2(this,m3)==true){
					node = new Node(m3, this);
					children.push_back(node);
				}
			}
			else if(i==3 && xwhitespace !=0){
				m3 = matrix;
				tmp = m3.get(xwhitespace-1, ywhitespace);
				m3.set(xwhitespace-1, ywhitespace , 0);
				m3.set(xwhitespace, ywhitespace, tmp);
				/*if (thereisCycle(m3) == true) {
					node = new Node(m3, this);
					children.push_back(node);
				}*/
					if(thereisCycle2(this,m3)==true){
					node = new Node(m3, this);
					children.push_back(node);
				}
			}
		}
	}
	return children;
}

bool Node::dfs(Matrix finalMatrix, int & numMoves, int & numNodes,Node *n)
{
	auto t1 = Clock::now();
	std::stack<Node *> Q;
	Q.push(n);
	n->depth=0;
	while (!Q.empty()) {
		Node* u = Q.top();
		Q.pop();
		if (u->matrix.itsEqual(u->matrix, finalMatrix) == true) {
			numberOfMoves(u, numMoves);
			std::cout << "chegamos ao final****************************************************" << std::endl;
			std::cout << "Numero de movimentos:" << numMoves << std::endl;
			std::cout << "Numero nos gerados:" << numNodes << std::endl;
			 auto t2 = Clock::now();
			  std::cout << "Duration: " 
              << (std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count())*pow(10, -9)
              << " seconds" << std::endl;
			return true;
		}
			if(u->depth > 13)
				continue;
			visited.push_back(u);
			u->getChildren();
			numNodes += u->children.size(); 
			for (int i = 0; i <u->children.size(); i++) {
			
				Q.push(u->children[i]);
				u->children[i]->depth+1;
			}
		

	}
	return false;

}

bool Node::bfs(Matrix finalMatrix, int &numMoves, int & numNodes, Node *n) {
	auto t1 = Clock::now();
	std::queue<Node*> Q;
	Q.push(n);
	while (!Q.empty()) {
		Node* t = Q.front();
		Q.pop();
		if (t->matrix.itsEqual(t->matrix, finalMatrix) == true) {
			numberOfMoves(t, numMoves);
			std::cout << "chegamos ao final****************************************************" << std::endl;
			std::cout << "Numero de movimentos:" << numMoves << std::endl;
			std::cout << "Numero nos gerados:" << numNodes << std::endl;
			 auto t2 = Clock::now();
			  std::cout << "Duration: " 
              << (std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count())*pow(10, -9)
              << " seconds" << std::endl;
			return true;
		}
		visited.push_back(t);
		t->getChildren();
		numNodes += getChildren().size();
		for (int i = 0; i < t->children.size(); i++) {
			Q.push(t->children[i]);
		}
	}
	return false;

}

bool Node::IDDFS(Matrix finalMatrix, int & numMoves, int & numNodes, Node * n)
{
  int Maxdepth = 0;
  bool solutionFound = false;
  auto t1 = Clock::now();
  while(!solutionFound){
    solutionFound = DLS(finalMatrix, numMoves, numNodes, n, Maxdepth);
    Maxdepth++;
    numNodes=0;

  }
 auto t2 = Clock::now();
			  std::cout << "Duration: " 
              << (std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count())*pow(10, -9)
              << " seconds" << std::endl;

}

bool Node::DLS(Matrix finalMatrix, int & numMoves, int & numNodes, Node * n, int Maxdepth){
	std::stack<Node*> Q;
	n->depth = 0;
	Q.push(n);
	while (!Q.empty()) {
		Node* t = Q.top();
		Q.pop();
		if (t->matrix.itsEqual(t->matrix, finalMatrix) == true) {
			numberOfMoves(t, numMoves);
			std::cout << "chegamos ao final****************************************************" << std::endl;
			std::cout << "Numero de movimentos:" << numMoves << std::endl;
			std::cout << "Numero nos gerados:" << numNodes << std::endl;
			return true;
		}
		if(t->depth >= Maxdepth)
		  continue;
		  
		t->getChildren();
		numNodes += getChildren().size();
		for (int i = 0; i < t->children.size(); i++) {
			Q.push(t->children[i]);
			t->children[i]->depth+1;
		}
		
	}
	return false;
}


bool Node::Greedy(Matrix finalMatrix, int &numMoves, int & numNodes, Node *n){
	typedef std::priority_queue<Node*, std::vector<Node*>, mycomparison> node_pq;
	auto t1 = Clock::now();
	node_pq openSet;
	openSet.push(n);
	Node *finalNode;
	finalNode = new Node(finalMatrix, nullptr);
	while (!openSet.empty()) {
		Node* t = openSet.top();
		openSet.pop();
		if(t->matrix.itsEqual(t->matrix, finalMatrix) == true){
			numberOfMoves(t, numMoves);
			std::cout << "chegamos ao final****************************************************" << std::endl;
			std::cout << "Numero de movimentos:" << numMoves << std::endl;
			std::cout << "Numero nos gerados:" << numNodes << std::endl;
			 auto t2 = Clock::now();
			  std::cout << "Duration: " 
              << (std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count())*pow(10, -9)
              << " seconds" << std::endl;
			return true;
		}
		visited.push_back(t);
		t->getChildren();
		numNodes += getChildren().size();
		
		for (int i = 0; i < t->children.size(); i++) {
			openSet.push(t->children[i]);
		}
	}
	return false;


}

void Node::Astar(Matrix finalMatrix, int & numMoves, int & numNodes, Node * n)
{
	auto t1 = Clock::now();
	typedef std::priority_queue<Node*, std::vector<Node*>, mycomparison> node_pq;

	Node* finalNode = new Node(finalMatrix,nullptr);
	std::vector<Node*> closedSet;
	node_pq openSet;
	openSet.push(n);
	n->inOpenSet = true;


	std::map<Node*, int> gScore;
	gScore.insert(std::pair<Node*, int>(n, 0));

	std::map<Node*, int> fScore;
	fScore.insert(std::pair<Node*, int>(n, std::numeric_limits<int>::infinity()));
	n->f = std::numeric_limits<int>::infinity();

	fScore[n] = heuristic(n, finalNode);
	n->f = heuristic(n, finalNode);

	while (!openSet.empty()) {
		Node* current = nullptr;
		current = openSet.top();
		openSet.pop();
		current->inOpenSet = false;
		if (current != nullptr) {
			if (current->matrix.itsEqual(current->matrix, finalMatrix)) {
				numberOfMoves(current, numMoves);
				std::cout << "chegamos ao final****************************************************" << std::endl;
				std::cout << "Numero de movimentos:" << numMoves << std::endl;
				std::cout << "Numero nos gerados:" << numNodes << std::endl;
				 auto t2 = Clock::now();
			  std::cout << "Duration: " 
              << (std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count())*pow(10, -9)
              << " seconds" << std::endl;
				return;
			}
		}
		else break;

		
		closedSet.push_back(current);
		current->inClosedSet = true;

		current->getChildren();
		numNodes += getChildren().size();
		std::vector<Node*> neighbors = current->children;

		for (Node* node : neighbors) {
			int inClosedSet = node->inClosedSet;

			if (inClosedSet)
				continue;

			int tentative_gScore = gScore[current] + 1;

			int inOpenSet =node->inOpenSet;
			if (!inOpenSet) {
				gScore[node] = tentative_gScore;
				fScore[node] = gScore.at(node) + heuristic(node, finalNode);
				node->f = fScore[node];
				current->visitado = true;

				node->inOpenSet = true;
				openSet.push(node);
			}
			else if (tentative_gScore >= gScore[node])
				continue;

			
		}
	}

	numMoves = -1;
	return;
}


bool Node::thereisCycle(Matrix m3) {
	for (int i = 0; i < visited.size(); i++) {
		if (m3.itsEqual(m3, visited[i]->matrix))
			return false;
	}
	return true;
}


bool Node::thereisCycle2(Node * n,Matrix m3) {
	Node *tmp = n;
	while(tmp->parent!=nullptr){
	
		if(tmp->parent->matrix.itsEqual(tmp->parent->matrix,m3))
			return false;
	 	tmp=tmp->parent;
	}
	return true;
}


void Node::numberOfMoves(Node *n, int &numMoves) {
	Node *current = n;
	while (current->parent != NULL) {	
		numMoves++;
		current = current->parent;
	}
	
}

int Node::heuristic(Node *n, Node * u) {
	int h= 0;
	for (int i = 0; i < n->matrix.getSize(); i++) {
		for (int j = 0; j < n->matrix.getSize(); j++) {
			if (n->matrix.get(i, j) != u->matrix.get(i, j))
				h++;
		}
	}
	return h;

	
}