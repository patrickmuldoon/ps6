#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <map>
#include <algorithm>
#include "MarkovModel.hpp"

MarkovModel::MarkovModel(std::string text, int k)
{
	Order = k;
	_alphabet = text;
	_text = text;

	int kgramEnd;
	if(Order >= _text.length()){
		throw std::runtime_error("k is too large");
	}
	std::sort(_alphabet.begin(), _alphabet.end());
	_alphabet.erase(std::unique(_alphabet.begin(), _alphabet.end()), _alphabet.end());

	for(unsigned int i = 1; i < text.length()+1; i++){
		std::string kgram_string, kplus_string, wraparound_string;
		int wrapLength;

		kgramEnd = i + k - 1;

		if(kgramEnd >= text.length()){
			wrapLength = kgramEnd - text.length() + 1;
			wraparound_string = text.substr(0, wrapLength);
			kgram_string = text.substr(i, text.length()-1) + wraparound_string;
			kplus_string = kgram_string + text.at(wrapLength);
		}
		else{
			kgram_string = text.substr(i, k);
			if(kgramEnd+1 >= text.length())
			{
				kplus_string = kgram_string + text.at(0);
			}
			else {
				kplus_string = text.substr(i, k+1);
			}
		}

		std::map<std::string, int>::iterator kgram_it = _kgrams.find(kgram_string);
		if(kgram_it != _kgrams.end()){
			kgram_it -> second += 1;
		}
		else{
			_kgrams[kgram_string] = 1;
		}

		std::map<std::string, int>::iterator kplus_it = _kgrams.find(kplus_string);
		if(kplus_it != _kgrams.end()){
			kplus_it->second += 1;
		}
		else{
			_kgrams[kplus_string] = 1;
		}
	}
}

MarkovModel::~MarkovModel(){

}

int MarkovModel::order()
{
	return Order;
}

char MarkovModel::randk(std::string kgram)
{
	std::vector<char> character_count;
	int kgram_freq;
	int index;

	if(freq(kgram) == 0){
		throw std::runtime_error("kgram does not exist in the text");
	}
	else{
		kgram_freq = freq(kgram);
	}

	for(unsigned int i = 0; i < _alphabet.length(); i++){
		char kplus_char = _alphabet.at(i);
		int kplus_freq = freq(kgram, kplus_char);
		for(int j = 0; j < kplus_freq; j++){
			character_count.push_back(kplus_char);
		}
	}

	index = rand() % character_count.size();
	return character_count.at(index);
}

std::string MarkovModel::gen(std::string kgram, int T)
{
	if(kgram.length() != Order){
		throw std::runtime_error("kgram length must == order");
	}
	
	std::string text = kgram;

	if(Order == 0 && T == 0)
		return _text;

	while(text.length() < T){
		char a = randk(kgram);
		std::string string(1,a);
		text.append(string);
		if(Order > 0){
			kgram = kgram.substr(1);
		}
		else{
			kgram = kgram;
		}
		std::string next_kgram = kgram + string;
		kgram = next_kgram;
	}
	return text;
}

int MarkovModel::freq(std::string kgram)
{
	if(Order != kgram.length()){
		throw std::runtime_error("kgram length must == order");
	}
	std::map<std::string, int>::iterator it = _kgrams.find(kgram);
	if(it != _kgrams.end()){
		return it->second;
	}
	else
		return 0;
}


int MarkovModel::freq(std::string kgram, char c)
{
	int frequency = 0;

	if(Order == 0){
		for(unsigned int i = 0; i < _text.length(); i++){
			if(_text.at(i) == c){
				frequency++;
			}
		}
		return frequency;
	}

	if(Order != kgram.length()){
		throw std::runtime_error("kgram length must == order");
	}

	std::string string(1, c);
	std::string kplus_string = kgram + string;
	std::map<std::string, int>::iterator it = _kgrams.find(kplus_string);
	if(it != _kgrams.end()){
		return it->second;
	}
	else
		return 0;

}

std::ostream& operator << (std::ostream& out, MarkovModel& MM)
{
	std::cout << std::endl << "Order = " << MM.Order << std::endl;
	std::cout << "Available alphabet = " << MM._alphabet << std::endl;

	for(std::map<std::string, int>::iterator it = MM._kgrams.begin(); it != MM._kgrams.end(); ++it)
	{
		if(it->first.length() == MM.Order){
			std::cout << std::endl;
			std::cout << "kgram:	";
			std::cout << it->first << "   | frequency: " << it->second;
			std::cout << std::endl;
		}
		else{
			std::cout << "		";
			std::cout << it->first << " ----->" << it->second;
			std::cout << std::endl;
		}
	}

	return out;
}
