#include "variable.h"

Variable::Variable()
	: name(""), value(NULL) {}

Variable::Variable(std::string id, int value) 
{
	this->value = value;
	this->name = id;
}

std::string Variable::getName() const
{
	return this->name;
}

int Variable::getValue() const
{
	return this->value;
}

void Variable::setValue(int val)
{
	this->value = val;
}