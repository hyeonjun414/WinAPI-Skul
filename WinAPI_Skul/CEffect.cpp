#include "pch.h"
#include "CEffect.h"

CEffect::CEffect(wstring _strKey, float _fDuration):
	CObject(OBJ_TYPE::EFFECT),
	m_fCurTime(0),
	m_fDuration(_fDuration),
	m_strKey(_strKey)
{
}

CEffect::~CEffect() { }
