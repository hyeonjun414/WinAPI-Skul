#pragma once
#include "CObject.h"
class CMonster :
    public CObject
{
private:
    
public:
    CMonster();
    CMonster(OBJ_TYPE _objGroup);
    virtual ~CMonster();

    virtual void        Init();
    virtual void        Update();
    virtual void        Render();

    virtual void	    OnCollision(CCollider* _pOther);
    virtual void	    OnCollisionEnter(CCollider* _pOther);
    virtual void	    OnCollisionExit(CCollider* _pOther);
};

