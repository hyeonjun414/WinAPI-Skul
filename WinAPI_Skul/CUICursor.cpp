#include "pch.h"
#include "CUICursor.h"
#include "CD2DImage.h"

CUICursor::CUICursor(OBJ_TYPE _eType):
	CUI(_eType)
{
	m_pImg = SINGLE(CResourceManager)->LoadD2DImage(L"CursorImg", L"texture\\skul_cursor.png");
}

CUICursor::CUICursor(const CUICursor& _origin):
	CUI(_origin)
{
}

CUICursor::~CUICursor()
{
    
}

void CUICursor::Update()
{
    Vec2 vMousePos = MOUSEPOS;
    if (vMousePos.x <= 0 || vMousePos.x >= WINSIZEX ||
        vMousePos.y <= 0 || vMousePos.y >= WINSIZEY)
        return;

    SetPos(MOUSEPOS);
}

void CUICursor::Render()
{
    SINGLE(CRenderManager)->RenderImage(
        m_pImg,
        m_vPos.x,
        m_vPos.y,
        m_vPos.x + 32,
        m_vPos.y + 32,
        1.f);
}
