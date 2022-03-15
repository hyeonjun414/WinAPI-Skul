#pragma once


class CD2DImage;

class CCore
{
	SINGLETON(CCore);

private:
	HDC			m_hDC;
	bool		m_bDebugMode; // ����� ��� �÷���

public :
	void		Init();	  // �ʱ�ȭ
	void		Update(); // ���� ������Ʈ
	void		Render(); // ���� �׸���

	HDC			GetMainDC()						{ return m_hDC; }
	bool		GetDebugMode()					{ return m_bDebugMode; }

};

