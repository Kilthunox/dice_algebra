#pragma once

#include <string>
#include <vector>
#include "expression_value.hpp"

/* PDMDAS */

class Expression {
	static std::vector<char> DIGITS;
	static std::vector<char> OPERATORS;

private:
	std::string value;
	int result;
	void eval_dice_pool();
	void eval_parentheses(size_t &start, size_t &end);
	void eval_multiplication();
	void eval_division(size_t &i);
	void eval_addition(size_t &i);
	void eval_subtraction(size_t &i);
	void subsitute(const int &start, const int &end, std::string &sub, const size_t offset);
	ExpressionValue get_lvalue(size_t &i);
	ExpressionValue get_rvalue(size_t &i);


public:
	Expression(const std::string &value);
	void eval();
	int get_result();
};
