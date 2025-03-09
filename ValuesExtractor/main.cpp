#include <iostream>
#include <iomanip>
#include "values_extract.h"

int main()
{
	const char* fmt = "TRADE TradeID:{x}, Price {}, Side: {}, CustID:{h}";

	const std::string input = "2025-02-05 12:10:23.547 TRADE TradeID:5614, Price 12000.50, Side: BUY, CustID:30AB";

	float price = 0;
	std::string side;
	int custID = 0;

	using namespace values;

	ValuesExtract(input, fmt, price, side, custID);

	std::cout << "Results: " << price << ", " << side << ", " << std::hex << custID << "\n";

	std::cout << "Done!\n";
	return 0;
}

/*
int main()
{
	const char* fmt = "TRADE TradeID:{x}, Price {}, Side: {}, CustID:{h}";

	const std::string input = "2025-02-05 12:10:23.547 TRADE TradeID:5614, Price 12000, Side: BUY, CustID:30AB";

	int price = 0;
	std::string side;
	int custID = 0;

	using namespace values;

	ValuesExtract(input, fmt, price, side, custID);

	std::cout << "Results: " << price << ", " << side << ", " << std::hex << custID << "\n";

	std::cout << "Done!\n";
	return 0;
}
*/

/*
int main()
{
	const char* fmt = "{x}My name is {} and gender is {} and has a {} and age is {h}";
	const std::string input = "123My name is Steven and gender is M and has a badminton and age is 0x30";

	using namespace values;

	std::vector<Token> tokens = TokenizeFmtString(fmt);

	std::string name;
	std::string gender;
	std::string hobby;
	int age = 0;

	ValuesExtract(input, tokens, name, gender, hobby, age);

	std::cout << "Results: " << name << ", " << gender << ", " << hobby << ", " << age << "\n";

	std::cout << "Done!\n";
	return 0;
}
*/

/*
int main()
{
	const char* fmt = "{x}My name is {} and gender is {} and has a {} and age is {h}";
	const std::string input = "123My name is Steven and gender is M and has a badminton and age is 0x30";

	std::string name;
	std::string gender;
	std::string hobby;
	int age = 0;

	using namespace values;

	ValuesExtract(input, fmt, name, gender, hobby, age);

	std::cout << "Results: " << name << ", " << gender << ", " << hobby << ", " << age << "\n";

	std::cout << "Done!\n";
	return 0;
}
*/
