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
	
	// ��޸��� ������� ���̾�α׸� ���� ����Ѵ�.
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
			return;		// Ÿ���� ���� ��ġ ����
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

	ofn.lStructSize = sizeof(OPENFILENAME);			// ����ü ������.
	ofn.hwndOwner = hWnd;							// �θ� ������ ����.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName;							// ���߿� �ϼ��� ��ΰ� ä���� ���� ����.
	ofn.nMaxFile = sizeof(szName);					// lpstrFile�� ������ ������ ���� ��.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile";	// ���� ����
	ofn.nFilterIndex = 0;							// �⺻ ���� ����. 0�� all�� �ʱ� ���õ�. ó����.
	ofn.lpstrFileTitle = nullptr;					// Ÿ��Ʋ ��
	ofn.nMaxFileTitle = 0;							// Ÿ��Ʋ �� ���ڿ� ũ��. nullptr�̸� 0.
	wstring strTileFolder = SINGLE(CPathManager)->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();	// �ʱ���. �츮�� Ÿ�� �����Ұű� ������, content->tile ��η� �ص���.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // ��Ÿ��

	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}
}
void CToolScene::LoadTileData()
{
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);			// ����ü ������.
	ofn.hwndOwner = hWnd;							// �θ� ������ ����.
	wchar_t szName[256] = {};
	ofn.lpstrFile = szName;							// ���߿� �ϼ��� ��ΰ� ä���� ���� ����.
	ofn.nMaxFile = sizeof(szName);					// lpstrFile�� ������ ������ ���� ��.
	ofn.lpstrFilter = L"ALL\0*.*\0tile\0*.tile";	// ���� ����
	ofn.nFilterIndex = 0;							// �⺻ ���� ����. 0�� all�� �ʱ� ���õ�. ó����.
	ofn.lpstrFileTitle = nullptr;					// Ÿ��Ʋ ��
	ofn.nMaxFileTitle = 0;							// Ÿ��Ʋ �� ���ڿ� ũ��. nullptr�̸� 0.
	wstring strTileFolder = SINGLE(CPathManager)->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();	// �ʱ���. �츮�� Ÿ�� �����Ұű� ������, content->tile ��η� �ص���.
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // ��Ÿ��

	if (GetOpenFileName(&ofn))
	{
		LoadTile(szName);
	}
}





// Ÿ�� ���̾�α� �ڽ��� �޽��� ó����.
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
			// �Էµ� ���� ��ȯ��Ų��.
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
				SetWindowText(hDlg, L"üũ�� ���� �Ǿ����ϴ�.");

				CScene* pCurScene = SINGLE(CSceneManager)->GetCurScene();

				CToolScene* pToolScene = dynamic_cast<CToolScene*>(pCurScene);
				assert(pToolScene);

				pToolScene->SetTileColl(false);

			}
			else
			{
				SetWindowText(hDlg, L"üũ�� ���� �Ǿ����ϴ�.");

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