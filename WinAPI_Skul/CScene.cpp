#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "CTile.h"
#include "CCollider.h"

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
	// ����� ������� ��鿡 �����Ҵ����� �߰��� ������Ʈ�� �޸� ���������ش�.
	for (int i = 0; i < (int)OBJ_TYPE::SIZE; i++)
	{
		Safe_Delete_Vec(m_vecObjectList[i]);
	}
}

void CScene::Update()
{
	if (SINGLE(CGameManager)->GetGamePlay())
	{
		for (int i = 0; i < (int)OBJ_TYPE::SIZE; i++)
		{
			if (i == (int)OBJ_TYPE::UI) continue;
			for (unsigned int j = 0; j < m_vecObjectList[i].size(); j++)
			{
				if (m_vecObjectList[i][j]->IsDead())
					m_vecObjectList[i][j]->Update();
			}
		}
	}
	for (unsigned int j = 0; j < m_vecObjectList[(int)OBJ_TYPE::UI].size(); j++)
	{
		if (m_vecObjectList[(int)OBJ_TYPE::UI][j]->IsDead())
			m_vecObjectList[(int)OBJ_TYPE::UI][j]->Update();
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
		if ((UINT)OBJ_TYPE::TILE == i)
		{
			RenderTile();
			continue;
		}
		// �����κп��� Ȱ��ȭ ���θ� üũ�ؼ� ������ ũ�⸦ �����Ѵ�.
		// �޸������� �̺�Ʈ�Ŵ������� �����ϱ� ������ ������ �޸������� ������ �ʾƵ� �ȴ�.
		vector<CObject*>::iterator iter = m_vecObjectList[i].begin();
		for (; iter != m_vecObjectList[i].end();)
		{
			if ((*iter)->IsDead())
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
	m_vecObjectList[(int)_pObj->GetObjType()].push_back(_pObj);
}

void CScene::EraseObject(CObject* _pObj)
{
	vector<CObject*>::iterator iter = m_vecObjectList[(int)_pObj->GetObjType()].begin();

	for (; iter != m_vecObjectList[(int)_pObj->GetObjType()].end();)
	{
		if (*iter == _pObj)
		{
			iter = m_vecObjectList[(int)_pObj->GetObjType()].erase(iter);
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

void CScene::CScene::LoadTile(const wstring& strPath)
{
	DeleteGroup(OBJ_TYPE::TILE);

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strPath.c_str(), L"rb");      // w : write, b : binary
	assert(pFile);

	UINT xCount = 0;
	UINT yCount = 0;
	UINT tileCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);
	fread(&tileCount, sizeof(UINT), 1, pFile);

	CD2DImage* pImg = CResourceManager::GetInst()->LoadD2DImage(L"Tile", L"texture\\tile\\tilemap.bmp");

	for (UINT i = 0; i < tileCount; i++)
	{
		CTile* newTile = new CTile;
		newTile->Load(pFile);
		newTile->SetImage(pImg);
		newTile->SetPos(Vec2((float)(newTile->GetX() * CTile::SIZE_TILE),
							(float)(newTile->GetY() * CTile::SIZE_TILE)));

		if (TILE_TYPE::FLOATING == newTile->GetType())
		{
			newTile->CreateCollider();
			newTile->GetCollider()->SetScale(Vec2(CTile::SIZE_TILE, CTile::SIZE_TILE/2));
			newTile->GetCollider()->SetOffsetPos(Vec2(CTile::SIZE_TILE / 2.f, CTile::SIZE_TILE/4.f));
		}
		else if (TILE_TYPE::NONE != newTile->GetType())
		{
			newTile->CreateCollider();
			newTile->GetCollider()->SetScale(Vec2(CTile::SIZE_TILE, CTile::SIZE_TILE));
			newTile->GetCollider()->SetOffsetPos(Vec2(CTile::SIZE_TILE / 2.f, CTile::SIZE_TILE / 2.f));
		}

		AddObject(newTile);
	}

	fclose(pFile);
}

void CScene::RenderTile()
{
	const vector<CObject*>& vecTile = GetGroupObject(OBJ_TYPE::TILE);
	for (UINT i = 0; i < vecTile.size(); i++)
	{
		vecTile[i]->Render();
	}
}

void CScene::ChangeNextScene(SCENE_TYPE _eType)
{
	if (m_bIsChange)
		return;
	SINGLE(CCameraManager)->LodingAnimation(2.0f);
	//SINGLE(CCameraManager)->FadeOut(1.0f);
	m_eNextScene = _eType;
	m_bIsChange = true;
	m_fTime = SINGLE(CTimeManager)->GetPlayTime();
}

void CScene::DelayChange(float _iTime)
{
	if (m_fTime + 1.f <= _iTime)
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
		if (i == (int)OBJ_TYPE::PLAYER)
		{
			m_vecObjectList[i].clear();
			continue;
		}

		Safe_Delete_Vec(m_vecObjectList[i]);
	}
}
