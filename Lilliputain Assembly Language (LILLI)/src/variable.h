#pragma once

#include <string>

class Variable
{
	std::string name;
	int value;

public:
	Variable(std::string id, int val);
	Variable();
	std::string getName() const;
	int getValue() const;
	void setValue(int val);
};

