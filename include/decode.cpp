#include "decode.h"

decode::decode(std::vector<int> numbers, int w, int h, int base)
{
	//Generate Matrix
	matrix.clear();
	std::vector<int> vector;
	for (int i = 0; i < h; i++) {
		for (int i = 0; i < w; i++) {
			vector.push_back(numbers.front());
			numbers.erase(numbers.begin());
		}
		matrix.push_back(vector);
		vector.clear();
	}
	cardinal = calculateCardinal(base, h);
	fillIdentityMatrix();
	fillGenMatrix();
	generateBasicWords(h, base);
	generateWords(base);

	hamming = calculateHamming();
}

decode::decode(std::vector<int> numbers, int w, int h, int base, std::vector<int> msg, std::vector<char> alphabet)
{
	matrix.clear();
	std::vector<int> vector;
	for (int i = 0; i < h; i++) {
		for (int i = 0; i < w; i++) {
			vector.push_back(numbers.front());
			numbers.erase(numbers.begin());
		}
		matrix.push_back(vector);
		vector.clear();
	}
	cardinal = calculateCardinal(base, h);
	fillIdentityMatrix();
	fillGenMatrix();

	
	codedMsg = msg;
	sourceSeg = calculateSourceSeg(alphabet.size(), base);


	generateBasicWords(sourceSeg, base);
	generateWords(base);
	hamming = calculateHamming();
	
	parityCheck(h, w, base);

	linealCodedMsg = linealDeco(h);
	decoMsg = sourceDeco();

	for (int i = 0; i < decoMsg.size(); i++) {
		for (int j = 0; j < alphabet.size(); j++) {
			if (decoMsg[i] == basicWords[j]) {
				originalMsg.push_back(alphabet[j]);
			}
		}
	}


}

std::vector<std::vector<int>> decode::getMatrix()
{
	return matrix;
}

std::vector<std::vector<int>> decode::getIdentiyMatrix()
{
	return identityMatrix;
}

std::vector<std::vector<int>> decode::getGenMatrix()
{
	return genMatrix;
}

int decode::getHamming()
{
	return hamming;
}

int decode::getCardinal()
{
	return cardinal;
}

int decode::getLinealSeg()
{
	return linealSeg;
}

int decode::getSourceSeg()
{
	return sourceSeg;
}

int decode::calculateCardinal(int base, int h)
{
	return (int) pow(base, h);
}

int decode::calculateHamming()
{
	/* 
	//Faster
	//not 100% precise???
	int distance = 99;
	int foo = 0;
	bool fooChanged = false;
	for (int i = 0; i < genMatrix.size(); i++) {
		for (int j = 0; j < genMatrix.size(); j++) {
			for (int t = 0; t < genMatrix[i].size(); t++) {
				foo += abs(genMatrix[i][t] - genMatrix[j][t]);
				if (foo > 0){
					fooChanged = true;
				}
			}
			if (foo < distance && fooChanged) {
				distance = foo;
			}
			foo = 0;
			fooChanged = false;
		}
	}
	return distance;
	*/

	int distance = 99;
	int foo = 0;
	bool fooChanged = false;
	for (int i = 0; i < words.size(); i++) {
		for (int j = 0; j < words.size(); j++) {
			for (int t = 0; t < words[i].size(); t++) {
				foo += abs(words[i][t] - words[j][t]);
				if (foo > 0) {
					fooChanged = true;
				}
			}
			if (foo < distance && fooChanged) {
				distance = foo;
			}
			foo = 0;
			fooChanged = false;
		}
	}
	return distance;
}

void decode::fillIdentityMatrix()
{
	std::vector<int> vector;
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix.size(); j++) {
			if (i == j) {
				vector.push_back(1);
			}
			else {
				vector.push_back(0);
			}
		}
		identityMatrix.push_back(vector);
		vector.clear();
	}
}

void decode::fillGenMatrix()
{
	std::vector<int> vector;
	genMatrix = identityMatrix;
	for (int i = 0; i < matrix.size(); i++) {
		genMatrix[i].insert(genMatrix[i].end(), matrix[i].begin(), matrix[i].end());
	}
}

void decode::generateWords(int base)
{
	words.resize(numberOfWords);
	int x;
	for (int i = 0; i < numberOfWords; i++) {
		for (int t = 0; t < genMatrix[0].size(); t++)  {
			x = 0;
			for (int j = 0; j < genMatrix.size(); j++) {
				x += (basicWords[i][j] * genMatrix[j][t]) % base;
			}
			words[i].push_back(x % base);
		}
	}
}

void decode::generateBasicWords(int length, int base)
{
	numberOfWords = pow(base, length);
	basicWords.resize(numberOfWords);
	for (int i = 0; i < numberOfWords; i++) {
		appendNumber(i, i, base);
	}
	for (int i = 0; i < numberOfWords; i++) {
		if (basicWords[i].size() < length) {
			for (int j = basicWords[i].size(); j < length; j++) {
				basicWords[i].insert(basicWords[i].begin(), 0);
			}
		}
	}
}

void decode::appendNumber(int pos, int number, int base)
{
	if (number == 0){
		return;
	}
	int x = number % base;
	number /= base;
	if (x < 0){
		number += 1;
	}
	appendNumber(pos, number, base);

	if (x < 0) {
		basicWords[pos].push_back(x + (base * -1));
	}
	else {
		basicWords[pos].push_back(x);
	}

	return;
}

void decode::parityCheck(int h, int w, int base)
{
	//It should work, problem may be coming from the decoding phase
	//only works for binary and up to 2bit errors

	//Generate control matrix H
	//	matrix.w = matrix.h
	//	generate new identity
	//	append identiy
	//Pick words length = G.w from codedMsg
	//multiply by H
	//	result = 0->good
	//	dif -> bad
	//		search result in H.columns   
	//		change bit in word position H.column
	// 		check sum of 2 H.columns if not corrected


	std::vector<int> syndrome;
	std::vector<int> vector;
	std::vector<int> foo;
	std::vector<std::vector<int>> controlH;
	int x, y, z , j;
	bool valid = true;
	//traspose matrix
	for (int cw = 0; cw < w; cw++) {
		for (int ch = 0; ch < h; ch++) {

			vector.push_back(matrix[ch][cw]);
		}
		controlH.push_back(vector);
		vector.clear();
	}
	//generate I for traspose
	std::vector<std::vector<int>> TidentityMatrix;
	for (int i = 0; i < controlH.size(); i++) {
		for (int j = 0; j < controlH.size(); j++) {
			if (i == j) {
				vector.push_back(1);
			}
			else {
				vector.push_back(0);
			}
		}
		TidentityMatrix.push_back(vector);
		vector.clear();
	}
	// merge T and new I ( control H | TidentityMatrix)
	std::vector<std::vector<int>> control;
	control = controlH;
	for (int i = 0; i < controlH.size(); i++) {
		control[i].insert(control[i].end(), TidentityMatrix[i].begin(), TidentityMatrix[i].end());
	}

	for (int i = 0; i < codedMsg.size() - control[0].size();) {
		for (int k = 0; k < control.size(); k++) {
			x = 0;
			y = 0;
			do{
				j = i % control[0].size();
				x+= (codedMsg[i] * control[k][j]) % base;
				i++;
			} while (i % control[0].size() != 0);

			i -= control[0].size();
			syndrome.push_back(x % base);
		}
		for (int t = 0; t < syndrome.size(); t++) {
			if (syndrome[t]) {
				valid = false;
				goto searchParity;
			}
		}
		searchParity:
		if (!valid){
			for (int s = 0; s < control[0].size(); s++) {
				z = 0;
				for (int r = 0; r < control.size(); r++) {
					if (syndrome[r] == control[r][s]) {
						z++;
					}
				}
				if (z == control.size()) {
					if (codedMsg[i + s]) {
						codedMsg[i + s] = 0;
					}
					else {
						codedMsg[i + s] = 1;
					}
					valid = true;
				}
			}
			//quickfix for 2 bits, should build a better method
			if(!valid){
				for (int q = 0; q < control[0].size(); q++) {
					for (int w = 0; w < control[0].size(); w++) {
						for (int e = 0; e < control.size(); e++) {
							foo.push_back((control[e][q] + control[e][w]) % base);
						}
						if (syndrome == foo){
							if (codedMsg[i + q]) {
								codedMsg[i + q] = 0;
							}
							else {
								codedMsg[i + q] = 1;
							}
							if (codedMsg[i + w]) {
								codedMsg[i + w] = 0;
							}
							else {
								codedMsg[i + w] = 1;
							}
						}
						foo.clear();
					}
				}
			}
		}
		i += genMatrix[0].size();
		syndrome.clear();
	}


}

std::vector<int> decode::linealDeco(int h)
{
	std::vector<int> vector;
	for (int i = 0; i < codedMsg.size()-h; i+=genMatrix[0].size()-h) {
		for (int j = 0; j < h; i++) {
			vector.push_back(codedMsg.at(i));
			j++;
		}
	}
	return vector;
}
std::vector<std::vector<int>> decode::sourceDeco()
{
	std::vector<std::vector<int>> decodedMsg;
	std::vector<int> vector;
	for (int i = 0; i < linealCodedMsg.size() - sourceSeg; ) {
		for (int j = 0; j < sourceSeg; i++) {
			vector.push_back(linealCodedMsg.at(i));
			j++;
		}
		decodedMsg.push_back(vector);
		vector.clear();
	}
	return decodedMsg;
}
int decode::calculateSourceSeg(int alphabetSize, int base)
{
	return ceil(log(alphabetSize) / log(base));
}
