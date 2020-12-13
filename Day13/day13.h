#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#include <chrono>

int part1();
unsigned long long part2();
std::vector<std::pair<unsigned short, unsigned int>> read_times(int min_time);
std::vector<std::pair<unsigned short, unsigned short>> read_times_with_offset();
bool compare_bus_ids(const std::pair<unsigned short, unsigned short> first, const std::pair<unsigned short, unsigned short> second);