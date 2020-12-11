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
	while (!are_layouts_equal(&layout, &(next_layout = calculate_next_layout(&layout, tolerance, look_further))))
		layout = next_layout;

	int total_occupied = 0;
	for (int i = 0; i < layout.size(); i++)
		for (int j = 0; j < layout[i].size(); j++)
			if (layout[i][j] == '#') total_occupied++;

	return total_occupied;
}

vector<string> calculate_next_layout(vector<string>* layout_ptr, int tolerance, bool look_further)
{
	vector<string> next_layout;
	for (int i = 0; i < layout_ptr->size(); i++)
	{
		string next_row = (*layout_ptr)[i];
		for (int j = 0; j < (*layout_ptr)[i].size(); j++)
		{
			char character = (*layout_ptr)[i][j];
			if (character != '.')
			{
				int occupied_adjacent = count_occupied_adjacent(layout_ptr, i, j, look_further);
				if (character == 'L' && occupied_adjacent == 0) character = '#'; // Empty seat with no adjacent occupied seats becomes occupied
				if (character == '#' && occupied_adjacent >= tolerance) character = 'L'; // Occupied seat with <tolerance> or more adjacent occupied seats becomes empty
				next_row[j] = character;
			}
		}
		next_layout.push_back(next_row);
	}

	return next_layout;
}

int count_occupied_adjacent(vector<string>* layout_ptr, int i, int j, bool look_further)
{
	return (is_visible_seat_occupied(layout_ptr, i, j, -1, -1, look_further) ? 1 : 0) +
		(is_visible_seat_occupied(layout_ptr, i, j, -1, 0, look_further) ? 1 : 0) +
		(is_visible_seat_occupied(layout_ptr, i, j, -1, +1, look_further) ? 1 : 0) +
		(is_visible_seat_occupied(layout_ptr, i, j, 0, -1, look_further) ? 1 : 0) +
		(is_visible_seat_occupied(layout_ptr, i, j, 0, +1, look_further) ? 1 : 0) +
		(is_visible_seat_occupied(layout_ptr, i, j, +1, -1, look_further) ? 1 : 0) +
		(is_visible_seat_occupied(layout_ptr, i, j, +1, 0, look_further) ? 1 : 0) +
		(is_visible_seat_occupied(layout_ptr, i, j, +1, +1, look_further) ? 1 : 0);
}

bool is_visible_seat_occupied(vector<string>* layout_ptr, int i, int j, int i_dir, int j_dir, bool look_further)
{
	int limit_i = i_dir > 0 ? layout_ptr->size() : -1;
	int limit_j = j_dir > 0 ? (*layout_ptr)[0].size() : -1;
	for (int next_i = i + i_dir, next_j = j + j_dir; next_i != limit_i && next_j != limit_j; next_i += i_dir, next_j += j_dir)
	{
		if ((*layout_ptr)[next_i][next_j] == '.')
		{
			if (!look_further) return false;
		}
		else return (*layout_ptr)[next_i][next_j] == '#';
	}

	return false;
}

bool are_layouts_equal(vector<string>* layout_ptr, vector<string>* other_layout_ptr)
{
	for (int i = 0; i < layout_ptr->size(); i++)
		for (int j = 0; j < (*layout_ptr)[i].size(); j++)
			if ((*layout_ptr)[i][j] != (*other_layout_ptr)[i][j])
				return false;

	return true;
}