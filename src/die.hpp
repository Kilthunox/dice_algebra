#pragma once


class Die {
	private:
		unsigned short nsides;
		unsigned short cached_result;
		
		static unsigned short random();
	public:
		Die(const unsigned short &nsides);
		~Die();
		int operator-();
		int operator+(Die &die);
		int operator-(Die &die);
		void roll();
		unsigned short &result();

};

int operator+(Die &die, const int num);
int operator+(const int num, Die &die);
int operator-(Die &die, const int num);
int operator-(const int num, Die &die);
int operator*(Die &die, const int num);
int operator*(const int num, Die &die);
int operator/(Die &die, const int num);
int operator/(const int num, Die &die);
int operator%(Die &die, const int num);
int operator%(const int num, Die &die);
