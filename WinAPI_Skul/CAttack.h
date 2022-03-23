#pragma once
#include "CObject.h"
class CAttack :
    public CObject
{
protected:
    CObject*    m_pOwner;

    float		m_fCurTime;	    // 오브젝트 생성되고 지나간 시간
    float		m_fDuration;	// 오브젝트 지속시간

public:
    CAttack(OBJ_TYPE _eType, CObject* _pObj, float _fDuration);
    virtual ~CAttack();

    CObject* GetOwner() { return m_pOwner; }

};

