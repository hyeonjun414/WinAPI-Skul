#include "pch.h"
#include "CGate.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "CCollider.h"
#include "CScene.h"
#include "CPlayer.h"

CGate::CGate()
{
}

CGate::CGate(OBJ_TYPE _eType):
	CMapObject(_eType)
{
	SetPos(Vec2(250, 1105));

	CreateAnimator();
	CD2DImage* pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Gate_Normal", L"texture\\object\\gate_normal.png");
	GetAnimator()->CreateAnimation(L"Gate_Normal_Close", pImg, Vec2(0, 0), Vec2(192, 192), Vec2(192, 0), 10.f, 1);
	GetAnimator()->CreateAnimation(L"Gate_Normal_Open", pImg, Vec2(192, 0), Vec2(192, 192), Vec2(192, 0), 0.1f, 8);

	GetAnimator()->Play(L"Gate_Normal_Open", true);
	
	CreateCollider();
	GetCollider()->SetScale(Vec2(100, 150));
	GetCollider()->SetOffsetPos(Vec2(-10, 20));
}

CGate::~CGate()
{
}

void CGate::Init()
{
}

void CGate::Update()
{
	GetAnimator()->Update();
}

void CGate::Render()
{
	ComponentRender();
}

void CGate::OnCollision(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetObjGroup() == OBJ_TYPE::PLAYER)
	{
		CPlayer* pPlayer = (CPlayer*)_pOther->GetObj();
		if (KEYTAP(KEY::F))
		{
			SINGLE(CSceneManager)->GetCurScene()->ChangeNextScene(SCENE_TYPE::START);
			SINGLE(CSoundManager)->Stop(L"Ch1Bgm");
			pPlayer->SetVelocity(Vec2(0, 0));
			pPlayer->SetIsGround(true);
			GAMEPLAY(false);
		}
	}
}

void CGate::OnCollisionEnter(CCollider* _pOther)
{
}

void CGate::OnCollisionExit(CCollider* _pOther)
{
}
