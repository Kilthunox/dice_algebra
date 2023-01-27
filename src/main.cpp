#include <iostream>
#include "dice_pool.hpp"
#include <vector>
#include <string>
#include "expression.hpp"


int main() {
	std::cout << Expression("(1d8+6)/2%10*10-2").get_result() << std::endl;
}
