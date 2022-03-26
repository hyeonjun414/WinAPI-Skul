#pragma once
#include "CProjectile.h"

class CD2DImage;
class CArrow :
    public CProjectile
{
private:
    CD2DImage* m_pArrowImg;
    bool m_bCanPierce;
    bool m_bHasResistance;
    bool m_bIsStuck;
public:
    CArrow(OBJ_TYPE _eType, CObject* _pObj,
        const wstring& _strKey, const wstring& _strPath,
        float _fDuration);
    virtual ~CArrow();

    virtual void Update();
    virtual void Render();

    virtual void	OnCollision(CCollider* _pOther) {};
    virtual void	OnCollisionEnter(CCollider* _pOther);
    virtual void	OnCollisionExit(CCollider* _pOther) {};

    void    SetPierce(bool _check)      { m_bCanPierce = _check; }
    void    SetResistance(bool _check)  { m_bHasResistance = _check; }
    bool    IsPierce()                  { return m_bCanPierce; }
    bool    IsResistance()              { return m_bHasResistance; }
};

