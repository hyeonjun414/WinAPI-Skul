#pragma once
#include "CMapObject.h"
class CGate :
    public CMapObject
{
private:
    bool m_bIsActivate;
public:
    CGate(OBJ_TYPE _eType);
    virtual ~CGate();

    virtual void        Init();
    virtual void        Update();
    virtual void        Render();

    virtual void	    OnCollision(CCollider* _pOther);
    virtual void	    OnCollisionEnter(CCollider* _pOther);
    virtual void	    OnCollisionExit(CCollider* _pOther);
};

