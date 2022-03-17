#include "pch.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CState.h"
#include "CStateIdle.h"

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(OBJ_TYPE _objGroup) :
	CObject(_objGroup)
{
	m_bIsGround = false;
	m_bIsJumping = false;
	m_bIsRight = true;
	m_iCollCount = 0;
	m_vVelocity = Vec2(300, 0);

	m_bCanDoubleJump = false;
	m_bCanSecondDash = true;

	m_fDashRechargeTime = 2.f;
	m_fDashRehargeCurTime = 0.f;

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

	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_Dash", L"texture\\player\\dash_skul.png");
	GetAnimator()->CreateAnimation(L"Player_Dash", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),
		Vec2(96, 0.f), 1.0f, 1);
	pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Player_JumpAttack", L"texture\\player\\jumpattack_skul.png");
	GetAnimator()->CreateAnimation(L"Player_JumpAttack", pImg, Vec2(0.f, 0.f), Vec2(96.f, 96.f),
		Vec2(96, 0.f), 0.125f, 4);



	// 애니메이터의 모든 애니메이션의 오프셋을 조절한다.
	m_pAnimator->SetAllAnimOffset(Vec2(0,30));

	m_pState = new CStateIdle();
	m_pState->Enter(this);

	SINGLE(CSoundManager)->AddSound(L"Jump", L"sound\\Default_Jump.wav", false);
	SINGLE(CSoundManager)->AddSound(L"JumpAir", L"sound\\Default_Jump_Air.wav", false);
	SINGLE(CSoundManager)->AddSound(L"AttackA", L"sound\\Legacy_AttackA.wav", false);
	SINGLE(CSoundManager)->AddSound(L"AttackB", L"sound\\Legacy_AttackB.wav", false);
	SINGLE(CSoundManager)->AddSound(L"Dash", L"sound\\Default_Dash.wav", false);



}

CPlayer::~CPlayer()
{
	delete m_pState;

	if (nullptr != SINGLE(CCameraManager)->GetTarget())
	{
		SINGLE(CCameraManager)->SetTarget(nullptr);
	}
}

void CPlayer::Init()
{
}

void CPlayer::Update()
{
	CState* pState = m_pState->HandleInput(this);
	if (nullptr != pState)
	{
		m_pState->Exit(this);
		delete m_pState;
		m_pState = pState;
		m_pState->Enter(this);
	}

	m_pState->Update(this);

	// 모든 상태에서 계산되어야하는 부분은 이부분에서 처리한다.
	// 만약 세컨드대시가 비활성화된 경우 재충전을 시작한다.
	if (!m_bCanSecondDash && m_bIsGround)
	{
		m_fDashRehargeCurTime += DT;
		if (m_fDashRehargeCurTime >= m_fDashRechargeTime)
			m_bCanSecondDash = true;
	}

	GetAnimator()->Update();
}

void CPlayer::Render()
{
	ComponentRender();
}

void CPlayer::OnCollision(CCollider* _pOther)
{
	//m_pState->OnCollision(this, _pOther);

    CPlayer* pPlayer = (CPlayer*)this;
    if (_pOther->GetObj()->GetObjGroup() == OBJ_TYPE::TILE)
    {
        Vec2 pos1 = m_pCollider->GetFinalPos();
        Vec2 pos2 = _pOther->GetFinalPos();
        Vec2 size1 = m_pCollider->GetScale();
        Vec2 size2 = _pOther->GetScale();
        if (pos2.y - size2.y / 2 <= pos1.y && pos1.y <= pos2.y + size2.y / 2)
        {
            if (pos1.x <= pos2.x - size2.x / 2)
            {
                pPlayer->m_vPos.x = pos2.x + (-size1.x - size2.x) / 2;
            }
            else if (pos1.x >= pos2.x + size2.x / 2)
            {
                pPlayer->m_vPos.x = pos2.x + (size1.x + size2.x) / 2;

            }
        }
    }
}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	//m_pState->OnCollisionEnter(this, _pOther);
    CPlayer* pPlayer = (CPlayer*)this;
    if (_pOther->GetObj()->GetObjGroup() == OBJ_TYPE::TILE)
    {
		Vec2 vLeftPos = m_pCollider->GetFinalPos();
		Vec2 vLeftScale = m_pCollider->GetScale();
		Vec2 vRightPos = _pOther->GetFinalPos();
		Vec2 vRightScale = _pOther->GetScale();
		pPlayer->m_iCollCount++;
		if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x-3) / 2.f)
		{
			
			if (pPlayer->m_iCollCount > 0)
			{
				pPlayer->m_bIsGround = true;
				m_bCanDoubleJump = true;
			}
		}


    }
}

void CPlayer::OnCollisionExit(CCollider* _pOther)
{
	//m_pState->OnCollisionExit(this, _pOther);

    CPlayer* pPlayer = (CPlayer*)this;
    if (_pOther->GetObj()->GetObjGroup() == OBJ_TYPE::TILE)
    {
		pPlayer->m_iCollCount--;
		if (pPlayer->m_iCollCount <= 0)
		{
			pPlayer->m_iCollCount = 0;
			pPlayer->m_bIsGround = false;
		}

    }
}

