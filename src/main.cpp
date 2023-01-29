#include <iostream>
#include "dice_algebra.hpp"
#include <queue>


int main(int argc, char *argv[]) {
	DiceAlgebra expression {argv[1]};
	switch (expression.validate()) {
		case DiceAlgebra::ValidationResponse::IS_VALID:
			std::cout << DiceAlgebra(argv[1]).get_result() << std::endl;
			break;
		case DiceAlgebra::ValidationResponse::BAD_CHAR:
			std::cout << "BAD CHARACTER" << std::endl;
			break;
		case DiceAlgebra::ValidationResponse::UNBALANCED:
			std::cout << "UNBALANCED PARENTHESES" << std::endl;
			break;
		case DiceAlgebra::ValidationResponse::BAD_FILTER:
			std::cout << "BAD USE OF FILTER" << std::endl;
			break;
		case DiceAlgebra::ValidationResponse::ZERO_DIVISION:
			std::cout << "ZERO DIVISION ERROR" << std::endl;
			break;
	}
}
