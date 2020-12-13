#include "day13.h"

int main()
{
	auto start_time = std::chrono::steady_clock::now();

	//auto result = part1();
	auto result = part2();
	std::cout << "Result: " << result << std::endl;

	auto end_time = std::chrono::steady_clock::now();
	const std::chrono::duration<double> elapsed_seconds = end_time - start_time;
	std::cout << "Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;

	return 0;
}

int part1()
{
	int min_time;
	std::cin >> min_time;
	auto times = read_times(min_time);
	auto min = times[0];
	for (std::size_t i = 1; i < times.size(); i++)
		min = times[i].second < min.second ? times[i] : min;

	auto waiting_time = min.second - min_time;
	return waiting_time * min.first;
}

unsigned long long part2()
{
	// To avoid unnecessary calculations, we assume the minimum time will be 100000000000000 because it says so in the puzzle
	const unsigned long long min = 100000000000000L;

	auto bus_ids_with_offset = read_times_with_offset();
	unsigned long long jump_size = bus_ids_with_offset[0].first;
	unsigned long long position = (min / jump_size) * jump_size;
	for (std::size_t i = 1; i < bus_ids_with_offset.size(); i++)
	{
		const unsigned long long local_jump_size = bus_ids_with_offset[i].first;
		const unsigned long long local_offset = bus_ids_with_offset[i].second;
		while (((position + local_offset) % local_jump_size) != 0)
			position += jump_size;

		jump_size = local_jump_size * jump_size;
	}

	return position;
}

std::vector<std::pair<unsigned short, unsigned int>> read_times(int min_time)
{
	std::vector<std::pair<unsigned short, unsigned int>> times;
	for (auto bus_id = 0; !std::cin.eof() && std::cin >> bus_id; )
	{
		auto time = (min_time / bus_id) * bus_id;
		time = time < min_time ? (time + bus_id) : time;
		times.push_back(std::pair<unsigned short, unsigned int>(bus_id, time));

		while (std::cin.peek() == ',' || std::cin.peek() == 'x' || std::cin.peek() == '\n')
			std::cin.get();
	}

	return times;
}

std::vector<std::pair<unsigned short, unsigned short>> read_times_with_offset()
{
	// Ignore first number
	int ignored;
	std::cin >> ignored;
	std::cin.get();

	// Read times
	std::vector<std::pair<unsigned short, unsigned short>> bus_ids_with_offset;
	for (unsigned long long bus_id = 0, offset = 0; !std::cin.eof() && std::cin >> bus_id; offset++)
	{
		bus_ids_with_offset.push_back(std::pair<unsigned short, unsigned short>(bus_id, offset));
		while (std::cin.peek() == ',' || std::cin.peek() == 'x' || std::cin.peek() == '\n')
		{
			if (std::cin.peek() == 'x') offset++;
			std::cin.get();
		}
	}

	return bus_ids_with_offset;
}