#pragma once
#include "CEnemyState.h"
class CEnemyStateDie :
    public CEnemyState
{
private:
    float m_fCurTime;   // 오브젝트가 죽은 상태에 진입한 이후의 시간
    float m_fDuration;  // 오브젝트를 제거시키기까지의 시간
public:
    virtual ~CEnemyStateDie() {}

    virtual CEnemyState* HandleInput(CObject* _pObj);
    virtual void Update(CObject* _pObj);

    virtual void Enter(CObject* _pObj);
    virtual void Exit(CObject* _pObj);


};

