#pragma once
#include "CObject.h"
class CEffect :
    public CObject
{
private:
	float m_fCurTime;	// 이펙트가 시작되고 지나간 시간
	float m_fDuration;	// 이펙트가 지속되는 시간

	bool  m_bIsPlay;	// 이펙트를 재생시키기 위해 설정되어야하는 값
	
	wstring m_strKey;

public:
	CEffect(OBJ_TYPE _eType, wstring _strImgName, wstring _strImgPath, float _fDuration, float _fPlayTime, int  _imgSize, bool _dir);
	virtual ~CEffect();

	virtual void Update();
	virtual void Render();

	void SetPlay(bool _bIsPlay)		{ m_bIsPlay = _bIsPlay; }
	bool GetPlay()					{ return m_bIsPlay; }

	void EffectPlay(Vec2 _vPos);
};

