#pragma once
#include <iostream>
#include <algorithm> 
#include <string>
#include <vector>
#include <list>
#include <cmath>

class encode
{
public:
	encode(std::string s);

	std::vector<int> getChar();
	std::vector<int> getFreq();
	std::vector<int> getProb();
	std::vector<std::string> getHuff();
	float getBitLength();
	float getEntropy();
	float getEfficacy();
	int getEncodedTextLength();

private:

	float bitlength = 0.0f;
	float entropy = 0.0f;
	float efficacy = 0.0f;
	int encodedTextLength = 0;
	std::string str;
	std::vector<int> Char;
	std::vector<int> freq;
	std::vector<int> prob;
	std::vector<std::string> huff;
	std::vector<std::vector<int>> positions;
	
	std::string sortString(std::string s);
	std::vector<std::vector<int>> calculateFreq(std::string s);
	void huffman(std::vector<int> prob);
	void fillHuff(std::string code, int size, int left, int right);
	void findHuff(std::string code, int size, int pos);
	void calculateBitLength();
	void calculateEntropyFreq();
	void calculateEficacy();
	float calculateExtendedEntropy(int n);
	std::vector<std::vector<int>> calculateExtendedSource();
};