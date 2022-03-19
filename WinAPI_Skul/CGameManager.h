#pragma once

class CObject;

class CGameManager
{
	SINGLETON(CGameManager);

private:
	CObject* m_pPlayer;
	bool	 m_bIsPlay;

public:
	void Init();
	void Update();

	void		SetPlayer(CObject* _pPlayer)	{ m_pPlayer = _pPlayer; }
	void		SetGamePlay(bool _bIsPlay)		{ m_bIsPlay = _bIsPlay; }
	CObject*	GetPlayer()						{ return m_pPlayer; }
	bool		GetGamePlay()					{ return m_bIsPlay; }



};

