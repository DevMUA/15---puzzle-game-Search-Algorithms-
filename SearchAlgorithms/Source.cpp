#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Node.h"

//prototypes


void menu();
std::vector<Node*> Node::visited;

//main
int main() {
	int n,numMoves=0,numNodes=0;
	Matrix m1, m2;
	std::cout << "matriz inicial:" << std::endl;
	m1.populateMatrix();
	std::cout << "matriz final:" << std::endl;
	m2.populateMatrix();
	Node startingnode(m1,NULL);
	startingnode.depth = 0;
	if (Matrix::hasParity(m1,m2))
	{
		menu();
		std::cin >> n;
		switch (n) {
		case 1: startingnode.dfs(m2,numMoves,numNodes,&startingnode); break;
		case 2: startingnode.bfs(m2, numMoves, numNodes, &startingnode); break;
		case 3: startingnode.IDDFS(m2, numMoves, numNodes, &startingnode); break;
	    case 4: startingnode.Greedy(m2, numMoves, numNodes, &startingnode); break;
		case 5: startingnode.Astar(m2, numMoves, numNodes, &startingnode); break;
		default:std::cout << "Escolha uma opção correcta" << std::endl;
		}
	}
	else
	{
		printf("Não há solução possivel\n");
	}




	return 0;
}

//functions


void menu() {
	std::cout << "Escolha o algoritmo:" << std::endl;
	std::cout << "1-Busca em profundidade" << std::endl;
	std::cout << "2-Busca em largura" << std::endl;
	std::cout << "3-IDFS" << std::endl;
	std::cout << "4-Gulosa" << std::endl;
	std::cout << "5-A*" << std::endl;


}


