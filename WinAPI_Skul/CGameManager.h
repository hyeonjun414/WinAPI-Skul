#pragma once

class CObject;
class CUIText;

class CGameManager
{
	SINGLETON(CGameManager);

public:
	CObject*	m_pPlayer;
	bool		m_bIsPlay;

	int			m_iRemainEnemyCount;

	CUIText*	m_pTimer;
	CUIText*	m_pRemainEnemy;

public:
	void		Init();
	void		Update();

	void		SetPlayer(CObject* _pPlayer)			{ m_pPlayer = _pPlayer; }
	void		SetTimer(CUIText* _pTimer)				{ m_pTimer = _pTimer; }
	void		SetRemainEnemy(CUIText* _pUIText)		{ m_pRemainEnemy = _pUIText; }
	void		SetGamePlay(bool _bIsPlay)				{ m_bIsPlay = _bIsPlay; }
	CObject*	GetPlayer()								{ return m_pPlayer; }
	bool		GetGamePlay()							{ return m_bIsPlay; }



};

