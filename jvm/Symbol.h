#pragma once
#include <string>

class Symbol {
public:
	short _length;
	short _identity;
	char pad[0x4];
	char _body[1];

	std::string AsString() {
		return std::string(_body, _length);
	}
};