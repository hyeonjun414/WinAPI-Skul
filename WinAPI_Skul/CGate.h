#pragma once
#include "CMapObject.h"
class CGate :
    public CMapObject
{
private:
    bool m_bIsActivate;
    SCENE_TYPE m_eNextScene;
    GATE_TYPE m_eGateType;

public:
    CGate(OBJ_TYPE _eType);
    CGate(OBJ_TYPE _eType, GATE_TYPE _eGateType, SCENE_TYPE _nextScene);
    virtual ~CGate();

    virtual void        Init();
    virtual void        Update();
    virtual void        Render();

    virtual void	    OnCollision(CCollider* _pOther);
    virtual void	    OnCollisionEnter(CCollider* _pOther);
    virtual void	    OnCollisionExit(CCollider* _pOther);

    void                SetNextScene(SCENE_TYPE _eType) { m_eNextScene = _eType; }
    GATE_TYPE           GetGateType()                   { return m_eGateType; }
};

