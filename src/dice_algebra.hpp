#pragma once

#include <string>
#include <vector>
#include "expression_value.hpp"


class DiceAlgebra {
	static std::vector<char> DIGITS;
	static std::vector<char> OPERATORS;

private:
	std::string expr;
	int result;
	void eval_filters();
	void eval_dice_pool();
	void eval_parentheses(size_t &start, size_t &end);
	void eval_multiplication();
	void eval_division();
	void eval_modulus();
	void eval_addition();
	void eval_subtraction();
	void subsitute(const int &start, const int &end, std::string &sub, const size_t offset);
	ExpressionValue get_lvalue(size_t &i);
	ExpressionValue get_rvalue(size_t &i);


public:
	DiceAlgebra(const std::string &expr);
	bool is_valid();
	void eval();
	int get_result();
};
