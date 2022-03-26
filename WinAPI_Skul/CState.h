#pragma once

class CState
{
public :
    virtual ~CState() {}
    virtual CState* HandleInput(CObject* _pObj) { return nullptr; }
    virtual void    Update(CObject* _pObj) {}

    virtual void    Enter(CObject* _pObj) {}
    virtual void    Exit(CObject* _pObj) {}
};

