#include "pch.h"
#include "CHealthBar.h"
#include "CEnemy.h"
#include "CD2DImage.h"
CHealthBar::CHealthBar()
{
	m_pFrameImg = SINGLE(CResourceManager)->LoadD2DImage(L"HealthBarFrame", L"texture\\ui\\EnemyHealthBar_Frame_img.png");
	m_pFrontImg = SINGLE(CResourceManager)->LoadD2DImage(L"HealthBarFront", L"texture\\ui\\EnemyHealthBar.png");
	m_vOffsetPos = Vec2(-m_pFrameImg->GetWidth(), 25);
	m_vBackScale = Vec2(m_pFrameImg->GetWidth() * 2, m_pFrameImg->GetHeight() * 2);
	m_vFrontScale = Vec2(m_pFrameImg->GetWidth()*2 - 4, m_pFrameImg->GetHeight() * 2 -4);
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
		m_pFrameImg,
		m_vRenderPos.x,
		m_vRenderPos.y,
		m_vRenderPos.x + m_vBackScale.x,
		m_vRenderPos.y + m_vBackScale.y,
		1.0f);

	RENDER->RenderImage(
		m_pFrontImg,
		m_vRenderPos.x+2,
		m_vRenderPos.y+2,
		m_vRenderPos.x+2 + m_vFrontScale.x,
		m_vRenderPos.y+2 + m_vFrontScale.y,
		1.0f);
}
