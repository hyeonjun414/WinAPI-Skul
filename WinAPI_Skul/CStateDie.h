#pragma once
#include "CState.h"
class CStateDie :
    public CState
{
private:
    float m_fCurTime;   // ������Ʈ�� ���� ���¿� ������ ������ �ð�
    float m_fDuration;  // ������Ʈ�� ���Ž�Ű������� �ð�
public:
    CStateDie() {}

    virtual CState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);


};

