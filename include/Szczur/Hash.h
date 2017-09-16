#pragma once
#include <stdint.h>

template<size_t N, size_t I=0>
struct hash_calc {
	static inline constexpr uint32_t apply(const char (&s)[N]) {
		return (hash_calc<N, I+1>::apply(s) ^ s[I]) * 16777619u;
	}
};

template<size_t N>
struct hash_calc<N,N> {
	static inline constexpr uint32_t apply(const char (&s)[N]) {
		return 2166136261u;
	}
};

template<size_t N>
inline constexpr uint32_t hash(const char (&s)[N]) {
	return hash_calc<N>::apply(s);
}


uint32_t hash(const char* s, size_t N);
