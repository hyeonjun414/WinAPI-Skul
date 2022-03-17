#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "CTile.h"

CScene::CScene() :
	m_strName{},
	m_eType(SCENE_TYPE::NONE),
	m_eNextScene(SCENE_TYPE::NONE),
	m_bIsChange(false),
	m_iTileX(0),
	m_iTileY(0)
{
}

CScene::CScene(wstring _strName, SCENE_TYPE _eTYpe) :
	m_strName(_strName),
	m_eType(_eTYpe),
	m_eNextScene(SCENE_TYPE::NONE),
	m_bIsChange(false),
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
			if (m_vecObjectList[i][j]->GetActive())
				m_vecObjectList[i][j]->Update();
		}
	}

	if (m_bIsChange)
		DelayChange(SINGLE(CTimeManager)->GetPlayTime());
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

void CScene::Render()
{
	for (int i = 0; i < (int)OBJ_TYPE::SIZE; i++)
	{
		if ((UINT)OBJ_TYPE::TILE == i && m_vecObjectList[i].size() != 0)
		{
			RenderTile();
			continue;
		}
		// 렌더부분에서 활성화 여부를 체크해서 벡터의 크기를 조절한다.
		// 메모리해제는 이벤트매니저에서 진행하기 때문에 별도를 메모리해제는 해주지 않아도 된다.
		vector<CObject*>::iterator iter = m_vecObjectList[i].begin();
		for (; iter != m_vecObjectList[i].end();)
		{
			if ((*iter)->GetActive())
			{
				(*iter)->Render();
				++iter;
			}
			else
			{
				iter = m_vecObjectList[i].erase(iter);
			}
		}
	}
}

void CScene::AddObject(CObject* _pObj)
{
	m_vecObjectList[(int)_pObj->GetObjGroup()].push_back(_pObj);
}

void CScene::EraseObject(CObject* _pObj)
{
	vector<CObject*>::iterator iter = m_vecObjectList[(int)_pObj->GetObjGroup()].begin();

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

	CD2DImage* pTileTex = SINGLE(CResourceManager)->LoadD2DImage(L"Tile", L"texture\\Tile\\tilemap.bmp");
	CTexture* pTileTex2 = SINGLE(CResourceManager)->LoadTexture(L"Tile", L"texture\\Tile\\tilemap.bmp");

	for (UINT i = 0; i < _ySize; i++)
	{
		for (UINT j = 0; j < _xSize; j++)
		{
			CTile* pTile = new CTile();
			pTile->SetPos(Vec2((float)(j * CTile::SIZE_TILE), (float)(i * CTile::SIZE_TILE)));
			pTile->SetImage(pTileTex);
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
	UINT	tileCount = 0;
	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	CreateTile(xCount, yCount);

	const vector<CObject*>& vecTile = GetGroupObject(OBJ_TYPE::TILE);
	for (UINT i = 0; i < vecTile.size(); i++)
	{
		// 위치 정보를 넣어줌.
		// 충돌 정보가 있다면 충돌체도 생성.
		((CTile*)vecTile[i])->Load(pFile);
	}

	fclose(pFile);
}

void CScene::RenderTile()
{
	const vector<CObject*>& vecTile = GetGroupObject(OBJ_TYPE::TILE);

	Vec2 vCamLook = SINGLE(CCameraManager)->GetCurLookAt();
	Vec2 vLeftTop = vCamLook - Vec2(WINSIZEX, WINSIZEY) / 2;

	UINT iLTX = (int)vLeftTop.x / CTile::SIZE_TILE;
	UINT iLTY = (int)vLeftTop.y / CTile::SIZE_TILE;
	UINT iLTIdx = m_iTileX * iLTY + iLTX;

	UINT iClientWidth = (int)WINSIZEX / CTile::SIZE_TILE;
	UINT iClientHeight = (int)WINSIZEY / CTile::SIZE_TILE;
	for (UINT iCurY = iLTY; iCurY <= (iLTY + iClientHeight); ++iCurY)
	{
		for (UINT iCurX = iLTX; iCurX <= (iLTX + iClientWidth); ++iCurX)
		{
			if (iCurX < 0 || m_iTileX <= iCurX || iCurY < 0 || m_iTileY <= iCurY)
			{
				continue;
			}
			int iIdx = (m_iTileX * iCurY) + iCurX;

			vecTile[iIdx]->Render();
		}
	}
}

void CScene::ChangeNextScene(SCENE_TYPE _eType)
{
	if (m_bIsChange)
		return;

	SINGLE(CCameraManager)->FadeOut(1.0f);
	m_eNextScene = _eType;
	m_bIsChange = true;
	m_iTime = SINGLE(CTimeManager)->GetPlayTime();
}

void CScene::DelayChange(UINT _iTime)
{
	if (m_iTime + 1 <= _iTime)
	{
		CHANGESCENE(m_eNextScene);
		m_eNextScene = SCENE_TYPE::NONE;
		m_bIsChange = false;
	}
}

void CScene::ClearObject()
{
	for (int i = 0; i < (int)OBJ_TYPE::SIZE; i++)
	{
		Safe_Delete_Vec(m_vecObjectList[i]);
	}
}
