#pragma once
#include "CObject.h"
class CLineObj :
    public CObject
{
private:
    CObject* m_pStart;
    CObject* m_pEnd;

    float m_fSize;
    Vec2 m_vOffsetStart;
    Vec2 m_vOffsetEnd;

public:
    CLineObj(CObject* _pStart, CObject* _pEnd, Vec2 _offsetStart, Vec2 _offsetEnd, float _size);
    virtual ~CLineObj();

    virtual void Render();
};

