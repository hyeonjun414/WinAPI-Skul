#include "pch.h"
#include "CScene.h"
#include "CGameObject.h"
#include "CTile.h"

CScene::CScene():
	m_strName{},
	m_eType(SCENE_TYPE::NONE),
	m_iTileX(0),
	m_iTileY(0)
{
}

CScene::CScene(wstring _strName, SCENE_TYPE _eTYpe):
	m_strName(_strName),
	m_eType(_eTYpe),
	m_iTileX(0),
	m_iTileY(0)
{
}

CScene::~CScene()
{
	// 장면이 사라질때 장면에 동적할당으로 추가된 오브젝트를 메모리 해제시켜준다.
	for (int i = 0; i < (int)OBJ_TYPE::SIZE; i++)
	{
		Safe_Delete_Vec(m_vecObjectList[i]);
	}
}

void CScene::Update()
{
	for (int i = 0; i < (int)OBJ_TYPE::SIZE; i++)
	{
		for (unsigned int j = 0; j < m_vecObjectList[i].size(); j++)
		{
			if(m_vecObjectList[i][j]->GetActive())
				m_vecObjectList[i][j]->Update();
		}
	}
}

void CScene::FinalUpdate()
{
	for (int i = 0; i < (int)OBJ_TYPE::SIZE; i++)
	{
		for (unsigned int j = 0; j < m_vecObjectList[i].size(); j++)
		{
			m_vecObjectList[i][j]->FinalUpdate();
		}
	}
}

void CScene::Render(HDC _hDC)
{
	for (int i = 0; i < (int)OBJ_TYPE::SIZE; i++)
	{
		if ((UINT)OBJ_TYPE::TILE == i && m_vecObjectList[i].size() != 0)
		{
			RenderTile(_hDC);
			continue;
		}
		// 렌더부분에서 활성화 여부를 체크해서 벡터의 크기를 조절한다.
		// 메모리해제는 이벤트매니저에서 진행하기 때문에 별도를 메모리해제는 해주지 않아도 된다.
		vector<CGameObject*>::iterator iter = m_vecObjectList[i].begin();
		for (; iter != m_vecObjectList[i].end();)
		{
			if ((*iter)->GetActive())
			{
				(*iter)->Render(_hDC);
				++iter;
			}
			else
			{
				iter = m_vecObjectList[i].erase(iter);
			}
		}
	}
}

void CScene::AddObject(CGameObject* _pObj)
{
	m_vecObjectList[(int)_pObj->GetObjGroup()].push_back(_pObj);
}

void CScene::EraseObject(CGameObject* _pObj)
{
	vector<CGameObject*>::iterator iter = m_vecObjectList[(int)_pObj->GetObjGroup()].begin();

	for (; iter != m_vecObjectList[(int)_pObj->GetObjGroup()].end();)
	{
		if (*iter == _pObj)
		{
			iter = m_vecObjectList[(int)_pObj->GetObjGroup()].erase(iter);
			delete _pObj;
			break;
		}
		else
		{
			iter++;
		}
	}
}

void CScene::DeleteGroup(OBJ_TYPE _group)
{
	for (int i = 0; i < m_vecObjectList[(UINT)_group].size(); i++)
	{
		delete m_vecObjectList[(UINT)_group][i];
	}
	m_vecObjectList[(UINT)_group].clear();
}

void CScene::CreateTile(UINT _xSize, UINT _ySize)
{
	DeleteGroup(OBJ_TYPE::TILE);

	m_iTileX = _xSize;
	m_iTileY = _ySize;

	CTexture* pTileTex = SINGLE(CResourceManager)->LoadTexture(L"Tile", L"texture\\Tile\\tilemap.bmp");

	for (int i = 0; i < _ySize; i++)
	{
		for (int j = 0; j < _xSize; j++)
		{
			CTile* pTile = new CTile();
			pTile->SetPos(Vec2((float)(j * CTile::SIZE_TILE), (float)(i * CTile::SIZE_TILE)));
			pTile->SetTexture(pTileTex);
			AddObject(pTile);
		}
	}
}

void CScene::LoadTile(const wstring& _strPath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _strPath.c_str(), L"rb");      // w : write, b : binary
	assert(pFile);

	UINT	xCount = 0;
	UINT	yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	CreateTile(xCount, yCount);

	const vector<CGameObject*>& vecTile = GetGroupObject(OBJ_TYPE::TILE);
	for (UINT i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}

	fclose(pFile);
}

void CScene::RenderTile(HDC _hDC)
{
	const vector<CGameObject*>& vecTile = GetGroupObject(OBJ_TYPE::TILE);

	Vec2 vCamLook = SINGLE(CCameraManager)->GetLookAt();
	Vec2 vLeftTop = vCamLook - Vec2(WINSIZEX, WINSIZEY) / 2.f;

	int iLTX = (int)vLeftTop.x / CTile::SIZE_TILE;
	int iLTY = (int)vLeftTop.y / CTile::SIZE_TILE;
	int iLTIdx = m_iTileX * iLTY + iLTX;

	int iClientWidth = (int)WINSIZEX / CTile::SIZE_TILE;
	int iClientHeight = (int)WINSIZEY / CTile::SIZE_TILE;
	for (int iCurY = iLTY; iCurY <= (iLTY + iClientHeight); ++iCurY)
	{
		for (int iCurX = iLTX; iCurX <= (iLTX + iClientWidth); ++iCurX)
		{
			if (iCurX < 0 || m_iTileX <= iCurX || iCurY < 0 || m_iTileY <= iCurY)
			{
				continue;
			}
			int iIdx = (m_iTileX * iCurY) + iCurX;

			vecTile[iIdx]->Render(_hDC);
		}
	}
}

void CScene::ClearObject()
{
	for (int i = 0; i < (int)OBJ_TYPE::SIZE; i++)
	{
		Safe_Delete_Vec(m_vecObjectList[i]);
	}
}
