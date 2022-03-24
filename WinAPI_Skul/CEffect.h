#pragma once
#include "CObject.h"
class CEffect :
    public CObject
{
private:
	float		m_fCurTime;		// 이펙트가 시작되고 지나간 시간
	float		m_fDuration;	// 이펙트가 지속되는 시간

	bool		m_bIsPlay;		// 이펙트를 재생시키기 위해 설정되어야하는 값
	CObject*	m_pTargetObj;	// 따라갈 오브젝트
	float		m_fSizeRate;

public:
	CEffect(wstring _strImgName, wstring _strImgPath, float _fDuration, float _fInterval, bool _dir);
	virtual ~CEffect();

	virtual void Update();
	virtual void Render();

	void SetTarget(CObject* _pObj) { m_pTargetObj = _pObj; }
	void SetPlay(bool _bIsPlay)		{ m_bIsPlay = _bIsPlay; }
	void SetSizeRate(float _size) { m_fSizeRate = _size; }
	bool GetPlay()					{ return m_bIsPlay; }


	void EffectPlay(Vec2 _vPos);


};

