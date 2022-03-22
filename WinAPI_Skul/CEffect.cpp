#include "pch.h"
#include "CEffect.h"
#include "CD2DImage.h"
#include "CAnimator.h"


CEffect::CEffect(wstring _strImgName, wstring _strImgPath,
				float _fDuration, float _fInterval, bool _dir):
	CObject(OBJ_TYPE::EFFECT),
	m_fCurTime(0),
	m_fDuration(_fDuration),
	m_bIsPlay(true)
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
		ComponentRender();
	}
}

void CEffect::EffectPlay(Vec2 _vPos)
{
	m_bIsPlay = true;
	SetPos(_vPos);
}
