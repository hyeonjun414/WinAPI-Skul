#pragma once
#include "CObject.h"
class CEffect :
    public CObject
{
protected:
	wstring		m_strKey;		
	float		m_fCurTime;		// 이펙트가 시작되고 지나간 시간
	float		m_fDuration;	// 이펙트가 지속되는 시간

public:
	CEffect(wstring _strKey, float _fDuration);
	virtual ~CEffect();

	virtual void Update() = 0;
	virtual void Render() {}


};

