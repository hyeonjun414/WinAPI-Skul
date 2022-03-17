#pragma once

class CObject;

class CGameManager
{
	SINGLETON(CGameManager);

private:
	CObject* m_pPlayer;

public:
	void Init();
	void Update();

	void		SetPlayer(CObject* _pPlayer)	{ m_pPlayer = _pPlayer; }
	CObject*	GetPlayer()						{ return m_pPlayer; }

};

