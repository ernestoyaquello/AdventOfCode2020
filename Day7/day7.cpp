#include "day7.h"

int main()
{
	//part1();
	part2();

	return 0;
}

void part1()
{
	vector<bag_type> bags = read_bags();
	int number_of_valid_bags = 0;
	for (bag_type bag : bags)
	{
		bool can_carry = can_carry_bag(bag, "shiny gold");
		if (can_carry) number_of_valid_bags++;
	}

	cout << number_of_valid_bags;

	for (bag_type bag : bags) delete bag.contains;
}

void part2()
{
	vector<bag_type> bags = read_bags();

	bag_type shinny_gold_bag;
	bool found = false;
	for (int i = 0; i < bags.size() && !found; i++)
	{
		bag_type bag = bags[i];
		if (bag.color.compare("shiny gold") == 0)
		{
			shinny_gold_bag = bag;
			found = true;
		}
	}

	int total_bags = number_of_bags_within(shinny_gold_bag);
	cout << total_bags;

	for (bag_type bag : bags) delete bag.contains;
}

vector<bag_type> read_bags()
{
	vector<bag_type> bags;

	while (!cin.eof())
	{
		bag_type bag = read_bag_type(true);
		if (bag.color.compare(" ") != 0)
			bags.push_back(bag);
	}

	for (bag_type bag : bags)
		complete_bag(bags, &bag);

	return bags;
}

// TODO Consider using regex to avoid this messy way of reading the data
bag_type read_bag_type(bool is_first)
{
	bag_type bag;
	bag.contains = new vector<bag_type>();

	string _;
	string first_color_word;
	string second_color_word;

	if (!is_first)
	{
		int last_number = 0;
		while (isdigit(cin.peek()))
		{
			cin >> bag.number;
			bag.number = (last_number * 10) + bag.number;
			last_number = bag.number;
		}
	}

	cin >> first_color_word >> second_color_word >> _;
	bag.color = first_color_word + " " + second_color_word;

	if (is_first)
	{
		cin >> _;
		cin.get();

		if (!isdigit(cin.peek()))
		{
			cin >> _ >> _ >> _;
			cin.get();
		}
		else
		{
			while (isdigit(cin.peek()))
			{
				bag_type inner_bag = read_bag_type(false);
				if (inner_bag.number > 0 && inner_bag.color.compare(" ") != 0)
					bag.contains->push_back(inner_bag);

				cin.get();
			}
		}
	}

	return bag;
}

void complete_bag(vector<bag_type> bags, bag_type* bag_to_complete)
{
	if (bag_to_complete->complete)
		return;

	for (int i = 0; i < bags.size(); i++)
	{
		bag_type bag = bags[i];
		if (bag.color.compare(bag_to_complete->color) == 0)
		{
			if ((*bag_to_complete).contains != bag.contains)
			{
				delete (*bag_to_complete).contains;
				(*bag_to_complete).contains = bag.contains;
				(*bag_to_complete).complete = bag.complete;
			}

			for (int j = 0; !bag_to_complete->complete && j < bag_to_complete->contains->size(); j++)
			{
				bag_type* inner_bag_to_complete = &(*bag_to_complete->contains)[j];
				complete_bag(bags, inner_bag_to_complete);
			}

			(*bag_to_complete).complete = true;

			break;
		}
	}
}

bool can_carry_bag(bag_type bag, string bag_color)
{
	for (bag_type inner_bag : *bag.contains)
	{
		if (inner_bag.color.compare(bag_color) == 0 || can_carry_bag(inner_bag, bag_color))
			return true;
	}

	return false;
}

int number_of_bags_within(bag_type bag)
{
	int total = 0;
	for (bag_type inner_bag : *bag.contains)
	{
		total += inner_bag.number;
		total += inner_bag.number * number_of_bags_within(inner_bag);
	}

	return total;
}