#include <string>
#include <bits/stdc++.h>
#include <ctype.h>
#include "dice_pool.hpp"
#include "die.hpp"
#include "expression.hpp"
#include <iostream>
#include "expression_value.hpp"


Expression::Expression(const std::string &value) {
	result = 0;
	this->value = value;
}


std::vector<char> Expression::DIGITS {
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

std::vector<char> Expression::OPERATORS {
		'+',
		'-',
		'*',
		'/',
		'%',
		'<',
		'<'
	};	

void Expression::eval() {
	std::cout << "EVAL=======" << value << std::endl;
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
		Expression inner_exp {value.substr(lpars.top() + 1, rpars.top() - lpars.top() - 1)};	
		std::cout << "----------------------" << inner_exp.value << std::endl;
		inner_exp.eval();	
		std::cout << "==========" << value << std::endl;
		value = value.substr(0, lpars.top()) + inner_exp.value + value.substr(rpars.top() + 1);
		std::cout << "===========" << value << std::endl;
		lpars.pop();
		rpars.pop();	
	}

	eval_dice_pool();
	eval_multiplication();
	eval_division();
	eval_modulus();
	eval_addition();
	eval_subtraction();
}

ExpressionValue Expression::get_lvalue(size_t &i) {
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

ExpressionValue Expression::get_rvalue(size_t &i) {
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



void Expression::eval_dice_pool() {
	bool has_operators = true;
	while (has_operators) {
		has_operators = false;
		for (size_t i=0; i < value.size(); ++i) {
			bool is_operator = std::toupper(value.at(i)) == 'D';
			if (is_operator) {
					has_operators = true;
					std::cout<<"EVAL_DICE " << value << std::endl;
					ExpressionValue lvalue {get_lvalue(i)};
					ExpressionValue rvalue {get_rvalue(i)};
					DicePool dice = DicePool(lvalue.value, rvalue.value);
					std::string result = std::to_string(dice.result());
					std::cout << "LEFT____:" << lvalue.value << " RIGHT___:" << rvalue.value << " i:" << i << std::endl; 
					std::cout << "MATHS " << result << std::endl;
					subsitute(lvalue.distance, rvalue.distance, result, i);
					break;
				} 
			}
		}
	}




void Expression::subsitute(const int &start, const int &end, std::string &sub, const size_t offset=0) {
	std::cout << "PRE SUB :: " << value << std::endl;
	std::string pre;
	pre = {value.substr(0, (offset - start) + 1)};
	std::cout << "CALCING POST NOW..." << std::endl;
	std::string post;
	post = {value.substr((end + offset))};
	std::cout << "PRE: " << pre << " POST: " << post << std::endl;
	value = pre + sub + post;
	std::cout << "POST SUB :: " << value << std::endl;
}


void Expression::eval_multiplication() {
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

void Expression::eval_division() {
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

void Expression::eval_modulus() {
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



void Expression::eval_addition() {
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


void Expression::eval_subtraction() {
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


int Expression::get_result() {
	eval();
	return std::stoi(value);
}

