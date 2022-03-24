#pragma once

class CObject;
class CPlayer;
class CUIText;
class CUIImage;

class CGameManager
{
	SINGLETON(CGameManager);

public:
	CPlayer*	m_pPlayer;
	CPlayer*	m_pPlayer2;
	bool		m_bIsPlay;

	int			m_iRemainEnemyCount;

	CUIText*	m_pTimer;
	CUIText*	m_pRemainEnemy;
	CUIImage*	m_pCurHealth;
	CUIText*	m_pCurHealthText;

	CUIImage*	m_pBossStatus;

	vector<CObject> m_vecItem;
public:
	void		Init();
	void		Update();

	void		SetPlayer(CObject* _pPlayer)			{ m_pPlayer = (CPlayer*)_pPlayer; }
	void		SetTimer(CUIText* _pTimer)				{ m_pTimer = _pTimer; }
	void		SetRemainEnemy(CUIText* _pUIText)		{ m_pRemainEnemy = _pUIText; }
	void		SetGamePlay(bool _bIsPlay)				{ m_bIsPlay = _bIsPlay; }
	CObject*	GetPlayer()								{ return (CObject*)m_pPlayer; }
	bool		GetGamePlay()							{ return m_bIsPlay; }



	void		EraseHeadObj();
	void		CreateEffect(const wstring& _strKey, const wstring& _strPath, Vec2 _vPos,
							float _fDuration, float _fInterval, bool _bDir, float _size = 1.0f);

	void		DamageText(const wstring& _strDamage, Vec2 _vPos, Color _color = Color::WHITE);
};

