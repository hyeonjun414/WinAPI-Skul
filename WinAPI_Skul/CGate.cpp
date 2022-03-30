#include "pch.h"
#include "CGate.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CScene.h"
#include "CPlayer.h"


CGate::CGate(OBJ_TYPE _eType):
	CMapObject(_eType)
{
	CreateAnimator();
	CD2DImage* pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Gate_Normal", L"texture\\object\\gate_normal.png");
	GetAnimator()->CreateAnimation(L"Gate_Normal_Close", pImg, Vec2(0, 0), Vec2(192, 192), Vec2(192, 0), 10.f, 1);
	GetAnimator()->CreateAnimation(L"Gate_Normal_Open", pImg, Vec2(192, 0), Vec2(192, 192), Vec2(192, 0), 0.1f, 8);

	GetAnimator()->Play(L"Gate_Normal_Close", true);
	
	CreateCollider();
	GetCollider()->SetScale(Vec2(100, 150));
	GetCollider()->SetOffsetPos(Vec2(-10, 20));
}

CGate::CGate(OBJ_TYPE _eType, GATE_TYPE _eGateType, SCENE_TYPE _nextScene):
	CMapObject(_eType),
	m_eNextScene(_nextScene),
	m_eGateType(_eGateType)
{
	Init();
}

CGate::~CGate()
{
}

void CGate::Init()
{
	switch (m_eGateType)
	{
	case GATE_TYPE::NORMAL:
	{
		CreateAnimator();
		CD2DImage* pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Gate_Normal", L"texture\\object\\gate_normal.png");
		GetAnimator()->CreateAnimation(L"Close", pImg, Vec2(0, 0), Vec2(192, 192), Vec2(192, 0), 10.f, 1);
		GetAnimator()->CreateAnimation(L"Open", pImg, Vec2(192, 0), Vec2(192, 192), Vec2(192, 0), 0.1f, 8);
		GetAnimator()->SetAllAnimOffset(Vec2(5, -118));
		GetAnimator()->Play(L"Close", true);

		CreateCollider();
		GetCollider()->SetScale(Vec2(120, 180));
		GetCollider()->SetOffsetPos(Vec2(0, -95));
		break;
	}

	case GATE_TYPE::BOSS:
	{
		CreateAnimator();
		CD2DImage* pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Gate_Boss", L"texture\\object\\gate_boss.png");
		GetAnimator()->CreateAnimation(L"Close", pImg, Vec2(0, 0), Vec2(314, 185), Vec2(314, 0), 10.f, 1);
		GetAnimator()->CreateAnimation(L"Open", pImg, Vec2(314, 0), Vec2(314, 185), Vec2(314, 0), 0.1f, 8);
		GetAnimator()->SetAllAnimOffset(Vec2(10, -173));

		GetAnimator()->Play(L"Close", true);

		CreateCollider();
		GetCollider()->SetScale(Vec2(140, 210));
		GetCollider()->SetOffsetPos(Vec2(0, -110));
		break;
	}
	
	case GATE_TYPE::PORTAL:
		break;
	}
}

void CGate::Update()
{
	if (nullptr != GetAnimator())
	{
		if (SINGLE(CGameManager)->m_iRemainEnemyCount == 0)
		{
			GetAnimator()->Play(L"Open", true);
			m_bIsActivate = true;
		}
		else
		{
			GetAnimator()->Play(L"Close", true);
			m_bIsActivate = false;
		}
		GetAnimator()->Update();
	}

	
}

void CGate::Render()
{
	ComponentRender();
}

void CGate::OnCollision(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::PLAYER)
	{
		CPlayer* pPlayer = (CPlayer*)_pOther->GetObj();
		if (KEYTAP(KEY::F) && m_bIsActivate)
		{
			SINGLE(CSceneManager)->GetCurScene()->ChangeNextScene(m_eNextScene);
			GAMEPLAY(false);
			SINGLE(CGameManager)->SetTimer(nullptr);
			SINGLE(CGameManager)->SetRemainEnemy(nullptr);
		}
		
	}
}

void CGate::OnCollisionEnter(CCollider* _pOther)
{
	if (GetGateType() == GATE_TYPE::PORTAL &&
		_pOther->GetObj()->GetObjType() == OBJ_TYPE::PLAYER)
	{
		SINGLE(CSceneManager)->GetCurScene()->ChangeNextScene(m_eNextScene);
	}
}

void CGate::OnCollisionExit(CCollider* _pOther)
{
}
