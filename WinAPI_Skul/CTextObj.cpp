#include "pch.h"
#include "CTextObj.h"
#include "CD2DImage.h"

CTextObj::CTextObj() :
    m_bRenderStyle(false)
{
    m_pImg = SINGLE(CResourceManager)->LoadD2DImage(L"test", L"texture\\startscene_bg.bmp");
    SetPos(Vec2(0, 0));
    SetScale(Vec2(m_pImg->GetWidth() * 2.f, m_pImg->GetHeight() * 2.f));
}

CTextObj::CTextObj(OBJ_TYPE _eType, wstring _strImgName, wstring _strImgPath, bool _renderStyle)
{
    m_pImg = SINGLE(CResourceManager)->LoadD2DImage(_strImgName, _strImgPath);
    SetPos(Vec2(0, 0));
    SetScale(Vec2(m_pImg->GetWidth() * 2.f, m_pImg->GetHeight() * 2.f));
    m_bRenderStyle = _renderStyle;
}

CTextObj::~CTextObj()
{
}

CTextObj* CTextObj::Clone()
{
    return nullptr;
}

void CTextObj::Update()
{
}

void CTextObj::Render()
{
    Vec2 pos = GetPos();
    Vec2 scale = GetScale();
    pos = SINGLE(CCameraManager)->GetRenderPos(pos);

    pos += SINGLE(CCameraManager)->GetCurLookAt() - Vec2(WINSIZEX / 2, WINSIZEY / 2);
    SINGLE(CRenderManager)->RenderImage(
        m_pImg,
        pos.x,
        pos.y,
        pos.x + WINSIZEX,
        pos.y + WINSIZEY,
        1.f);

}