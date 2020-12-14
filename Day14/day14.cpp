#include "day14.h"

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

unsigned long long part1()
{
	const auto memory = read_memory(false);
	unsigned long long total = 0;
	for (auto memory_value : memory) total += memory_value.second;

	return total;
}

unsigned long long part2()
{
	const auto memory = read_memory(true);
	unsigned long long total = 0;
	for (auto memory_value : memory) total += memory_value.second;

	return total;
}

std::map<unsigned long long, unsigned long long> read_memory(bool use_address_decoder)
{
	std::map<unsigned long long, unsigned long long> memory;
	unsigned long long or = 0, and = 0b111111111111111111111111111111111111;

	char _[6];
	std::string mask;
	char command;
	std::cin.get();
	while (!std::cin.eof() && (command = std::cin.get()))
	{
		if (command == 'a') // Mask
		{
			std::cin.read(_, 5);
			std::cin >> mask;
			or = 0;
			and = 0b111111111111111111111111111111111111;

			for (std::size_t i = 0; i < mask.size(); i++)
			{
				const char mask_char = mask[i];
				if (mask_char != 'X')
				{
					unsigned short bit;
					std::stringstream mask_helper;
					mask_helper << mask_char;
					mask_helper >> bit;

					if (bit == 1)
						or += std::pow(2, mask.size() - i - 1);
					else
						and -= std::pow(2, mask.size() - i - 1);
				}
			}
		}
		else if (command == 'e') // Memory access
		{
			unsigned long long address, value;
			std::cin.read(_, 2);
			std::cin >> address;
			std::cin.read(_, 4);
			std::cin >> value;

			if (!use_address_decoder)
			{
				value |= or;
				value &= and;

				std::map<unsigned long long, unsigned long long>::iterator it;
				if ((it = memory.find(address)) == memory.end())
					memory.insert(std::make_pair(address, value));
				else
					it->second = value;
			}
			else
			{
				std::vector<unsigned long long> addresses = get_decoded_addresses(address, mask, 0);
				for (const auto decoded_address : addresses)
				{
					std::map<unsigned long long, unsigned long long>::iterator it;
					if ((it = memory.find(decoded_address)) == memory.end())
						memory.insert(std::make_pair(decoded_address, value));
					else
						it->second = value;
				}
			}
		}

		while (std::cin.peek() == '\n' || std::cin.peek() == 'm')
			std::cin.get();
	}

	return memory;
}

std::vector<unsigned long long> get_decoded_addresses(unsigned long long address, std::string mask, std::size_t index)
{
	std::vector<unsigned long long> result;

	if (index == mask.size())
	{
		unsigned long long or = 0, and = 0b111111111111111111111111111111111111;
		for (std::size_t i = 0; i < mask.size(); i++)
		{
			if (mask[i] != '.' && mask[i] != '_')
			{
				unsigned short bit;
				std::stringstream mask_helper;
				mask_helper << mask[i];
				mask_helper >> bit;
				or += bit == 1 ? std::pow(2, mask.size() - i - 1) : 0;
			}
			else if (mask[i] == '.') // Mandatory 0
			{
				and -= std::pow(2, mask.size() - i - 1);
			}
			else if (mask[i] == '_') // Mandatory 1
			{
				or += std::pow(2, mask.size() - i - 1);
			}
		}
		result.push_back(address & and| or);
	}
	else if (mask[index] == 'X')
	{
		auto mask1 = mask;
		auto mask2 = mask;
		mask1[index] = '.'; // Mandatory 0
		mask2[index] = '_'; // Mandatory 1
		auto mask1_addresses = get_decoded_addresses(address, mask1, index + 1);
		auto mask2_addresses = get_decoded_addresses(address, mask2, index + 1);
		for (const auto address_to_add : mask1_addresses)
			result.push_back(address_to_add);
		for (const auto address_to_add : mask2_addresses)
			result.push_back(address_to_add);
	}
	else
	{
		return get_decoded_addresses(address, mask, index + 1);
	}

	return result;
}