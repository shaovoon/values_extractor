#include <iostream>
#include <iomanip>
#include "values_extract.h"


int main()
{
	// test new trim specifier: {t} to trim the string.
	const char* fmt = "LOGIN UserName:{t}, CustomerID:{x}";

	const std::string input = "LOGIN UserName: Sherry Williams , CustomerID:30AB";

	std::string name;

	using namespace values;

	auto tokens = TokenizeFmtString(fmt);

	ValuesExtract(input, tokens, name);

	std::cout << "Results: [" << name << "]\n";

	return 0;
}


/*
int main()
{
	const char* fmt = "LOGIN UserName:{}, CustomerID:{x}";

	const std::string input = "LOGIN UserName:Sherry Williams, CustomerID:30AB";

	//const std::string input = "2025-01-01 12:00:00.001 LOGIN UserName:Sherry Williams, CustomerID:30AB";

	std::string name;

	using namespace values;

	ValuesExtract(input, fmt, name);

	std::cout << "Results: " << name << "\n";

	return 0;
}
*/

/*
int main()
{
	const char* fmt = "LOGIN UserName:{}, CustomerID:{h}";

	const std::string input = "LOGIN UserName:Sherry Williams, CustomerID:30AB";

	//const std::string input = "2025-01-01 12:00:00.001 LOGIN UserName:Sherry Williams, CustomerID:30AB";

	std::string name;

	int custID = 0;

	using namespace values;

	ValuesExtract(input, fmt, name, custID);

	std::cout << "Results: " << name << ", " << std::hex << custID << "\n";

	return 0;
}
*/

/*
int main()
{
	const char* fmt = "REGISTER Name:{}, Age:{}";

	//const std::string input = "REGISTER Name:Sherry, Age:20";

	const std::string input = "2025-01-01 12:00:00.001 REGISTER Name:Sherry, Age:20";

	std::string name;
	
	int age = 0;

	using namespace values;

	ValuesExtract(input, fmt, name, age);

	std::cout << "Results: " << name << ", " << age << "\n";

	return 0;
}
*/