#pragma once
#include <vector>
#include <string>
#include <exception>

class IndexOutOfBoundsException : public std::exception {
	int x, y;
public:
	IndexOutOfBoundsException(int x, int y) {
		this->x = x;
		this->y = y;
	}

	const char* what() const throw() override{
		std::string error = "Trying to access indexes " + std::to_string(x) + " and " + std::to_string(y) + " which are out of the bounds of the matrix.";
		return error.c_str();
	}
};

class Matrix {
private:
	std::vector<std::vector<int>> m;
	int size=4;
public:
	static bool hasParity(Matrix m1, Matrix m2);
	Matrix(int size = 4);
	int get(int x, int y) const;
	void populateMatrix();
	bool solvability(int soma, int pos1, int soma1, int pos2);
	int whiteSpacePosition(int xwhitespace, int ywhitespace);
	void findWhitespace(int &xwhitespace, int &ywhitespace);
	bool operator ==(const Matrix &m2) const;
	void set(int x, int y, int val);
	int getSize() const;
	bool itsEqual(Matrix m1, Matrix m2) const;
};