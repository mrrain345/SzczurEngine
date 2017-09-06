#pragma once

template <typename T, const T&(*GET)(), void(*SET)(const T&) = ((void(*)(const int&))0)>
class property {
public:
	const T& operator=(const T& val) { SET(val); return GET(); }
	operator T() { return GET(); }
};
