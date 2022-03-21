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

	CD2DImage* pImg = SINGLE(CResourceManager)->LoadD2DImage(_strImgName, _strImgPath);
	SetObjDir(_dir);
	float imgX = (float)pImg->GetWidth();
	float imgY = (float)pImg->GetHeight();
	int imgCountX = (int)(imgX / imgY);
	float imgDiviedSizeX = imgX / imgCountX;
	CreateAnimator();

	m_pAnimator->CreateAnimation(_strImgName, pImg, Vec2(0, 0), Vec2(imgDiviedSizeX, imgY),
		Vec2(imgDiviedSizeX, 0), (float)(_fInterval /imgCountX), imgCountX);
	m_pAnimator->Play(_strImgName, true);
	//SetScale(Vec2(imgDiviedSizeX, imgSizeY));
	
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
