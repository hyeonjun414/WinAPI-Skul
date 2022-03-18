#include "pch.h"
#include "CToolScene.h"
#include "CTexture.h"
#include "resource.h"
#include "CTile.h"
#include "commdlg.h"
#include "CUI.h"
#include "CButtonUI.h"
#include "CPanelUI.h"
#include "CCollider.h"
#include "CImageObj.h"
#include "CD2DImage.h"

INT_PTR CALLBACK TileWndProc(HWND, UINT, WPARAM, LPARAM);

CToolScene::CToolScene()
{
}

CToolScene::CToolScene(wstring _sceneName, SCENE_TYPE _sceneType) :
	CScene(_sceneName, _sceneType)
{
}

CToolScene::~CToolScene()
{
}

void CToolScene::Update()
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
}


void CALLBACK test(DWORD_PTR _param1, DWORD_PTR _param2)
{
	CHANGESCENE(SCENE_TYPE::START);
}
void CToolScene::Enter()
{
	SINGLE(CCameraManager)->FadeIn(2.f);

	SINGLE(CCameraManager)->SetWorldSize(Vec2(10000, 10000));
	SINGLE(CCameraManager)->SetLookAt(Vec2(WINSIZEX / 2, WINSIZEY / 2));
	
	// 모달리스 방식으로 다이얼로그를 띄우고 출력한다.
	m_hWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TILEBOX), hWnd, TileWndProc);
	ShowWindow(m_hWnd, SW_SHOW);

	CImageObj* BgObj = new CImageObj(OBJ_TYPE::IMAGE,
		L"InGameSceneTile",
		L"texture\\stage01.png", true);
	AddObject(BgObj);

	CreateTile(0, 0);

}

void CToolScene::Exit()
{
	DeleteGroup(OBJ_TYPE::TILE);
	DeleteGroup(OBJ_TYPE::UI);
	EndDialog(m_hWnd, IDOK);
}

void CToolScene::SetIdx(UINT _idx)
{
	m_iIdx = _idx;
}

void CToolScene::SetTileColl(bool _bTileColl)
{
	m_bIsTileCol = _bTileColl;
}

void CToolScene::SetTileIdx()
{
	if (KEYCHECK(KEY::LBTN)==KEY_STATE::HOLD)
	{
		Vec2 vMousePos = SINGLE(CKeyManager)->GetMousePos();
		vMousePos = SINGLE(CCameraManager)->GetRealPos(vMousePos);

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		int iX = (int)vMousePos.x / CTile::SIZE_TILE;
		int iY = (int)vMousePos.y / CTile::SIZE_TILE;

		if (vMousePos.x < 0.f || iTileX <= iX ||
			vMousePos.y < 0.f || iTileY <= iY)
		{
			return;		// 타일이 없는 위치 무시
		}

		UINT iIdx = iY * iTileX + iX;
		const vector<CObject*>& vecTile = GetGroupObject(OBJ_TYPE::TILE);
		((CTile*)vecTile[iIdx])->SetImgIdx(m_iIdx);
		if (m_bIsTileCol)
		{
			((CTile*)vecTile[iIdx])->CreateCollider();
			((CTile*)vecTile[iIdx])->GetCollider()->SetOffsetPos(vecTile[iIdx]->GetScale()/2);
			((CTile*)vecTile[iIdx])->GetCollider()->SetScale(vecTile[iIdx]->GetScale());
			((CTile*)vecTile[iIdx])->SetColl(true);
		}
		else
		{
			delete vecTile[iIdx]->GetCollider();
			vecTile[iIdx]->SetCollider(nullptr);
			((CTile*)vecTile[iIdx])->SetColl(false);
		}
	}
}
void CToolScene::SaveTile(const wstring& _strPath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _strPath.c_str(), L"wb");
	assert(pFile);

	UINT	xCount = GetTileX();
	UINT	yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);
	
	const vector<CObject*>& vecTile = GetGroupObject(OBJ_TYPE::TILE);
	for (UINT i = 0; i < vecTile.size(); i++)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}
void CToolScene::SaveTileData()
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
void CToolScene::LoadTileData()
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
			CToolScene* pToolScene = dynamic_cast<CToolScene*>(pCurScene);
			assert(pToolScene);

			pToolScene->SaveTileData();

			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_BTN_LOAD)
		{
			CScene* pCurScene = SINGLE(CSceneManager)->GetCurScene();
			CToolScene* pToolScene = dynamic_cast<CToolScene*>(pCurScene);
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
			CToolScene* pToolScene = dynamic_cast<CToolScene*>(pCurScene);
			assert(pToolScene);

			pToolScene->CreateTile(x, y);

		}
		else if (LOWORD(wParam) == IDC_BTN_TILE)
		{
			int m_iIdx = GetDlgItemInt(hDlg, IDC_EDIT_TILE, nullptr, false);

			CScene* pCurScene = SINGLE(CSceneManager)->GetCurScene();
			CToolScene* pToolScene = dynamic_cast<CToolScene*>(pCurScene);
			assert(pToolScene);

			CTexture* pTex = SINGLE(CResourceManager)->FindTexture(L"Tile");

			UINT iWidth = pTex->GetWidth();
			UINT iHeight = pTex->GetHeight();

			UINT iMaxY = iHeight / CTile::SIZE_TILE;
			UINT iMaxX = iWidth / CTile::SIZE_TILE;

			UINT iCurY = (m_iIdx / iMaxX) % iMaxY;
			UINT iCurX = (m_iIdx % iMaxX);

			StretchBlt(GetDC(hDlg),
				(int)(100),
				(int)(150),
				(int)(CTile::SIZE_TILE) * 2,
				(int)(CTile::SIZE_TILE) * 2,
				pTex->GetDC(),
				(int)(iCurX * CTile::SIZE_TILE),
				(int)(iCurY * CTile::SIZE_TILE),
				(int)(CTile::SIZE_TILE),
				(int)(CTile::SIZE_TILE),
				SRCCOPY);

			//BitBlt(GetDC(hDlg),
			//	(int)(150),
			//	(int)(150),
			//	(int)(CTile::SIZE_TILE),
			//	(int)(CTile::SIZE_TILE),
			//	pTex->GetDC(),
			//	(int)(iCurX * CTile::SIZE_TILE),
			//	(int)(iCurY * CTile::SIZE_TILE),
			//	SRCCOPY);

			pToolScene->SetIdx(m_iIdx);
		}
		else if (LOWORD(wParam) == IDC_CHECK_COLL)
		{
			HWND user_check = GetDlgItem(hDlg, IDC_CHECK_COLL);
			if (SendMessage(user_check, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			{
				SetWindowText(hDlg, L"체크가 해제 되었습니다.");

				CScene* pCurScene = SINGLE(CSceneManager)->GetCurScene();

				CToolScene* pToolScene = dynamic_cast<CToolScene*>(pCurScene);
				assert(pToolScene);

				pToolScene->SetTileColl(false);

			}
			else
			{
				SetWindowText(hDlg, L"체크가 설정 되었습니다.");

				CScene* pCurScene = SINGLE(CSceneManager)->GetCurScene();

				CToolScene* pToolScene = dynamic_cast<CToolScene*>(pCurScene);
				assert(pToolScene);

				pToolScene->SetTileColl(true);
			}
		}
		break;
	}
	return (INT_PTR)FALSE;
}