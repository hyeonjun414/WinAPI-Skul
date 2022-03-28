#pragma once
#include "CObject.h"
class CItem :
    public CObject
{
protected:
    bool m_bIsUsed;

public:
    CItem();
    virtual ~CItem();

    virtual void Init() {}
    virtual void Update() {}
    virtual void Render() {}

    virtual void	OnCollision(CCollider* _pOther) {};
    virtual void	OnCollisionEnter(CCollider* _pOther) {};
    virtual void	OnCollisionExit(CCollider* _pOther) {};

    virtual void Use() {}

    bool    IsUsed() { return m_bIsUsed; }
};

