//#include <WPIlib.h>
#include <time.h>
#include <iostream>

int PutColor(int numLEDs, long color);

void sleep(unsigned int mseconds)
{
	clock_t goal = mseconds + clock();
	while (goal > clock());
}

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
			std::cout << "\tData: " << (color & (1 << j)) << "\n";
			std::cout << "Clock: " << 1 << "\n";
			sleep(500);
		}
	}

	return 0;
}
