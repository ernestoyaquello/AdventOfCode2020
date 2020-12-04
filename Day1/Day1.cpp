#include <iostream>
#include <list>

using namespace std;

int main()
{
	list<int> numbers;

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