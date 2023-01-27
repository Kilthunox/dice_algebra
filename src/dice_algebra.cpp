#include <string>
#include <bits/stdc++.h>
#include <ctype.h>
#include "dice_pool.hpp"
#include "die.hpp"
#include "dice_algebra.hpp"
#include "expression_value.hpp"


DiceAlgebra::DiceAlgebra(const std::string &value) {
	result = 0;
	this->value = value;
}


std::vector<char> DiceAlgebra::DIGITS {
	'0', 
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9'
};

std::vector<char> DiceAlgebra::OPERATORS {
	'+',
	'-',
	'*',
	'/',
	'%',
	'<',
	'<'
};	

void DiceAlgebra::eval() {
	std::stack<size_t> lpars {};
	std::stack<size_t> rpars {};
	for (size_t i=0; i < value.length(); ++i) {
		switch (value.at(i)) {
			case '(':
				lpars.push(i);
				break;
			case ')':
				rpars.push(i);
				break;
		}
	}

	while (!lpars.empty()) {
		DiceAlgebra inner_exp {value.substr(lpars.top() + 1, rpars.top() - lpars.top() - 1)};	
		inner_exp.eval();	
		value = value.substr(0, lpars.top()) + inner_exp.value + value.substr(rpars.top() + 1);
		lpars.pop();
		rpars.pop();	
	}

	eval_filters();
	eval_dice_pool();
	eval_multiplication();
	eval_division();
	eval_modulus();
	eval_addition();
	eval_subtraction();
}

ExpressionValue DiceAlgebra::get_lvalue(size_t &i) {
	int step = 1;
	std::string result;
	while (true) {
		if ((static_cast<int>(i) - step) >= 0) {
			if (std::isdigit(value.at(i - step))) {
				result = value.at(i - step) + result;
				++step;
			} else {
				break;
			}
		} else {
			break;
		}
	}

	if (result == "") {
		result = "1";
	}
	return ExpressionValue(std::stoi(result), step);
}

ExpressionValue DiceAlgebra::get_rvalue(size_t &i) {
	int step = 1;
	std::string result;
	while (true) {
		if ((i + step) < value.size()) {
			if (std::isdigit(value.at(i + step))) {
				result += value.at(i + step);
				step++;
			} else {
				break;
			}
		} else {
			break;
		}
	}

	if (result == "") {
		result = "1";
	}
	return ExpressionValue(std::stoi(result), step);
}


void DiceAlgebra::eval_filters() {
	bool has_operators = true;
	while (has_operators) {
		has_operators = false;
		for (size_t i=0; i < value.size(); ++i) {
			if (value.at(i) == '>') {
				has_operators = true;
				ExpressionValue filter_value {get_rvalue(i)};
				size_t step = i;
				while (step > 0) {
					if (std::toupper(value.at(--step)) == 'D') {
						ExpressionValue lvalue {get_lvalue(step)};
						ExpressionValue rvalue {get_rvalue(step)};
						DicePool dice = DicePool(lvalue.value, rvalue.value);
						dice.roll();
						dice > filter_value.value;
						dice.sum();
						std::string result = std::to_string(dice.get_result());
						value = value.substr(0, (step - lvalue.distance) + 1) + result + value.substr(i + filter_value.distance);
						break;
					}
				}
				break;
			} else if (value.at(i) == '<') {
				if (value.at(i) == '<') {
					has_operators = true;
					ExpressionValue filter_value {get_rvalue(i)};
					size_t step = i;
					while (step > 0) {
					if (std::toupper(value.at(--step)) == 'D') {
						ExpressionValue lvalue {get_lvalue(step)};
						ExpressionValue rvalue {get_rvalue(step)};
						DicePool dice = DicePool(lvalue.value, rvalue.value);
						dice.roll();
						dice < filter_value.value;
						dice.sum();
						std::string result = std::to_string(dice.get_result());
						value = value.substr(0, (step - lvalue.distance) + 1) + result + value.substr(i + filter_value.distance);
						break;
						}
					}
					break;
				} 
			}
		}
	}
}



void DiceAlgebra::eval_dice_pool() {
	bool has_operators = true;
	while (has_operators) {
		has_operators = false;
		for (size_t i=0; i < value.size(); ++i) {
			bool is_operator = std::toupper(value.at(i)) == 'D';
			if (is_operator) {
				has_operators = true;
				ExpressionValue lvalue {get_lvalue(i)};
				ExpressionValue rvalue {get_rvalue(i)};
				DicePool dice = DicePool(lvalue.value, rvalue.value);
				dice.roll();
				dice.sum();
				std::string result = std::to_string(dice.get_result());
				subsitute(lvalue.distance, rvalue.distance, result, i);
				break;
			} 
		}
	}
}




void DiceAlgebra::subsitute(const int &start, const int &end, std::string &sub, const size_t offset=0) {
	std::string pre;
	pre = {value.substr(0, (offset - start) + 1)};
	std::string post;
	post = {value.substr((end + offset))};
	value = pre + sub + post;
}


void DiceAlgebra::eval_multiplication() {
	bool has_operators = true;
	while (has_operators) {
		has_operators = false;
		for (size_t i=0; i < value.size(); ++i) {
			bool is_operator = value.at(i) == '*';
			if (is_operator) {
				has_operators = true;
				ExpressionValue lvalue {get_lvalue(i)};
				ExpressionValue rvalue {get_rvalue(i)};
				std::string result = std::to_string(lvalue.value * rvalue.value);
				subsitute(lvalue.distance, rvalue.distance, result, i);
				break;
			} 
		}
	}
}

void DiceAlgebra::eval_division() {
	bool has_operators = true;
	while (has_operators) {
		has_operators = false;
		for (size_t i=0; i < value.size(); ++i) {
			bool is_operator = value.at(i) == '/';
			if (is_operator) {
				has_operators = true;
				ExpressionValue lvalue {get_lvalue(i)};
				ExpressionValue rvalue {get_rvalue(i)};
				std::string result = std::to_string(lvalue.value / rvalue.value);
				subsitute(lvalue.distance, rvalue.distance, result, i);
				break;
			} 
		}
	}
}

void DiceAlgebra::eval_modulus() {
	bool has_operators = true;
	while (has_operators) {
		has_operators = false;
		for (size_t i=0; i < value.size(); ++i) {
			bool is_operator = value.at(i) == '%';
			if (is_operator) {
				has_operators = true;
				ExpressionValue lvalue {get_lvalue(i)};
				ExpressionValue rvalue {get_rvalue(i)};
				std::string result = std::to_string(lvalue.value % rvalue.value);
				subsitute(lvalue.distance, rvalue.distance, result, i);
				break;
			} 
		}
	}
}



void DiceAlgebra::eval_addition() {
	bool has_operators = true;
	while (has_operators) {
		has_operators = false;
		for (size_t i=0; i < value.size(); ++i) {
			bool is_operator = value.at(i) == '+';
			if (is_operator) {
				has_operators = true;
				ExpressionValue lvalue {get_lvalue(i)};
				ExpressionValue rvalue {get_rvalue(i)};
				std::string result = std::to_string(lvalue.value + rvalue.value);
				subsitute(lvalue.distance, rvalue.distance, result, i);
				break;
			} 
		}
	}
}


void DiceAlgebra::eval_subtraction() {
	bool has_operators = true;
	while (has_operators) {
		has_operators = false;
		for (size_t i=0; i < value.size(); ++i) {
			bool is_operator = value.at(i) == '-';
			if (is_operator) {
				has_operators = true;
				ExpressionValue lvalue {get_lvalue(i)};
				ExpressionValue rvalue {get_rvalue(i)};
				std::string result = std::to_string(lvalue.value - rvalue.value);
				subsitute(lvalue.distance, rvalue.distance, result, i);
				break;
			} 
		}
	}
}


int DiceAlgebra::get_result() {
	eval();
	return std::stoi(value);
}

