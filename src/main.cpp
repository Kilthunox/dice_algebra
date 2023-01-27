#include <iostream>
#include "dice_pool.hpp"
#include <vector>
#include <string>
#include "expression.hpp"


int main() {
	std::cout << Expression("(10d10>3)+10").get_result() << std::endl;
}
