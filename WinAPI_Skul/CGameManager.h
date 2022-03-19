#pragma once

class CObject;
class CUIText;

class CGameManager
{
	SINGLETON(CGameManager);

private:
	CObject* m_pPlayer;
	bool	 m_bIsPlay;

	CUIText* m_pTimer;

public:
	void Init();
	void Update();

	void		SetPlayer(CObject* _pPlayer)	{ m_pPlayer = _pPlayer; }
	void		SetTimer(CUIText* _pTimer)		{ m_pTimer = _pTimer; }
	void		SetGamePlay(bool _bIsPlay)		{ m_bIsPlay = _bIsPlay; }
	CObject*	GetPlayer()						{ return m_pPlayer; }
	bool		GetGamePlay()					{ return m_bIsPlay; }



};

