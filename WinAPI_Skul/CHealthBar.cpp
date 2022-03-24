#include "pch.h"
#include "CHealthBar.h"
#include "CEnemy.h"
CHealthBar::CHealthBar()
{
	m_pBackImg = SINGLE(CResourceManager)->LoadD2DImage(L"HealthBarBack", L"texture\\ui\\EnemyHealthBar_Base.png");
	m_pFrameImg = SINGLE(CResourceManager)->LoadD2DImage(L"HealthBarFrame", L"texture\\ui\\EnemyHealthBar_Frame.png");
	m_pFrontImg = SINGLE(CResourceManager)->LoadD2DImage(L"HealthBarFront", L"texture\\ui\\EnemyHealthBar.png");
}

CHealthBar::~CHealthBar()
{
}

void CHealthBar::FinalUpdate()
{
	m_vFinalPos = m_pEnemy->GetPos() + m_vOffsetPos;
	m_vRenderPos = SINGLE(CCameraManager)->GetRenderPos(m_vFinalPos);
}

void CHealthBar::Render()
{
	RENDER->RenderImage(
		m_pBackImg,
		m_vRenderPos.x,
		m_vRenderPos.y,
		m_vRenderPos.x + m_vBackScale.x,
		m_vRenderPos.y + m_vBackScale.y,
		1.0f);

	RENDER->RenderImage(
		m_pFrameImg,
		m_vRenderPos.x,
		m_vRenderPos.y,
		m_vRenderPos.x + m_vBackScale.x,
		m_vRenderPos.y + m_vBackScale.y,
		1.0f);

	RENDER->RenderImage(
		m_pFrontImg,
		m_vRenderPos.x,
		m_vRenderPos.y,
		m_vRenderPos.x + m_vFrontScale.x,
		m_vRenderPos.y + m_vFrontScale.y,
		1.0f);
}
