#include <encode.h>
#include <correction.h>
#include <iostream>

int main(int argc, char* argv[])
{
	/*
	//Practica 1

	//std::string s = "Existe una cosa muy misteriosa, pero muy cotidiana. Todo el mundo participa de ella, todo el mundo la conoce, pero muy pocos se paran a pensar en ella. Casi todos se limitan a tomarla como viene, sin hacer preguntas. Esta cosa es el tiempo.";
	std::string s = "La noche cae, brumosa ya y morada. Vagas claridades malvas y verdes perduran tras la torre de la iglesia. El camino sube, lleno de sombras, de campanillas, de fragancia de hierba, de canciones, de cansancio y de anhelo.";
	encode p1 = encode(s);

	//Print Chars
	std::vector<int> Char = p1.getChar();
	std::cout << "Ordered Chars:" << std::endl;
	for (int i = 0; i < Char.size(); i++) {
		std::cout << (char) Char[i] << ' ';
	}
	std::cout << std::endl;

	//Print frequency
	std::vector<int> freq = p1.getFreq();
	std::cout << "Frequency:" << std::endl;
	for (int i = 0; i < freq.size(); i++) {
		std::cout << freq[i] << ' ';
	}
	std::cout << std::endl;

	//Print probability
	std::vector<int> prob = p1.getProb();
	std::cout << "Probability:" << std::endl;
	for (int i = 0; i < prob.size(); i++) {
		std::cout << prob[i] << ' ';
	}
    std::cout  << std::endl;

	std::cout << "Bit Length:" ;
	float bitlength = p1.getBitLength();
	std::cout << bitlength << std::endl;
	
	std::cout << "Entropy:" ;
	float entropy = p1.getEntropy();
	std::cout << entropy << std::endl;

	std::cout << "Efficacy:";
	float efficacy = p1.getEfficacy();
	std::cout << efficacy << std::endl;

	
	*/	

	//Practica 2
	//std::vector<int> numbers = { 0, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2}; //w4 h3
	//correction c = correction(numbers, 4, 3, 3);
	/*
	std::vector<int> numbers = { 1,1,0,1,1,1,0,0,0,1,0,1,1,0,1,1,1,0,0,0,1,0,1,1,0,1,1,1,0,0,0,1,0,1,1,1,1,1,1,0,0,0,1,0,1,1,0,1,1,1,0,0,0,1,0,1,1,0,1,1,1,0,0,0,1,0,1,1,0,1,1,1,0,0,0,1,0,1,1,0,1,1,1,1,0,0,1,0,1,1,0,1,1,1,0,1,0,1,0,1,1,0,1,1,1,0,0,1,1,0,1,1,0,1,1,1,0,0,0,1,0,1,1,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0 }; //w12 h12
	correction c = correction(numbers, 12, 12, 2);
	std::vector<std::vector<int>> matrix = c.getMatrix();
	int hamming = c.getHamming();
	int cardinal = c.getCardinal();

	std::cout << "Hamming Distance:";
	std::cout << hamming << std::endl;
	std::cout << "Cardinal:";
	std::cout << cardinal << std::endl;
	*/
	std::vector<int> A = {1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1};
	std::vector<int> msg = {0,1,0,1,1,0,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0,1,1,0,0,0,1,1,1,1,0,1,0,1,0,0,1,0,0,0,0,1,0,1,1,0,0,0,1,0,1,1,0,1,1,0,0,1,1,0,0,1,0,1,0,1,0,0,0,1,0,1,1,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,0,0,0,1,1,1,1,1,1,0,1,0,0,0,1,0,0,1,1,0,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,1,1,0,1,0,1,0,0,0,0,1,0,1,1,0,1,0,1,1,0,1,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,1,1,1,0,0,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,1,0,1,0,0,1,0,0,1,1,0,0,1,0,1,1,0,1,0,0,1,0,1,0,1,1,0,0,1,1,0,0,0,0,0,1,0,1,1,0,0,0,1,0,1,1,0,1,0,1,1,0,1,0,0,1,0,1,0,1,0,0,0,1,0,1,1,0,0,0,1,0,1,1,0,0,1,1,1,1,0,1,0,0,0,1,1,1,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,0,0,0,0,1,0,1,0,0,1,1,0,0,0,0,1,0,1,1,0,1,0,0,1,1,0,0,1,0,0,1,1,0,1,0,0,0,1,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0,1,0,0,0,0,0,0,0,1,0,0,1,1,0,0,1,1,0,1,0,1,0,1,0,0,0,1,1,1,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,1,0,0,0,1,1,1,1,0,0,1,1,0,0,1,1,0,1,0,1,0,1,1,1,0,1,0,0,1,1,1,1,1,1,1,1,0,1,1,0,0,1};
	std::string str = "abcde ABCDEfghijklmnFGHIJKLMNopqrstuvwxyzOPQRSTUVWXYZ.,;¿?¡!";
	std::vector<char> alphabet;
	std::copy(str.c_str(), str.c_str()+str.length(), back_inserter(alphabet));
	correction decode = correction(A, 3, 4, 2, msg, alphabet);
	int sourceSeg = decode.getSourceSeg();

	std::cout << "Source Segment Size:";
	std::cout << sourceSeg << std::endl;
	std::cin.ignore();
	return 0;
}


