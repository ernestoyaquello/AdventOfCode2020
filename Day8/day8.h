#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct instruction
{
	char type = -1;
	short value = 0;
	bool visited = false;
};

const char nop = 'n';
const char acc = 'a';
const char jmp = 'j';

vector<instruction> read_instructions();
int part1(vector<instruction> instructions);
int part2(vector<instruction> instructions);
bool execute(vector<instruction> instructions, int* accumulator);