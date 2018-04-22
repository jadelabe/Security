#pragma once
#include <iostream>
#include <vector>
#include <cmath> 

class decode
{
public:
	decode(std::vector<int> numbers, int w, int h, int base);
	decode(std::vector<int> numbers, int w, int h, int base, std::vector<int> msg, std::vector<char> alphabet);

	std::vector<std::vector<int>> getMatrix();
	std::vector<std::vector<int>> getIdentiyMatrix();
	std::vector<std::vector<int>> getGenMatrix();
	int getHamming();
	int getCardinal();
	int getLinealSeg();
	int getSourceSeg();
private:
	std::vector<std::vector<int>> matrix;
	std::vector<std::vector<int>> identityMatrix;
	std::vector<std::vector<int>> genMatrix;
	std::vector<int> codedMsg;
	std::vector<int> linealCodedMsg;
	std::vector<int> originalMsg;
	int hamming;
	int cardinal;
	int linealSeg;
	int sourceSeg;

	int calculateCardinal(int base, int h);
	int calculateHamming();
	void fillIdentityMatrix();
	void fillGenMatrix();
	
	std::vector<int> linealDeco(int h);
	std::vector<int> sourceDeco();
	int calculateSourceSeg(int alphabetSize, int base);
};