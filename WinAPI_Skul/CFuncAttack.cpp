#include "pch.h"
#include "CFuncAttack.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CEffect.h"
#include "CTextObj.h"

CFuncAttack::CFuncAttack(OBJ_TYPE _eType, wstring _strImgName, wstring _strImgPath,
	float _fDuration, float _fPlayTime, int _imgSize, bool _dir):
	CFuncObj(_eType,_strImgName, _strImgPath, _fDuration, _fPlayTime, _imgSize, _dir),
	m_fCurTime(0),
	m_fDuration(_fDuration)
{
	CreateEffect(_strImgName, _strImgPath, _fDuration, _fPlayTime, _imgSize, _dir);
}

CFuncAttack::~CFuncAttack()
{
}

void CFuncAttack::Update()
{
	m_fCurTime += DT;

	if (m_fCurTime >= m_fDuration)
		DELETEOBJECT(this);
}

void CFuncAttack::Render()
{
	ComponentRender();
}




void CFuncAttack::CreateAttackArea(CObject* _pObj, Vec2 _vPos, Vec2 _vScale)
{
	CreateCollider();
	SetPos(_pObj->GetPos());
	m_pCollider->SetOffsetPos(Vec2(0, -_pObj->GetScale().y / 4));
	if (_pObj->GetObjDir())
	{
		m_pCollider->SetOffsetPos(Vec2(_vPos.x, -_pObj->GetScale().y / 4));
	}
	else
	{
		m_pCollider->SetOffsetPos(Vec2(-_vPos.x, -_pObj->GetScale().y / 4));
	}

	m_pCollider->SetScale(_vScale);
}

void CFuncAttack::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::ENEMY_MELEE)
	{
		CTextObj* pObj = new CTextObj(OBJ_TYPE::TEXT, L"1010", TEXT_EFFECT::BOUNCE);
		pObj->SetPos((m_pCollider->GetFinalPos() + _pOther->GetFinalPos()) / 2);
		CREATEOBJECT(pObj);
		SINGLE(CSoundManager)->Play(L"Attack");
		GetEffect()->EffectPlay((m_pCollider->GetFinalPos()+ _pOther->GetFinalPos())/2);
	}
}