#pragma once
#include "CObject.h"
class CGate :
    public CObject
{
public:
    CGate();
    CGate(OBJ_TYPE _eType);
    virtual ~CGate();

    virtual void        Init();
    virtual void        Update();
    virtual void        Render();

    virtual void	    OnCollision(CCollider* _pOther);
    virtual void	    OnCollisionEnter(CCollider* _pOther);
    virtual void	    OnCollisionExit(CCollider* _pOther);
};

