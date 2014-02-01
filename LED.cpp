//#include <WPIlib.h>
#include <iostream>

int PutColor(int numLEDs, long color);


int main()
{
	PutColor(80, 0xFF0000);
	
	return 0;
}

int PutColor(int numLEDs, long color)
{
	for (int i=0; i<numLEDs; i++)
	{
		for (int j=0; j<24; j++)
		{
			std::cout << "Clock: " << 0;
			std::cout << "\tData: " << ((color & (1 << j)) >> j) << "\n";
			std::cout << "Clock: " << 1 << "\n";
		}
	}

	return 0;
}
