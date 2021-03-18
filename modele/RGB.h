#pragma once

#include <string>

class RGB
{
public:
	unsigned char R;
	unsigned char G;
	unsigned char B;

	RGB(unsigned char r, unsigned char g, unsigned char b);
	static int HexadecimalToDecimal(std::string hex);
	static RGB HexadecimalToRGB(std::string hex);
	bool Equals(RGB rgb);
};

