#ifndef MARKOVMODEL_HPP_
#define MARKOVMODEL_HPP_
#include <string>
#include <map>

class MarkovModel{
public:
	MarkovModel(std::string text, int k);
	~MarkovModel();
	int order();
	int freq(std::string kgram);
	int freq(std::string kgram, char c);
	char randk(std::string kgram);
	std::string gen(std::string kgram, int T);
	friend std::ostream& operator<<(std::ostream& out, MarkovModel& MM);
	
private:
	int Order;
	std::string _text;
	std::map <std::string, int> _kgrams;
	std::string _alphabet;
};

#endif
