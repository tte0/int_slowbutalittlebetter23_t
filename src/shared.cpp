#include "../include/shared.hpp"
#include "../include/qalc.hpp"

char int23_t::fullAdder(char const&b1, char const&b2, char&carry) {
	const char ans = q_bitwise_xor(q_bitwise_xor(b1,b2),carry);
	carry = q_bitwise_or(q_bitwise_or(q_bitwise_and(b1,b2),q_bitwise_and(b1,carry)),q_bitwise_and(b2,carry));
	return ans;
}
char int23_t::fullSub(char const&b1, char const&b2, char&borrow) {
	char diff;
	if(borrow) {
		diff = q_bitwise_xor(q_bitwise_xor(1,b1),b2);
		borrow = q_bitwise_or(q_bitwise_xor(1,b1),q_bitwise_and(b1,b2));
	}
	else {
		diff = q_bitwise_xor(b1,b2);
		borrow = q_bitwise_and(q_bitwise_xor(1,b1),b2);
	}
	return diff;
}
