#include <string>
#include <bits/stdc++.h>
#include <ctype.h>
#include "dice_pool.hpp"
#include "die.hpp"
#include "expression.hpp"
#include <iostream>


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
	std::vector<size_t> dice_indices {};
	std::vector<size_t> start_paren_indices {};
	std::vector<size_t> end_paren_indices {};

	for (size_t i = 0; i < value.length(); ++i) {
		switch (value.at(i)) {
			case '(':
				start_paren_indices.push_back(i);
				break;
			case ')':
				end_paren_indices.push_back(i);
				break;
			case 'd':
				dice_indices.push_back(i);
				break;
		}

	}

	

	for (size_t i = 0; i < start_paren_indices.size(); ++i) {
		eval_parentheses(start_paren_indices.at(i), end_paren_indices.at(i));
	}

	for (size_t &i: dice_indices) {
		eval_dice_pool(i);
	}
}


void Expression::eval_dice_pool(size_t &i) {
	std::string ndice;
	std::string nsides;
	
	int start = 1;
	int end = 1;
	bool start_finished = false;
	bool end_finished = false;
	while (!start_finished && !end_finished) {
			if ((static_cast<int>(i) - start) >= 0) {
				if (std::isdigit(value.at(i - start))) {
					ndice = ndice + value.at(i - start);
					start++;
				} else {
					start_finished = true;
				}
			} else {
				start_finished = true;
			}
			if ((i + end) < value.size()) {
				if (std::isdigit(value.at(i + end))) {
					nsides = nsides + value.at(i + end);
					end++;
				} else {
					end_finished = true;
				}
			} else {
				end_finished = true;
			}
	}

	if (nsides == "") {
		nsides = "1";
	}

	if (ndice == "") {
		ndice = "1";
	}
	DicePool dice = DicePool(std::stoi(ndice), std::stoi(nsides));
	std::string result = std::to_string(dice.result());
	subsitute(start, end, result, i);
}


void Expression::subsitute(const int &start, const int &end, std::string &sub, const size_t offset=0) {
	std::string pre;
	if (start > 1) {
		pre = {value.substr(0, start - 1)};
	}
	std::string post;
	if (end > 1) {
		post = {value.substr(offset + end, end - 1)};
	} 
	value = pre + sub + post;
}


void Expression::eval_parentheses(size_t &start, size_t &end) {
	int expr_length = (end) - (start + 1);
	Expression inner_expr {value.substr(start + 1, expr_length)};
	std::cout << inner_expr.value << std::endl;
	inner_expr.eval();
	subsitute(start, end, inner_expr.value);
}


int Expression::get_result() {
	eval();
	return std::stoi(value.substr(1, value.size() - 1));
}
