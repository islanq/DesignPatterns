#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>

class Strategy;

class TestBed {
public:

	enum StrategyType
	{
		Dummy,
		Left,
		Right,
		Center
	};
	TestBed() {
		strategy_ = nullptr;
	}

	auto SetStrategy(int type,
									 int width)->void;
	auto DoIt() const->void;

private:

	Strategy *strategy_;
};

class Strategy {
public:

	virtual ~Strategy() = default;
	explicit Strategy(int width)
		: width_(width)
	{}

	auto NeedsJustify(char line[80], char word[30]) const->bool {
		return strlen(line) + strlen(word) + 1 > width_;
	}

	auto Format()->void
	{
		char line[80], word[30];

		std::ifstream inFile("quote.txt", std::ios::in);
		line[0] = '\0';

		inFile >> word;
		strcat_s(line, word);

		while (inFile >> word) {
			if (NeedsJustify(line, word)) Justify(line);
			else strcat_s(line, " ");
			strcat_s(line, word);
		}
		Justify(line);
	}

protected:

	int width_;

private:

	virtual auto Justify(char *line)->void = 0;
};

class LeftStrategy
	: public Strategy {
public:

	explicit LeftStrategy(int width)
		: Strategy(width)
	{}

private:

	virtual auto Justify(char *line)->void override
	{
		std::cout << line << std::endl;
		line[0] = '\0';
	}
};

class RightStrategy
	: public Strategy {
public:

	explicit RightStrategy(int width)
		: Strategy(width)
	{}

private:

	virtual auto Justify(char *line)->void override
	{
		char buf[80];
		auto offset = GetAlignmentOffset(line);

		memset(buf, ' ', 80);
		CopyString(line, buf, offset);
		std::cout << buf << std::endl;
		line[0] = '\0';
	}

	auto GetAlignmentOffset(char *line) const->size_t {
		return width_ - strlen(line);
	}

	static auto CopyString(char *line, char buf[80], size_t offset)->void {
		strcpy(&(buf[offset]), line);
	}
};

class CenterStrategy
	: public Strategy {
public:

	explicit CenterStrategy(int width)
		: Strategy(width)
	{}

private:

	virtual auto Justify(char *line)->void override
	{
		char buf[80];
		auto offset = (width_ - strlen(line)) / 2;

		memset(buf, ' ', 80);
		strcpy(&buf[offset], line);
		std::cout << buf << std::endl;
		line[0] = '\0';
	}
};

auto TestBed::SetStrategy(int type, int width)->void
{
	delete strategy_;

	if (type == Left) strategy_ = new LeftStrategy(width);
	else if (type == Right) strategy_ = new RightStrategy(width);
	else if (type == Center) strategy_ = new CenterStrategy(width);
}

auto TestBed::DoIt() const->void {
	strategy_->Format();
}

auto main()->int
{
	const auto alignment_choices
	{
		"Exit(0)  \
		 Left(1)  \
		 Right(2) \
		 Center(3): "
	};

	TestBed test;
	int     answer, width;

	std::cout << alignment_choices;
	std::cin >> answer;

	while (answer) {
		std::cout << "Width: ";
		std::cin >> width;
		test.SetStrategy(answer, width);
		test.DoIt();
		std::cout << alignment_choices;
		std::cin >> answer;
	}
	return EXIT_SUCCESS;
}
