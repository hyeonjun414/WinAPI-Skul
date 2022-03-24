#include "pch.h"
#include "CUIImage.h"

CUIImage::CUIImage(OBJ_TYPE _eType, const wstring& _strKey, const wstring& _strPath, Vec2 _sizeRate):
	CUI(_eType),
	m_pImg(nullptr),
	m_vScaleRate(_sizeRate),
	m_vOriginScaleRate(_sizeRate)
{
	m_pImg = SINGLE(CResourceManager)->LoadD2DImage(_strKey, _strPath);
	assert(m_pImg);

}

CUIImage::~CUIImage()
{
}

void CUIImage::Render()
{
	RENDER->RenderImage(
		m_pImg,
		GetFinalPos().x,
		GetFinalPos().y,
		GetFinalPos().x + m_vScale.x * m_vScaleRate.x,
		GetFinalPos().y + m_vScale.y * m_vScaleRate.y,
		1.0f);

	RenderChild();
}
