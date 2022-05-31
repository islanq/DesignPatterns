#include <iostream>
#include <vector>
using namespace std;

class Number
{
public:
	void Double(int& value) { value *= 2; }
};

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute(int&) = 0;
};

class SimpleCommand : public Command
{
	typedef void (Number::*Action)(int&);
	Number* receiver;
	Action action;
public:
	SimpleCommand(Number* rec, Action act)
		: receiver{ rec }
		, action{ act } {}


	virtual void Execute(int& num) override { (receiver ->* action)(num); }
};

class MacroCommand : public Command
{
	vector<Command *> list;
public:
	void Add(Command* cmd) { list.push_back(cmd); }

	virtual void Execute(int& num) override
	{
		for (auto i = 0; i < list.size(); i++)
			list[i]->Execute(num);
	}
};

int main()
{
	Number object;
	Command* commands[3];
	commands[0] = &SimpleCommand(&object, &Number::Double);

	MacroCommand two;
	two.Add(commands[0]);
	two.Add(commands[0]);
	commands[1] = &two;

	MacroCommand four;
	four.Add(&two);
	four.Add(&two);
	commands[2] = &four;

	int num, index;
	while (true) {
		cout << "Enter number selection (0=2x 1=4x 2=16x): ";
		cin >> num >> index;
		if (num == 0000)
			break;
		commands[index]->Execute(num);
		cout << "   " << num << '\n';

	}

	return EXIT_SUCCESS;
}
