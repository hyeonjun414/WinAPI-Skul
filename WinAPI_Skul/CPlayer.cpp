#include "pch.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CPlayerState.h"
#include "CSPlayerIdle.h"

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(OBJ_TYPE _objGroup) :
	CObject(_objGroup)
{
	m_bIsFloor = false;
	m_bIsJumping = false;
	m_bIsRight = true;
	m_iCollCount = 0;

	SetScale(Vec2(96, 96));
	// Collider 만들기
	CreateCollider();
	m_pCollider->SetOffsetPos(Vec2(0, -GetScale().y/4));
	m_pCollider->SetScale(Vec2(GetScale()/2));

	CreateAnimator();
	CD2DImage* pImg;
	// 애니메이터 만들기
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_Idle", L"texture\\player\\idle_skul.png");
	GetAnimator()->CreateAnimation(L"Player_Idle", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),
									Vec2(96, 0.f), 0.15f, 4);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_Move", L"texture\\player\\move_skul.png");
	GetAnimator()->CreateAnimation(L"Player_Move", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),
									Vec2(96, 0.f), 0.1f, 8);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_Jump", L"texture\\player\\jump_skul.png");
	GetAnimator()->CreateAnimation(L"Player_Jump", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),
									Vec2(96, 0.f), 0.1f, 2);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_Fall", L"texture\\player\\fall_skul.png");
	GetAnimator()->CreateAnimation(L"Player_Fall", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),
									Vec2(96, 0.f), 0.5f, 2);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_FallRepeat", L"texture\\player\\fallrepeat_skul.png");
	GetAnimator()->CreateAnimation(L"Player_FallRepeat", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),
									Vec2(96, 0.f), 0.2f, 3);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_AttackA", L"texture\\player\\attackA_skul.png");
	GetAnimator()->CreateAnimation(L"Player_AttackA", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),
		Vec2(96, 0.f), 0.1f, 5);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_AttackB", L"texture\\player\\attackB_skul.png");
	GetAnimator()->CreateAnimation(L"Player_AttackB", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),
		Vec2(96, 0.f), 0.125f, 4);


	GetAnimator()->Play(L"Player_Idle", true);

	// 애니메이터의 모든 애니메이션의 오프셋을 조절한다.
	m_pAnimator->SetAllAnimOffset(Vec2(0,30));

	m_pState = new CSPlayerIdle();

}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
}

void CPlayer::Update()
{
	m_pState->HandleInput(this);
	m_pState->Update(this);
	if (m_bIsGravity && !m_bIsFloor) m_vVelocity.y -= 700 * DT;
	m_vPos.y += -m_vVelocity.y * DT;
	
	if (m_vVelocity.y > 0)
	{
		m_bIsJumping = true;
		GetAnimator()->Play(L"Player_Jump", true);
	}
	else
	{
		if (m_vVelocity.y < -1)
		{
			GetAnimator()->Play(L"Player_Fall", true);
		}
		if(m_vVelocity.y < -200)
		{
			GetAnimator()->Play(L"Player_FallRepeat", true);
		}
		m_bIsJumping = false;
	}
	//if (KEYCHECK(KEY::A) == KEY_STATE::HOLD)
	//{
	//	// 왼쪽
	//	m_vPos.x -= 300 * DT;
	//	m_bIsRight = false;
	//	if (m_bIsFloor && !m_bIsJumping)
	//		GetAnimator()->Play(L"Player_Move", true);
	//}
	//if (KEYCHECK(KEY::A) == KEY_STATE::AWAY)
	//{
	//	m_bIsRight = false;
	//	if (m_bIsFloor && !m_bIsJumping)
	//		GetAnimator()->Play(L"Player_Idle", true);
	//}
	//if (KEYCHECK(KEY::D) == KEY_STATE::HOLD)
	//{
	//	// 오른쪽
	//	m_vPos.x += 300 * DT;
	//	m_bIsRight = true;
	//	if(m_bIsFloor && !m_bIsJumping)
	//		GetAnimator()->Play(L"Player_Move", true);
	//}
	//if (KEYCHECK(KEY::D) == KEY_STATE::AWAY)
	//{
	//	m_bIsRight = true;
	//	if (m_bIsFloor && !m_bIsJumping)
	//		GetAnimator()->Play(L"Player_Idle", true);
	//}

	if (KEYCHECK(KEY::SPACE) == KEY_STATE::TAP && m_bIsFloor)
	{
		m_vVelocity.y += 500;

	}
	if (KEYTAP(KEY::X))
	{
		GetAnimator()->PlayAndNextAnim(L"Player_AttackA", false, L"Player_Idle");

	}
	if (KEYTAP(KEY::C))
	{
		GetAnimator()->PlayAndNextAnim(L"Player_AttackB", false, L"Player_Idle");

	}

	GetAnimator()->Update();
}

void CPlayer::Render()
{
	ComponentRender();
}

void CPlayer::OnCollision(CCollider* _pOther)
{
	if (_pOther->GetObj()->GetObjGroup() == OBJ_TYPE::TILE &&
		m_vPos.y > _pOther->GetFinalPos().y)
	{
		if (m_vPos.x < _pOther->GetFinalPos().x)
			m_vPos.x = _pOther->GetFinalPos().x - _pOther->GetScale().x / 2 - m_pCollider->GetScale().x / 2;
		else
			m_vPos.x = _pOther->GetFinalPos().x + _pOther->GetScale().x / 2 + m_pCollider->GetScale().x / 2;
	}
}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	m_iCollCount++;
	if (_pOther->GetObj()->GetObjGroup() == OBJ_TYPE::TILE && !m_bIsJumping && m_iCollCount == 1 &&
		m_vPos.y < _pOther->GetFinalPos().y)
	{

		LOG(L"바닥 충돌");
		
		m_vVelocity.y = 0;

		m_vPos.y = _pOther->GetFinalPos().y - _pOther->GetScale().y / 2 + 1;
		m_bIsFloor = true;
		GetAnimator()->Play(L"Player_Idle", true);
	}
}

void CPlayer::OnCollisionExit(CCollider* _pOther)
{
	m_iCollCount--;
	if (_pOther->GetObj()->GetObjGroup() == OBJ_TYPE::TILE && m_iCollCount == 0 &&
		m_vPos.y < _pOther->GetFinalPos().y)
	{

		LOG(L"바닥 충돌 해제");
		
		m_bIsFloor = false;
	}
}

