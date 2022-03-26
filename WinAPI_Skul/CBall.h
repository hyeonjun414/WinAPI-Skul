#pragma once
#include "CProjectile.h"
class CBall :
    public CProjectile
{
public:
    CBall(OBJ_TYPE _eType, CObject* _pObj,
        const wstring& _strKey, const wstring& _strPath,
        float _fDuration);
    virtual ~CBall();

    virtual void Update();
    virtual void Render();

    virtual void	OnCollision(CCollider* _pOther) {};
    virtual void	OnCollisionEnter(CCollider* _pOther);
    virtual void	OnCollisionExit(CCollider* _pOther) {};
};

