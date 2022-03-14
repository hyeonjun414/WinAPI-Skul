#pragma once

class CKeyManager
{
	SINGLETON(CKeyManager);

private:
	vector<tKeyInfo>	m_vecKey;		// 키와 현재 프레임의 키 상태를 저장하는 벡터
	Vec2				m_vCurMousePos; // 현재 프레임의 마우스 위치
public:
	void				Init();
	void				Update();

	KEY_STATE	GetKeyState(KEY _eKey)	{ return m_vecKey[(int)_eKey].eState; }
	Vec2		GetMousePos()			{ return m_vCurMousePos; }
};

