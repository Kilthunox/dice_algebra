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
	void eval_parentheses();
	void eval_multiplication();
	void eval_division();
	void eval_modulus();
	void eval_addition();
	void eval_subtraction();
	void subsitute(const int &start, const int &end, std::string &sub, const size_t offset);
	ExpressionValue get_lvalue(size_t &i, const char operand) const;
	ExpressionValue get_rvalue(size_t &i, const char operand) const;


public:
	DiceAlgebra(const std::string &expr);
	bool is_valid();
	void eval();
	int get_result();
	std::string get_expr();
};
