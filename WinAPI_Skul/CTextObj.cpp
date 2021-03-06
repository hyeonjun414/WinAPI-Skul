#include "pch.h"
#include "CTextObj.h"
#include "CD2DImage.h"

CTextObj::CTextObj(OBJ_TYPE _eType, const wstring& _strText, TEXT_EFFECT _eEffect, Color _color) :
    CObject(_eType),
    m_strText(_strText),
    m_fDuration(1.f),
    m_fCurTime(0.f),
    m_eColor(_color)
{
    m_vVelocity.y = 600;
    m_vVelocity.x = (float)((rand() % 200) - 100);
}

CTextObj::~CTextObj()
{
}
void CTextObj::Update()
{
    m_fCurTime += DT;

    m_vPos.y -= m_vVelocity.y * DT;
    m_vPos.x += m_vVelocity.x * DT;
    m_vVelocity.y -= 1000 * DT;


    if (m_fCurTime >= m_fDuration)
        DELETEOBJECT(this);
}
void CTextObj::Render()
{
    Vec2 pos = GetPos();
    Vec2 scale = GetScale();
    pos = SINGLE(CCameraManager)->GetRenderPos(pos);

    pos += SINGLE(CCameraManager)->GetCurLookAt() - Vec2(WINSIZEX / 2, WINSIZEY / 2);
    RENDER->RenderText(
        m_strText,
        GetRenderPos().x,
        GetRenderPos().y,
        GetRenderPos().x + 100,
        GetRenderPos().y + 100,
        30.f,
        2,
        m_eColor);//RGB(255.f,150.f,150.f));

}