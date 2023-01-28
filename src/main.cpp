#include <iostream>
#include "dice_algebra.hpp"
#include <queue>


int main(int argc, char *argv[]) {
	std::cout << DiceAlgebra(argv[1]).get_result() << std::endl;
}
