#include "day11.h"

int main()
{
	//int result = part1();
	int result = part2();
	cout << result;

	return 0;
}

int part1()
{
	vector<string> layout = read_layout();
	return count_occupied_seats_when_movement_stops(layout, 4, false);
}

int part2()
{
	vector<string> layout = read_layout();
	return count_occupied_seats_when_movement_stops(layout, 5, true);
}

vector<string> read_layout()
{
	vector<string> layout;
	for (string line; getline(cin, line); layout.push_back(line));
	return layout;
}

int count_occupied_seats_when_movement_stops(vector<string> layout, int tolerance, bool look_further)
{
	vector<string> next_layout;
	while (!are_layouts_equal(layout, next_layout = calculate_next_layout(layout, tolerance, look_further)))
		layout = next_layout;

	int total_occupied = 0;
	for (int i = 0; i < layout.size(); i++)
		for (int j = 0; j < layout[i].size(); j++)
			if (layout[i][j] == '#') total_occupied++;

	return total_occupied;
}

vector<string> calculate_next_layout(vector<string> layout, int tolerance, bool look_further)
{
	vector<string> next_layout;
	for (int i = 0; i < layout.size(); i++)
	{
		string next_row = layout[i];
		for (int j = 0; j < layout[i].size(); j++)
		{
			char character = layout[i][j];
			if (character != '.')
			{
				int occupied_adjacent = count_occupied_adjacent(layout, i, j, look_further);
				if (character == 'L' && occupied_adjacent == 0) character = '#'; // Empty seat with no adjacent occupied seats becomes occupied
				if (character == '#' && occupied_adjacent >= tolerance) character = 'L'; // Occupied seat with <tolerance> or more adjacent occupied seats becomes empty
			}
			next_row[j] = character;
		}
		next_layout.push_back(next_row);
	}

	return next_layout;
}

int count_occupied_adjacent(vector<string> layout, int i, int j, bool look_further)
{
	return is_visible_seat_occupied(layout, i, j, -1, -1, look_further) +
		is_visible_seat_occupied(layout, i, j, -1, 0, look_further) +
		is_visible_seat_occupied(layout, i, j, -1, +1, look_further) +
		is_visible_seat_occupied(layout, i, j, 0, -1, look_further) +
		is_visible_seat_occupied(layout, i, j, 0, +1, look_further) +
		is_visible_seat_occupied(layout, i, j, +1, -1, look_further) +
		is_visible_seat_occupied(layout, i, j, +1, 0, look_further) +
		is_visible_seat_occupied(layout, i, j, +1, +1, look_further);
}

bool is_visible_seat_occupied(vector<string> layout, int i, int j, int i_dir, int j_dir, bool look_further)
{
	for (int next_i = i + i_dir, next_j = j + j_dir;
		next_i >= 0 && next_i < layout.size() && next_j >= 0 && next_j < layout[0].size();
		next_i += i_dir, next_j += j_dir)
	{
		if (layout[next_i][next_j] == '.')
		{
			if (!look_further) return false;
		}
		else return layout[next_i][next_j] == '#';
	}

	return false;
}

bool are_layouts_equal(vector<string> layout, vector<string> other_layout)
{
	for (int i = 0; i < layout.size(); i++)
		for (int j = 0; j < layout[i].size(); j++)
			if (layout[i][j] != other_layout[i][j])
				return false;

	return true;
}