#include <iostream>
#include <vector>

using namespace std;

int main()
{
	// Read data
	vector<vector<char>> matrix;
	while (true)
	{
		vector<char> row;
		char character;
		while ((character = fgetc(stdin)) != '\n' && character != EOF)
			row.push_back(character);

		if (row.size() > 0)
			matrix.push_back(row);

		if (character == EOF) break;
	}

	// Count number of trees
	const int matrix_width = matrix.at(0).size();
	int pos_x = 0;
	int pos_y = 0;
	int numberOfTrees = 0;

	while (pos_y < matrix.size())
	{
		char character = matrix.at(pos_y).at(pos_x);
		numberOfTrees += character == '#' ? 1 : 0;

		pos_x = (pos_x + 3) % matrix_width;
		pos_y += 1;
	}

	cout << numberOfTrees;

	return 0;
}