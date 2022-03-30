#include "pch.h"
#include "CImageObj.h"
#include "CD2DImage.h"

CImageObj::CImageObj():
    m_pImg(nullptr),
    m_bRenderStyle(false),
    m_fAlpha(1.0f),
    m_eEffectType(IMG_EFFECT::NONE),
    m_fCurTime(0),
    m_fEffectDuration(1.5f),
    m_fDepthLevel(0),
    m_bEffectSwitch(false)
{
}

CImageObj::CImageObj(OBJ_TYPE _eType, wstring _strImgName, wstring _strImgPath, bool _renderStyle):
    CObject(_eType),
    m_pImg(nullptr),
    m_bRenderStyle(false),
    m_fAlpha(1.0f),
    m_eEffectType(IMG_EFFECT::NONE),
    m_fCurTime(0),
    m_fEffectDuration(1.5f),
    m_fDepthLevel(0),
    m_bEffectSwitch(false)
{
    m_pImg = SINGLE(CResourceManager)->LoadD2DImage(_strImgName, _strImgPath);
    SetPos(Vec2(0, 0));
    SetScale(Vec2((float)m_pImg->GetWidth(), (float)m_pImg->GetHeight()));
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
    if (IMG_EFFECT::FLICKER == m_eEffectType)
    {
        m_fCurTime += DT;
        float fRatio = m_fCurTime / m_fEffectDuration;

        if (m_fCurTime >= m_fEffectDuration)
        {
            m_fCurTime = 0;
            m_bEffectSwitch = !m_bEffectSwitch;
        }


        if (m_bEffectSwitch)
            m_fAlpha = fRatio;
        else
            m_fAlpha = (1 - fRatio);
    }
}

void CImageObj::Render()
{
    Vec2 pos = GetPos();
    Vec2 scale = GetScale();
    Vec2 renderPos = SINGLE(CCameraManager)->GetRenderPos(pos);
    if (0 != m_fDepthLevel)
    {
        renderPos.x = pos.x + (renderPos.x - pos.x) / (int)m_fDepthLevel;
        renderPos.y = pos.y + (renderPos.y - pos.y) / (int)m_fDepthLevel;
    }
        
    
    if (m_bRenderStyle)
    {
        
        RENDER->RenderImage(
            m_pImg,
            renderPos.x,
            renderPos.y,
            renderPos.x + m_pImg->GetWidth(),
            renderPos.y + m_pImg->GetHeight(),
            m_fAlpha);
    }
    else
    {
        RENDER->RenderImage(
            m_pImg,
            m_vPos.x,
            m_vPos.y,
            m_vPos.x + GetScale().x,
            m_vPos.y + GetScale().y,
            m_fAlpha);
    }

}
