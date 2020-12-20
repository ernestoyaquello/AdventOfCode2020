#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <chrono>

struct rule_type
{
	int number = -1;
	std::vector<int>* left = NULL;
	std::vector<int>* right = NULL;
	char character = '\0';
	std::set<std::string>* combinations = NULL;
};

unsigned long long part1();
unsigned long long part2();
std::unordered_map<int, rule_type*> read_rules();
std::vector<std::string> read_messages();
std::set<std::string>* get_text_rules(std::unordered_map<int, rule_type*>* rules, rule_type* rule, std::vector<std::string>* messages);
std::set<std::string>* get_combinations(std::vector<std::set<std::string>*>* texts_to_combine, std::vector<std::string>* messages);