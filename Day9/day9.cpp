#include "day9.h"

int main()
{
	//int result = part1();
	int result = part2();
	cout << result;

	return 0;
}

int part1()
{
	vector<int> read_numbers = read_until_invalid_number();
	return read_numbers[read_numbers.size() - 1];
}

int part2()
{
	vector<int> read_numbers = read_until_invalid_number();
	int goal_number = read_numbers[read_numbers.size() - 1];
	for (int i = 0; i < read_numbers.size() - 1; i++)
	{
		int acc = read_numbers[i];
		int i_offset = 1;
		while ((acc += read_numbers[i + i_offset++]) < goal_number);
		if (acc == goal_number)
		{
			int min = INT_MAX, max = INT_MIN;
			for (int j = i; j < (i + i_offset); j++)
			{
				if (read_numbers[j] > max) max = read_numbers[j];
				if (read_numbers[j] < min) min = read_numbers[j];
			}

			return min + max;
		}
	}

	return 0;
}

vector<int> read_until_invalid_number(const int max_numbers)
{
	vector<int> all_numbers;

	int number;
	int* preamble = new int[max_numbers]();
	int preamble_position = 0;
	while (cin >> number)
	{
		all_numbers.push_back(number);

		// If the preamble isn't full yet, the number will be valid automatically; otherwise, we verify it is
		bool is_valid = preamble[preamble_position] == 0;
		for (int i = 0; !is_valid && i <= preamble_position; i++)
		{
			for (int j = 0; !is_valid && j <= preamble_position; j++)
			{
				if (i == j) continue;
				if (preamble[i] + preamble[j] == number)
					is_valid = true;
			}
		}

		// Found the invalid number, we stop reading now
		if (!is_valid) break;

		if ((preamble_position + 1) < max_numbers)
		{
			preamble[preamble_position++] = number;
		}
		else
		{
			// If the preamble is full, we need to shift the previous numbers to make space for the new one
			if (preamble[preamble_position] != 0)
				for (int i = 0; i < preamble_position; i++)
					preamble[i] = preamble[i + 1];
			preamble[preamble_position] = number;
		}
	}

	delete[] preamble;

	return all_numbers;
}