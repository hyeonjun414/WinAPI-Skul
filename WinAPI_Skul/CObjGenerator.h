#pragma once
#include "CObject.h"

class CObject;
class CEffect;

class CObjGenerator :
    public CObject
{
private:
    vector<CObject*>    m_vecObject;
    vector<CEffect*>    m_vecVfx;
    vector<CEffect*>    m_vecSfx;
    float               m_fDelayTime;
    float               m_fCurTime;
    Vec2                m_vGenerateArea;

    float               m_fReservTime;

public:
    CObjGenerator(float _delay, Vec2 _pos, Vec2 _areasize, float _reservTime = 0.f);
    virtual ~CObjGenerator();

    virtual void	Init();
    virtual void	Update();

    void            ReserveObj(CObject* _pObj) { m_vecObject.push_back(_pObj); }
    void            ReserveVfx(CEffect* _pEft) { m_vecVfx.push_back(_pEft); }
    void            ReserveSfx(CEffect* _pEft) { m_vecVfx.push_back(_pEft); }
};

