#pragma once
#include "CObject.h"
class CAttack :
    public CObject
{
protected:
    CObject*    m_pOwner;

    float		m_fCurTime;	    // ������Ʈ �����ǰ� ������ �ð�
    float		m_fDuration;	// ������Ʈ ���ӽð�

public:
    CAttack(OBJ_TYPE _eType, CObject* _pObj, float _fDuration);
    virtual ~CAttack();

    CObject* GetOwner() { return m_pOwner; }

};

