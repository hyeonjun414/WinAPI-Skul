#pragma once
#include "CObject.h"
class CAttack :
    public CObject
{
protected:
    CObject*    m_pOwner;
    int     m_iDamage;
    CObject* m_pTraceObj;

    float		m_fCurTime;	    // ������Ʈ �����ǰ� ������ �ð�
    float		m_fDuration;	// ������Ʈ ���ӽð�

public:
    CAttack(OBJ_TYPE _eType, CObject* _pObj, float _fDuration);
    virtual ~CAttack();

    CObject* GetOwner() { return m_pOwner; }

    void  SetTraceObj(CObject* _pObj) { m_pTraceObj = _pObj; }
    int     GetDamage() { return m_iDamage; }

};

