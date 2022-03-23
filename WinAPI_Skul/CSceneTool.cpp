#include "pch.h"
#include "CSceneTool.h"
#include "CTexture.h"
#include "resource.h"
#include "CTile.h"
#include "commdlg.h"
#include "CUI.h"
#include "CUIButton.h"
#include "CUIPanel.h"
#include "CCollider.h"
#include "CImageObj.h"
#include "CD2DImage.h"
#include "CUITileBtn.h"

INT_PTR CALLBACK TileWndProc(HWND, UINT, WPARAM, LPARAM);

CSceneTool::CSceneTool(wstring _sceneName, SCENE_TYPE _sceneType) :
	CScene(_sceneName, _sceneType),
	m_pMapImg(nullptr),
	m_hWnd(0),
	m_iIdx(0),
	m_eTileType(TILE_TYPE::NONE),
	m_velocity(500.f),
	m_iTileX(0),
	m_iTileY(0)
{
}

CSceneTool::~CSceneTool()
{
}

void CSceneTool::Update()
{
	CScene::Update();
	if (KEYCHECK(KEY::ESC) == KEY_STATE::TAP)
		ChangeNextScene(SCENE_TYPE::START);

	if (KEYCHECK(KEY::A) == KEY_STATE::HOLD)
	{
		SINGLE(CCameraManager)->Scroll(Vec2(-1, 0), 300);
	}
	if (KEYCHECK(KEY::D) == KEY_STATE::HOLD)
	{
		SINGLE(CCameraManager)->Scroll(Vec2(1, 0), 300);
	}
	if (KEYCHECK(KEY::W) == KEY_STATE::HOLD)
	{
		SINGLE(CCameraManager)->Scroll(Vec2(0, -1), 300);
	}
	if (KEYCHECK(KEY::S) == KEY_STATE::HOLD)
	{
		SINGLE(CCameraManager)->Scroll(Vec2(0, 1), 300);
	}

	SetTileIdx();
	SetTileGroup();
}

void CSceneTool::Render()
{
	const vector<CObject*>& vecTile = GetGroupObject(OBJ_TYPE::TILE);
	for (UINT i = 0; i < vecTile.size(); i++)
	{
		vecTile[i]->Render();
	}

	PrintMap();
	PrintTileLine();
	PrintTileGroup();

	const vector<CObject*>& vecUI = GetGroupObject(OBJ_TYPE::UI);
	for (UINT i = 0; i < vecUI.size(); i++)
	{
		vecUI[i]->Render();
	}
}


void CALLBACK test(DWORD_PTR _param1, DWORD_PTR _param2)
{
	CHANGESCENE(SCENE_TYPE::START);
}
void CSceneTool::Enter()
{
	SINGLE(CCameraManager)->FadeIn(1.f);

	SINGLE(CCameraManager)->SetWorldSize(Vec2(10000, 10000));
	SINGLE(CCameraManager)->SetLookAt(Vec2(WINSIZEX / 2, WINSIZEY / 2));
	
	// 모달리스 방식으로 다이얼로그를 띄우고 출력한다.
	m_hWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TILEBOX), hWnd, TileWndProc);
	ShowWindow(m_hWnd, SW_SHOW);

	CreateTile(10, 10);
	CreateTilePanel();

}

void CSceneTool::Exit()
{
	DeleteGroup(OBJ_TYPE::TILE);
	DeleteGroup(OBJ_TYPE::UI);
	EndDialog(m_hWnd, IDOK);
}

void CSceneTool::SetIdx(UINT _idx)
{
	m_iIdx = _idx;
}

void CSceneTool::SetTileColl(bool _bTileColl)
{
	m_bIsTileCol = _bTileColl;
}

void CSceneTool::SetTileIdx()
{
	if (KEYHOLD(KEY::LBTN) || KEYHOLD(KEY::RBTN))
	{
		Vec2 vMousePos = SINGLE(CKeyManager)->GetMousePos();
		vMousePos = SINGLE(CCameraManager)->GetRealPos(vMousePos);

		int iTileX = m_iTileX;
		int iTileY = m_iTileY;


		int iX = (int)vMousePos.x / CTile::SIZE_TILE;
		int iY = (int)vMousePos.y / CTile::SIZE_TILE;

		if (vMousePos.x < 0.f || iTileX <= iX ||
			vMousePos.y < 0.f || iTileY <= iY)
		{
			return;		// 타일이 없는 위치 무시
		}

		UINT iIdx = iY * iTileX + iX;
		const vector<CObject*>& vecTile = GetGroupObject(OBJ_TYPE::TILE);
		if (KEYHOLD(KEY::LBTN))
		{
			((CTile*)vecTile[iIdx])->SetImgIdx(m_iIdx);

		}
		else if (KEYHOLD(KEY::RBTN))
		{
			((CTile*)vecTile[iIdx])->SetImgIdx(0);

		}
	}
}
void CSceneTool::SetTileGroup()
{
	if (KEYHOLD(KEY::LBTN) || KEYHOLD(KEY::RBTN))
	{
		Vec2 vMousePos = MOUSEPOS;
		vMousePos = CCameraManager::GetInst()->GetRealPos(vMousePos);

		int iTileX = m_iTileX;
		int iTileY = m_iTileY;

		int iCol = (int)vMousePos.x / CTile::SIZE_TILE;
		int iRow = (int)vMousePos.y / CTile::SIZE_TILE;

		if (vMousePos.x < 0.f || iTileX <= iCol ||
			vMousePos.y < 0.f || iTileY <= iRow)
		{
			return;		// 타일이 없는 위치 무시
		}

		UINT iIdx = iRow * iTileX + iCol;
		const vector<CObject*>& vecTile = GetGroupObject(OBJ_TYPE::TILE);
		if (KEYHOLD(KEY::LBTN))
			((CTile*)vecTile[iIdx])->SetType(m_eTileType);
		else if (KEYHOLD(KEY::RBTN))
			((CTile*)vecTile[iIdx])->SetType(TILE_TYPE::NONE);
	}
}
void CSceneTool::CreateTile(UINT _xSize, UINT _ySize)
{
	DeleteGroup(OBJ_TYPE::TILE);

	m_iTileX = _xSize;
	m_iTileY = _ySize;

	CD2DImage* pImg = CResourceManager::GetInst()->LoadD2DImage(L"Tile", L"texture\\tile\\tilemap.bmp");
	CTexture* pTileTex2 = SINGLE(CResourceManager)->LoadTexture(L"Tile", L"texture\\tile\\tilemap.bmp");
	for (UINT y = 0; y < _ySize; y++)
	{
		for (UINT x = 0; x < _xSize; x++)
		{
			CTile* pTile = new CTile(OBJ_TYPE::TILE);
			pTile->SetPos(Vec2((float)(x * CTile::SIZE_TILE), (float)(y * CTile::SIZE_TILE)));
			pTile->SetX(x);
			pTile->SetY(y);
			pTile->SetImage(pImg);
			AddObject(pTile);
		}
	}
}
void CSceneTool::SaveTile(const wstring& _strPath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _strPath.c_str(), L"wb");		// w : write, b : binary
	assert(pFile);

	UINT xCount = m_iTileX;
	UINT yCount = m_iTileY;
	UINT tileCount = 0;

	const vector<CObject*>& vecTile = GetGroupObject(OBJ_TYPE::TILE);

	for (UINT i = 0; i < vecTile.size(); i++)
	{
		CTile* pTile = (CTile*)vecTile[i];
		if (0 != pTile->GetIdx() || TILE_TYPE::NONE != pTile->GetType())
			tileCount++;
	}

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);
	fwrite(&tileCount, sizeof(UINT), 1, pFile);

	for (UINT i = 0; i < vecTile.size(); i++)
	{
		CTile* pTile = (CTile*)vecTile[i];
		if (0 != pTile->GetIdx() || TILE_TYPE::NONE != pTile->GetType())
			((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}
void CSceneTool::LoadTile(const wstring& _strPath)
{
	DeleteGroup(OBJ_TYPE::TILE);

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _strPath.c_str(), L"rb");      // w : write, b : binary
	assert(pFile);

	UINT xCount = 0;
	UINT yCount = 0;
	UINT tileCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);
	fread(&tileCount, sizeof(UINT), 1, pFile);

	CreateTile(xCount, yCount);

	const vector<CObject*>& vecTile = GetGroupObject(OBJ_TYPE::TILE);
	CD2DImage* pImg = CResourceManager::GetInst()->LoadD2DImage(L"Tile", L"texture\\tile\\tilemap.bmp");
	CTile* pTile = new CTile;

	for (UINT i = 0; i < tileCount; i++)
	{
		pTile->Load(pFile);
		UINT iIdx = pTile->GetY() * xCount + pTile->GetX();
		((CTile*)vecTile[iIdx])->SetX(pTile->GetX());
		((CTile*)vecTile[iIdx])->SetY(pTile->GetY());
		((CTile*)vecTile[iIdx])->SetImgIdx(pTile->GetIdx());
		((CTile*)vecTile[iIdx])->SetType(pTile->GetType());
	}

	fclose(pFile);
}
void CSceneTool::SaveTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);			// 구조체 사이즈.
	ofn.hwndOwner = hWnd;							// 부모 윈도우 지정.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName;							// 나중에 완성된 경로가 채워질 버퍼 지정.
	ofn.nMaxFile = sizeof(szName);					// lpstrFile에 지정된 버퍼의 문자 수.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile";	// 필터 설정
	ofn.nFilterIndex = 0;							// 기본 필터 세팅. 0는 all로 초기 세팅됨. 처음꺼.
	ofn.lpstrFileTitle = nullptr;					// 타이틀 바
	ofn.nMaxFileTitle = 0;							// 타이틀 바 문자열 크기. nullptr이면 0.
	wstring strTileFolder = SINGLE(CPathManager)->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();	// 초기경로. 우리는 타일 저장할거기 때문에, content->tile 경로로 해두자.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // 스타일

	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}
}
void CSceneTool::LoadTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);			// 구조체 사이즈.
	ofn.hwndOwner = hWnd;							// 부모 윈도우 지정.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName;							// 나중에 완성된 경로가 채워질 버퍼 지정.
	ofn.nMaxFile = sizeof(szName);					// lpstrFile에 지정된 버퍼의 문자 수.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile";	// 필터 설정
	ofn.nFilterIndex = 0;							// 기본 필터 세팅. 0는 all로 초기 세팅됨. 처음꺼.
	ofn.lpstrFileTitle = nullptr;					// 타이틀 바
	ofn.nMaxFileTitle = 0;							// 타이틀 바 문자열 크기. nullptr이면 0.
	wstring strTileFolder = SINGLE(CPathManager)->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();	// 초기경로. 우리는 타일 저장할거기 때문에, content->tile 경로로 해두자.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // 스타일

	if (GetOpenFileName(&ofn))
	{
		LoadTile(szName);
	}
}

void CSceneTool::LoadMap()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);  // 구조체 사이즈.
	ofn.hwndOwner = hWnd; // 부모 윈도우 지정.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName; // 나중에 완성된 경로가 채워질 버퍼 지정.
	ofn.nMaxFile = sizeof(szName); // lpstrFile에 지정된 버퍼의 문자 수.
	ofn.lpstrFilter = L"ALL\0*.*\0Image\0*.png"; // 필터 설정
	ofn.nFilterIndex = 0; // 기본 필터 세팅. 0는 all로 초기 세팅됨. 처음꺼.
	ofn.lpstrFileTitle = nullptr; // 타이틀 바
	ofn.nMaxFileTitle = 0; // 타이틀 바 문자열 크기. nullptr이면 0.
	wstring strTileFolder = CPathManager::GetInst()->GetContentPath();
	strTileFolder += L"map";
	ofn.lpstrInitialDir = strTileFolder.c_str(); // 초기경로. 우리는 타일 저장할거기 때문에, content->tile 경로로 해두자.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // 스타일

	if (GetOpenFileName(&ofn))
	{
		m_pMapImg = CResourceManager::GetInst()->LoadToolD2DImage(szName);
	}
}

void ClickTileGroupButton(DWORD_PTR param1, DWORD_PTR param2)
{
	CSceneTool* scene_tool = (CSceneTool*)param1;
	CUIButton* btn = (CUIButton*)param2;
	scene_tool->ClickTileGroup(btn);
}

void ClickTileButton(DWORD_PTR param1, DWORD_PTR param2)
{
	// param1 : Scene_tool
// param2 : CTileButton
	CSceneTool* scene_tool = (CSceneTool*)param1;
	CUITileBtn* button = (CUITileBtn*)param2;
	scene_tool->ClickTile(button);
}

void CSceneTool::ClickTileGroup(CUIButton* _btn)
{
	if (m_eTileType == TILE_TYPE::NONE)
	{
		m_eTileType = TILE_TYPE::GROUND;
		_btn->SetText(L"GROUND");
	}
	else if (m_eTileType == TILE_TYPE::GROUND)
	{
		m_eTileType = TILE_TYPE::FLOATING;
		_btn->SetText(L"FLOATING");
	}
	else if (m_eTileType == TILE_TYPE::FLOATING)
	{
		m_eTileType = TILE_TYPE::WALL;
		_btn->SetText(L"WALL");
	}
	else if (m_eTileType == TILE_TYPE::WALL)
	{
		m_eTileType = TILE_TYPE::NONE;
		_btn->SetText(L"NONE");
	}
}

void CSceneTool::ClickTile(CUITileBtn* _btn)
{
	SetIdx(_btn->GetIdx());
}

void CSceneTool::CreateTilePanel()
{
	CUIPanel* panelTile = new CUIPanel(OBJ_TYPE::UI);
	panelTile->SetName(L"panelTile");
	panelTile->SetScale(Vec2(200, 100));
	panelTile->SetPos(Vec2(WINSIZEX - 450.f, 50.f));

	CUIButton* btnTileGroup = new CUIButton(OBJ_TYPE::UI);
	btnTileGroup->SetScale(Vec2(100.f, 50.f));
	btnTileGroup->SetPos(Vec2(50.f, 25.f));
	btnTileGroup->SetText(L"NONE");
	btnTileGroup->SetClickCallBack(ClickTileGroupButton, (DWORD_PTR)this, (DWORD_PTR)btnTileGroup);
	panelTile->AddChild(btnTileGroup);

	AddObject(panelTile);
}

void CSceneTool::PrintMap()
{
	if (nullptr == m_pMapImg)
		return;

	Vec2 pos = CCameraManager::GetInst()->GetCurLookAt();
	pos = pos - Vec2(WINSIZEX / 2.f, WINSIZEY / 2.f);

	CRenderManager::GetInst()->RenderImage(
		m_pMapImg,
		0-pos.x,
		0-pos.y,
		m_pMapImg->GetWidth()- pos.x,
		m_pMapImg->GetHeight()- pos.y, 1.0f
	);
}

void CSceneTool::PrintTileLine()
{
	Vec2 pos = CCameraManager::GetInst()->GetCurLookAt();
	pos = pos - Vec2(WINSIZEX / 2.f, WINSIZEY / 2.f);

	// 가로줄 출력
	for (UINT y = 0; y <= m_iTileY; y++)
	{
		CRenderManager::GetInst()->RenderLine(
			Vec2(0 - pos.x, y * CTile::SIZE_TILE - pos.y),
			Vec2(CTile::SIZE_TILE * m_iTileX - pos.x, y * CTile::SIZE_TILE - pos.y)
		);
	}

	// 세로줄 출력
	for (UINT x = 0; x <= m_iTileX; x++)
	{
		CRenderManager::GetInst()->RenderLine(
			Vec2(x * CTile::SIZE_TILE - pos.x, 0 - pos.y),
			Vec2(x * CTile::SIZE_TILE - pos.x, CTile::SIZE_TILE * m_iTileY - pos.y)
		);
		CRenderManager::GetInst()->RenderLine(
			Vec2(x * CTile::SIZE_TILE - pos.x, 0 - pos.y),
			Vec2(x * CTile::SIZE_TILE - pos.x, CTile::SIZE_TILE * m_iTileY - pos.y),
			RGB(255, 0, 255), 40.f
		);
	}
}

void CSceneTool::PrintTileGroup()
{
	Vec2 pos = CCameraManager::GetInst()->GetCurLookAt();
	pos = pos - Vec2(WINSIZEX / 2.f, WINSIZEY / 2.f);

	const vector<CObject*>& vecTile = GetGroupObject(OBJ_TYPE::TILE);
	CTile* pTile;

	for (UINT i = 0; i < vecTile.size(); i++)
	{
		pTile = (CTile*)vecTile[i];
		if (TILE_TYPE::GROUND == pTile->GetType())
		{
			CRenderManager::GetInst()->RenderEllipse(
				pTile->GetPos().x + CTile::SIZE_TILE / 2.f - pos.x,
				pTile->GetPos().y + CTile::SIZE_TILE / 2.f - pos.y,
				CTile::SIZE_TILE / 2.f,
				CTile::SIZE_TILE / 2.f,
				RGB(255, 0, 0),
				3.f
			);
		}
		else if (TILE_TYPE::FLOATING == pTile->GetType())
		{
			CRenderManager::GetInst()->RenderEllipse(
				pTile->GetPos().x + CTile::SIZE_TILE / 2.f - pos.x,
				pTile->GetPos().y + CTile::SIZE_TILE / 2.f - pos.y,
				CTile::SIZE_TILE / 2.f,
				CTile::SIZE_TILE / 2.f,
				RGB(0, 255, 0),
				3.f
			);
		}
		else if (TILE_TYPE::WALL == pTile->GetType())
		{
			CRenderManager::GetInst()->RenderEllipse(
				pTile->GetPos().x + CTile::SIZE_TILE / 2.f - pos.x,
				pTile->GetPos().y + CTile::SIZE_TILE / 2.f - pos.y,
				CTile::SIZE_TILE / 2.f,
				CTile::SIZE_TILE / 2.f,
				RGB(0, 0, 255),
				3.f
			);
		}
	}
}


// 타일 다이얼로그 박스의 메시지 처리기.
INT_PTR CALLBACK TileWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BTN_SAVE)
		{
			CScene* pCurScene = SINGLE(CSceneManager)->GetCurScene();
			CSceneTool* pToolScene = dynamic_cast<CSceneTool*>(pCurScene);
			assert(pToolScene);

			pToolScene->SaveTileData();

			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_BTN_LOAD)
		{
			CScene* pCurScene = SINGLE(CSceneManager)->GetCurScene();
			CSceneTool* pToolScene = dynamic_cast<CSceneTool*>(pCurScene);
			assert(pToolScene);

			pToolScene->LoadTileData();

			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_BTN_SIZE)
		{
			// 입력된 값을 반환시킨다.
			int x = GetDlgItemInt(hDlg, IDC_EDIT_SIZEX, nullptr, false);
			int y = GetDlgItemInt(hDlg, IDC_EDIT_SIZEY, nullptr, false);

			CScene* pCurScene = SINGLE(CSceneManager)->GetCurScene();
			CSceneTool* pToolScene = dynamic_cast<CSceneTool*>(pCurScene);
			assert(pToolScene);

			pToolScene->CreateTile(x, y);

		}
		else if (LOWORD(wParam) == IDC_BTN_MAP)
		{
			CScene* pCurScene = CSceneManager::GetInst()->GetCurScene();

			CSceneTool* pToolScene = dynamic_cast<CSceneTool*>(pCurScene);
			assert(pToolScene);

			pToolScene->LoadMap();

			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}