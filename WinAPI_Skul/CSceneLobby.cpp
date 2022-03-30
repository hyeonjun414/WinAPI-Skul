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
#include "CAnimator.h";

CSceneLobby::CSceneLobby(wstring _sceneName, SCENE_TYPE _sceneType):
	CScene(_sceneName,_sceneType)
{
}

CSceneLobby::~CSceneLobby()
{
}

void CSceneLobby::Update()
{
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

	switch (m_eType)
	{
	case SCENE_TYPE::LOBBY_INNER:
		SINGLE(CSoundManager)->Stop(L"Lobby");
		break;
	case SCENE_TYPE::LOBBY_OUTER:
		break;
	default:
		break;
	}
}

void CSceneLobby::LobbyInnerInit()
{
	GAMEPLAY(true);
	SINGLE(CCameraManager)->FadeIn(1.f);
	CreateUI();

	CPlayer* obj = SINGLE(CGameManager)->GetCurSkul();
	obj->SetPos(Vec2(800, 200));
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

	CGate* pGate = new CGate(OBJ_TYPE::MAPOBJECT, GATE_TYPE::PORTAL, SCENE_TYPE::LOBBY_OUTER);
	pGate->SetPos(Vec2(3200, 4200));
	pGate->CreateCollider();
	pGate->GetCollider()->SetScale(Vec2(1000, 20));
	CREATEOBJECT(pGate);


	CObject* pObj = new CObject(OBJ_TYPE::MAPOBJECT);
	pObj->CreateAnimator();
	pObj->GetAnimator()->CreateAnim(L"Witch_Idle", L"texture\\object\\witch_idle.png", 1.f);
	pObj->GetAnimator()->Play(L"Witch_Idle", true);
	pObj->SetPos(Vec2(1550, 485));
	pObj->SetObjDir(true);
	CREATEOBJECT(pObj);


	SINGLE(CCameraManager)->SetWorldSize(Vec2(BgObj->GetImage()->GetWidth(), BgObj->GetImage()->GetHeight()));

	// 저장한 타일 충돌체 불러오기
	wstring strPath = SINGLE(CPathManager)->GetContentPath();
	strPath += L"texture\\tile\\Map\\LobbyInner.tile";
	LoadTile(strPath);

	SINGLE(CSoundManager)->AddSound(L"Lobby", L"sound\\DemonCastle.wav", true);
	SINGLE(CSoundManager)->Play(L"Lobby");

	// 어떤 오브젝트 그룹끼리 충돌할것인지 미리 정함
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::TILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::ENEMY, OBJ_TYPE::TILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::MAPOBJECT);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::ENEMY);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::ITEM);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER_ATTACK, OBJ_TYPE::ENEMY);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER_ATTACK, OBJ_TYPE::TILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::MELEE_ATTACK, OBJ_TYPE::PLAYER);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::PROJECTILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::ENEMY, OBJ_TYPE::PROJECTILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::TILE, OBJ_TYPE::PROJECTILE);
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

	CImageObj* pGateWall = new CImageObj(OBJ_TYPE::MAPOBJECT, L"GateWall", L"texture\\object\\Gate_Wall.png", true);
	pGateWall->SetPos(Vec2(480, 430));
	CREATEOBJECT(pGateWall);

	CGate* gateObj = new CGate(OBJ_TYPE::MAPOBJECT, GATE_TYPE::NORMAL, SCENE_TYPE::STAGE_01);
	gateObj->SetPos(Vec2(1280, 650));
	CREATEOBJECT(gateObj);


	// 어떤 오브젝트 그룹끼리 충돌할것인지 미리 정함
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::TILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::ENEMY, OBJ_TYPE::TILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::MAPOBJECT);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::ENEMY);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::ITEM);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER_ATTACK, OBJ_TYPE::ENEMY);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER_ATTACK, OBJ_TYPE::TILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::MELEE_ATTACK, OBJ_TYPE::PLAYER);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::PROJECTILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::ENEMY, OBJ_TYPE::PROJECTILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::TILE, OBJ_TYPE::PROJECTILE);
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
