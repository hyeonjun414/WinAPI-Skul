#include "pch.h"
#include "CUITileBtn.h"
#include "CD2DImage.h"
#include "CTile.h"


CUITileBtn::CUITileBtn(OBJ_TYPE _eType) :
	CUIButton(_eType),
	m_iIdx(0)
{
}

CUITileBtn::~CUITileBtn()
{
}

void CUITileBtn::Render()
{
	if (nullptr != m_pImg)
	{
		UINT iWidth = m_pImg->GetWidth();
		UINT iHeight = m_pImg->GetHeight();

		UINT iMaxRow = iHeight / CTile::SIZE_TILE;
		UINT iMaxCol = iWidth / CTile::SIZE_TILE;

		UINT iCurRow = (m_iIdx / iMaxCol) % iMaxRow;
		UINT iCurCol = (m_iIdx % iMaxCol);


		CRenderManager::GetInst()->RenderFrame(
			m_pImg,
			GetFinalPos().x,
			GetFinalPos().y,
			GetFinalPos().x + GetScale().x,
			GetFinalPos().y + GetScale().y,
			iCurCol * GetScale().x,
			iCurRow * GetScale().y,
			(iCurCol + 1) * GetScale().x,
			(iCurRow + 1) * GetScale().y, 1.0f
		);
	}
}
