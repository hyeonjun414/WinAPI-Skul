#include "pch.h"
#include "CCameraManager.h"
#include "CGameObject.h"
#include "CTexture.h"

CCameraManager::CCameraManager() :
	m_vLookAt(Vec2(WINSIZEX / 2.f, WINSIZEY / 2.f)),
	m_vCamSize(Vec2(1280.f, 720.f)),
	m_vWorldSize(Vec2(1280.f, 720.f)),
	m_vCurLookAt(m_vLookAt),
	m_vPrevLookAt(m_vLookAt),
	m_pTargetObj(nullptr),
	m_fFlowTime(m_fTime),
	m_fSpeed(500),
	m_fPreSpeed(m_fSpeed),
	m_fAccel(0)
{
}
CCameraManager::~CCameraManager() {}

void CCameraManager::CalDiff()
{
	m_fFlowTime += DT;

	CheckBoundary();

	// 시간이 지나면, 도착한것으로 간주
	if (m_fTime <= m_fFlowTime || (m_vLookAt - m_vPrevLookAt).Length() < 10)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vec2 fptCenter = Vec2(WINSIZEX / 2.f, WINSIZEY / 2.f);

		m_vCurLookAt = m_vPrevLookAt + (m_vLookAt - m_vPrevLookAt).Normalize() * m_fSpeed * DT;
		m_vDiff = m_vCurLookAt - fptCenter;
		m_vPrevLookAt = m_vCurLookAt;
	}
}

void CCameraManager::Init()
{
	// 효과를 주는 텍스쳐의 사이즈는 프로그램의 해상도 만큼으로 만들어준다.
	m_pTex = SINGLE(CResourceManager)->CreateTexture(L"CameraTex", WINSIZEX, WINSIZEY);
}

void CCameraManager::Update()
{
	if (m_pTargetObj)
	{
		if (!m_pTargetObj->GetActive())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			SetLookAt(m_pTargetObj->GetPos());
		}
	}

	// 화면 중앙과 카메라 LookAt 좌표 사이의 차이 계산
	CalDiff();

}

void CCameraManager::SetLookAt(Vec2 _vLook)
{
	m_vLookAt = _vLook;
	float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();

	m_fSpeed = fMoveDist / m_fTime;
	m_fFlowTime = 0.f;
}



void CCameraManager::Render(HDC _hDC)
{
	// 카메라 효과가 시작되었을때만 렌더가 작동한다.
	if (CAM_EFFECT::NONE == m_eEffect)
		return;

	m_fCurTime += DT;
	if (m_fEffectDuration < m_fCurTime)
	{
		m_eEffect = CAM_EFFECT::NONE;
		return;
	}

	float fRatio = m_fCurTime / m_fEffectDuration;
	int iAlpha;
	if (CAM_EFFECT::FADE_OUT == m_eEffect)
	{
		iAlpha = (int)(255.f * fRatio);
	}
	else if (CAM_EFFECT::FADE_IN == m_eEffect)
	{
		iAlpha = (int)(255.f * (1 - fRatio));
	}

	// 블렌딩 구조체
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha; // 0 ~ 255

	AlphaBlend(_hDC,
		0,
		0,
		(int)(m_pTex->Width()),
		(int)(m_pTex->Height()),
		m_pTex->GetDC(),
		0,
		0,
		(int)(m_pTex->Width()),
		(int)(m_pTex->Height()),
		bf);

}

void CCameraManager::CheckBoundary()
{
	if (m_vLookAt.x - m_vCamSize.x / 2 <= 0)
	{
		m_vLookAt.x = m_vCamSize.x / 2;
		m_vCurLookAt.x = m_vLookAt.x;
	}
	if (m_vLookAt.x + m_vCamSize.x / 2 >= m_vWorldSize.x)
	{
		m_vLookAt.x = m_vWorldSize.x - m_vCamSize.x / 2;
		m_vCurLookAt.x = m_vLookAt.x;
	}
	if (m_vLookAt.y - m_vCamSize.y / 2 <= 0)
	{
		m_vLookAt.y = m_vCamSize.y / 2;
		m_vCurLookAt.x = m_vLookAt.x;
	}
	if (m_vLookAt.y + m_vCamSize.y / 2 >= m_vWorldSize.y)
	{
		m_vLookAt.y = m_vWorldSize.y - m_vCamSize.y / 2;
		m_vCurLookAt.x = m_vLookAt.x;
	}
}

void CCameraManager::Scroll(Vec2 vec, float velocity)
{
	m_vLookAt += vec * velocity * DT;
	m_vCurLookAt += vec * velocity * DT;

	Vec2 vCenter = Vec2(WINSIZEX / 2.f, WINSIZEY / 2.f);
	m_vDiff = m_vCurLookAt - vCenter;
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

