#pragma once
#include "CObject.h"

class CState;

class CEnemy :
    public CObject
{
protected:
    Vec2        m_vVelocity;
    int         m_iHp;
    int         m_iDamage;
    int         m_iDetectDist;

    ENEMY_TYPE  m_eEnemyType;
    CState*     m_pState;

public:
    CEnemy(OBJ_TYPE _eType, ENEMY_TYPE _eMonsterType);
    virtual ~CEnemy();

    virtual void        Init();
    virtual void        Update();
    virtual void        Render();

    ENEMY_TYPE          GetEnemyType()  { return m_eEnemyType; }
};

