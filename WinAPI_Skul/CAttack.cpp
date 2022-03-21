#include "pch.h"
#include "CAttack.h"

CAttack::CAttack(OBJ_TYPE _eType, CObject* _pObj, float _fDuration):
	CObject(_eType),
	m_pOwner(_pObj),
	m_fCurTime(0.f),
	m_fDuration(_fDuration)
{
}

CAttack::~CAttack()
{
}
