#pragma once

class Jstring
{
public:
	char pad[0x24];
	unsigned int size;
	wchar_t str[1];
};