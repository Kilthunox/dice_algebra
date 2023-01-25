#pragma once

#include <vector>
#include "die.hpp"


class DicePool 
{
private:
	unsigned short cached_result;
	std::vector<Die> pool;
	static bool compare_highest(Die &l_die, Die &r_die);
	static bool compare_lowest(Die &l_die, Die &r_die);


public:
	DicePool(const unsigned short ndice, const unsigned short nsides);
	~DicePool();
	void roll();
	void total();
	unsigned short size();
	unsigned short result();
	int operator-();
	int operator+(DicePool &pool);
	int operator-(DicePool &pool);
	void keep_highest(unsigned short num);
	void keep_lowest(unsigned short num);
};


int operator+(DicePool &pool, const int num);
int operator+(const int num, DicePool &pool);
int operator-(DicePool &pool, const int num);
int operator-(const int num, DicePool &pool);
int operator*(DicePool &pool, const int num);
int operator*(const int num, DicePool &pool);
int operator/(DicePool &pool, const int num);
int operator/(const int num, DicePool &pool);
int operator%(DicePool &pool, const int num);
int operator%(const int num, DicePool &pool);
int operator<(DicePool &pool, const int num);
int operator>(DicePool &pool, const int num);
