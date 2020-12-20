#include "day19.h"

int main()
{
	const auto start_time = std::chrono::steady_clock::now();

	std::cout << "Part 1: " << part1() << std::endl;
	//std::cout << "Part 2: " << part2() << std::endl;

	const auto end_time = std::chrono::steady_clock::now();
	const std::chrono::duration<double> elapsed_seconds = end_time - start_time;
	std::cout << "Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;

	return 0;
}

unsigned long long part1()
{
	unsigned long long total = 0;
	auto rules = read_rules();
	auto messages = read_messages();
	auto text_rules = get_text_rules(&rules, rules[0], &messages);
	for (const auto& message : messages)
	{
		bool is_valid_message = false;
		for (auto it = text_rules->begin(); !is_valid_message && it != text_rules->end(); ++it)
			is_valid_message = message.compare(*it) == 0;
		total += is_valid_message ? 1 : 0;
	}
	
	for (const auto& rule : rules)
	{
		if (rule.second->left != NULL)
			delete rule.second->left;
		if (rule.second->right != NULL)
			delete rule.second->right;
		delete rule.second->combinations;
		delete rule.second;
	}

	return total;
}

unsigned long long part2()
{
	return 0;
}

std::unordered_map<int, rule_type*> read_rules()
{
	std::unordered_map<int, rule_type*> rules;

	int loop_rule = 1000;
	while (std::cin.peek() != '\n')
	{
		auto rule = new rule_type();
		std::cin >> rule->number;
		std::cin.get();
		bool left = true;
		while (std::cin.peek() == ' ')
		{
			std::cin.get();
			if (isdigit(std::cin.peek()))
			{
				int number;
				std::cin >> number;
				rule->left = rule->left == NULL ? new std::vector<int>() : rule->left;
				if (left) rule->left->push_back(number);
				else rule->right->push_back(number);
			}
			else if (std::cin.peek() == '|')
			{
				std::cin.get();
				left = false;
				rule->right = new std::vector<int>();
			}
			else if (std::cin.peek() == '"')
			{
				std::cin.get();
				rule->character = std::cin.get();
				std::cin.get();
			}
		}
		std::cin.ignore();
		rules.insert(std::make_pair(rule->number, rule));

		for (std::size_t i = 0; rule->right != NULL && i < rule->right->size(); i++)
		{
			if ((*rule->right)[i] == rule->number)
			{
				// Remove loops by unrolling them into new rules that only go a few levels deep
				int count = 4;
				while (--count >= 0)
				{
					auto additional_rule = new rule_type();
					additional_rule->number = loop_rule++;
					additional_rule->left = new std::vector<int>();
					additional_rule->right = new std::vector<int>();
					for (const auto& left_val : *rule->left)
						additional_rule->left->push_back(left_val);
					for (std::size_t j = 0; j < rule->right->size(); j++)
					{
						const auto right_val = (*rule->right)[j];
						if (right_val == rule->number)
						{
							additional_rule->right->push_back(additional_rule->number);
							(*rule->right)[j] = additional_rule->number;
						}
						else
						{
							additional_rule->right->push_back(right_val);
						}
					}

					rules.insert(std::make_pair(additional_rule->number, additional_rule));
					rule = additional_rule;
				}

				delete rule->right;
				rule->right = NULL;

				break;
			}
		}		
	}
	std::cin.get();

	return rules;
}

std::vector<std::string> read_messages()
{
	std::vector<std::string> lines;
	for (std::string line; !std::cin.eof() && std::getline(std::cin, line) && line.compare("") != 0; lines.push_back(line));
	return lines;
}

std::set<std::string>* get_text_rules(std::unordered_map<int, rule_type*>* rules, rule_type* rule, std::vector<std::string>* messages)
{
	if (rule->combinations != NULL)
		return rule->combinations;

	rule->combinations = new std::set<std::string>();
	if (rule->character != '\0')
	{
		std::string character_as_string(1, rule->character);
		rule->combinations->insert(character_as_string);
	}
	else
	{
		if (rule->left != NULL)
		{
			std::vector<std::set<std::string>*> left_text_rules(rule->left != NULL ? rule->left->size() : 0);
			for (std::size_t i = 0; i < rule->left->size(); i++)
				left_text_rules[i] = get_text_rules(rules, (*rules)[(*rule->left)[i]], messages);

			auto left_combinations = get_combinations(&left_text_rules, messages);
			for (const auto& left_combination : *left_combinations)
				rule->combinations->insert(left_combination);
			delete left_combinations;
		}

		if (rule->right != NULL)
		{
			std::vector<std::set<std::string>*> right_text_rules(rule->right != NULL ? rule->right->size() : 0);
			for (std::size_t i = 0; i < rule->right->size(); i++)
				right_text_rules[i] = get_text_rules(rules, (*rules)[(*rule->right)[i]], messages);

			auto right_combinations = get_combinations(&right_text_rules, messages);
			for (const auto& right_combination : *right_combinations)
				rule->combinations->insert(right_combination);
			delete right_combinations;
		}
	}

	return rule->combinations;
}

std::set<std::string>* get_combinations(std::vector<std::set<std::string>*>* texts_to_combine, std::vector<std::string>* messages)
{
	auto combinations = new std::set<std::string>();

	if (texts_to_combine->size() > 0)
	{
		const auto& inner_combinations = (*texts_to_combine)[0];
		std::set<std::string>* inner_inner_combinations = NULL;
		for (const auto& text : *inner_combinations)
		{
			// TODO Improve this check even further to discard more branches?
			bool combination_is_valid = false;
			for (std::size_t i = 0; !combination_is_valid && i < messages->size(); i++)
			{
				const auto& message = (*messages)[i];
				combination_is_valid = message.size() >= text.size() && (message.find(text) != std::string::npos || message.compare(text) == 0);
			}
			if (!combination_is_valid)
				continue;

			if (inner_inner_combinations == NULL && texts_to_combine->size() > 1)
			{
				std::vector<std::set<std::string>*> subarray(texts_to_combine->begin() + 1, texts_to_combine->end());
				inner_inner_combinations = get_combinations(&subarray, messages);
			}
			if (inner_inner_combinations == NULL || inner_inner_combinations->size() == 0)
				combinations->insert(text);
			else
				for (const auto& subtext : *inner_inner_combinations)
					combinations->insert(text + subtext);
		}

		if (inner_inner_combinations != NULL)
			delete inner_inner_combinations;
	}

	return combinations;
}