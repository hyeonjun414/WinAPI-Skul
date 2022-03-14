#pragma once

//================================================
//## Logger	(visual studio 출력창에 정보 표시)	##
//================================================

#include <string>

class Logger
{
	static std::wstring format(const std::wstring fmt, va_list args)
	{
		int size = ((int)fmt.size()) * 2;
		wchar_t* buffer = nullptr;
		while (true) {
			if (buffer != nullptr)
			{
				delete[] buffer;
			}
			buffer = new wchar_t[size + 1];
			int n = _vsnwprintf_s(buffer, size + 1, size, (wchar_t*)fmt.c_str(), args);
			if (-1 < n && n < size) {
				break;
			}
			else
			{
				size *= 2;
			}
		}
		std::wstring result = buffer;
		delete[] buffer;
		return result;
	}

	static std::wstring format(const std::wstring fmt, ...)
	{
		va_list args; va_start(args, fmt);
		std::wstring result = format(fmt, args);
		va_end(args);
		return result;
	}

public:

	static void debug(const wchar_t log[])
	{
		SYSTEMTIME st;
		GetLocalTime(&st);

		std::wstring str = L"";
		str = format(L"%d/%d/%d %d:%2d:%2d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

		OutputDebugStringW(str.c_str());
		OutputDebugStringW(L" [DEBUG] ");
		OutputDebugStringW(log);
		OutputDebugStringW(L"\n");
	}
};
