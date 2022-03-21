#pragma once
#include "CAttack.h"
class CProjectile :
    public CAttack
{
private:
    Vec2    m_vVelocity;
    bool    m_bIsGround;
    bool    m_bIsHit;
public:
    CProjectile(OBJ_TYPE _eType, CObject* _pObj,
        const wstring& _strKey, const wstring& _strPath,
        float _fDuration);
    virtual ~CProjectile();

    virtual void Update();
    virtual void Render();
    
    void SetVelocity(Vec2 _vVelocity) { m_vVelocity = _vVelocity; }

    virtual void	OnCollision(CCollider* _pOther) {};
    virtual void	OnCollisionEnter(CCollider* _pOther);
    virtual void	OnCollisionExit(CCollider* _pOther) {};
    

};

