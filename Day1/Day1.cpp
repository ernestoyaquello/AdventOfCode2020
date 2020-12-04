#include <iostream>
#include <vector>

using namespace std;

int part1()
{
	vector<int> numbers;

	while (!cin.eof())
	{
		int number;
		cin >> number;

		for (auto const& previous_number : numbers)
		{
			if (previous_number + number == 2020)
			{
				cout << previous_number * number;
				return 0;
			}
		}

		numbers.push_back(number);
	}

	return -1;
}

int part2()
{
	vector<int> numbers;

	while (!cin.eof())
	{
		int number;
		cin >> number;

		for (int i = 0; i < numbers.size(); i++)
		{
			for (int j = 0; j < numbers.size(); j++)
			{
				if (i == j)
					continue;

				int previous_number = numbers.at(i);
				int previous_number_2 = numbers.at(j);
				if (number + previous_number + previous_number_2 == 2020)
				{
					cout << number * previous_number * previous_number_2;
					return 0;
				}
			}
		}

		numbers.push_back(number);
	}

	return -1;
}

int main()
{
	//return part1();
	return part2();
}