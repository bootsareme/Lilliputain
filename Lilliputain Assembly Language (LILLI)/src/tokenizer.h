#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "opcode.h"
#include "variable.h"
#include "dword.h"

namespace Tokenizer 
{
	void parse(std::ifstream& src);

	std::vector<std::string> split(const std::string& str, const std::string& delim);

	void link(std::vector<std::string> instruction, std::vector<std::string> arg1,
		std::vector<std::string> modifier, std::vector<std::string> arg2);
}