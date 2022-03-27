#include "pch.h"
#include "CBorn.h"
#include "CD2DImage.h"
#include "CCollider.h"

CBorn::CBorn(SKUL_TYPE _eType):
	CItem(),
	m_eSkulType(_eType),
	m_pImg(nullptr)
{
	Init();
}

CBorn::~CBorn()
{
}

void CBorn::Init()
{
	switch (m_eSkulType)
	{
	case SKUL_TYPE::Little_Born:
		m_pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Little_Born", L"texture\\object\\Hunter_Head.png");
		break;
	case SKUL_TYPE::Hunter:
		m_pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Hunter_Born", L"texture\\object\\Hunter_Head.png");
		break;
	}

	SetScale(Vec2(m_pImg->GetWidth(), m_pImg->GetHeight()));
	CreateCollider();
	m_pCollider->SetScale(Vec2(200, 100));

	m_fCurTime = 1.f;
	m_iDir = -2;
}

void CBorn::Update()
{
	m_fCurTime -= DT;

	if (m_vVelocity.y < -50.f)
		m_iDir = 2;
	if (m_vVelocity.y > 50.f)
		m_iDir = -2;

	m_vVelocity.y += m_iDir;
	m_vPos += m_vVelocity * DT;
}

void CBorn::Render()
{
	RENDER->RenderImage(
		m_pImg,
		m_vRenderPos.x - m_vScale.x,
		m_vRenderPos.y - m_vScale.y,
		m_vRenderPos.x + m_vScale.x,
		m_vRenderPos.y + m_vScale.y,
		1.0f
		);
	ComponentRender();
}

void CBorn::OnCollision(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::PLAYER)
	{
		if (KEYTAP(KEY::F))
		{
			Use();
		}
	}
}

void CBorn::OnCollisionEnter(CCollider* _pOther)
{

}

void CBorn::Use()
{
	SINGLE(CGameManager)->AddSkul(m_eSkulType);
	DELETEOBJECT(this);
}
