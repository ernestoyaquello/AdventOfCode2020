#include "day15.h"

int main()
{
	const auto start_time = std::chrono::steady_clock::now();

	//const auto number = part1();
	const auto number = part2();
	std::cout << "Result: " << number << std::endl;

	const auto end_time = std::chrono::steady_clock::now();
	const std::chrono::duration<double> elapsed_seconds = end_time - start_time;
	std::cout << "Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;

	return 0;
}

int part1()
{
	return read_numbers_until_iteration(2020);
}

int part2()
{
	return read_numbers_until_iteration(30000000);
}

int read_numbers_until_iteration(std::size_t last_iteration)
{
	std::map<int, std::vector<std::size_t>> numbers_with_index;
	std::map<int, std::vector<std::size_t>>::iterator numbers_map_iterator;
	std::size_t iteration = 0;
	int number = 0;
	while (iteration < last_iteration)
	{
		if (!std::cin.eof())
			std::cin >> number;
		else
			number = ((numbers_map_iterator = numbers_with_index.find(number)) != numbers_with_index.end() && numbers_map_iterator->second.size() > 1)
			? numbers_map_iterator->second[numbers_map_iterator->second.size() - 1] - numbers_map_iterator->second[numbers_map_iterator->second.size() - 2]
			: 0;

		if ((numbers_map_iterator = numbers_with_index.find(number)) == numbers_with_index.end())
			numbers_with_index.insert(std::make_pair(number, std::vector<std::size_t> { iteration }));
		else
			numbers_map_iterator->second.push_back(iteration);

		while (!std::cin.eof() && !std::isdigit(std::cin.peek())) std::cin.get();
		iteration++;
	}

	return number;
}