#include <iostream>
#include <iomanip>
#include "unittest.h"
#include "values_extract.h"

using namespace values;

void Integer()
{
	const char* fmt = "ID:{}";

	const std::string input = "ID:123";

	int id = 0;

	ValuesExtract(input, fmt, id);

	CHECK(id, == , 123);
}

void String()
{
	const char* fmt = "ID:{}";

	const std::string input = "ID:123";

	std::string id;

	ValuesExtract(input, fmt, id);

	CHECK(id, == , "123");
}

void StringWithTimestamp()
{
	const char* fmt = "ID:{}";

	const std::string input = "2025-01-01 10:00:56 ID:123";

	std::string id;

	ValuesExtract(input, fmt, id);

	CHECK(id, == , "123");
}

void StringWithSuffix()
{
	const char* fmt = "ID:{} or OAuth Login";

	const std::string input = "ID:123 or OAuth Login";

	std::string id;

	ValuesExtract(input, fmt, id);

	CHECK(id, == , "123");
}


void TrimString()
{
	const char* fmt = "Name:{t}";

	const std::string input = "Name:  Sherry William  ";

	std::string name;

	ValuesExtract(input, fmt, name);

	CHECK(name, == , "Sherry William");
}

void HexString()
{
	const char* fmt = "Binary:{h}";

	const std::string input = "Binary:0xA";

	int hex = 0;

	ValuesExtract(input, fmt, hex);

	CHECK(hex, == , 10);
}

void HexString2()
{
	const char* fmt = "Binary:{h}";

	const std::string input = "Binary:A";

	int hex = 0;

	ValuesExtract(input, fmt, hex);

	CHECK(hex, == , 10);
}

void HexString3()
{
	const char* fmt = "Binary:{h}";

	const std::string input = "Binary:a";

	int hex = 0;

	ValuesExtract(input, fmt, hex);

	CHECK(hex, == , 10);
}

void IgnoreVariable()
{
	const char* fmt = "CustID:{x}, Binary:{h}";

	const std::string input = "CustID:234, Binary:a";

	int hex = 0;

	ValuesExtract(input, fmt, hex);

	CHECK(hex, == , 10);
}

void ThreeVariable()
{
	const char* fmt = "Name:{t}, Gender:{}, Salary:{}";

	const std::string input = "Name:  Sherry William  , Gender:F, Salary:3600";

	std::string Name;

	char Gender = 'A';

	int Salary = 0;

	ValuesExtract(input, fmt, Name, Gender, Salary);

	CHECK(Name, == , "Sherry William");

	CHECK(Gender, == , 'F');

	CHECK(Salary, == , 3600);
}

void IntegerTokenized()
{
	const char* fmt = "ID:{}";

	const std::string input = "ID:123";

	int id = 0;

	std::vector<Token> tokens = TokenizeFmtString(fmt);

	ValuesExtract(input, tokens, id);

	CHECK(id, == , 123);
}

void StringTokenized()
{
	const char* fmt = "ID:{}";

	const std::string input = "ID:123";

	std::string id;

	std::vector<Token> tokens = TokenizeFmtString(fmt);

	ValuesExtract(input, tokens, id);

	CHECK(id, == , "123");
}

void StringWithTimestampTokenized()
{
	const char* fmt = "ID:{}";

	const std::string input = "2025-01-01 10:00:56 ID:123";

	std::string id;

	std::vector<Token> tokens = TokenizeFmtString(fmt);

	ValuesExtract(input, tokens, id);

	CHECK(id, == , "123");
}

void StringWithSuffixTokenized()
{
	const char* fmt = "ID:{} or OAuth Login";

	const std::string input = "ID:123 or OAuth Login";

	std::string id;

	std::vector<Token> tokens = TokenizeFmtString(fmt);

	ValuesExtract(input, tokens, id);

	CHECK(id, == , "123");
}


void TrimStringTokenized()
{
	const char* fmt = "Name:{t}";

	const std::string input = "Name:  Sherry William  ";

	std::string name;

	std::vector<Token> tokens = TokenizeFmtString(fmt);

	ValuesExtract(input, tokens, name);

	CHECK(name, == , "Sherry William");
}

void HexStringTokenized()
{
	const char* fmt = "Binary:{h}";

	const std::string input = "Binary:0xA";

	int hex = 0;

	std::vector<Token> tokens = TokenizeFmtString(fmt);

	ValuesExtract(input, tokens, hex);

	CHECK(hex, == , 10);
}

void HexStringTokenized2()
{
	const char* fmt = "Binary:{h}";

	const std::string input = "Binary:A";

	int hex = 0;

	std::vector<Token> tokens = TokenizeFmtString(fmt);

	ValuesExtract(input, tokens, hex);

	CHECK(hex, == , 10);
}

void HexStringTokenized3()
{
	const char* fmt = "Binary:{h}";

	const std::string input = "Binary:a";

	int hex = 0;

	std::vector<Token> tokens = TokenizeFmtString(fmt);

	ValuesExtract(input, tokens, hex);

	CHECK(hex, == , 10);
}

void IgnoreVariableTokenized()
{
	const char* fmt = "CustID:{x}, Binary:{h}";

	const std::string input = "CustID:234, Binary:a";

	int hex = 0;

	std::vector<Token> tokens = TokenizeFmtString(fmt);

	ValuesExtract(input, tokens, hex);

	CHECK(hex, == , 10);
}

void ThreeVariableTokenized()
{
	const char* fmt = "Name:{t}, Gender:{}, Salary:{}";

	const std::string input = "Name:  Sherry William  , Gender:F, Salary:3600";

	std::string Name;

	char Gender = 'A';

	int Salary = 0;

	std::vector<Token> tokens = TokenizeFmtString(fmt);

	ValuesExtract(input, tokens, Name, Gender, Salary);

	CHECK(Name, == , "Sherry William");

	CHECK(Gender, == , 'F');

	CHECK(Salary, == , 3600);
}

void IsInputMatchedFmtTest()
{
	const char* fmt = "Name:{t}, Gender:{}, Salary:{}";

	const std::string input = "Name:  Sherry William  , Gender:F, Salary:3600";

	bool result = IsInputMatchedFmt(input, fmt);

	CHECK(result, == , true);
}

void IsInputMatchedTokensTest()
{
	const char* fmt = "Name:{t}, Gender:{}, Salary:{}";

	const std::string input = "Name:  Sherry William  , Gender:F, Salary:3600";

	std::vector<Token> tokens = TokenizeFmtString(fmt);

	bool result = IsInputMatchedTokens(input, tokens);

	CHECK(result, == , true);
}

void IsInputMatchedFmtFailTest()
{
	const char* fmt = "Name:{t}, Gender:{}, Salary:{}";

	const std::string input = "Name:  Sherry William  , Gender1:F, Salary:3600";

	bool result = IsInputMatchedFmt(input, fmt);

	CHECK(result, == , false);
}

void IsInputMatchedTokensFailTest()
{
	const char* fmt = "Name:{t}, Gender:{}, Salary:{}";

	const std::string input = "Name:  Sherry William  , Gender1:F, Salary:3600";

	std::vector<Token> tokens = TokenizeFmtString(fmt);

	bool result = IsInputMatchedTokens(input, tokens);

	CHECK(result, == , false);
}

void EmptyTokenized()
{
	const char* fmt = "Name:{t}, Gender:{}, Salary:{}";

	const std::string input = "Name:  Sherry William  , Gender:, Salary:3600";

	std::string Name;

	std::string Gender = "A";

	int Salary = 0;

	std::vector<Token> tokens = TokenizeFmtString(fmt);

	ValuesExtract(input, tokens, Name, Gender, Salary);

	CHECK(Name, == , "Sherry William");

	CHECK(Gender, == , "");

	CHECK(Salary, == , 3600);
}

void LastEmptyTokenized()
{
	const char* fmt = "Name:{t}, Gender:{}";

	const std::string input = "Name:  Sherry William  , Gender:";

	std::string Name;

	std::string Gender = "A";

	std::vector<Token> tokens = TokenizeFmtString(fmt);

	ValuesExtract(input, tokens, Name, Gender);

	CHECK(Name, == , "Sherry William");

	CHECK(Gender, == , "");
}

int main()
{
	UnitTest::Add("SingleVariable", "Integer", Integer);
	UnitTest::Add("SingleVariable", "String", String);
	UnitTest::Add("SingleVariable", "StringWithTimestamp", StringWithTimestamp);
	UnitTest::Add("SingleVariable", "StringWithSuffix", StringWithSuffix);
	UnitTest::Add("SingleVariable", "TrimString", TrimString);
	UnitTest::Add("SingleVariable", "HexString", HexString);
	UnitTest::Add("SingleVariable", "HexString2", HexString2);
	UnitTest::Add("SingleVariable", "HexString3", HexString3);
	UnitTest::Add("SingleVariable", "IgnoreVariable", IgnoreVariable);

	UnitTest::Add("MuiltiVariable", "ThreeVariable", ThreeVariable);
	UnitTest::Add("MuiltiVariable", "IsInputMatchedFmtTest", IsInputMatchedFmtTest);
	UnitTest::Add("MuiltiVariable", "IsInputMatchedTokensTest", IsInputMatchedTokensTest);
	UnitTest::Add("MuiltiVariable", "IsInputMatchedFmtFailTest", IsInputMatchedFmtFailTest);
	UnitTest::Add("MuiltiVariable", "IsInputMatchedTokensFailTest", IsInputMatchedTokensFailTest);

	UnitTest::Add("Tokens", "IntegerTokenized", IntegerTokenized);
	UnitTest::Add("Tokens", "StringTokenized", StringTokenized);
	UnitTest::Add("Tokens", "StringWithTimestampTokenized", StringWithTimestampTokenized);
	UnitTest::Add("Tokens", "StringWithSuffixTokenized", StringWithSuffixTokenized);
	UnitTest::Add("Tokens", "TrimStringTokenized", TrimStringTokenized);
	UnitTest::Add("Tokens", "HexStringTokenized", HexStringTokenized);
	UnitTest::Add("Tokens", "HexStringTokenized2", HexStringTokenized2);
	UnitTest::Add("Tokens", "HexStringTokenized3", HexStringTokenized3);
	UnitTest::Add("Tokens", "IgnoreVariableTokenized", IgnoreVariableTokenized);

	UnitTest::Add("Tokens", "ThreeVariableTokenized", ThreeVariableTokenized);
	UnitTest::Add("Tokens", "EmptyTokenized", EmptyTokenized);
	UnitTest::Add("Tokens", "LastEmptyTokenized", LastEmptyTokenized);

	// RunAllTests() return number of errors
	return UnitTest::RunAllTests();
}