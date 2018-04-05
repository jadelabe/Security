#include <encode.h>


int main(int argc, char* argv[])
{
	//std::string s = "Existe una cosa muy misteriosa, pero muy cotidiana. Todo el mundo participa de ella, todo el mundo la conoce, pero muy pocos se paran a pensar en ella. Casi todos se limitan a tomarla como viene, sin hacer preguntas. Esta cosa es el tiempo.";
	//std::string s = "La noche cae, brumosa ya y morada. Vagas claridades malvas y verdes perduran tras la torre de la iglesia. El camino sube, lleno de sombras, de campanillas, de fragancia de hierba, de canciones, de cansancio y de anhelo.";
	std::string s = "A lo largo de mi vida he tenido multitud de contactos con multitud de gente seria. Vivi mucho con personas mayores y les he conocido muy de cerca; pero esto no ha mejorado mi opinion sobre ellas.";
	encode p1 = encode(s);

	//Print Chars
	std::vector<std::string> Char = p1.getChar();
	std::cout << "Ordered Chars:" << std::endl;
	for (int i = 0; i < Char.size(); i++) {
		std::cout << Char[i].length() << ' ';
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

	std::cout << "Encoded Text Length:";
	float encodedTextLength = p1.getEncodedTextLength();
	std::cout << encodedTextLength << std::endl;



	std::cin.ignore();
	return 0;
}
