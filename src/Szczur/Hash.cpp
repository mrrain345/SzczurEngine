#include <cstddef>
#include <stdint.h>

static uint32_t dynHash_calc(const char* s, size_t N, size_t I) {
	return (I == N) ? 2166136261u : (dynHash_calc(s, N, I+1) ^ s[I]) * 16777619u;
}

uint32_t hash(const char* s, size_t N) {
	return dynHash_calc(s, N, 0);
}
