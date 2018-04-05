#include "encode.h"


encode::encode(std::string s)
{
<<<<<<< HEAD
=======
	
>>>>>>> origin/master
	std::string str = s;
	std::vector<std::vector<int>> CharFreqProb = calculateFreq(s);
	for (int i = 0; i < CharFreqProb.size(); i++) {
		Char.push_back(CharFreqProb[i][0]);
		freq.push_back(CharFreqProb[i][1]);
		prob.push_back(CharFreqProb[i][2]);
	}
	huffman(freq);
	calculateBitLength();
	calculateEntropyFreq();
	calculateEficacy();
	
	for (int i = 0; i < huff.size(); i++) {
		encodedTextLength += (huff[i].length() * freq[i]);
	}
	
	/*
	std::vector<int> dataVec;
	//int dataArray[] = { 30, 20, 10, 10, 5, 5, 5, 5, 5, 5 };
	//int dataArray[] = { 27, 16, 4, 56, 22, 2, 78, 45, 36, 13, 12, 7 };
	//int dataArray[] = { 83, 69, 67, 82, 69, 84, 79, 32, 68, 69, 32, 85, 78, 79, 32, 83, 69, 67, 82, 69, 84, 79, 32, 83, 69, 71, 85, 82, 79 };
	//int dataArray[] = { 32,45,37,13};
	//int dataArray[] = {37/157, 11/314, 13/157, 10/157, 45/314, 3/314, 27/314, 4/157, 11/314, 8/157, 73/314};
	//int dataArray[] = {74, 11, 26, 20, 45, 3, 27, 8, 11, 16, 73};
	//int dataArray[] = {2,5,4,4,3,6,4,6,4,4,2};
	unsigned dataArraySize = sizeof(dataArray) / sizeof(int);
	std::copy(&dataArray[0], &dataArray[dataArraySize], back_inserter(dataVec));


	huff.resize(dataVec.size());
	std::sort(dataVec.begin(), dataVec.end());
	std::reverse(dataVec.begin(), dataVec.end());
	
	float millan = 0.0f;
	
	for (int i = 0; i < dataVec.size(); i++) {
		millan+= pow(2.0, -dataVec[i]);
	}
	entropy = millan;
	
	freq = dataVec;

	huffman(dataVec);
	calculateBitLength();
	calculateEntropyFreq();
	calculateEficacy();

	float extendedEntropy = calculateExtendedEntropy(2);


	//override original src
	calculateExtendedSource();
	*/
}

std::vector<std::string> encode::getChar()
{
	return huff;
}
std::vector<int> encode::getFreq()
{
	return freq;
}
std::vector<int> encode::getProb()
{
	return prob;
}
std::vector<std::string> encode::getHuff()
{
	return huff;
}
float encode::getBitLength()
{
	return bitlength;
}

float encode::getEntropy()
{
	return entropy;
}

float encode::getEfficacy()
{
	return efficacy;
}
int encode::getEncodedTextLength()
{
	return encodedTextLength;
}

std::string encode::sortString(std::string s)
{
	std::sort(s.begin(), s.end());
	return s;

}

std::vector<std::vector<int>> encode::calculateFreq(std::string s)
{
	std::string orderedS = sortString(s);

	std::vector<int> table;
	std::vector<std::vector<int>> list;

	int i = 1, prob;
	char c = NULL;
	while (orderedS != "") {
		
		c = orderedS[0];
		orderedS.erase(orderedS.begin());
		while (orderedS[0] == c) {
			i++;
			orderedS.erase(orderedS.begin());
		}
		prob = (int) std::round(((float)i / (float)s.length()) *1000);

		table.push_back(c);
		table.push_back(i);
		table.push_back(prob);
		list.push_back(table);
		
		table.clear();
		i = 1;
	}	
	struct sortList
	{
		inline bool operator() (std::vector<int> v1, std::vector<int> v2)
		{
			return (v1[1] > v2[1]);
		}
	};
	std::sort(list.begin(), list.end(), sortList());

	return list;
}

void encode::huffman(std::vector<int> proba)
{

	huff.resize(proba.size());
	int size = proba.size();
	std::vector<int> table;
	int min1, min2, pos1, pos2;
	
	for(int t = size; t> 0; t--){	
		min1 = proba[proba.size()-1];
		min2 = proba[proba.size()-2];
		pos1 = proba.size()-1;
		pos2 = proba.size()-2;
		for (int i = 0; i < proba.size(); i++) {
			if (proba[i] <= min1 && proba[i] != -1 && i != pos1) {
				pos2 = pos1;
				min2 = min1;
				pos1 = i;
				min1 = proba[i];
			}
			else if (min2 == -1 && proba[i] != -1) {
				min2 = proba[i];
				pos2 = i;

			}
			else if (proba[i] <= min2 && proba[i] != -1 && i != pos1) {
				min2 = proba[i];
				pos2 = i;
			
			}
		}
		if( min1 != NULL && min2 != NULL && pos1 != pos2){
			table.push_back(pos2);
			table.push_back(pos1);
			table.push_back(proba.size());
			positions.push_back(table);
			table.clear();

			proba.push_back(min1 + min2);
			proba.at(pos2) = -1;
			proba.at(pos1) = -1;
		}
	}
	std::string code = "";
	findHuff(code, size-1, proba.size()-1);
	
}

void encode::fillHuff(std::string code, int size, int left, int right)
{
	if (left > size) {
		findHuff((std::string) "0" + code, size, left);
	}
	else {
		huff[left]= "0" + code;
	}
	if (right > size) {
		findHuff((std::string) "1" + code, size, right);
	} else{
		huff[right] = "1" + code;
	}
}

void encode::findHuff(std::string code, int size, int pos)
{
	for (int i = 0; i < positions.size(); i++) {
		if (positions[i][2] == pos) {
			fillHuff(code, size, positions[i][0], positions[i][1]);
		}
	}
}

void encode::calculateBitLength()
{
	float totalProb = 0;
	for (int i = 0; i < freq.size(); i++) {
		bitlength += (huff[i].length() * freq[i]);
		totalProb += freq[i];
	}
	bitlength = bitlength / totalProb;
}

void encode::calculateEntropyFreq()
{
	float totalEntr = 0.0f;
	float prob;
	int nchars = 0;
	for (int i = 0; i < freq.size(); i++) {
		nchars += freq[i];
	}
	for (int i = 0; i < freq.size(); i++) {
		prob =(float)freq[i] / (float) nchars;
		totalEntr += prob * log2((1.0f / prob));
	}
	entropy = totalEntr;
}

void encode::calculateEficacy()
{
	efficacy = entropy / bitlength;
}

float encode::calculateExtendedEntropy(int n)
{
	return n * entropy;
}

std::vector<std::vector<int>> encode::calculateExtendedSource()
{
	std::vector<std::vector<int>> extendedSrc;
	std::vector<std::string> extCode;
	std::vector<int> extFreq;

	int nchars = 0;
	for (int i = 0; i < freq.size(); i++) {
		nchars += freq[i];
	}

	for (int i = 0; i < huff.size(); i++) {
		for (int t = 0; t < huff.size(); t++) {
			//extCode.push_back(huff[i] + huff[t]);
			extFreq.push_back(freq[i] * freq[t]);
		}
	}

	//Clean this to new variables so no overlaping
	freq = extFreq;
	huffman(extFreq);
	calculateBitLength();
	calculateEntropyFreq();
	calculateEficacy();

	return extendedSrc;
}
