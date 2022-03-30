#include "pch.h"
#include "CPlayer.h"
#include "CScene.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CState.h"
#include "CPlayerStateIdle.h"
#include "CTile.h"
#include "CProjectile.h"
#include "CMeleeAttack.h"
#include "CAttack.h"
#include "CEnemy.h"
#include "CUIImage.h"
#include "CUIText.h"

CPlayer::CPlayer(OBJ_TYPE _objGroup) :
	CObject(_objGroup)
{
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
	if (!IsActive()) return;
	CState* pState = m_pState->HandleInput(this);
	if (nullptr != pState)
	{
		m_pState->Exit(this);
		delete m_pState;
		m_pState = pState;
		m_pState->Enter(this);
	}

	m_pState->Update(this);
	CoolTime();
	GetAnimator()->Update();
}

void CPlayer::Render()
{
	if (!IsActive()) return;
	ComponentRender();
	RenderPlayerInfo();
}

void CPlayer::OnCollision(CCollider* _pOther)
{
    if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::TILE )
    {
		CTile* pTile = (CTile*)_pOther->GetObj();
		if (pTile->GetType() == TILE_TYPE::FLOATING) return;
        Vec2 pos1 = m_pCollider->GetFinalPos();
        Vec2 pos2 = _pOther->GetFinalPos();
        Vec2 size1 = m_pCollider->GetScale();
        Vec2 size2 = _pOther->GetScale();
        if (pos2.y - size2.y / 2 <= pos1.y && pos1.y <= pos2.y + size2.y / 2)
        {
            if (pos1.x <= pos2.x - size2.x / 2)
            {
				m_vPos.x = pos2.x + (-size1.x - size2.x) / 2;//Player->m_vVelocity.x* DT;
            }
            else if (pos1.x >= pos2.x + size2.x / 2)
            {
				m_vPos.x = pos2.x + (size1.x + size2.x) / 2;//Player->m_vVelocity.x* DT;

            }
        }

    }
}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
    CPlayer* pPlayer = (CPlayer*)this;
    if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::TILE)
    {
		CTile* tile = (CTile*)_pOther->GetObj();
		Vec2 vLeftPos = m_pCollider->GetFinalPos();
		Vec2 vLeftScale = m_pCollider->GetScale();
		Vec2 vRightPos = _pOther->GetFinalPos();
		Vec2 vRightScale = _pOther->GetScale();
		pPlayer->m_iCollCount++;
		if (TILE_TYPE::CEILING == tile->GetType())
			m_vVelocity.y = 0;
		if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x-10) / 2.f)
		{
			
			if (pPlayer->m_iCollCount > 0 && 
				vLeftPos.y <= vRightPos.y - vRightScale.x/2)
			{
				pPlayer->m_bIsGround = true;
				m_bCanJumpAttack = true;
				m_bCanDoubleJump = true;
				m_vVelocity.y = 0;
				m_vPos.y = _pOther->GetFinalPos().y - _pOther->GetScale().y / 2 + 1;
			}
		}
    }
	if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::MELEE_ATTACK)
	{
		CAttack* pAttack = (CAttack*)_pOther->GetObj();
		CEnemy* pEnemy = (CEnemy*)pAttack->GetOwner();
		SINGLE(CSoundManager)->Play(L"Hit");
		SINGLE(CGameManager)->CreateVfx(L"Hit", L"texture\\effect\\hit_normal.png",
			(m_pCollider->GetFinalPos() + _pOther->GetFinalPos()) / 2, 0.5f, 0.5f, GetObjDir());
		SINGLE(CGameManager)->DamageText(to_wstring(pAttack->GetDamage()),
			(m_pCollider->GetFinalPos() + _pOther->GetFinalPos()) / 2, Color::ORANGE);
		Hit(pAttack->GetDamage());
	}
	if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::PROJECTILE)
	{
		if (L"Wizard_Fireball" == _pOther->GetObj()->GetName())
		{
			CAttack* pAttack = (CAttack*)_pOther->GetObj();
			CEnemy* pEnemy = (CEnemy*)pAttack->GetOwner();
			SINGLE(CGameManager)->CreateVfx(L"Explosion", L"texture\\effect\\explosion_small.png",
				(m_pCollider->GetFinalPos() + _pOther->GetFinalPos()) / 2, 1.0f, 1.0f, GetObjDir());
			SINGLE(CGameManager)->DamageText(to_wstring(pAttack->GetDamage()),
				(m_pCollider->GetFinalPos() + _pOther->GetFinalPos()) / 2, Color::ORANGE);
			SINGLE(CSoundManager)->Play(L"Explosion");

			Hit(pAttack->GetDamage());
		}
		else if (L"BossBomb" == _pOther->GetObj()->GetName())
		{
			CAttack* pAttack = (CAttack*)_pOther->GetObj();
			CEnemy* pEnemy = (CEnemy*)pAttack->GetOwner();
			SINGLE(CGameManager)->CreateVfx(L"Explosion", L"texture\\effect\\explosion_small.png",
				(m_pCollider->GetFinalPos() + _pOther->GetFinalPos()) / 2, 1.0f, 1.0f, GetObjDir());
			SINGLE(CGameManager)->DamageText(to_wstring(pAttack->GetDamage()),
				(m_pCollider->GetFinalPos() + _pOther->GetFinalPos()) / 2, Color::ORANGE);
			SINGLE(CSoundManager)->Play(L"Hit");

			Hit(pAttack->GetDamage());
		}
	}
	if (L"SkulHead" == _pOther->GetObj()->GetName())
	{
		m_bCanSkill = true;
		m_fSkillCurTime = 0.f;
	}
}

void CPlayer::OnCollisionExit(CCollider* _pOther)
{
    CPlayer* pPlayer = (CPlayer*)this;
    if (_pOther->GetObj()->GetObjType() == OBJ_TYPE::TILE)
    {
		pPlayer->m_iCollCount--;
		if (pPlayer->m_iCollCount <= 0)
		{
			pPlayer->m_iCollCount = 0;
			pPlayer->m_bIsGround = false;
		}

    }
}

void CPlayer::RenderPlayerInfo()
{
	if (SINGLE(CCore)->GetDebugMode())
	{
		Vec2 pos = GetRenderPos() + Vec2(GetScale().x / 2, -GetScale().y);
		CD2DImage* pImg = SINGLE(CResourceManager)->LoadD2DImage(L"CameraTex", L"texture\\cameraTex.png");
		RENDER->RenderImage(
			pImg,
			pos.x - 3,
			pos.y,
			pos.x + 160,
			pos.y + 90,
			0.3f);
		RENDER->RenderText(
			L"이름 : " + GetName(),
			pos.x,
			pos.y + 20,
			pos.x + 200,
			pos.y,
			16.f,
			0,
			RGB(255, 255, 255));
		RENDER->RenderText(
			L"상태 : " + m_strCurState,
			pos.x,
			pos.y + 50,
			pos.x + 200,
			pos.y,
			16.f,
			0,
			RGB(255, 255, 255));
		RENDER->RenderText(
			L"위치 : (" + to_wstring((int)GetPos().x) + L", " + to_wstring((int)GetPos().y) + L")",
			pos.x,
			pos.y + 80,
			pos.x + 200,
			pos.y,//+ 20 + 100,
			16.f,
			0,
			RGB(255, 255, 255));
		RENDER->RenderText(
			L"현재 애니메이션\n : " + GetAnimator()->GetCurAnim()->GetName(),
			pos.x,
			pos.y + 130,
			pos.x + 200,
			pos.y,//+ 20 + 100,
			16.f,
			0,
			RGB(255, 255, 255));
	}
}

void CPlayer::Move(float _speed)
{
	m_bIsRight = _speed > 0 ? true : false;
	m_vPos.x += _speed * DT;
}

void CPlayer::Jump(float _speed)
{
	m_vVelocity.y -= _speed;
}


void CPlayer::CoolTime()
{
	// 모든 상태에서 계산되어야하는 부분은 이부분에서 처리한다.
	if (!m_bCanSecondDash)
	{
		m_fSecondDashCurTime += DT;
		if (m_fSecondDashCurTime >= m_fSecondDashCoolTime)
		{
			m_bCanSecondDash = true;
			m_fSecondDashCurTime = 0.f;

		}
	}

	if (!m_bCanDash)
	{
		m_fDashCurTime += DT;
		if (m_fDashCurTime >= m_fDashCoolTime)
		{
			m_bCanDash = true;
		}
	}

	if (!m_bCanSkill)
	{
		m_fSkillCurTime += DT;
		if (m_fSkillCurTime >= m_fSkillCoolTime)
		{
			m_bCanSkill = true;

		}
	}
}


void CPlayer::Hit(int _damage)
{
	m_tPlayerInfo.m_iHp = m_tPlayerInfo.m_iHp -_damage < 0 ? 0 : m_tPlayerInfo.m_iHp - _damage;
	Vec2 vec = SINGLE(CGameManager)->m_pCurHealth->GetOriginSize();
	SINGLE(CGameManager)->m_pCurHealth->SetScaleRate(Vec2(vec.x * GetCurHealthRatio(), vec.y));
	SINGLE(CGameManager)->m_pCurHealthText->SetText(to_wstring(m_tPlayerInfo.m_iHp) + L" / " + to_wstring(m_tPlayerInfo.m_iMaxHp));
	
}
