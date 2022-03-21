#pragma once
#include "CAttack.h"
class CMeleeAttack :
    public CAttack
{
public:
	CMeleeAttack(OBJ_TYPE _eType, CObject* _pObj, float _fDuration);
	virtual ~CMeleeAttack();

	virtual void	Update();
	virtual void	Render();

	virtual void	OnCollision(CCollider* _pOther) {};
	virtual void	OnCollisionEnter(CCollider* _pOther);
	virtual void	OnCollisionExit(CCollider* _pOther) {};

	void			CreateAttackArea(CObject* _pObj, Vec2 _vPos, Vec2 _vScale);
};

