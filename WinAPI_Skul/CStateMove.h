#pragma once
#include "CState.h"

class CStateMove :
    public CState
{
private:
    bool m_bIsFloor;
public:
    CStateMove(){}

    virtual CState* HandleInput(CObject* _pObj);
    virtual void    Update(CObject* _pObj);

    virtual void    Enter(CObject* _pObj);
    virtual void    Exit(CObject* _pObj);


};

