// The MIT License (MIT)
// C++ Values Extractor aka scanf 0.1.0
// Copyright (C) 2025, by Wong Shao Voon (shaovoon@yahoo.com)
//
// http://opensource.org/licenses/MIT

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cstdint>

namespace values
{
	enum class TokenType
	{
		None,
		Hex,
		Matter,
		Trim
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

	class DataTypeRef
	{
	public:
		~DataTypeRef() {}

		union UNIONPTR
		{
			int32_t* pi;
			uint32_t* pui;
			int16_t* psi;
			uint16_t* pusi;
			int64_t* pi64;
			uint64_t* pui64;
			float* pf;
			double* pd;
			std::string* ps;
			std::wstring* pws;
			char* pc;
			unsigned char* puc;
			wchar_t* pwc;
		};

		enum DTR_TYPE
		{
			DTR_INT,
			DTR_UINT,
			DTR_SHORT,
			DTR_USHORT,
			DTR_INT64,
			DTR_UINT64,
			DTR_FLOAT,
			DTR_DOUBLE,
			DTR_STR,
			DTR_WSTR,
			DTR_CHAR,
			DTR_UCHAR,
			DTR_WCHAR
		};

		DataTypeRef(int32_t& i) { m_ptr.pi = &i; m_type = DTR_INT; }

		DataTypeRef(uint32_t& ui) { m_ptr.pui = &ui; m_type = DTR_UINT; }

		DataTypeRef(int16_t& si) { m_ptr.psi = &si; m_type = DTR_SHORT; }

		DataTypeRef(uint16_t& usi) { m_ptr.pusi = &usi; m_type = DTR_USHORT; }

		DataTypeRef(int64_t& i64) { m_ptr.pi64 = &i64; m_type = DTR_INT64; }

		DataTypeRef(uint64_t& ui64) { m_ptr.pui64 = &ui64; m_type = DTR_UINT64; }

		DataTypeRef(float& f) { m_ptr.pf = &f; m_type = DTR_FLOAT; }

		DataTypeRef(double& d) { m_ptr.pd = &d; m_type = DTR_DOUBLE; }

		DataTypeRef(std::string& s) { m_ptr.ps = &s; m_type = DTR_STR; }

		DataTypeRef(std::wstring& ws) { m_ptr.pws = &ws; m_type = DTR_WSTR; }

		DataTypeRef(char& c) { m_ptr.pc = &c; m_type = DTR_CHAR; }

		DataTypeRef(unsigned char& uc) { m_ptr.puc = &uc; m_type = DTR_UCHAR; }

		DataTypeRef(wchar_t& wc) { m_ptr.pwc = &wc; m_type = DTR_WCHAR; }

		static std::string TrimRight(const std::string& str, const std::string& trimChars)
		{
			std::string result = "";
			// trim trailing spaces
			size_t endpos = str.find_last_not_of(trimChars);
			if (std::string::npos != endpos)
			{
				result = str.substr(0, endpos + 1);
			}
			else
				result = str;

			return result;
		}

		static std::string TrimLeft(const std::string& str, const std::string& trimChars)
		{
			std::string result = "";

			// trim leading spaces
			size_t startpos = str.find_first_not_of(trimChars);
			if (std::string::npos != startpos)
			{
				result = str.substr(startpos);
			}
			else
				result = str;

			return result;
		}

		static std::string Trim(const std::string& str, const std::string& trimChars)
		{
			return TrimLeft(TrimRight(str, trimChars), trimChars);
		}

		bool ConvStrToType(const std::string& str, TokenType tokenType)
		{
			using namespace std;
			int base = (tokenType == TokenType::Hex) ? 16 : 10;

			int offset = 0;
			if (base == 16)
			{
				if (str.size() >= 2 && str.at(0) == '0' && str.at(1) == 'x')
				{
					offset = 2;
				}
			}

			switch (m_type)
			{
			case DTR_INT:
			{
				*(m_ptr.pi) = strtol(str.c_str() + offset, nullptr, base);
				return true;
			}
			case DTR_UINT:
			{
				*(m_ptr.pui) = strtol(str.c_str() + offset, nullptr, base);
				return true;
			}
			case DTR_SHORT:
			{
				*(m_ptr.psi) = strtol(str.c_str() + offset, nullptr, base);
				return true;
			}
			case DTR_USHORT:
			{
				*(m_ptr.pusi) = strtol(str.c_str() + offset, nullptr, base);
				return true;
			}
			case DTR_FLOAT:
			{
				*(m_ptr.pf) = strtof(str.c_str(), nullptr);
				return true;
			}
			case DTR_DOUBLE:
			{
				*(m_ptr.pd) = strtod(str.c_str(), nullptr);
				return true;
			}
			case DTR_STR:
				if (tokenType == TokenType::Trim)
				{
					std::string str2 = Trim(str, " \r\n\t\v");
					*(m_ptr.ps) = str2;
				}
				else
				{
					*(m_ptr.ps) = str;
				}
				return true;
			case DTR_WSTR:
			{
				std::string str2;
				if (tokenType == TokenType::Trim)
				{
					str2 = Trim(str, " \r\n\t\v");
				}
				else
				{
					str2 = str;
				}
				*(m_ptr.pws) = L"";
				for (char ch : str2)
					*(m_ptr.pws) += (wchar_t)ch;
			}
				return true;
			case DTR_INT64:
			{
				*(m_ptr.pi64) = strtoll(str.c_str() + offset, nullptr, base);
				return true;
			}
			case DTR_UINT64:
			{
				*(m_ptr.pui64) = strtoull(str.c_str() + offset, nullptr, base);
				return true;
			}
			case DTR_CHAR:
				if (str.size() > 0)
				{
					*(m_ptr.pc) = (char)str[0];
					return true;
				}
				else
					return false;
			case DTR_UCHAR:
				if (str.size() > 0)
				{
					*(m_ptr.puc) = (unsigned char)str[0];
					return true;
				}
				else
					return false;
			case DTR_WCHAR:
				if (str.size() > 0)
				{
					*(m_ptr.pwc) = str.at(0);
					return true;
				}
				else
					return false;
			default:
				return false;
			}

			return false;
		}

		DTR_TYPE m_type;

		UNIONPTR m_ptr;
	};

	namespace detail
	{
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
	}

	inline std::vector<Token> TokenizeFmtString(const std::string& fmt)
	{
		std::vector<Token> vecMatter = detail::Find(fmt, "{}", TokenType::Matter);
		std::vector<Token> vecHex = detail::Find(fmt, "{h}", TokenType::Hex);
		std::vector<Token> vecX = detail::Find(fmt, "{x}", TokenType::None);
		std::vector<Token> vecTrim = detail::Find(fmt, "{t}", TokenType::Trim);

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
		for (auto& a : vecTrim)
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
	namespace detail
	{

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
						results.at(curr.index).ConvStrToType(res, curr.type);
					}
				}
				prefix_pos += res.size();
			}
		}
	}

	template<typename... Args>
	void ValuesExtract(const std::string& input, const char* fmt, Args & ... args)
	{
		std::vector<Token> tokens = TokenizeFmtString(fmt);

		std::vector<DataTypeRef> results;

		detail::AddData(results, args...);

		//std::cout << "vec size(): " << results.size() << "\n";

		detail::ValuesExtractHelp(input, tokens, results);
	}

	template<typename... Args>
	void ValuesExtract(const std::string& input, const std::vector<Token>& tokens, Args & ... args)
	{
		std::vector<DataTypeRef> results;

		detail::AddData(results, args...);

		//std::cout << "vec size(): " << results.size() << "\n";

		detail::ValuesExtractHelp(input, tokens, results);
	}

}