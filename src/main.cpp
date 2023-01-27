#include <iostream>
#include <string>
#include "dice_pool.hpp"
#include "expression.hpp"


int main(int argc, char *argv[]) {
	std::cout << Expression(argv[argc - 1]).get_result() << std::endl;
}
