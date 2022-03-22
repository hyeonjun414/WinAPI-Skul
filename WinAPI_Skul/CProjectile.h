#pragma once
#include "CAttack.h"
class CProjectile :
    public CAttack
{
private:
    Vec2    m_vVelocity;
    bool    m_bIsGround;
    bool    m_bIsHit;
    bool    m_bIsMove;

    float   m_fDalayTime;
    float   m_fTraceTime;
    float   m_fCurTime;
public:
    CProjectile(OBJ_TYPE _eType, CObject* _pObj,
        const wstring& _strKey, const wstring& _strPath,
        float _fDuration);
    virtual ~CProjectile();

    virtual void Update();
    virtual void Render();

    virtual void	OnCollision(CCollider* _pOther) {};
    virtual void	OnCollisionEnter(CCollider* _pOther);
    virtual void	OnCollisionExit(CCollider* _pOther) {};

    void SetVelocity(Vec2 _vVelocity) { m_vVelocity = _vVelocity; }

    void Move(Vec2 _vVelocity, float _fDelay = 0.f );
    void Stop(float _fDelay = 0.f);
    void Trace(CObject* _pObj, Vec2 _vVelocity, float _fTraceTime = 0.f);
    

};

