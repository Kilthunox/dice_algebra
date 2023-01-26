#include <string>
#include <bits/stdc++.h>
#include <ctype.h>
#include "dice_pool.hpp"
#include "die.hpp"
#include "expression.hpp"
#include <iostream>


Expression::Expression(const std::string &value) {
	result = 0;
	this->value = '_' + value + '_';
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
	for (size_t i = 1; i < value.length() - 1; ++i) {
		switch (value.at(i)) {
			case 'd':
				dice_indices.push_back(i);
				break;
		}

	}

	for (size_t i: dice_indices) {
		eval_dice_pool(i);
	}
}


void Expression::eval_dice_pool(int i) {
	std::string ndice;
	std::string nsides;
	
	int left = 1;
	int right = 1;
	while (true) {
		bool l_finished = false;
		bool r_finished = false;
			if (std::isdigit(value.at(i - left))) {
				ndice = ndice + value.at(i - left);
				left++;
			} else {
				l_finished = true;
			}
			if (std::isdigit(value.at(i + right))) {
				nsides = nsides + value.at(i + right);
				right++;
		} else {
			r_finished = true;
		}

		if (l_finished && r_finished) {
			break;
		}
	}
	std::cout << "ndice: " << ndice << " nsides: " << nsides << std::endl;
	DicePool dice = DicePool(std::stoi(ndice), std::stoi(nsides));
	std::string result = std::to_string(dice.result());
	value = "_" + value.substr(0, i - left) + result + value.substr(i + right, value.size());
}


int Expression::get_result() {
	eval();
	std::cout << value << std::endl;
	return 1;
}

