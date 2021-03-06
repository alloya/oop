#include <iostream>
#include <string>

using namespace std;

bool AreArgumentsCorrect(int argc)
{
	if (argc != 2)
	{
		return false;
	}
	return true;
}

bool IsItNumber(const string &number)
{
	for (unsigned int i = 0; i < number.length(); i++)
	{
		if (!isdigit(number[i]))
		{
			return false;
		}
	}
	return true;
}

bool IsNumberCorrect(const int &inputNumber)
{
	return (!(inputNumber < 0 || inputNumber > 255));
}

uint8_t ReverseNumber(uint8_t number)
{
	number = (number & 0b11110000) >> 4 | (number & 0b00001111) << 4;
	number = (number & 0b11001100) >> 2 | (number & 0b00110011) << 2;
	number = (number & 0b10101010) >> 1 | (number & 0b01010101) << 1;
	return number;
}

int main(int argc, char * argv[])
{
	if (!AreArgumentsCorrect(argc))
	{
		cout << "Invalid arguments count" << endl <<
			"Usage: flipbyte.exe <0-255>" << endl;
	}
	else
	{
		unsigned int inputNumber = atoi(argv[1]);
		if (IsItNumber(argv[1]))
		{
			if (IsNumberCorrect(inputNumber))
			{
				cout << "Your value is " << inputNumber << endl;
				int flippedValue = (int)ReverseNumber(inputNumber);
				cout << "Flipped value is " << flippedValue << endl;
			}
			else
			{
				cout << "Input value should be from 0 to 255" << endl;
			}
		}
		else
		{
			cout << "Input value should contain only digits" << endl;
		}
	}
	return 0;
}