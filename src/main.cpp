#include <iostream>
#include "dice_algebra.hpp"


int main(int argc, char *argv[]) {
	std::cout << DiceAlgebra(argv[argc - 1]).get_result() << std::endl;
}
