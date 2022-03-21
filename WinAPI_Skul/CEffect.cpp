#include "pch.h"
#include "CEffect.h"
#include "CD2DImage.h"
#include "CAnimator.h"


CEffect::CEffect(OBJ_TYPE _eType, wstring _strImgName, wstring _strImgPath,
				float _fDuration, float _fPlayTime, int _imgSize, bool _dir):
	CObject(_eType),
	m_fCurTime(0),
	m_fDuration(_fDuration),
	m_bIsPlay(true)
{

	CD2DImage* pImg = SINGLE(CResourceManager)->LoadD2DImage(_strImgName, _strImgPath);
	SetObjDir(_dir);
	float imgSizeX = (float)pImg->GetWidth();
	float imgSizeY = (float)pImg->GetHeight();
	int imgCountX = (int)(imgSizeX / _imgSize);
	float imgDiviedSizeX = imgSizeX / imgCountX;
	CreateAnimator();

	m_pAnimator->CreateAnimation(_strImgName, pImg, Vec2(0, 0), Vec2(imgDiviedSizeX, imgSizeY),
		Vec2(imgDiviedSizeX, 0), (float)(_fPlayTime/imgCountX), imgCountX);
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
