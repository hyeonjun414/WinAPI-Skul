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

	tPlayer_Info m_tCurPlayerInfo;
	bool		m_bIsPlay;

	int			m_iRemainEnemyCount;

	CUIText*	m_pTimer;
	CUIText*	m_pRemainEnemy;
	CUIImage*	m_pCurHealth;
	CUIText*	m_pCurHealthText;

	CUIImage*	m_pPortrait;
	CUIImage*	m_pSkillA;
	CUIImage*	m_pSkillB;
	CUIImage*	m_pSubSkillA;
	CUIImage*	m_pSubSkillB;
	CUIImage*	m_pSubSkul;

	CUIImage*	m_pSubSkillFrame;
	CUIImage*	m_pSubSkulFrame;


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

	CPlayer*	GetCurSkul();

	void		SwitchSkul();
	void		AddSkul(SKUL_TYPE _eSkulType);



	void		EraseHeadObj();
	void		CreateVfx(const wstring& _strKey, const wstring& _strPath, Vec2 _vPos,
							float _fDuration, float _fInterval, bool _bDir, float _size = 1.0f);
	void		DamageText(const wstring& _strDamage, Vec2 _vPos, Color _color = Color::WHITE);
	int			RandomInt(int _value, float _volume);
};

