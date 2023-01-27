#include <iostream>
#include "dice_pool.hpp"
#include <vector>
#include <string>
#include "expression.hpp"


int main() {
	DicePool dice1d8 = DicePool {1, 8};
	DicePool dice4d6 = DicePool {4, 6};
	Die d6 = Die {6};
	Die d4 = Die {4};

	std::cout << Expression("1*1*1*(d100*1)").get_result() << std::endl;
}
