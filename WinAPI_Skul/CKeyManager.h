#pragma once

class CKeyManager
{
	SINGLETON(CKeyManager);

private:
	vector<tKeyInfo>	m_vecKey;		// Ű�� ���� �������� Ű ���¸� �����ϴ� ����
	Vec2				m_vCurMousePos; // ���� �������� ���콺 ��ġ

	bool				m_bAnyKeyTap;

public:
	void				Init();
	void				Update();

	KEY_STATE	GetKeyState(KEY _eKey)	{ return m_vecKey[(int)_eKey].eState; }
	Vec2		GetMousePos()			{ return m_vCurMousePos; }

	bool		GetAnyKeyTap() { return m_bAnyKeyTap; }
};

