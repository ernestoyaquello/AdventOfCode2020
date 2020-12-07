#include <iostream>
#include <vector>

using namespace std;

struct bag_type
{
	int number = 0;
	string color;
	vector<bag_type>* contains;
};

void part1();
void part2();
vector<bag_type> read_bags();
bag_type read_bag_type(bool is_first);
void complete_bag(vector<bag_type> bags, bag_type* bag_to_complete);
bool can_carry_bag(bag_type bag, string bag_color);
int number_of_bags_within(bag_type bag);