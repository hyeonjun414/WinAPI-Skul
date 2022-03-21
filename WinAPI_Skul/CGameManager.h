#pragma once

class CObject;
class CUIText;

class CGameManager
{
	SINGLETON(CGameManager);

public:
	CObject*	m_pPlayer;
	CObject*	m_pPlayer2;
	bool		m_bIsPlay;

	int			m_iRemainEnemyCount;

	CUIText*	m_pTimer;
	CUIText*	m_pRemainEnemy;

	vector<CObject> m_vecItem;
public:
	void		Init();
	void		Update();

	void		SetPlayer(CObject* _pPlayer)			{ m_pPlayer = _pPlayer; }
	void		SetTimer(CUIText* _pTimer)				{ m_pTimer = _pTimer; }
	void		SetRemainEnemy(CUIText* _pUIText)		{ m_pRemainEnemy = _pUIText; }
	void		SetGamePlay(bool _bIsPlay)				{ m_bIsPlay = _bIsPlay; }
	CObject*	GetPlayer()								{ return m_pPlayer; }
	bool		GetGamePlay()							{ return m_bIsPlay; }

	void		CreateEffect(const wstring& _strKey, const wstring& _strPath, Vec2 _vPos,
							float _fDuration, float _fInterval, bool _bDir);

	void		DamageText(const wstring& _strDamage, Vec2 _vPos);
};

