#pragma once

#include <string>
#include <vector>

/* DPMDAS */

class Expression {
	static std::vector<char> DIGITS;
	static std::vector<char> OPERATORS;

private:
	std::string value;
	int result;
	void eval_dice_pool(int i);
	void eval_parentheses();
	void eval_multiplication();
	void eval_division();
	void eval_addition();
	void eval_subtraction();


public:
	Expression(const std::string &value);
	void eval();
	int get_result();
};
