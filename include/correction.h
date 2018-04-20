#pragma once
#include <iostream>
#include <vector>
#include <cmath> 

class correction
{
public:
	correction(std::vector<int> numbers, int w, int h, int base);


	std::vector<std::vector<int>> getMatrix();
	std::vector<std::vector<int>> getIdentiyMatrix();
	std::vector<std::vector<int>> getGenMatrix();
	int getHamming();
	int getCardinal();
private:
	std::vector<std::vector<int>> matrix;
	std::vector<std::vector<int>> identityMatrix;
	std::vector<std::vector<int>> genMatrix;
	int hamming;
	int cardinal;

	int calculateCardinal(int base, int h);
	int calculateHamming();
	void fillIdentityMatrix();
	void fillGenMatrix();
};