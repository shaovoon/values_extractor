# Values Extractor

C++11 header-only library to extract values from a string. Only basic types (ASCII `string`, `int` and `float`) are supported.

```Cpp
#include <iostream>
#include <iomanip>
#include "values_extract.h"

const char* fmt = "REGISTER Name:{}, Age:{}";

const std::string input = "REGISTER Name:Sherry, Age:20";

std::string name;
	
int age = 0;

using namespace values;

ValuesExtract(input, fmt, name, age);

std::cout << "Results: " << name << ", " << age << "\n";
```

The extracted output is below.

```
Results: Sherry, 20
```

The extracted output remains same even when the input string contains timestamp on the left.

```Cpp
const std::string input = "2025-01-01 12:00:00.001 REGISTER Name:Sherry, Age:20";
```

When the `fmt` string is tokenized, it is splitted into `"REGISTER Name:"`, `", Age:"` and `""`. To extract the first value, it searches for the 1st and 2nd token in the `input` string and use their position to extract the substring inbetween them. The timestamp is ignored by accident.

`{h}` can be used to extract hexidecimal values. Whether the hexidecimal is preceded with `0x` is taken care of.

```Cpp
const char* fmt = "LOGIN UserName:{}, CustomerID:{h}";

const std::string input = "LOGIN UserName:Sherry Williams, CustomerID:30AB";

std::string name;

int custID = 0;

using namespace values;

ValuesExtract(input, fmt, name, custID);

std::cout << "Results: " << name << ", " << std::hex << custID << "\n";
```

The extracted output is as below.

```
Results: Sherry Williams, 30ab
```

`{x}` can be used to specify a value to be ignored and a parameter is not passed to hold this value. In the example below, we are not interested in `CustomerID` since it is random key in the database.

```Cpp
const char* fmt = "LOGIN UserName:{}, CustomerID:{x}";

const std::string input = "LOGIN UserName:Sherry Williams, CustomerID:30AB";

std::string name;

using namespace values;

ValuesExtract(input, fmt, name);

std::cout << "Results: " << name << "\n";
```

The extracted output is below. We need not to pass a parameter to hold the 2nd value.

```
Results: Sherry Williams
```

Since tokeniznig the `fmt` string is computation intensive activity, we do not want to always tokenize the same `fmt` string whenever we want to extract the `input` string repeatedly. `TokenizeFmtString` is provided to tokenize the `fmt` and a overloaded `ValuesExtract` can accept the `tokens` instead of `fmt` to speedup the operation.

```Cpp
const char* fmt = "LOGIN UserName:{}, CustomerID:{x}";

const std::string input = "LOGIN UserName:Sherry Williams, CustomerID:30AB";

std::string name;

using namespace values;

auto tokens = TokenizeFmtString(fmt);

ValuesExtract(input, tokens, name);

std::cout << "Results: " << name << "\n";
```

The extracted contents remains the same.

```
Results: Sherry Williams
```

Three extractor specifier are supported.

* `{}` : to extract substring.
* `{h}` : to extract hexidecimal substring. Prefix of `0x` is taken care of.
* `{x}` : to ignore this substring and do not supply a parameter to extract it into.
* `{t}` : to extract substring and trim it.

__Coming soon__: Example on how to use it to read a file.