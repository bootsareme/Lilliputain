#include "opcode.h"

std::map<std::string, Variable> stack;
std::map<std::string, DWORD> dstack;

std::vector<std::string> split(const std::string& str, const std::string& delim)
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

void Opcode::set(std::string operand1, std::string modifier, std::string operand2)
{
	if (modifier != "=")
		exit(-1);

	Variable var = Variable(operand1, stoi(operand2));
	stack.insert({ var.getName(), var });
}

void Opcode::move(std::string operand1, std::string modifier, std::string operand2)
{
	if (modifier != "->")
		exit(-1);

	if (operand2 == "STDOUT") {
		Variable var = stack[operand1];
		std::cout << var.getValue() << '\n';
	}

	Variable var = stack[operand1];
	stack[operand2].setValue(var.getValue());
	
}

void Opcode::add(std::string operand1, std::string modifier, std::string operand2)
{
	if (modifier == "+") {
		Variable var1 = stack[operand1];
		Variable var2 = stack[operand2];
		var2.setValue(var1.getValue() + var2.getValue());
		stack.erase(var2.getName());
		stack.insert({ var2.getName(), var2 });
	} else if (modifier == "-") {
		Variable var1 = stack[operand1];
		Variable var2 = stack[operand2];
		var2.setValue(var1.getValue() - var2.getValue());
		stack.erase(var2.getName());
		stack.insert({ var2.getName(), var2 });
	} else if (modifier == "*") {
		Variable var1 = stack[operand1];
		Variable var2 = stack[operand2];
		var2.setValue(var1.getValue() * var2.getValue());
		stack.erase(var2.getName());
		stack.insert({ var2.getName(), var2 });
	} else if (modifier == "/") {
		Variable var1 = stack[operand1];
		Variable var2 = stack[operand2];
		var2.setValue(var1.getValue() / var2.getValue());
		stack.erase(var2.getName());
		stack.insert({ var2.getName(), var2 });
	}
	else {
		exit(-1);
	}
}

void Opcode::dword(std::string operand1, std::string modifier, std::string operand2)
{
	if (modifier != "=")
		exit(-1);

	std::vector<std::string> chars = split(operand2, ",");
	std::vector<char> export_e;
	DWORD newString = DWORD(operand1, "");
	dstack.insert({ newString.getName(), newString });

	for (auto i : chars) {
		Variable var = stack[i];
		char j = char(var.getValue());
		export_e.push_back(j);
	}

	newString.setValue(export_e);
	dstack.erase(newString.getName());
	dstack.insert({ newString.getName(), newString });
}

void Opcode::print(std::string operand1, std::string modifier, std::string operand2)
{
	if (modifier != "->")
		exit(-1);

	if (operand2 == "STDOUT") {
		DWORD var = dstack[operand1];
		std::cout << var.getValue() << '\n';
	}
	else {
		DWORD var = dstack[operand1];
		std::ofstream output(operand2);
		output << var.getValue() << '\n';
	}
}

int Opcode::conditional(std::string operand1, std::string modifier)
{
	std::vector<std::string> statement = split(modifier, "=");
	Variable var1 = stack[std::string(1, statement[0].at(0))];
	Variable var2 = stack[statement[1]];

	try {
		if (std::string(1, statement[0].at(1)) == "!") {
			if (var1.getValue() != var2.getValue())
				return NULL;
			else
				return stoi(operand1) + 1;
		} else if (std::string(1, statement[0].at(1)) == "<") {
			if (var1.getValue() <= var2.getValue())
				return NULL;
			else
				return stoi(operand1) + 1;
		}
		else if (std::string(1, statement[0].at(1)) == ">") {
			if (var1.getValue() >= var2.getValue())
				return NULL;
			else
				return stoi(operand1) + 1;
		}
	}
	catch (std::out_of_range e) {
		if (var1.getValue() == var2.getValue())
			return NULL;
		else
			return stoi(operand1) + 1;
	}
}

void Opcode::del(std::string operand1)
{
	DWORD dword = dstack[operand1];
	Variable var = stack[operand1];
	dstack.erase(dword.getName());
	stack.erase(var.getName());
}