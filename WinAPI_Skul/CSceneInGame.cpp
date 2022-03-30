#include "pch.h"
#include "CSceneInGame.h"
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

CSceneInGame::CSceneInGame()
{
}

CSceneInGame::CSceneInGame(wstring _sceneName, SCENE_TYPE _sceneType) :
	CScene(_sceneName, _sceneType)
{
}


CSceneInGame::~CSceneInGame()
{
}

void CSceneInGame::Update()
{
	CScene::Update();


}

void CSceneInGame::Enter()
{
	switch (m_eType)
	{
	case SCENE_TYPE::STAGE_01:
		Stage01Init();
		break;
	case SCENE_TYPE::STAGE_02:
		Stage02Init();
		break;
	}

}

void CSceneInGame::Exit()
{
	ClearObject();

	switch (m_eType)
	{
	case SCENE_TYPE::STAGE_01:
		SINGLE(CSoundManager)->Stop(L"Ch1Bgm");
		break;
	case SCENE_TYPE::STAGE_02:
		SINGLE(CSoundManager)->Stop(L"Ch1Bgm");
		break;
	default:
		break;
	}

	// 기존의 충돌 그릅을 해제시켜야한다.
	SINGLE(CCollisionManager)->Reset();


}

void CSceneInGame::Stage01Init()
{
	GAMEPLAY(true);
	SINGLE(CCameraManager)->FadeIn(1.f);
	CreateUI();


	CPlayer* obj = SINGLE(CGameManager)->GetCurSkul();
	obj->SetPos(Vec2(500, 700));
	SINGLE(CCameraManager)->SetCurLookAt(Vec2(500, 700));
	SINGLE(CCameraManager)->SetTarget(obj);



	CImageObj* BgObj = nullptr;
	// 백그라운드 레이어 생성
	BgObj = new CImageObj(OBJ_TYPE::IMAGE, L"Stage01BG1", L"texture\\background\\stage01_1.png", true);
	BgObj->SetDepth(16.f);
	CREATEOBJECT(BgObj);
	BgObj = new CImageObj(OBJ_TYPE::IMAGE, L"Stage01BG2", L"texture\\background\\stage01_2.png", true);
	BgObj->SetDepth(14.f);
	CREATEOBJECT(BgObj);
	BgObj = new CImageObj(OBJ_TYPE::IMAGE, L"Stage01BG3", L"texture\\background\\stage01_3.png", true);
	BgObj->SetDepth(12.f);
	CREATEOBJECT(BgObj);
	BgObj = new CImageObj(OBJ_TYPE::IMAGE, L"Stage01BG4", L"texture\\background\\stage01_4.png", true);
	BgObj->SetDepth(10.0f);
	CREATEOBJECT(BgObj);
	BgObj = new CImageObj(OBJ_TYPE::IMAGE, L"Stage01BG5", L"texture\\background\\stage01_5.png", true);
	BgObj->SetDepth(8.0f);
	CREATEOBJECT(BgObj);
	BgObj = new CImageObj(OBJ_TYPE::IMAGE, L"Stage01BG6", L"texture\\background\\stage01_6.png", true);
	BgObj->SetDepth(6.0f);
	CREATEOBJECT(BgObj);

	// 타일맵 출력
	BgObj = new CImageObj(OBJ_TYPE::IMAGE,
		L"Stage01map",
		L"texture\\stage01_map.png", true);
	SINGLE(CCameraManager)->SetWorldSize(Vec2(BgObj->GetImage()->GetWidth(), BgObj->GetImage()->GetHeight()));

	CREATEOBJECT(BgObj);

	CEnemy* monsterMelee = new CEnemyMelee(OBJ_TYPE::ENEMY, ENEMY_TYPE::BIG_KNIGHT);
	monsterMelee->SetPos(Vec2(900.f, 800.f));
	CREATEOBJECT(monsterMelee);
	monsterMelee = new CEnemyMelee(OBJ_TYPE::ENEMY, ENEMY_TYPE::BIG_KNIGHT);
	monsterMelee->SetPos(Vec2(1300.f, 1300.f));
	CREATEOBJECT(monsterMelee);
	monsterMelee = new CEnemyMelee(OBJ_TYPE::ENEMY, ENEMY_TYPE::BIG_KNIGHT);
	monsterMelee->SetPos(Vec2(1900.f, 1300.f));
	CREATEOBJECT(monsterMelee);

	CEnemy*monsterRange = new CEnemyRange(OBJ_TYPE::ENEMY, ENEMY_TYPE::WIZARD);
	monsterRange->SetPos(Vec2(1670.f, 750.f));
	CREATEOBJECT(monsterRange);
	monsterRange = new CEnemyRange(OBJ_TYPE::ENEMY, ENEMY_TYPE::WIZARD);
	monsterRange->SetPos(Vec2(1350.f, 880.f));
	CREATEOBJECT(monsterRange);




	CGate* gateObj = new CGate(OBJ_TYPE::MAPOBJECT, GATE_TYPE::NORMAL, SCENE_TYPE::STAGE_02);
	gateObj->SetPos(Vec2(2700, 1160));
	CREATEOBJECT(gateObj);

	CBorn* pItem = new CBorn(SKUL_TYPE::Hunter);
	pItem->SetPos(Vec2(2400, 1110));
	pItem->Init();
	CREATEOBJECT(pItem);


	// 저장한 타일 충돌체 불러오기
	wstring strPath = SINGLE(CPathManager)->GetContentPath();
	strPath += L"texture\\tile\\Map\\stage01.tile";
	LoadTile(strPath);

	// 사운드 설정
	SINGLE(CSoundManager)->AddSound(L"Ch1Bgm", L"sound\\Chapter1.wav", true);
	SINGLE(CSoundManager)->Play(L"Ch1Bgm");

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

void CSceneInGame::Stage02Init()
{
	GAMEPLAY(true);
	SINGLE(CCameraManager)->FadeIn(1.f);
	CreateUI();

	CPlayer* obj = SINGLE(CGameManager)->GetCurSkul();
	obj->SetPos(Vec2(200, 1800));
	SINGLE(CCameraManager)->SetCurLookAt(Vec2(200, 1800));

	SINGLE(CCameraManager)->SetTarget(obj);


	CImageObj* BgObj = nullptr;
	// 백그라운드 레이어 생성
	BgObj = new CImageObj(OBJ_TYPE::IMAGE, L"Stage01BG1", L"texture\\background\\stage01_1.png", true);
	BgObj->SetDepth(16.f);
	CREATEOBJECT(BgObj);
	BgObj = new CImageObj(OBJ_TYPE::IMAGE, L"Stage01BG2", L"texture\\background\\stage01_2.png", true);
	BgObj->SetDepth(14.f);
	CREATEOBJECT(BgObj);
	BgObj = new CImageObj(OBJ_TYPE::IMAGE, L"Stage01BG3", L"texture\\background\\stage01_3.png", true);
	BgObj->SetDepth(12.f);
	CREATEOBJECT(BgObj);
	BgObj = new CImageObj(OBJ_TYPE::IMAGE, L"Stage01BG4", L"texture\\background\\stage01_4.png", true);
	BgObj->SetDepth(10.0f);
	CREATEOBJECT(BgObj);
	BgObj = new CImageObj(OBJ_TYPE::IMAGE, L"Stage01BG5", L"texture\\background\\stage01_5.png", true);
	BgObj->SetDepth(8.0f);
	CREATEOBJECT(BgObj);
	BgObj = new CImageObj(OBJ_TYPE::IMAGE, L"Stage01BG6", L"texture\\background\\stage01_6.png", true);
	BgObj->SetDepth(6.0f);
	CREATEOBJECT(BgObj);

	// 타일맵 출력
	BgObj = new CImageObj(OBJ_TYPE::IMAGE,
		L"Stage02map",
		L"texture\\stage02_map.png", true);
	SINGLE(CCameraManager)->SetWorldSize(Vec2(BgObj->GetImage()->GetWidth(), BgObj->GetImage()->GetHeight()));

	CREATEOBJECT(BgObj);

	CEnemy* monsterMelee = new CEnemyMelee(OBJ_TYPE::ENEMY, ENEMY_TYPE::BIG_KNIGHT);
	monsterMelee->SetPos(Vec2(1050.f, 1700.f));
	CREATEOBJECT(monsterMelee);
	monsterMelee = new CEnemyMelee(OBJ_TYPE::ENEMY, ENEMY_TYPE::BIG_KNIGHT);
	monsterMelee->SetPos(Vec2(1850.f, 1600.f));
	CREATEOBJECT(monsterMelee);
	monsterMelee = new CEnemyMelee(OBJ_TYPE::ENEMY, ENEMY_TYPE::BIG_KNIGHT);
	monsterMelee->SetPos(Vec2(2750.f, 1600.f));
	CREATEOBJECT(monsterMelee);

	CEnemy* monsterRange = new CEnemyRange(OBJ_TYPE::ENEMY, ENEMY_TYPE::WIZARD);
	monsterRange->SetPos(Vec2(550.f, 820.f));
	CREATEOBJECT(monsterRange);
	monsterRange = new CEnemyRange(OBJ_TYPE::ENEMY, ENEMY_TYPE::WIZARD);
	monsterRange->SetPos(Vec2(890.f, 1520.f));
	CREATEOBJECT(monsterRange);
	monsterRange = new CEnemyRange(OBJ_TYPE::ENEMY, ENEMY_TYPE::WIZARD);
	monsterRange->SetPos(Vec2(2280.f, 1600.f));
	CREATEOBJECT(monsterRange);

	CGate* gateObj = new CGate(OBJ_TYPE::MAPOBJECT, GATE_TYPE::BOSS, SCENE_TYPE::BOSS);
	gateObj->SetPos(Vec2(3580, 1415));
	CREATEOBJECT(gateObj);


	// 저장한 타일 충돌체 불러오기
	wstring strPath = SINGLE(CPathManager)->GetContentPath();
	strPath += L"texture\\tile\\Map\\stage02.tile";
	LoadTile(strPath);


	// 사운드 설정
	SINGLE(CSoundManager)->AddSound(L"Ch1Bgm", L"sound\\Chapter1.wav", true);
	SINGLE(CSoundManager)->Play(L"Ch1Bgm");

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

void CSceneInGame::CreateUI()
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
