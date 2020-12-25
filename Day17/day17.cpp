#include "day17.h"

int main()
{
	const auto start_time = std::chrono::steady_clock::now();

	//std::cout << "Part 1: " << part1() << std::endl;
	std::cout << "Part 2: " << part2() << std::endl;

	const auto end_time = std::chrono::steady_clock::now();
	const std::chrono::duration<double> elapsed_seconds = end_time - start_time;
	std::cout << "Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;

	return 0;
}

int part1()
{
	return execute(3, 6);
}

int part2()
{
	return execute(4, 6);
}

int execute(int dimensions, int iterations)
{
	auto layout = read_initial_layout(dimensions);
	auto neightbour_directions = calculate_adyacent_directions(dimensions, &std::vector<int>());
	while (--iterations >= 0)
	{
		auto old_layout = layout;
		layout = calculate_next_layout(layout, &neightbour_directions);
		free_memory(old_layout);
	}

	auto result = count_active_cubes(layout);
	free_memory(layout);

	return result;
}

layout_type* read_initial_layout(int dimensions)
{
	auto layout = new layout_type();

	layout->inner_vector = new std::vector<layout_type*>();
	for (std::string line; std::getline(std::cin, line) && line.compare("") != 0;)
	{
		auto sublayout = new layout_type();
		sublayout->inner_vector = new std::vector<layout_type*>();
		for (const auto line_char : line)
		{
			auto subsublayout = new layout_type();
			auto subsublayout_backup = subsublayout;
			for (std::size_t i = 3; i < dimensions; i++)
			{
				auto new_subsublayout = new layout_type();
				subsublayout->inner_vector = new std::vector<layout_type*>();
				subsublayout->inner_vector->push_back(new_subsublayout);
				subsublayout = new_subsublayout;
			}
			subsublayout->last_vector = new std::vector<char>();
			subsublayout->last_vector->push_back(line_char);
			sublayout->inner_vector->push_back(subsublayout_backup);
		}
		layout->inner_vector->push_back(sublayout);
	}

	return layout;
}

std::vector<std::vector<int>> calculate_adyacent_directions(int dimensions, std::vector<int>* current_direction)
{
	std::vector<std::vector<int>> permutations;

	for (auto dir = -1; dir <= 1; dir++)
	{
		current_direction->push_back(dir);
		if (current_direction->size() == dimensions)
		{
			auto is_all_zeroes = true;
			for (std::size_t j = 0; is_all_zeroes && j < current_direction->size(); j++)
				is_all_zeroes = (*current_direction)[j] == 0;

			if (!is_all_zeroes)
				permutations.push_back(*current_direction);
		}
		else
		{
			for (const auto& permutation : calculate_adyacent_directions(dimensions, current_direction))
				permutations.push_back(permutation);
		}
		current_direction->erase(current_direction->end() - 1);
	}

	return permutations;
}

layout_type* calculate_next_layout(layout_type* old_layout, const std::vector<std::vector<int>>* adyacent_directions)
{
	auto new_layout = get_next_layout_empty(old_layout);
	auto new_indices = calculate_layout_indices(new_layout, &std::vector<int>());
	
	for (const auto &indices : new_indices) // Iterate over each position
	{
		char old_cube_value = '.';
		auto old_inner = old_layout;
		auto new_inner = new_layout;
		for (int i = 0; i < indices.size(); i++)
		{
			const auto new_inner_index = indices[i];
			const auto old_inner_index = new_inner_index - 1;

			new_inner = new_inner->inner_vector != NULL ? (*new_inner->inner_vector)[new_inner_index] : new_inner;

			if (old_inner == NULL)
				old_inner = NULL;
			else if (old_inner->last_vector != NULL)
				old_cube_value = old_inner_index >= 0 && old_inner_index < old_inner->last_vector->size() ? (*old_inner->last_vector)[old_inner_index] : '.';
			else
				old_inner = old_inner_index >= 0 && old_inner_index < old_inner->inner_vector->size() ? (*old_inner->inner_vector)[old_inner_index] : NULL;
		}

		unsigned int total_active_adyacents = 0;
		for (const auto &adyacents : *adyacent_directions) // Iterate over neightbour direction
		{
			char value = '.';
			auto old_inner = old_layout;
			for (int i = 0; old_inner != NULL && i < indices.size(); i++)
			{
				auto old_inner_index = indices[i] - 1 + adyacents[i];
				if (old_inner == NULL)
					old_inner = NULL;
				else if (old_inner->last_vector != NULL)
					value = old_inner_index >= 0 && old_inner_index < old_inner->last_vector->size() ? (*old_inner->last_vector)[old_inner_index] : '.';
				else
					old_inner = old_inner_index >= 0 && old_inner_index < old_inner->inner_vector->size() ? (*old_inner->inner_vector)[old_inner_index] : NULL;
			}
			total_active_adyacents += value == '#' ? 1 : 0;
			if (total_active_adyacents > 3)
				break;
		}

		if (old_cube_value == '#')
			(*new_inner->last_vector)[indices[indices.size() - 1]] = (total_active_adyacents == 2 || total_active_adyacents == 3) ? '#' : '.';
		else
			(*new_inner->last_vector)[indices[indices.size() - 1]] = total_active_adyacents == 3 ? '#' : '.';
	}

	return new_layout;
}

layout_type* get_next_layout_empty(layout_type* old_layout)
{
	const auto new_layout = new layout_type();

	if (old_layout->inner_vector != NULL)
	{
		new_layout->inner_vector = new std::vector<layout_type*>();
		new_layout->inner_vector->push_back(get_next_layout_empty((*old_layout->inner_vector)[0]));
		new_layout->inner_vector->push_back(get_next_layout_empty((*old_layout->inner_vector)[0]));
		for (const auto& inner_old : *old_layout->inner_vector)
			new_layout->inner_vector->push_back(get_next_layout_empty(inner_old));
	}
	else
	{
		new_layout->last_vector = new std::vector<char>(old_layout->last_vector->size() + 2);
	}

	return new_layout;
}

std::vector<std::vector<int>> calculate_layout_indices(layout_type* layout, std::vector<int>* current_index_sequence)
{
	std::vector<std::vector<int>> indices;

	if (layout->last_vector != NULL)
	{
		for (int i = 0; i < layout->last_vector->size(); i++)
		{
			current_index_sequence->push_back(i);
			indices.push_back(*current_index_sequence);
			current_index_sequence->erase(current_index_sequence->end() - 1);
		}
	}
	else
	{
		for (int i = 0; i < layout->inner_vector->size(); i++)
		{
			current_index_sequence->push_back(i);
			for (auto &inner_index : calculate_layout_indices((*layout->inner_vector)[i], current_index_sequence))
				indices.push_back(inner_index);
			current_index_sequence->erase(current_index_sequence->end() - 1);
		}
	}

	return indices;
}

unsigned int count_active_cubes(layout_type* layout)
{
	unsigned int total = 0;

	if (layout->last_vector != NULL)
		for (int i = 0; i < layout->last_vector->size(); i++)
			total += (*layout->last_vector)[i] == '#' ? 1 : 0;
	else
		for (int i = 0; i < layout->inner_vector->size(); i++)
			total += count_active_cubes((*layout->inner_vector)[i]);

	return total;
}

void free_memory(layout_type* layout)
{
	if (layout->last_vector != NULL)
	{
		delete layout->last_vector;
	}
	else
	{
		for (int i = 0; i < layout->inner_vector->size(); i++)
			free_memory((*layout->inner_vector)[i]);
		
		delete layout->inner_vector;
	}

	delete layout;
}