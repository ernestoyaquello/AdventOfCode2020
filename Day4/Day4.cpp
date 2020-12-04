#include <iostream>
#include <string>

using namespace std;

int main()
{
	string required_fields[] = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
	int required_fields_size = sizeof(required_fields) / sizeof(required_fields[0]);
	string _;
	char* field = new char[4];
	field[3] = '\0';
	int valid_total = 0;

	while (!cin.eof())
	{
		int required_found = 0;
		while (cin.peek() != '\n' && !cin.eof())
		{
			cin.read(field, 3);

			// Ignore the value of the field and the space/new line that exists after it
			cin >> _;
			if (cin.peek() == ' ' || cin.peek() == '\n') cin.get();

			bool is_required_field = find(begin(required_fields), end(required_fields), field) != end(required_fields);
			required_found += is_required_field ? 1 : 0;
			if (required_found == required_fields_size)
			{
				// All the required fields have been found for this passport, so we ignore the rest of it
				while (cin.peek() != '\n' && !cin.eof())
				{
					cin >> _;
					if (cin.peek() == ' ' || cin.peek() == '\n') cin.get();
				}

				valid_total++;
				break;
			}
		}

		while (cin.peek() == '\n') cin.get();
	}

	cout << valid_total;

	delete[] field;

	return 0;
}