#include <iostream>
#include <unistd.h>
#include "mathlib.h"

struct calc
{
	int firstNumber;
	int secondNumber;
	char operation;
	float result;
};

void runner();

int main()
{
	runner();
}

void runner() 
{
	int sum = mathlib::sum(2,3);
	printf("сумма = %d", sum);
}
