#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "data_type_ref.h"

namespace values
{

	enum class TokenType
	{
		None,
		Hex,
		Matter
	};

	struct Token
	{
		int index;
		size_t start;
		size_t size;
		TokenType type;
		std::string prefix;
		std::string postfix;
	};

	inline std::vector<Token> Find(const std::string& input, const char* find, TokenType type)
	{
		std::vector<Token> vec;
		size_t find_size = strlen(find);
		if (find_size == 0)
			return {};

		size_t pos = 0;
		pos = input.find(find);
		while (pos != std::string::npos)
		{
			vec.push_back({ -1, pos, find_size, type });
			pos += find_size;
			pos = input.find(find, pos);
		}
		return vec;
	}

	inline std::vector<Token> TokenizeFmtString(const std::string& fmt)
	{
		std::vector<Token> vecMatter = Find(fmt, "{}", TokenType::Matter);
		std::vector<Token> vecHex = Find(fmt, "{h}", TokenType::Hex);
		std::vector<Token> vecX = Find(fmt, "{x}", TokenType::None);

		std::vector<Token> vec;
		for (auto& a : vecMatter)
		{
			vec.push_back(a);
		}
		for (auto& a : vecHex)
		{
			vec.push_back(a);
		}
		for (auto& a : vecX)
		{
			vec.push_back(a);
		}

		std::sort(vec.begin(), vec.end(), [](const Token& a, const Token& b)
			{ return a.start < b.start; });

		for (size_t i = 0; i < vec.size(); ++i)
		{
			auto& curr = vec[i];

			if (i == 0)
			{
				if (curr.start == 0)
				{
					curr.prefix = "";
				}
				else
				{
					curr.prefix = fmt.substr(0, curr.start);
				}

				if (i + 1 < vec.size())
				{
					auto& next = vec[i + 1];
					if (curr.start + curr.size == next.start)
					{
						std::cerr << "Error: Format specifier {} cannot be side by side! For example: {}{}\n";
						return {};
					}
					else if (curr.start + curr.size < next.start)
					{
						curr.postfix = fmt.substr(curr.start + curr.size, next.start - (curr.start + curr.size));
					}
				}
				else
				{
					curr.postfix = fmt.substr(curr.start + curr.size);
				}
				continue;
			}

			if (i + 1 < vec.size() && i > 0)
			{
				auto& prev = vec[i - 1];

				curr.prefix = fmt.substr(prev.start + prev.size, curr.start - (prev.start + prev.size));

				auto& next = vec[i + 1];
				if (curr.start + curr.size == next.start)
				{
					std::cerr << "Error: Format specifier {} cannot be side by side! For example: {}{}\n";
					return {};
				}
				else if (curr.start + curr.size < next.start)
				{
					curr.postfix = fmt.substr(curr.start + curr.size, next.start - (curr.start + curr.size));
				}
				continue;
			}

			if (i == (vec.size() - 1) && i > 0)
			{
				auto& prev = vec[i - 1];

				curr.prefix = fmt.substr(prev.start + prev.size, curr.start - (prev.start + prev.size));
				curr.postfix = fmt.substr(curr.start + curr.size);
			}
		}

		int index = 0;
		for (auto& a : vec)
		{
			if (a.type != TokenType::None)
			{
				a.index = index;

				++index;
			}
		}

		return vec;
	}

	inline void AddData(std::vector<DataTypeRef>& results)
	{
	}


	template<typename T, typename... Args>
	void AddData(std::vector<DataTypeRef>& results, T& value, Args & ... args)
	{
		results.push_back({ value });
		AddData(results, args...);
	}

	inline void ValuesExtractHelp(const std::string& input, const std::vector<Token>& tokens, std::vector<DataTypeRef>& results)
	{
		size_t token_size = 0;

		for (size_t i = 0; i < tokens.size(); ++i)
		{
			if (tokens[i].type != TokenType::None)
				++token_size;
		}

		if (results.size() != token_size)
		{
			std::cerr << "Number of parameters and fmt token mismatched\n";
			return;
		}

		size_t prefix_pos = 0;
		size_t postfix_pos = 0;
		for (size_t i = 0; i < tokens.size(); ++i)
		{
			auto& curr = tokens[i];

			if (curr.prefix.empty() == false)
			{
				prefix_pos = input.find(curr.prefix, prefix_pos);

				if (prefix_pos == std::string::npos)
				{
					std::cerr << "prefix_pos Error\n";
					return;
				}
				prefix_pos += curr.prefix.size();
			}

			postfix_pos = prefix_pos + 1;
			if (curr.postfix.empty() == false)
			{
				postfix_pos = input.find(curr.postfix, postfix_pos);

				if (postfix_pos == std::string::npos)
				{
					std::cerr << "postfix_pos Error\n";
					return;
				}
			}
			else
			{
				postfix_pos = std::string::npos;
			}

			std::string res;
			if (prefix_pos != std::string::npos)
			{
				res = input.substr(prefix_pos, postfix_pos - prefix_pos);
				//std::cout << "results: " << res << "\n";
				if (curr.index != -1)
				{
					results.at(curr.index).ConvStrToType(res, curr.type == TokenType::Hex);
				}
			}
			prefix_pos += res.size();
		}
	}


	template<typename... Args>
	void ValuesExtract(const std::string& input, const char* fmt, Args & ... args)
	{
		std::vector<Token> tokens = TokenizeFmtString(fmt);

		std::vector<DataTypeRef> results;

		AddData(results, args...);

		//std::cout << "vec size(): " << results.size() << "\n";

		ValuesExtractHelp(input, tokens, results);
	}

	template<typename... Args>
	void ValuesExtract(const std::string& input, const std::vector<Token>& tokens, Args & ... args)
	{
		std::vector<DataTypeRef> results;

		AddData(results, args...);

		//std::cout << "vec size(): " << results.size() << "\n";

		ValuesExtractHelp(input, tokens, results);
	}

}