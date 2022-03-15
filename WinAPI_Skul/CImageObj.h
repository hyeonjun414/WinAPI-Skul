#pragma once
#include "CObject.h"

class CD2DImage;

class CImageObj :
    public CObject
{
	CD2DImage*  m_pImg;
	bool		m_bRenderStyle;

public:
	CImageObj();
	CImageObj(OBJ_TYPE _eType, wstring _strImgName, wstring _strImgPath, bool _renderStyle);
	~CImageObj();

	
	CD2DImage* GetImage() { return m_pImg; }

	virtual CImageObj* Clone();
	virtual void Update();
	virtual void Render();
};

