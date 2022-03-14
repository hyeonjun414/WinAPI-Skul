#pragma once


class CTexture;

class CCore
{
	SINGLETON(CCore);

private:
	HDC			m_hDC;
	CTexture*	m_pMemTex;

	// 자주 사용할 그리기용 펜을 관리
	HBRUSH		m_arrBrush[(UINT)BRUSH_TYPE::SIZE];
	HPEN		m_arrPen[(UINT)PEN_TYPE::SIZE];

	bool		m_bDebugMode; // 디버그 모드 플래그

public :
	void		Init();	  // 초기화
	void		Update(); // 게임 업데이트
	void		Render(); // 게임 그리기

	HDC			GetMainDC()						{ return m_hDC; }
	HBRUSH		GetBrush(BRUSH_TYPE _brushType) { return m_arrBrush[(UINT)_brushType]; }
	HPEN		GetPEN(PEN_TYPE _penType)		{ return m_arrPen[(UINT)_penType]; }
	bool		GetDebugMode()					{ return m_bDebugMode; }

private:
	void		CreateBrushPen(); // 그리기에서 사용할 펜과 브러쉬 생성
};

