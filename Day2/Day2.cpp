#include <iostream>

using namespace std;

int part1()
{
	int validTotal = 0;

	while (!cin.eof())
	{
		int min;
		int max;
		char character;
		string password;
		char _;
		cin >> min >> _ >> max >> character >> _ >> password;

		int occurrences = 0;
		for (int i = 0; i < password.size(); i++)
		{
			char password_char = password.at(i);
			occurrences += character == password_char ? 1 : 0;
		}

		if (occurrences >= min && occurrences <= max)
			validTotal++;
	}

	cout << validTotal;

	return 0;
}

int part2()
{
	int validTotal = 0;

	while (!cin.eof())
	{
		int first_index;
		int second_index;
		char character;
		string password;
		char _;
		cin >> first_index >> _ >> second_index >> character >> _ >> password;

		int is_at_first = first_index <= password.size() && password.at(first_index - 1) == character ? 1 : 0;
		int is_at_second = second_index <= password.size() && password.at(second_index - 1) == character ? 1 : 0;

		if (is_at_first + is_at_second == 1)
			validTotal++;
	}

	cout << validTotal;

	return 0;
}

int main()
{
	//return part1();
	return part2();
}