#include "tokenizer.h"

std::vector<std::string> Tokenizer::split(const std::string& str, const std::string& delim)
{
	std::vector<std::string> tokens;
	size_t prev = 0, pos = 0; 

	do 
	{
		pos = str.find(delim, prev);

		if (pos == std::string::npos)
			pos = str.length();
		
		std::string token = str.substr(prev, pos - prev);

		if (!token.empty()) 
			tokens.push_back(token);
		
		prev = pos + delim.length();

	} while (pos < str.length() && prev < str.length());

	return tokens;
}

void Tokenizer::parse(std::ifstream& src) 
{
	std::vector<std::string> opcodes;
	std::vector<std::string> arg1, arg2;
	std::vector<std::string> operand;
	
	for (std::string instruction; std::getline(src, instruction);)
	{
		std::string pos1 = instruction.substr(0, instruction.find(" "));
		std::vector<std::string> token = split(instruction, " ");

		if (token.size() > 1 && token.size() > 2 && token.size() > 3) {
			opcodes.push_back(pos1);
			arg1.push_back(token[1]);
			arg2.push_back(token[3]);
			operand.push_back(token[2]);
		} else if (token.size() > 1 && token.size() > 2) {
			opcodes.push_back(pos1);
			arg1.push_back(token[1]);
			arg2.push_back("`");
			operand.push_back(token[2]);
		} else if (token.size() > 1) {
			opcodes.push_back(pos1);
			arg1.push_back(token[1]);
			arg2.push_back("`");
			operand.push_back("`");
		} else {
			opcodes.push_back(pos1);
			arg1.push_back("`");
			arg2.push_back("`");
			operand.push_back("`");
		}
	}
	link(opcodes, arg1, operand, arg2);
}

void Tokenizer::link(std::vector<std::string> instruction, std::vector<std::string> arg1,
	std::vector<std::string> modifier, std::vector<std::string> arg2)
{	
	size_t lines = 0;

	for (int i = 0; i < instruction.size(); i++) {
		if (instruction[i] == "SET")
			Opcode::set(arg1[i], modifier[i], arg2[i]);
		else if (instruction[i] == "MOV")
			Opcode::move(arg1[i], modifier[i], arg2[i]);
		else if (instruction[i] == "ARITH")
			Opcode::add(arg1[i], modifier[i], arg2[i]);
		else if (instruction[i] == "DWORD")
			Opcode::dword(arg1[i], modifier[i], arg2[i]);
		else if (instruction[i] == "PRINT")
			Opcode::print(arg1[i], modifier[i], arg2[i]);
		else if (instruction[i] == "DEL")
			Opcode::del(arg1[i]);
		else if (instruction[i] == "INT")
			std::this_thread::sleep_for(std::chrono::milliseconds(stoi(arg1[i])));
		else if (instruction[i] == "CHECK") {
			if (Opcode::conditional(arg1[i], modifier[i]) != NULL) {
				lines = i + Opcode::conditional(arg1[i], modifier[i]);
				goto _thread;
			}
			else {
				continue;
			}
		}
		else if (instruction[i] == "JMP") {
			lines = stoi(arg1[i]);
			goto _thread;
		}
	}

	goto _end;

_thread:
	for (int i = lines - 1; i < instruction.size(); i++) {
		if (instruction[i] == "SET")
			Opcode::set(arg1[i], modifier[i], arg2[i]);
		else if (instruction[i] == "MOV")
			Opcode::move(arg1[i], modifier[i], arg2[i]);
		else if (instruction[i] == "ARITH")
			Opcode::add(arg1[i], modifier[i], arg2[i]);
		else if (instruction[i] == "DWORD")
			Opcode::dword(arg1[i], modifier[i], arg2[i]);
		else if (instruction[i] == "PRINT")
			Opcode::print(arg1[i], modifier[i], arg2[i]);
		else if (instruction[i] == "DEL")
			Opcode::del(arg1[i]);
		else if (instruction[i] == "INT")
			std::this_thread::sleep_for(std::chrono::milliseconds(stoi(arg1[i])));
		else if (instruction[i] == "CHECK") {
			if (Opcode::conditional(arg1[i], modifier[i]) != NULL) {
				lines = i + Opcode::conditional(arg1[i], modifier[i]);
				goto _thread;
			}
			else {
				continue;
			}
		} else if (instruction[i] == "JMP") {
			lines = stoi(arg1[i]);
			goto _thread;
		}
	}
_end:
	exit(0);
}
