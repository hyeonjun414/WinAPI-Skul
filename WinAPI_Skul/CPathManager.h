#pragma once
class CPathManager
{
	SINGLETON(CPathManager);

private:
	wchar_t		m_strContentPath[255]; // 윈도우 자체에 경로 글자 수가 255글자로 제한되어있음.

public:
	void			Init(); // 초기화 단계에서 현재 환경에서의 절대 경로를 얻어온다.

	// 경로를 반환하는 함수들 ( 절대, 상대 )
	const wchar_t*	GetContentPath() { return m_strContentPath; }
	const wchar_t*	GetContextRelativePath();
};

