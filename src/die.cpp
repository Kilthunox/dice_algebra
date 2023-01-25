#include <cstdlib>
#include <chrono>
#include <random>
#include "die.hpp"



Die::Die(const unsigned short &nsides): cached_result{0} {
	this->nsides = nsides;
}

Die::~Die(){};

unsigned short Die::random() {
	long seed {std::chrono::system_clock::now().time_since_epoch().count()};
	std::mt19937 generator (seed);
	return generator();
}

void Die::roll() {
	cached_result = 0;
	cached_result = (random() % nsides) + 1;
}

unsigned short &Die::result() {
	if (cached_result == 0) {
		roll();
	}
	return cached_result;
}

int Die::operator-() {
	return -result(); 
}

int Die::operator+(Die &die) {
	return result() + die.result();
} 

int Die::operator-(Die &die) {
	return result() - die.result();
}

int operator+(Die &die, const int num) {
	return die.result() + num;
}

int operator+(const int num, Die &die) {
	return num + die.result();
}

int operator-(Die &die, const int num) {
	return die.result() - num;
}

int operator-(const int num, Die &die) {
	return num - die.result();
}

int operator*(Die &die, const int num) {
	return die.result() * num;
}

int operator*(const int num, Die &die) {
	return num * die.result();
}


int operator/(Die &die, const int num) {
	if (num == 0) {
		return 0;
	}
	return die.result() / num;
}

int operator/(const int num, Die &die) {
	return num / die.result();
}

int operator%(Die &die, const int num) {
	if (num == 0) {
		return 0;
	}
	return die.result() % num;
}

int operator%(const int num, Die &die) {
	return num % die.result();
}


