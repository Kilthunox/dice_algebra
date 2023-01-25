#include <iostream>
#include "dice_pool.hpp"
#include <vector>


int main() {
	DicePool dice1d8 = DicePool {1, 8};
	DicePool dice4d6 = DicePool {4, 6};
	Die d6 = Die {6};
	Die d4 = Die {4};

	std::cout << (dice1d8*2)+((dice4d6>2)+1) << std::endl;
}
