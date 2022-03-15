#include "pch.h"
#include "CImageObj.h"
#include "CD2DImage.h"

CImageObj::CImageObj():
    m_bRenderStyle(false)
{
    m_pImg = SINGLE(CResourceManager)->LoadD2DImage(L"test", L"texture\\startscene_bg.bmp");
    SetPos(Vec2(0, 0));
    SetScale(Vec2(m_pImg->GetWidth() * 2.f, m_pImg->GetHeight() * 2.f));
}

CImageObj::CImageObj(OBJ_TYPE _eType, wstring _strImgName, wstring _strImgPath, bool _renderStyle)
{
    m_pImg = SINGLE(CResourceManager)->LoadD2DImage(_strImgName, _strImgPath);
    SetPos(Vec2(0, 0));
    SetScale(Vec2(m_pImg->GetWidth() * 2.f, m_pImg->GetHeight() * 2.f));
    m_bRenderStyle = _renderStyle;
}

CImageObj::~CImageObj()
{
}

CImageObj* CImageObj::Clone()
{
    return nullptr;
}

void CImageObj::Update()
{
}

void CImageObj::Render()
{
    Vec2 pos = GetPos();
    Vec2 scale = GetScale();
    pos = SINGLE(CCameraManager)->GetRenderPos(pos);

    if (m_bRenderStyle)
    {
        
        RENDER->RenderImage(
            m_pImg,
            pos.x,
            pos.y,
            pos.x + m_pImg->GetWidth(),
            pos.y + m_pImg->GetHeight(),
            1.f);
    }
    else
    {
        pos += SINGLE(CCameraManager)->GetCurLookAt() - Vec2(WINSIZEX/2, WINSIZEY/2);
        SINGLE(CRenderManager)->RenderImage(
            m_pImg,
            pos.x,
            pos.y,
            pos.x + WINSIZEX,
            pos.y + WINSIZEY,
            1.f);
    }

}
