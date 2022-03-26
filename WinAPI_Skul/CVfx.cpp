#include "pch.h"
#include "CVfx.h"
#include "CD2DImage.h"
#include "CAnimator.h"

CVfx::CVfx(wstring _strKey, wstring _strPath, float _fDuration, float _fInterval, bool _dir) :
	CEffect(_strKey, _fDuration),
	m_strPath(_strPath),
	m_fSizeRate(1.f)
{
	SetObjDir(_dir);
	CreateAnimator();
	m_pAnimator->CreateAnim(_strKey, _strPath, _fInterval);
	m_pAnimator->Play(_strKey, true);
}

CVfx::~CVfx()
{
}

void CVfx::Update()
{
	m_fCurTime += DT;

	if (m_fCurTime >= m_fDuration)
		DELETEOBJECT(this);

	GetAnimator()->Update();
}

void CVfx::Render()
{
	GetAnimator()->Render(m_bIsRight, m_fSizeRate);
}
