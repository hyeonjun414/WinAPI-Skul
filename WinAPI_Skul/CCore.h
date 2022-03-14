#pragma once


class CTexture;

class CCore
{
	SINGLETON(CCore);

private:
	HDC			m_hDC;
	CTexture*	m_pMemTex;

	// ���� ����� �׸���� ���� ����
	HBRUSH		m_arrBrush[(UINT)BRUSH_TYPE::SIZE];
	HPEN		m_arrPen[(UINT)PEN_TYPE::SIZE];

	bool		m_bDebugMode; // ����� ��� �÷���

public :
	void		Init();	  // �ʱ�ȭ
	void		Update(); // ���� ������Ʈ
	void		Render(); // ���� �׸���

	HDC			GetMainDC()						{ return m_hDC; }
	HBRUSH		GetBrush(BRUSH_TYPE _brushType) { return m_arrBrush[(UINT)_brushType]; }
	HPEN		GetPEN(PEN_TYPE _penType)		{ return m_arrPen[(UINT)_penType]; }
	bool		GetDebugMode()					{ return m_bDebugMode; }

private:
	void		CreateBrushPen(); // �׸��⿡�� ����� ��� �귯�� ����
};

