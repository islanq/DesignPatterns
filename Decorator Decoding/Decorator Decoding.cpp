#include <iostream>
#include <string>
using namespace std;

class Interface
{
public:

	virtual void Write(string&) = 0;
	virtual void Read(string&) = 0;
	virtual ~Interface() {}
};

class Core : public Interface
{
public:
	~Core() { cout << "dtor-Core\n"; }

	virtual void Write(string& b) override { b += "MESSAGE|"; }

	void Read(string&) override;
};

class Decorator : public Interface
{
	Interface* inner;
public:
	explicit Decorator(Interface* c)
		: inner{ c } {}

	~Decorator() { delete inner; }

	virtual void Write(string& b) override { inner->Write(b); }

	virtual void Read(string& b) override { inner->Read(b); }
};

class Wrapper : public Decorator
{
	string forward, backward;
public:
	Wrapper(Interface* c, string str) : Decorator(c)
	{
		forward = str;
		string::reverse_iterator it;
		it = str.rbegin();
		for (; it != str.rend(); ++it)
			backward += *it;
	}
	~Wrapper() { cout << "dtor-" << forward << "  "; }
	virtual void Write(string&) override;
	virtual void Read(string&) override;
};

int main()
{
	Interface* object =
			new Wrapper(
				new Wrapper(
					new Wrapper(
						new Core(), "123"
					), "abc"
				), "987");
	string buf;
	object->Write(buf);
	cout << "main: " << buf << endl;
	object->Read(buf);
	delete object;

	getchar();
	return EXIT_SUCCESS;
}
