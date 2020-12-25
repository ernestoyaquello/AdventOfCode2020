#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <chrono>

struct layout_type
{
    std::vector<layout_type*>* inner_vector = NULL;
    std::vector<char>* last_vector = NULL;
};

int part1();
int part2();

int execute(int dimensions, int iterations);
layout_type* read_initial_layout(int dimensions);
std::vector<std::vector<int>> calculate_adyacent_directions(int dimensions, std::vector<int>* current_direction);
layout_type* calculate_next_layout(layout_type* old_layout, const std::vector<std::vector<int>>* adyacent_directions);
layout_type* get_next_layout_empty(layout_type* old_layout);
std::vector<std::vector<int>> calculate_layout_indices(layout_type* layout, std::vector<int>* current_index_sequence);
unsigned int count_active_cubes(layout_type* layout);
void free_memory(layout_type* layout);