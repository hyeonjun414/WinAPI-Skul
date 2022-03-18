#include "pch.h"
#include "CEffect.h"
#include "CD2DImage.h"
#include "CAnimator.h"

CEffect::CEffect():
	m_fCurTime(0),
	m_fDuration(0)
{
}

CEffect::CEffect(OBJ_TYPE _eType, wstring _strImgName, wstring _strImgPath, float _fDuration, float _fPlayTime, int _imgSize, bool _dir):
	CObject(_eType),
	m_fCurTime(0),
	m_fDuration(_fDuration)
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
	SetScale(Vec2(imgDiviedSizeX, imgSizeY));
	
	m_pAnimator->Play(_strImgName, true);
}

CEffect::~CEffect()
{
}

void CEffect::Init()
{
}

void CEffect::Update()
{
	m_fCurTime += DT;

	if (m_fCurTime >= m_fDuration)
		DELETEOBJECT(this);

	GetAnimator()->Update();
}

void CEffect::Render()
{
	ComponentRender();
}
