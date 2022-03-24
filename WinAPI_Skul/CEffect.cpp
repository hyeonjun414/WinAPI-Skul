#include "pch.h"
#include "CEffect.h"
#include "CD2DImage.h"
#include "CAnimator.h"


CEffect::CEffect(wstring _strImgName, wstring _strImgPath,
				float _fDuration, float _fInterval, bool _dir):
	CObject(OBJ_TYPE::EFFECT),
	m_fCurTime(0),
	m_fDuration(_fDuration),
	m_bIsPlay(true),
	m_pTargetObj(nullptr),
	m_fSizeRate(1.0f)
{
	SetObjDir(_dir);
	CreateAnimator();
	m_pAnimator->CreateAnim(_strImgName, _strImgPath, _fInterval);
	m_pAnimator->Play(_strImgName, true);
}

CEffect::~CEffect()
{
}

void CEffect::Update()
{
	if (nullptr != m_pTargetObj)
	{
		SetPos(m_pTargetObj->GetPos());
	}
	if (m_bIsPlay)
	{
		m_fCurTime += DT;

		if (m_fCurTime >= m_fDuration)
			DELETEOBJECT(this);

		GetAnimator()->Update();
	}
}

void CEffect::Render()
{
	if (m_bIsPlay)
	{
		GetAnimator()->Render(m_bIsRight, m_fSizeRate);
	}
}