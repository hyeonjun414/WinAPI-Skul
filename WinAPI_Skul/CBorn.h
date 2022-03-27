#pragma once
#include "CItem.h"

class CD2DImage;

class CBorn :
    public CItem
{
    SKUL_TYPE   m_eSkulType;
    CD2DImage*  m_pImg;

    Vec2        m_vVelocity;
    float       m_fCurTime;
    int         m_iDir;
public:
    CBorn(SKUL_TYPE _eType);
    virtual ~CBorn();

    virtual void Init();
    virtual void Update();
    virtual void Render();

    virtual void	OnCollision(CCollider* _pOther);
    virtual void	OnCollisionEnter(CCollider* _pOther);
    virtual void	OnCollisionExit(CCollider* _pOther) {};

    virtual void Use();
};

