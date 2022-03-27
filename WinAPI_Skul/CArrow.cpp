#include "pch.h"
#include "CArrow.h"
#include "CD2DImage.h"
#include "CCollider.h"

CArrow::CArrow(OBJ_TYPE _eType, CObject* _pObj, const wstring& _strKey, const wstring& _strPath, float _fDuration):
	CProjectile(_eType, _pObj,_fDuration),
	m_bIsStuck(false)
{
	m_pArrowImg = SINGLE(CResourceManager)->LoadD2DImage(_strKey, _strPath);
	CreateCollider();
	m_pCollider->SetOffsetPos(Vec2(30, 0));
	m_pCollider->SetScale(Vec2(5, 5));
}

CArrow::~CArrow()
{
}

void CArrow::Update()
{
	m_fCurTime += DT;

	if (m_fCurTime >= m_fDuration)
		DELETEOBJECT(this);
	//if (m_vVelocity.x > 0)
	//	m_vVelocity.x -= 50 * DT;
	//if (m_vVelocity.y < 0)
	//	m_vVelocity.y += 50 * DT;
	if (!m_bIsStuck)
	{
		Vec2 velo = m_vVelocity;
		velo.Normalize();
		m_pCollider->SetOffsetPos(Vec2(velo.x * 20, velo.y * 20 -3));
		m_vPos += m_vVelocity * DT;
		m_vVelocity.y += 700 * DT;
	}

}

void CArrow::Render()
{
	Vec2 velo = m_vVelocity;
	velo.Normalize();
	float theta = atan2(velo.x, velo.y) * 57;
	LOG(to_wstring(theta));
	RENDER->RenderRotateImage(
		m_pArrowImg,
		m_vRenderPos.x - m_pArrowImg->GetWidth(),
		m_vRenderPos.y - m_pArrowImg->GetHeight(),
		m_vRenderPos.x + m_pArrowImg->GetWidth(),
		m_vRenderPos.y + m_pArrowImg->GetHeight(),
		90-theta,
		1.0f
	);
	ComponentRender();
}

void CArrow::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::TILE)
	{
		m_bIsStuck = true;
		if (abs(m_vVelocity.x) >= 2000)
			m_pArrowImg = SINGLE(CResourceManager)->LoadD2DImage(L"Arrow_Completed_Stuck", L"texture\\player\\hunter\\Hunter_Attack_Completed_Projectile_Stuck.png");
		else
			m_pArrowImg = SINGLE(CResourceManager)->LoadD2DImage(L"Arrow_Incompleted_Stuck", L"texture\\player\\hunter\\Hunter_Attack_Incompleted_Projectile_Stuck.png");
		if (GetName() == L"ArrowRain")
		{
			SINGLE(CGameManager)->CreateVfx(L"ArrowRain_Spark", L"texture\\effect\\Hunter_ArrowRain_Spark.png",
				m_pCollider->GetFinalPos() + Vec2(0, -70), 1.f, 1.f, rand() % 2);
			m_fDuration = m_fCurTime + 1.f;
		}
	}
	if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::ENEMY)
	{
		m_bIsStuck = true;
		if (abs(m_vVelocity.x) >= 2000)
			m_pArrowImg = SINGLE(CResourceManager)->LoadD2DImage(L"Arrow_Completed_Stuck", L"texture\\player\\hunter\\Hunter_Attack_Completed_Projectile_Stuck.png");
		else
			m_pArrowImg = SINGLE(CResourceManager)->LoadD2DImage(L"Arrow_Incompleted_Stuck", L"texture\\player\\hunter\\Hunter_Attack_Incompleted_Projectile_Stuck.png");
		m_fDuration = m_fCurTime + 1.f;
		if (GetName() == L"ArrowRain")
		{
			SINGLE(CGameManager)->CreateVfx(L"ArrowRain_Spark", L"texture\\effect\\Hunter_ArrowRain_Spark.png",
				m_pCollider->GetFinalPos() + Vec2(0, -70), 1.f, 1.f, rand() % 2);
			m_fDuration = m_fCurTime + 1.f;
		}
	}

}
