#include <exception>
#include <stdexcept>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <ostream>
#include <iterator>
#include <istream>
#include "MarkovModel.hpp"

int main(int argc, char* argv[])
{
	if(argc < 2){
		throw std::runtime_error("Not enough arguments");
	}
	
	int k = atoi(argv[1]);
	int t = atoi(argv[2]);
	std::string kgram;
	std::cin >> std::noskipws;
	std::istream_iterator<char> it(std::cin);
	std::istream_iterator<char>end;
	std::string input(it,end);

	

	MarkovModel mm(input, k);

	std::cout << mm << std::endl;
	kgram = input.substr(0, k);
	std::string gen_text = mm.gen(kgram,t);

	std::cout << "Original text: " << input << std::endl;
	std::cout << "Generated text: " << gen_text << std::endl;
	
	return 0;
}
