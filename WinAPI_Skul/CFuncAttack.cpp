#include "pch.h"
#include "CFuncAttack.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CEffect.h"
#include "CTextObj.h"
#include "CPlayer.h"

CFuncAttack::CFuncAttack(OBJ_TYPE _eType, const wstring& _strImgName, const wstring& _strImgPath,
	float _fDuration, float _fPlayTime, int _imgSize, bool _dir):
	CFuncObj(_eType,_strImgName, _strImgPath, _fDuration, _fPlayTime, _imgSize, _dir),
	m_fCurTime(0),
	m_fDuration(_fDuration)
{
	m_bIsRight = _dir;
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

	if (OBJ_TYPE::PROJECTILE == GetObjType())
	{
		m_vPos.x += m_vVelocity.x * DT;
		m_vPos.y -= m_vVelocity.y * DT;
		GetEffect()->SetPos(GetCollider()->GetFinalPos());
		if (m_bIsHit && ! m_bIsGround)
		{
			m_vVelocity.y -= 1000 * DT;
		}
	}
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

void CFuncAttack::CreateProjectile(CObject* _pObj, const wstring& _strObjName, Vec2 _vPos, Vec2 _vScale, Vec2 _vVelocity)
{
	CreateCollider();
	SetName(_strObjName);
	m_vVelocity = 0;
	if (_pObj->GetObjDir())
	{
		Vec2 vPos = Vec2(_vPos.x, _vPos.y);
		m_pCollider->SetOffsetPos(vPos);
		SetPos(_pObj->GetPos() + vPos);
		m_vVelocity += _vVelocity;
	}
	else
	{
		Vec2 vPos = Vec2(-_vPos.x, _vPos.y);
		m_pCollider->SetOffsetPos(vPos);
		SetPos(_pObj->GetPos() + vPos);
		m_vVelocity -= _vVelocity;
	}
	m_pCollider->SetScale(GetEffect()->GetScale()*2);
	GetEffect()->EffectPlay(GetPos());
}

void CFuncAttack::OnCollisionEnter(CCollider* _pOther)
{
	if (OBJ_TYPE::PROJECTILE == GetObjType())
	{
		if (m_bIsHit && _pOther->GetObj()->GetObjType() == OBJ_TYPE::TILE)
		{
			m_vVelocity = 0;
			m_bIsGround = true;
		}
		else if (!m_bIsHit)
		{
			if (_pOther->GetFinalPos().x > m_pCollider->GetFinalPos().x)
				m_vPos.x = _pOther->GetFinalPos().x + (-_pOther->GetScale().x - m_pCollider->GetScale().x) / 2 - 30;
			else
				m_vPos.x = _pOther->GetFinalPos().x + (_pOther->GetScale().x + m_pCollider->GetScale().x) / 2 + 30;
			m_vVelocity = 0;
			m_vVelocity.y += 200;
			m_bIsHit = true;
		}

	}
	if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::ENEMY_MELEE)
	{
		CPlayer* pPlayer = (CPlayer*)GetOwner();
		CTextObj* pObj = new CTextObj(OBJ_TYPE::TEXT, to_wstring(pPlayer->GetPlayerInfo().m_iDamage), TEXT_EFFECT::BOUNCE);
		pObj->SetPos((m_pCollider->GetFinalPos() + _pOther->GetFinalPos()) / 2);
		CREATEOBJECT(pObj);
		SINGLE(CSoundManager)->Play(L"Attack");
		GetEffect()->EffectPlay((m_pCollider->GetFinalPos()+ _pOther->GetFinalPos())/2);
	}

}