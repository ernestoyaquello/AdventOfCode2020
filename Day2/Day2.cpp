#include <iostream>

using namespace std;

int main()
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