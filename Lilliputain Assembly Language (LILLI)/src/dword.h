#pragma once

#include <string>
#include <vector>

class DWORD
{
	std::string name;
	std::string value;

public:
	DWORD(std::string id, std::string val)
		: name(id), value(val) {}
	
	DWORD() 
		: name(""), value("") {}
	
	std::string getName() const {
		return this->name;
	}

	std::string getValue() const {
		return this->value;
	}

	void setValue(std::vector<char> char_list) {
		for (char i : char_list)
			this->value += i;
	}
};