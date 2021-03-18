#include "RGB.h"

RGB::RGB(unsigned char r, unsigned char g, unsigned char b)
{
	this->R = r;
	this->G = g;
	this->B = b;
}

int RGB::HexadecimalToDecimal(std::string hex)
{
	int hexLength = hex.length();
	double dec = 0;

	for (int i = 0; i < hexLength; ++i)
	{
		char b = hex[i];

		if (b >= 48 && b <= 57)
			b -= 48;
		else if (b >= 65 && b <= 70)
			b -= 55;

		dec += b * pow(16, ((hexLength - i) - 1));
	}

	return (int)dec;
}

RGB RGB::HexadecimalToRGB(std::string hex)
{
	if (hex[0] == '#')
		hex = hex.erase(0, 1);

	unsigned char r = (unsigned char)HexadecimalToDecimal(hex.substr(0, 2));
	unsigned char g = (unsigned char)HexadecimalToDecimal(hex.substr(2, 2));
	unsigned char b = (unsigned char)HexadecimalToDecimal(hex.substr(4, 2));

	return RGB(r, g, b);
}
