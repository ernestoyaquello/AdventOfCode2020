#include "day8.h"

int main()
{
	vector<instruction> instructions = read_instructions();
	//int result = part1(instructions);
	int result = part2(instructions);
	cout << result;

	return 0;
}

vector<instruction> read_instructions()
{
	vector<instruction> instructions;

	string command, value;
	while (cin >> command && cin >> value)
	{
		instruction instruction;
		instruction.type = command.at(0);
		instruction.value = stoi(value);
		instructions.push_back(instruction);
	}

	return instructions;
}

int part1(vector<instruction> instructions)
{
	int accumulator = 0;
	execute(instructions, &accumulator);
	return accumulator;
}

int part2(vector<instruction> instructions)
{
	for (int i = 0; i < instructions.size(); i++)
	{
		instruction* fixable_instruction = &instructions[i];
		if (fixable_instruction->type != nop && fixable_instruction->type != jmp)
			continue;

		fixable_instruction->type = fixable_instruction->type == jmp ? nop : jmp;
		for (int j = 0; j < instructions.size(); j++)
			(&instructions[j])->visited = false;

		int accumulator = 0;
		if (execute(instructions, &accumulator))
			return accumulator;

		fixable_instruction->type = fixable_instruction->type == jmp ? nop : jmp;
	}

	return 0;
}

bool execute(vector<instruction> instructions, int* accumulator)
{
	for (int i = 0; i < instructions.size(); i++)
	{
		instruction* instruction = &instructions[i];

		if (instruction->visited)
			return false;

		switch (instruction->type)
		{
		case nop:
			break;
		case acc:
			*accumulator += instruction->value;
			break;
		case jmp:
			i += instruction->value - 1;
			break;
		}

		instruction->visited = true;
	}

	return true;
}