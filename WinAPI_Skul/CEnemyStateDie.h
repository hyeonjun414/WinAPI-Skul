#pragma once
#include "CEnemyState.h"
class CEnemyStateDie :
    public CEnemyState
{
private:
    float m_fCurTime;   // ������Ʈ�� ���� ���¿� ������ ������ �ð�
    float m_fDuration;  // ������Ʈ�� ���Ž�Ű������� �ð�
public:
    virtual ~CEnemyStateDie() {}

    virtual CEnemyState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);


};

