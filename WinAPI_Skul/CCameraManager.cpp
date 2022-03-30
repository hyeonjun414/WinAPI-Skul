#include "pch.h"
#include "CCameraManager.h"
#include "CObject.h"
#include "CTexture.h"
#include "CD2DImage.h"
#include "CAnimator.h"
#include "CScene.h"

CCameraManager::CCameraManager() :
	m_vLookAt(Vec2(WINSIZEX / 2.f, WINSIZEY / 2.f)),
	m_vCamSize(Vec2(1280.f, 720.f)),
	m_vWorldSize(Vec2(1280.f, 720.f)),
	m_vCurLookAt(m_vLookAt),
	m_vPrevLookAt(m_vLookAt),
	m_pTargetObj(nullptr),
	m_fFlowTime(m_fTime),
	m_fSpeed(700),
	m_fPreSpeed(m_fSpeed),
	m_fAccel(0)
{
	CreateAnimator();
	CD2DImage* pImg = SINGLE(CResourceManager)->LoadD2DImage(L"Loding", L"texture\\scene_loding.png");
	m_pAnimator->CreateAnimation(L"Loding", pImg, Vec2(0.f, 0.f), Vec2(64.f, 64.f),
		Vec2(64, 0.f), 0.06f, 8);
}
CCameraManager::~CCameraManager() 
{
	if (nullptr != m_pAnimator)
		delete m_pAnimator;
}

void CCameraManager::CalDiff()
{
	m_fFlowTime += DT;

	float fDist = (m_vLookAt - m_vPrevLookAt).Length();

	// �ð��� ������, �����Ѱ����� ����
	if (m_fTime <= m_fFlowTime || fDist < 2 )
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vec2 vCenter = Vec2(WINSIZEX / 2.f, WINSIZEY / 2.f);

		m_vCurLookAt = m_vPrevLookAt + (m_vLookAt - m_vPrevLookAt).Normalize() * m_fSpeed * DT;
		m_vDiff = m_vCurLookAt - vCenter;
		m_vPrevLookAt = m_vCurLookAt;
	}
}

void CCameraManager::Init()
{
	// ȿ���� �ִ� �ؽ����� ������� ���α׷��� �ػ� ��ŭ���� ������ش�.
	m_pImg = SINGLE(CResourceManager)->LoadD2DImage(L"CameraTex", L"texture\\cameraTex.png");
	m_pWhiteImg = SINGLE(CResourceManager)->LoadD2DImage(L"CameraWhite", L"texture\\cameraWhite.png");
}

void CCameraManager::Update()
{
	m_pAnimator->Update();

	if (!SINGLE(CGameManager)->GetGamePlay()) return;

	if (m_pTargetObj)
	{
		if (!m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			SetLookAt(m_pTargetObj->GetPos()+Vec2(0,-200));
		}
	}

	// ȭ�� �߾Ӱ� ī�޶� LookAt ��ǥ ������ ���� ���
	CalDiff();

	CheckBoundary();

	if (CAM_EFFECT::SHAKING == m_eEffect)
	{
		Vec2 shakePos = Vec2(rand() % m_iMagnitude - m_iMagnitude/2, rand() % m_iMagnitude - m_iMagnitude/2);

		//m_vLookAt += shakePos;
		//m_vCurLookAt += shakePos;
		m_vPrevLookAt += shakePos * DT;
	}
	
}

void CCameraManager::SetLookAt(Vec2 _vLook)
{
	m_vLookAt = _vLook;
	float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();

	m_fSpeed = fMoveDist / m_fTime * 5;
	m_fFlowTime = 0.f;

	
}



void CCameraManager::Render()
{

	// ī�޶� ȿ���� ���۵Ǿ������� ������ �۵��Ѵ�.
	if (CAM_EFFECT::NONE == m_eEffect)
		return;

	m_fCurTime += DT;
	if (m_fEffectDuration < m_fCurTime)
	{
		m_eEffect = CAM_EFFECT::NONE;
 		m_iMagnitude = 0;
		return;
	}
	if (CAM_EFFECT::LODING_IMAGE == m_eEffect)
	{
		RENDER->RenderImage(m_pImg,
			0,
			0,
			(float)m_pImg->GetWidth(),
			(float)m_pImg->GetHeight(), 1.0f);
		m_pAnimator->Play(L"Loding", true);
		m_pAnimator->Render_Without_Obj();
		return;
	}

	float fRatio = m_fCurTime / m_fEffectDuration;
	float iAlpha;

	if (CAM_EFFECT::FADE_OUT == m_eEffect)
	{
		iAlpha = fRatio;
		RENDER->RenderImage(m_pImg,
			0,
			0,
			(float)m_pImg->GetWidth(),
			(float)m_pImg->GetHeight(), iAlpha);
	}
	else if (CAM_EFFECT::FADE_IN == m_eEffect)
	{
		iAlpha = (1 - fRatio);
		RENDER->RenderImage(m_pImg,
			0,
			0,
			(float)m_pImg->GetWidth(),
			(float)m_pImg->GetHeight(), iAlpha);
	}
	else if (CAM_EFFECT::WHITEOUT == m_eEffect)
	{
		iAlpha = (1 - fRatio);
		RENDER->RenderImage(m_pWhiteImg,
			0,
			0,
			(float)m_pImg->GetWidth(),
			(float)m_pImg->GetHeight(), iAlpha);
		if (0 != m_iMagnitude)
		{
			Vec2 shakePos = Vec2(rand() % m_iMagnitude - m_iMagnitude / 2, rand() % m_iMagnitude - m_iMagnitude / 2);
			//m_vLookAt += shakePos;
			//m_vCurLookAt += shakePos;
			m_vPrevLookAt += shakePos * DT;
		}

		
	}


}

void CCameraManager::CheckBoundary()
{
	if (m_vCurLookAt.x - m_vCamSize.x / 2 < 0)
	{
		m_vCurLookAt.x = m_vCamSize.x / 2;
	}
	if (m_vCurLookAt.x + m_vCamSize.x / 2 > m_vWorldSize.x)
	{
		m_vCurLookAt.x = m_vWorldSize.x - m_vCamSize.x / 2;
	}
	if (m_vCurLookAt.y - m_vCamSize.y / 2 < 0)
	{
		m_vCurLookAt.y = m_vCamSize.y / 2;
	}
	if (m_vCurLookAt.y + m_vCamSize.y / 2 > m_vWorldSize.y)
	{
		m_vCurLookAt.y = m_vWorldSize.y - m_vCamSize.y / 2;
	}

	m_vDiff = m_vCurLookAt - m_vCamSize/2;

}

void CCameraManager::Scroll(Vec2 vec, float velocity)
{
	m_vLookAt += vec * velocity * DT;
	m_vCurLookAt += vec * velocity * DT;

	Vec2 vCenter = Vec2(WINSIZEX / 2.f, WINSIZEY / 2.f);
	m_vDiff = m_vCurLookAt - vCenter;
}

void CCameraManager::CreateAnimator()
{
	m_pAnimator = new CAnimator;
}

void CCameraManager::FadeIn(float _duration)
{
	m_eEffect = CAM_EFFECT::FADE_IN;
	m_fEffectDuration = _duration;
	m_fCurTime = 0.f;
}

void CCameraManager::FadeOut(float _duration)
{
	m_eEffect = CAM_EFFECT::FADE_OUT;
	m_fEffectDuration = _duration;
	m_fCurTime = 0.f;
}

void CCameraManager::LodingAnimation(float _duration)
{
	m_eEffect = CAM_EFFECT::LODING_IMAGE;
	m_fEffectDuration = _duration;
	m_fCurTime = 0.f;
}

void CCameraManager::CameraShaking(int _magnitude, float _duration)
{
	m_eEffect = CAM_EFFECT::SHAKING;
	m_fEffectDuration = _duration;
	m_iMagnitude = _magnitude;
	m_fCurTime = 0.f;
}

void CCameraManager::WhiteOut(float _duration, int _magnitude)
{
	m_eEffect = CAM_EFFECT::WHITEOUT;
	m_fEffectDuration = _duration;
	m_iMagnitude = _magnitude;
	m_fCurTime = 0.f;
}