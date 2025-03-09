#pragma once
#include <string>
#include "conv.h"

namespace values
{
	class DataTypeRef
	{
	public:
		~DataTypeRef() {}

		union UNIONPTR
		{
			int* pi;
			unsigned int* pui;
			short* psi;
			unsigned short* pusi;
			long long* pi64;
			unsigned long long* pui64;
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

		DataTypeRef(int& i) { m_ptr.pi = &i; m_type = DTR_INT; }

		DataTypeRef(unsigned int& ui) { m_ptr.pui = &ui; m_type = DTR_UINT; }

		DataTypeRef(short& si) { m_ptr.psi = &si; m_type = DTR_SHORT; }

		DataTypeRef(unsigned short& usi) { m_ptr.pusi = &usi; m_type = DTR_USHORT; }

		DataTypeRef(long long& i64) { m_ptr.pi64 = &i64; m_type = DTR_INT64; }

		DataTypeRef(unsigned long long& ui64) { m_ptr.pui64 = &ui64; m_type = DTR_UINT64; }

		DataTypeRef(float& f) { m_ptr.pf = &f; m_type = DTR_FLOAT; }

		DataTypeRef(double& d) { m_ptr.pd = &d; m_type = DTR_DOUBLE; }

		DataTypeRef(std::string& s) { m_ptr.ps = &s; m_type = DTR_STR; }

		DataTypeRef(std::wstring& ws) { m_ptr.pws = &ws; m_type = DTR_WSTR; }

		DataTypeRef(char& c) { m_ptr.pc = &c; m_type = DTR_CHAR; }

		DataTypeRef(unsigned char& uc) { m_ptr.puc = &uc; m_type = DTR_UCHAR; }

		DataTypeRef(wchar_t& wc) { m_ptr.pwc = &wc; m_type = DTR_WCHAR; }

		bool ConvStrToType(const std::string_view& str, bool hex)
		{
			int base = hex ? 16 : 10;
			switch (m_type)
			{
			case DTR_INT:
				return conv::str_to_num(str, *(m_ptr.pi), base);
			case DTR_UINT:
				return conv::str_to_num(str, *(m_ptr.pui), base);
			case DTR_SHORT:
				return conv::str_to_num(str, *(m_ptr.psi), base);
			case DTR_USHORT:
				return conv::str_to_num(str, *(m_ptr.pusi), base);
			case DTR_FLOAT:
				return conv::str_to_float(str, *(m_ptr.pf));
			case DTR_DOUBLE:
				return conv::str_to_float(str, *(m_ptr.pd));
			case DTR_STR:
				*(m_ptr.ps) = str;
				return true;
			case DTR_WSTR:
				*(m_ptr.pws) = L"";
				for (char ch : str)
					*(m_ptr.pws) += (wchar_t)ch;
				return true;
			case DTR_INT64:
				return conv::str_to_num(str, *(m_ptr.pi64), base);
			case DTR_UINT64:
				return conv::str_to_num(str, *(m_ptr.pui64), base);
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

}