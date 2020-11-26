#pragma once

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>

#include "variable.h"
#include "dword.h"

namespace Opcode
{
	void set(std::string operand1, std::string modifier, std::string operand2);
	void move(std::string operand1, std::string modifier, std::string operand2);
	void add(std::string operand1, std::string modifier, std::string operand2);
	void dword(std::string operand1, std::string modifier, std::string operand2);
	void print(std::string operand1, std::string modifier, std::string operand2);
	int conditional(std::string operand1, std::string modifier);
	void del(std::string operand1);
}