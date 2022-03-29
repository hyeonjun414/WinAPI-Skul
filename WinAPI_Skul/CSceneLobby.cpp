#include "pch.h"
#include "CSceneLobby.h"
#include "CPlayer.h"
#include "CImageObj.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CEffect.h"
#include "CGate.h"
#include "CEnemy.h"
#include "CEnemyMelee.h"
#include "CEnemyRange.h"
#include "CUIImage.h"
#include "CUIText.h"
#include "CHunter.h"
#include "CLittleBorn.h"
#include "CBorn.h"
#include "CStatusHUD.h"
#include "CMenuUI.h"
#include "CMinimap.h"

CSceneLobby::CSceneLobby(wstring _sceneName, SCENE_TYPE _sceneType):
	CScene(_sceneName,_sceneType)
{
}

CSceneLobby::~CSceneLobby()
{
}

void CSceneLobby::Update()
{

	switch (m_eType)
	{
	case SCENE_TYPE::LOBBY_INNER:
		if (SINGLE(CGameManager)->GetPlayer()->GetPos().y >=
			SINGLE(CCameraManager)->GetWorldSize().y)
			ChangeNextScene(SCENE_TYPE::LOBBY_OUTER);
		break;
	}
	CScene::Update();


}

void CSceneLobby::Enter()
{
	switch (m_eType)
	{
	case SCENE_TYPE::LOBBY_INNER:
		LobbyInnerInit();
		break;
	case SCENE_TYPE::LOBBY_OUTER:
		LobbyOuterInit();
		break;
	default:
		break;
	}

}

void CSceneLobby::Exit()
{
	ClearObject();

	// 기존의 충돌 그릅을 해제시켜야한다.
	SINGLE(CCollisionManager)->Reset();
}

void CSceneLobby::LobbyInnerInit()
{
	GAMEPLAY(true);
	SINGLE(CCameraManager)->FadeIn(1.f);
	CreateUI();

	CPlayer* obj = SINGLE(CGameManager)->GetCurSkul();
	obj->SetPos(Vec2(1800, 200));
	SINGLE(CCameraManager)->SetCurLookAt(Vec2(800, 200));
	SINGLE(CCameraManager)->SetTarget(obj);


	// 타일맵 출력
	CImageObj* BgObj = new CImageObj(OBJ_TYPE::IMAGE,
		L"LobbyInner",
		L"texture\\stageLobby_inner.png", true);
	CREATEOBJECT(BgObj);

	CImageObj* lobbyWall = new CImageObj(OBJ_TYPE::EFFECT,
		L"LobbyWallOuter",
		L"texture\\lobby_wall_outer.png", true);
	lobbyWall->SetPos(Vec2(2303, -40));
	CREATEOBJECT(lobbyWall);

	SINGLE(CCameraManager)->SetWorldSize(Vec2(BgObj->GetImage()->GetWidth(), BgObj->GetImage()->GetHeight()));

	// 저장한 타일 충돌체 불러오기
	wstring strPath = SINGLE(CPathManager)->GetContentPath();
	strPath += L"texture\\tile\\Map\\LobbyInner.tile";
	LoadTile(strPath);

	// 어떤 오브젝트 그룹끼리 충돌할것인지 미리 정함
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::TILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::ENEMY, OBJ_TYPE::TILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::MAPOBJECT);

}

void CSceneLobby::LobbyOuterInit()
{
	GAMEPLAY(true);
	SINGLE(CCameraManager)->FadeIn(1.f);
	CreateUI();

	CPlayer* obj = SINGLE(CGameManager)->GetCurSkul();
	obj->SetPos(Vec2(WINSIZEX/2, -300));
	SINGLE(CCameraManager)->SetCurLookAt(Vec2(WINSIZEX / 2, 200));
	SINGLE(CCameraManager)->SetTarget(obj);


	// 타일맵 출력
	CImageObj* BgObj = new CImageObj(OBJ_TYPE::IMAGE,
		L"LobbyOuter",
		L"texture\\stageLobby_outer.png", true);
	CREATEOBJECT(BgObj);

	SINGLE(CCameraManager)->SetWorldSize(Vec2(BgObj->GetImage()->GetWidth(), BgObj->GetImage()->GetHeight()));

	// 저장한 타일 충돌체 불러오기
	wstring strPath = SINGLE(CPathManager)->GetContentPath();
	strPath += L"texture\\tile\\Map\\LobbyOuter.tile";
	LoadTile(strPath);

	// 어떤 오브젝트 그룹끼리 충돌할것인지 미리 정함
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::TILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::ENEMY, OBJ_TYPE::TILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::MAPOBJECT);
}

void CSceneLobby::CreateUI()
{
	CStatusHUD* pHUD = new CStatusHUD();
	pHUD->Init();

	CUIImage* pUI = new CUIImage(OBJ_TYPE::UI, L"TimerUI", L"texture\\ui\\Timer_Frame.png");
	pUI->SetScale(Vec2((float)pUI->GetImage()->GetWidth(), (float)pUI->GetImage()->GetHeight()));
	pUI->SetScaleRate(Vec2(2.f, 2.f));
	pUI->SetPos(Vec2(0, 0));
	CUIText* pTimer = new CUIText(OBJ_TYPE::UI);
	pTimer->SetPos(Vec2(20, 5));
	pTimer->SetScale(Vec2(100, 30));
	pTimer->SetFontSize(15.f);
	SINGLE(CGameManager)->SetTimer(pTimer);
	pUI->AddChild(pTimer);
	CREATEOBJECT(pUI);

	CMinimap* pMinimap = new CMinimap();
	pMinimap->Init();

	CMenuUI* pMenuUI = new CMenuUI();
	pMenuUI->Init();
}
