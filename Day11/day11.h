#include <iostream>
#include <vector>
#include <string>

using namespace std;

int part1();
int part2();

vector<string> read_layout();
int count_occupied_seats_when_movement_stops(vector<string> layout, int tolerance = 4, bool look_further = false);
vector<string> calculate_next_layout(vector<string>* layout_ptr, int tolerance, bool look_further);
int count_occupied_adjacent(vector<string>* layout_ptr, int i, int j, bool look_further);
bool is_visible_seat_occupied(vector<string>* layout_ptr, int i, int j, int i_dir, int j_dir, bool look_further);
bool are_layouts_equal(vector<string>* layout_ptr, vector<string>* other_layout_ptr);