#include "pch.h"
#include "CTile.h"
#include "CTexture.h"


CTile::CTile(OBJ_TYPE _eObjType):
	CGameObject(_eObjType)
{
	m_pTex = nullptr;
	m_iIdx = 0;
	SetScale(Vec2(SIZE_TILE, SIZE_TILE));
}

CTile::~CTile()
{
}
void CTile::Init()
{
}

void CTile::Update()
{
}

void CTile::Render(HDC _hDC)
{
	if (nullptr == m_pTex) return;

	UINT iWidth = m_pTex->Width();
	UINT iHeight = m_pTex->Height();

	UINT iMaxX = iWidth / SIZE_TILE;
	UINT iMaxY = iHeight / SIZE_TILE;

	UINT iCurX = (m_iIdx % iMaxX);
	UINT iCurY = (m_iIdx / iMaxX) % iMaxY;

	Vec2 vRenderPos = SINGLE(CCameraManager)->GetRenderPos(GetPos());
	if (vRenderPos.x < 200 || vRenderPos.x > WINSIZEX - 200 ||
		vRenderPos.y < 200 || vRenderPos.y > WINSIZEY - 200)
		return;

	Vec2 vScale = GetScale();


	//BitBlt(_hDC,
	//	(int)(vRenderPos.x),
	//	(int)(vRenderPos.y),
	//	(int)(vScale.x),
	//	(int)(vScale.y),
	//	m_pTex->GetDC(),
	//	iCurX * SIZE_TILE,
	//	iCurY * SIZE_TILE,
	//	SRCCOPY);

	TransparentBlt(_hDC,
		(int)(vRenderPos.x),
		(int)(vRenderPos.y),
		(int)(vScale.x),
		(int)(vScale.y),
		m_pTex->GetDC(),
		iCurX * SIZE_TILE,
		iCurY * SIZE_TILE,
		SIZE_TILE,
		SIZE_TILE,
		RGB(255, 0, 255));
}

void CTile::Save(FILE* _pFile)
{
	fwrite(&m_iIdx, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	fread(&m_iIdx, sizeof(int), 1, _pFile);
}
