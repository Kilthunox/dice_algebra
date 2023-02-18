# Dice Algebra


dice_algebra is a game development utility to evaluate [dice notation](https://en.wikipedia.org/wiki/Dice_notation) with pseudo-random number generation.



# Compile
Compile from source using g++.
```
g++ src/*.cpp -std=c++17 -o dice_algebra.64
```


# Usage
The default build evaluates a string from the command line arguments as a dice expression.
```
./bin/dice_algebra.64 "1d6"
```
This will produce a random number between 1 and 6 inclusively.


## Operators:
- d -> Dice: Denotes number of dice (n) and number of sides (s) each die has when rolled:: `nds`
- < -> Less Than: Filters the resulting dice pool to keep the lowest (f) results:: `nds<f`
- > -> Greater Than: Filters the resulting dice pool to keep the highest (f) results:: `nds>f`
- () -> Parentheses: Evaluates expressions within balanced parentheses first.
- * -> Multiplication: Multiplies the left integer(l) by the right integer(r):: `l*r`
- / -> Integer division: Divides using the left integer(l) as the numerator and the right integer(r) as the denominator. Returns the result without the remainder:: `l/r`
- % -> Modulus: Divides using the left integer(l) as the numerator and the right integer(r) as the denominator. Returns the remainder:: `l%r`
- + -> Addition: Sums the left and right integers:: `l+r`
- - -> Subtraction: Subtracts the left integer from the right integer:: `l-r`


## Important notes:
Evaluated expressions can never be negative values. The expression `1d20-20` will always equal 0.



# Examples:

- `1d6`: Rolls 1 6 sided dice.
- `4d10`: Rolls 4 10 sided dice and sums the result.
- `1d6+4d10`: Rolls 1 6 sided dice and 4 10 sided dice and sums the result.
- `10d10>2`: Rolls 10 10 sided dice and returns the sum of the highest 2 results.
- `(10d100<1)%1d4`: Rolls 10 100 sided dice returning the lowest single result and divides it by the result of rolling 1 4 sided dice only returning the remainder.
