#include "Matrix.h"
#include <iostream>

bool Matrix::hasParity(Matrix m1, Matrix m2)
{
  int contador = 0, soma = 0, i, j, l, c, soma1 = 0, k = 0;
	
  int xwhitespace, ywhitespace;
  m1.findWhitespace(xwhitespace,ywhitespace);
  int pos1 = m1.whiteSpacePosition(xwhitespace,ywhitespace); //whitespace position na matriz inicial
  
  m2.findWhitespace(xwhitespace,ywhitespace);
  int pos2 = m2.whiteSpacePosition(xwhitespace,ywhitespace);  // whitespace position na matriz final

	for (i = 0; i<4; i++) {
		for (j = 0; j<4; j++) {
			for (l = i; l<4; l++) {
				if (l == i)
					k = j;
				else k = 0;
				for (c = 0 + k; c<4; c++) {
					if (m1.get(i, j)>m1.get(l, c) && m1.get(l, c) != 0)
						contador++;
				}
			}
			soma += contador;
			contador = 0;
		}
	}
	contador = 0;
	k = 0;
	for (i = 0; i<4; i++) {
		for (j = 0; j<4; j++) {
			for (l = i; l<4; l++) {
				if (l == i)
					k = j;
				else k = 0;
				for (c = 0 + k; c<4; c++) {
					if (m2.get(i, j)>m2.get(l, c) && m2.get(l, c) != 0)
						contador++;
				}
			}
			soma1 += contador;
			contador = 0;
		}
	}

        return m1.solvability(soma, pos1, soma1, pos2);

}

bool Matrix::solvability(int soma, int pos1, int soma1, int pos2){
	bool startState = false; //false = 0 & true = 1;
	bool finalState = false;

	//startState solvability
	if((soma%2 && !(pos1%2)) || (!(soma%2) && pos1%2))
	  startState = true;
	else startState = false;

	//finalState solvability
	if((soma1%2 && !(pos2%2)) || (!(soma1%2) && pos2%2))
	  finalState = true;
	else finalState = false;

	//final solvability
	if(startState == finalState)
	  return true;
	  else return false;
}

int Matrix::whiteSpacePosition(int xwhitespace, int ywhitespace)
{
  int position;

  position = 4 - xwhitespace;
  
  return position;
}
Matrix::Matrix(int size)
{
	this->size = size;
}

int Matrix::get(int x, int y) const
{
	if (x < m.size()) {
		if (y < m[x].size()) {
			return m[x][y];
		}
	}
	
	throw IndexOutOfBoundsException(x, y);
}

void Matrix::populateMatrix()
{
	for (int i = 0; i < size; i++) {
		m.push_back(std::vector<int>());
		for (int j = 0; j < size; j++) {
			int input;
			std::cin >> input;

			m[i].push_back(input);
		}
	}
}

void Matrix::findWhitespace(int &xwhitespace, int &ywhitespace)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (this->get(i, j) == 0){
				xwhitespace = i;
				ywhitespace = j;
			}
		}
	}
}

bool Matrix::operator==(const Matrix & m2) const
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (this->get(i, j) != m2.get(i, j))
				return false;
		}
	}
	return true;
}

void Matrix::set(int x, int y,int val)
{
	if ((unsigned int) x < m.size()) {
		if (y < m[y].size()) {
			m[x][y]=val;
			return;
		}
	}

	throw IndexOutOfBoundsException(x, y);
}

int Matrix::getSize() const
{
	return size;
}

bool Matrix::itsEqual(Matrix m1, Matrix m2) const
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (m1.get(i, j) != m2.get(i, j))
				return false;
		}
	}
	return true;
}
