#include "pch.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

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


	// �ؽ��� �ҷ�����
	//m_pTex = SINGLE(CResourceManager)->LoadTexture(L"PlayerTex", L"texture\\monster01.bmp");
	SetScale(Vec2(90, 90));
	// Collider �����
	CreateCollider();
	m_pCollider->SetOffsetPos(Vec2(0, -5));
	m_pCollider->SetScale(Vec2(GetScale().x/2, 10));

	// �ִϸ����� �����
	CD2DImage* m_pTexture = SINGLE(CResourceManager)->LoadD2DImage(L"PlayerTex", L"texture\\skul_Animation.png");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Player_Idle_Right", m_pTexture, Vec2(1.f, 1.f), Vec2(90.f, 90.f),
									Vec2(91.f, 0.f), 0.15f, 8);
	GetAnimator()->CreateAnimation(L"Player_Idle_Left", m_pTexture, Vec2(1.f, 92.f), Vec2(90.f, 90.f),
									Vec2(91.f, 0.f), 0.15f, 8);
	GetAnimator()->CreateAnimation(L"Player_Move_Right", m_pTexture, Vec2(1.f, 183.f), Vec2(90.f, 90.f),
									Vec2(91.f, 0.f), 0.1f, 8);
	GetAnimator()->CreateAnimation(L"Player_Move_Left", m_pTexture, Vec2(1.f, 274.f), Vec2(90.f, 90.f),
									Vec2(91.f, 0.f), 0.1f, 8);
	GetAnimator()->CreateAnimation(L"Player_Jump_Right", m_pTexture, Vec2(1.f, 365.f), Vec2(90.f, 90.f),
									Vec2(91.f, 0.f), 0.1f, 2);
	GetAnimator()->CreateAnimation(L"Player_Jump_Left", m_pTexture, Vec2(183.f, 365.f), Vec2(90.f, 90.f),
									Vec2(91.f, 0.f), 0.1f, 2);
	GetAnimator()->CreateAnimation(L"Player_Fall_Right", m_pTexture, Vec2(1.f, 456.f), Vec2(90.f, 90.f),
									Vec2(91.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"Player_Fall_Left", m_pTexture, Vec2(183.f, 456.f), Vec2(90.f, 90.f),
									Vec2(91.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"Player_Fall2_Right", m_pTexture, Vec2(1.f, 547.f), Vec2(90.f, 90.f),
									Vec2(91.f, 0.f), 0.2f, 3);
	GetAnimator()->CreateAnimation(L"Player_Fall2_Left", m_pTexture, Vec2(274.f, 547.f), Vec2(90.f, 90.f),
									Vec2(91.f, 0.f), 0.2f, 3);

	GetAnimator()->Play(L"Player_Idle_Right", true);

	// �ִϸ������� ��� �ִϸ��̼��� �������� �����Ѵ�.
	m_pAnimator->SetAllAnimOffset();

}

CPlayer::~CPlayer()
{
	delete m_pAnimator;
}

void CPlayer::Init()
{
}

void CPlayer::Update()
{
	if (m_bIsGravity && !m_bIsFloor) m_vVelocity.y -= 700 * DT;
	m_vPos.y += -m_vVelocity.y * DT;
	
	if (m_vVelocity.y > 0)
	{
		m_bIsJumping = true;
		if (m_bIsRight)
			GetAnimator()->Play(L"Player_Jump_Right", true);
		else
			GetAnimator()->Play(L"Player_Jump_Left", true);
	}
	else
	{
		if (m_vVelocity.y < -1)
		{
			if (m_bIsRight)
				GetAnimator()->Play(L"Player_Fall_Right", true);
			else
				GetAnimator()->Play(L"Player_Fall_Left", true);
		}
		if(m_vVelocity.y < -200)
		{
			if (m_bIsRight)
				GetAnimator()->Play(L"Player_Fall2_Right", true);
			else
				GetAnimator()->Play(L"Player_Fall2_Left", true);
		}
		m_bIsJumping = false;
	}
	if (KEYCHECK(KEY::A) == KEY_STATE::HOLD)
	{
		// ����
		m_vPos.x -= 300 * DT;
		m_bIsRight = false;
		if (m_bIsFloor && !m_bIsJumping)
			GetAnimator()->Play(L"Player_Move_Left", true);
	}
	if (KEYCHECK(KEY::A) == KEY_STATE::AWAY)
	{
		m_bIsRight = false;
		if (m_bIsFloor && !m_bIsJumping)
			GetAnimator()->Play(L"Player_Idle_Left", true);
	}
	if (KEYCHECK(KEY::D) == KEY_STATE::HOLD)
	{
		// ������
		m_vPos.x += 300 * DT;
		m_bIsRight = true;
		if(m_bIsFloor && !m_bIsJumping)
			GetAnimator()->Play(L"Player_Move_Right", true);
	}
	if (KEYCHECK(KEY::D) == KEY_STATE::AWAY)
	{
		m_bIsRight = true;
		if (m_bIsFloor && !m_bIsJumping)
			GetAnimator()->Play(L"Player_Idle_Right", true);
	}

	if (KEYCHECK(KEY::SPACE) == KEY_STATE::TAP && m_bIsFloor)
	{
		m_vVelocity.y += 500;

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
	if (_pOther->GetObj()->GetObjGroup() == OBJ_TYPE::TILE && !m_bIsJumping && m_iCollCount == 1)
	{

		LOG(L"�ٴ� �浹");
		
		m_vVelocity.y = 0;

		m_vPos.y = _pOther->GetFinalPos().y - _pOther->GetScale().y / 2 + 1;
		m_bIsFloor = true;
		if (m_bIsRight)
			GetAnimator()->Play(L"Player_Idle_Right", true);
		else
			GetAnimator()->Play(L"Player_Idle_Left", true);
	}
}

void CPlayer::OnCollisionExit(CCollider* _pOther)
{
	m_iCollCount--;
	if (_pOther->GetObj()->GetObjGroup() == OBJ_TYPE::TILE && m_iCollCount == 0)
	{

		LOG(L"�ٴ� �浹 ����");
		
		m_bIsFloor = false;
	}
}

