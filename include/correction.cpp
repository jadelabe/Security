#include "correction.h"

correction::correction(std::vector<int> numbers, int w, int h, int base)
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
	hamming = calculateHamming();
}

correction::correction(std::vector<int> numbers, int w, int h, int base, std::vector<int> msg, std::vector<char> alphabet)
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
	hamming = calculateHamming();
	
	codedMsg = msg;
	sourceSeg = calculateSourceSeg(alphabet.size(), base);

}

std::vector<std::vector<int>> correction::getMatrix()
{
	return matrix;
}

std::vector<std::vector<int>> correction::getIdentiyMatrix()
{
	return identityMatrix;
}

std::vector<std::vector<int>> correction::getGenMatrix()
{
	return genMatrix;
}

int correction::getHamming()
{
	return hamming;
}

int correction::getCardinal()
{
	return cardinal;
}

int correction::getLinealSeg()
{
	return linealSeg;
}

int correction::getSourceSeg()
{
	return sourceSeg;
}

int correction::calculateCardinal(int base, int h)
{
	return pow(base, h);
}

int correction::calculateHamming()
{
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
}

void correction::fillIdentityMatrix()
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


void correction::fillGenMatrix()
{
	std::vector<int> vector;
	genMatrix = identityMatrix;
	for (int i = 0; i < matrix.size(); i++) {
		genMatrix[i].insert(genMatrix[i].end(), matrix[i].begin(), matrix[i].end());
	}
}

std::vector<int> correction::linealDeco(int h)
{
	std::vector<int> vector;
	for (int i = 0; i < codedMsg.size(); i+=genMatrix[0].size()) {
		for (int j = 0; j < h; i++) {
			vector.push_back(codedMsg.at(i+j));
		}
	}
	return vector;
}
std::vector<int> correction::sourceDeco()
{
	std::vector<int> vector;
	return vector;
}
int correction::calculateSourceSeg(int alphabetSize, int base)
{
	return ceil(log(alphabetSize) / log(base));
}
