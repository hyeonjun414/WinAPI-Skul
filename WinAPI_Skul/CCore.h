#pragma once


class CD2DImage;

class CCore
{
	SINGLETON(CCore);

private:
	HDC			m_hDC;
	bool		m_bDebugMode; // 디버그 모드 플래그

public :
	void		Init();	  // 초기화
	void		Update(); // 게임 업데이트
	void		Render(); // 게임 그리기

	HDC			GetMainDC()						{ return m_hDC; }
	bool		GetDebugMode()					{ return m_bDebugMode; }

};

