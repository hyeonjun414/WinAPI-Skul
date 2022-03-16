#pragma once
#include "CObject.h"
class CTextObj :
    public CObject
{
	CD2DImage* m_pImg;
	bool		m_bRenderStyle;

public:
	CTextObj();
	CTextObj(OBJ_TYPE _eType, wstring _strImgName, wstring _strImgPath, bool _renderStyle);
	~CTextObj();


	CD2DImage* GetImage() { return m_pImg; }

	virtual CTextObj* Clone();
	virtual void Update();
	virtual void Render();
};

