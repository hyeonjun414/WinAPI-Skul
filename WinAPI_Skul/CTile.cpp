#include "pch.h"
#include "CTile.h"
#include "CD2DImage.h"
#include "CCollider.h"


CTile::CTile(OBJ_TYPE _eObjType):
	CObject(_eObjType)
{
	m_pImg = nullptr;
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

void CTile::Render()
{
	if (nullptr == m_pImg) return;

	UINT iWidth = m_pImg->GetWidth();
	UINT iHeight = m_pImg->GetHeight();

	UINT iMaxX = iWidth / SIZE_TILE;
	UINT iMaxY = iHeight / SIZE_TILE;

	UINT iCurX = (m_iIdx % iMaxX);
	UINT iCurY = (m_iIdx / iMaxX) % iMaxY;

	Vec2 vRenderPos = SINGLE(CCameraManager)->GetRenderPos(GetPos());
	if (vRenderPos.x < -200 || vRenderPos.x > WINSIZEX +200 ||
		vRenderPos.y < -200 || vRenderPos.y > WINSIZEY + 200 )
		return;

	Vec2 vScale = GetScale();

	if (m_iIdx != 0)
	{
		RENDER->RenderFrame(
			m_pImg,
			vRenderPos.x,
			vRenderPos.y,
			vRenderPos.x + vScale.x,
			vRenderPos.y + vScale.y,
			(float)(iCurX * SIZE_TILE),
			(float)(iCurY * SIZE_TILE),
			(float)((iCurX+1) * SIZE_TILE),
			(float)((iCurY+1) * SIZE_TILE), 1.0f
		);
	}
	else if (SINGLE(CCore)->GetDebugMode())
	{
		RENDER->RenderFrame(
			m_pImg,
			vRenderPos.x,
			vRenderPos.y,
			vRenderPos.x + vScale.x,
			vRenderPos.y + vScale.y,
			(float)(iCurX * SIZE_TILE),
			(float)(iCurY * SIZE_TILE),
			(float)((iCurX + 1) * SIZE_TILE),
			(float)((iCurY + 1) * SIZE_TILE), 0.3f
		);
	}

	ComponentRender();
}

void CTile::Save(FILE* _pFile)
{
	fwrite(&m_iIdx, sizeof(int), 1, _pFile);
	fwrite(&m_bIsColl, sizeof(bool), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	fread(&m_iIdx, sizeof(int), 1, _pFile);
	fread(&m_bIsColl, sizeof(bool), 1, _pFile);

	if (m_bIsColl)
	{
		CreateCollider();
		m_pCollider->SetOffsetPos(GetScale() / 2);
		m_pCollider->SetScale(GetScale());
	}
}
