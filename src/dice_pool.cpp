#include "dice_pool.hpp"
#include "die.hpp"
#include <vector>
#include <bits/stdc++.h>

#include <iostream>


DicePool::DicePool(const unsigned short ndice, const unsigned short nsides) {
	this->cached_result = 0;
	for (unsigned short i=0; i < ndice; ++i) {
		pool.push_back(Die(nsides));
	}
}

DicePool::~DicePool() {
};

void DicePool::roll() {
	cached_result = 0;
	for (Die &die: pool) {
			die.roll();
	}
}

void DicePool::total() {
	cached_result = 0;
	for (Die &die: pool) {
		cached_result += die.result();
	}
}

unsigned short DicePool::result() {
	if (cached_result == 0) {
		total();
	}
	return cached_result;
}

int DicePool::operator-() {
	return -result(); 
}


int DicePool::operator+(DicePool &pool){
	return result() + pool.result();
}

int DicePool::operator-(DicePool &pool){
	return result() - result();	
}

unsigned short DicePool::size() {
	return pool.size();
}

bool DicePool::compare_lowest(Die &l_die, Die &r_die) {
	return l_die.result() < r_die.result();
}

void DicePool::keep_lowest(unsigned short num) {
	cached_result = 0;
	std::sort(pool.begin(), pool.end(), compare_lowest);
	pool.resize(num, Die{0});
}

bool DicePool::compare_highest(Die &l_die, Die &r_die) {
	return l_die.result() > r_die.result();

}

void DicePool::keep_highest(unsigned short num) {
	cached_result = 0;
	std::sort(pool.begin(), pool.end(), compare_highest);
	pool.resize(num, Die{0});
}

int operator+(DicePool &pool, const int num) {
	return pool.result() + num;
}

int operator+(const int num, DicePool &pool) {
	return num + pool.result();
}

int operator-(DicePool &pool, const int num) {
	return pool.result() - num; 
}

int operator-(const int num, DicePool &pool) {
	return num - pool.result();
}

int operator*(DicePool &pool, const int num) {
	return pool.result() * num;
}

int operator*(const int num, DicePool &pool) {
	return num * pool.result();
}

int operator/(DicePool &pool, const int num) {
	return pool.result() / num;
}

int operator/(const int num, DicePool &pool) {
	return num / pool.result();
}

int operator%(DicePool &pool, const int num) {
	return pool.result() % num;
}

int operator%(const int num, DicePool &pool) {
	return num % pool.result();
} 

int operator<(DicePool &pool, const int num) {
	pool.keep_lowest(num);
	return pool.result();
}

int operator>(DicePool &pool, const int num) {
	pool.keep_highest(num);
	return pool.result();
}
