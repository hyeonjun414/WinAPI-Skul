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
	default:
		break;
	}

}

void CSceneInGame::Exit()
{
	ClearObject();

	// 기존의 충돌 그릅을 해제시켜야한다.
	SINGLE(CCollisionManager)->Reset();
}

void CSceneInGame::Stage01Init()
{
	GAMEPLAY(true);
	SINGLE(CCameraManager)->FadeIn(1.f);
	CreateUI();

	CPlayer* obj = SINGLE(CGameManager)->GetCurSkul();
	obj->GetPlayerInfo().m_iHp = 2;
	obj->SetPos(Vec2(400.f, 1000.f));
	obj->Enter();

	//CHunter* obj = new CHunter(OBJ_TYPE::PLAYER);
	//obj->Init();
	//obj->SetActive(true);
	//obj->SetPos(Vec2(400.f, 1140.f));
	//SINGLE(CGameManager)->SetPlayer(obj);
	//CREATEOBJECT(obj);

	SINGLE(CCameraManager)->SetWorldSize(Vec2(3200.f, 1600.f));
	SINGLE(CCameraManager)->SetCurLookAt(Vec2(400.f, 1140.f));
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
		L"texture\\stage01.png", true);
	CREATEOBJECT(BgObj);

	CEnemy* monsterMelee = new CEnemyMelee(OBJ_TYPE::ENEMY, ENEMY_TYPE::BIG_KNIGHT);
	monsterMelee->SetPos(Vec2(600.f, 1100.f));
	CREATEOBJECT(monsterMelee);
	//for (size_t i = 0; i < 10; i++)
	//{
	//	monsterMelee = new CEnemyRange(OBJ_TYPE::ENEMY, ENEMY_TYPE::WIZARD);
	//	monsterMelee->SetPos(Vec2(800.f, 1300.f));
	//	CREATEOBJECT(monsterMelee);
	//}
	
	monsterMelee = new CEnemyRange(OBJ_TYPE::ENEMY, ENEMY_TYPE::WIZARD);
	monsterMelee->SetPos(Vec2(800.f, 1300.f));
	CREATEOBJECT(monsterMelee);


	CGate* gateObj = new CGate(OBJ_TYPE::MAPOBJECT);
	gateObj->SetNextScene(SCENE_TYPE::STAGE_01);
	gateObj->SetPos(Vec2(250, 1105));
	CREATEOBJECT(gateObj);

	gateObj = new CGate(OBJ_TYPE::MAPOBJECT);
	gateObj->SetNextScene(SCENE_TYPE::STAGE_02);
	gateObj->SetPos(Vec2(2800, 1230));
	CREATEOBJECT(gateObj);

	CBorn* pItem = new CBorn(SKUL_TYPE::Hunter);
	pItem->SetPos(Vec2(450, 1170));
	CREATEOBJECT(pItem);


	// 저장한 타일 충돌체 불러오기
	wstring strPath = SINGLE(CPathManager)->GetContentPath();
	strPath += L"texture\\tile\\Map\\stage01.tile";
	LoadTile(strPath);

	// 사운드 설정
	SINGLE(CSoundManager)->AddSound(L"Hit", L"sound\\arrow_hit.wav", false);
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
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::TILE, OBJ_TYPE::PROJECTILE);
}

void CSceneInGame::Stage02Init()
{
	GAMEPLAY(true);
	SINGLE(CCameraManager)->FadeIn(1.f);
	CreateUI();

	CPlayer* obj = SINGLE(CGameManager)->GetCurSkul();
	obj->SetPos(Vec2(400.f, 1000.f));
	SINGLE(CGameManager)->SetPlayer(obj);
	CREATEOBJECT(obj);
	SINGLE(CGameManager)->SetPlayer(obj);

	SINGLE(CCameraManager)->SetWorldSize(Vec2(3200.f, 1600.f));
	SINGLE(CCameraManager)->SetCurLookAt(Vec2(400.f, 1140.f));
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
		L"texture\\stage02.png", true);
	CREATEOBJECT(BgObj);

	CEnemy* monsterMelee = new CEnemyMelee(OBJ_TYPE::ENEMY, ENEMY_TYPE::BIG_KNIGHT);
	monsterMelee->SetPos(Vec2(600.f, 1100.f));
	CREATEOBJECT(monsterMelee);


	CGate* gateObj = new CGate(OBJ_TYPE::MAPOBJECT);
	gateObj->SetNextScene(SCENE_TYPE::STAGE_02);
	gateObj->SetPos(Vec2(250, 1050));
	CREATEOBJECT(gateObj);

	gateObj = new CGate(OBJ_TYPE::MAPOBJECT);
	gateObj->SetNextScene(SCENE_TYPE::BOSS);
	gateObj->SetPos(Vec2(2800, 1050));
	CREATEOBJECT(gateObj);


	// 저장한 타일 충돌체 불러오기
	wstring strPath = SINGLE(CPathManager)->GetContentPath();
	strPath += L"texture\\tile\\Map\\stage02.tile";
	LoadTile(strPath);


	


	// 사운드 설정
	SINGLE(CSoundManager)->AddSound(L"Hit", L"sound\\arrow_hit.wav", false);
	SINGLE(CSoundManager)->AddSound(L"Ch1Bgm", L"sound\\Chapter1.wav", true);
	SINGLE(CSoundManager)->Play(L"Ch1Bgm");

	// 어떤 오브젝트 그룹끼리 충돌할것인지 미리 정함
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::TILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::ENEMY, OBJ_TYPE::TILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::MAPOBJECT);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::ENEMY);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER_ATTACK, OBJ_TYPE::ENEMY);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER_ATTACK, OBJ_TYPE::TILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::PROJECTILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::ENEMY, OBJ_TYPE::PROJECTILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::TILE, OBJ_TYPE::PROJECTILE);
}

void CSceneInGame::CreateUI()
{
	CUIImage* pUI = new CUIImage(OBJ_TYPE::UI, L"PlayerUI", L"texture\\ui\\Player_Normal_Frame.png");
	pUI->SetScale(Vec2((float)pUI->GetImage()->GetWidth(), (float)pUI->GetImage()->GetHeight()));
	pUI->SetScaleRate(Vec2(2.f, 2.f));
	pUI->SetPos(Vec2(0, WINSIZEY - pUI->GetImage()->GetHeight() * pUI->GetScaleRate().y));
	CUIImage* pUIChild = new CUIImage(OBJ_TYPE::UI, L"HealthBar", L"texture\\ui\\Player_HealthBar.png", Vec2(232.f, 2.f));
	pUIChild->SetScale(Vec2((float)pUIChild->GetImage()->GetWidth(), (float)pUIChild->GetImage()->GetHeight()));

	SINGLE(CGameManager)->m_pCurHealth = pUIChild;
	pUIChild->SetPos(Vec2(88, 90));
	pUI->AddChild(pUIChild);
	CUIText* pUIChildText = new CUIText(OBJ_TYPE::UI);
	pUIChildText->SetPos(Vec2(70, 77));
	pUIChildText->SetScale(Vec2(250, 40));
	pUIChildText->SetFontSize(24.f);
	SINGLE(CGameManager)->m_pCurHealthText = pUIChildText;
	
	pUI->AddChild(pUIChildText);
	pUIChild = new CUIImage(OBJ_TYPE::UI, L"Portrait", L"texture\\ui\\portrait_skul.png");
	pUIChild->SetScale(Vec2((float)pUIChild->GetImage()->GetWidth(), (float)pUIChild->GetImage()->GetHeight()));
	pUIChild->SetScaleRate(Vec2(4.f, 4.f));
	pUIChild->SetPos(Vec2(15, 10));
	pUI->AddChild(pUIChild);
	pUIChild = new CUIImage(OBJ_TYPE::UI, L"Skill_SkullThrowing", L"texture\\ui\\SkullThrowing.png");
	pUIChild->SetScale(Vec2((float)pUIChild->GetImage()->GetWidth(), (float)pUIChild->GetImage()->GetHeight()));
	pUIChild->SetScaleRate(Vec2(2.f, 2.f));
	pUIChild->SetPos(Vec2(115, 30));
	pUI->AddChild(pUIChild);
	pUIChild = new CUIImage(OBJ_TYPE::UI, L"PlayerUI_Btn_A", L"texture\\ui\\A.png");
	pUIChild->SetScale(Vec2((float)pUIChild->GetImage()->GetWidth(), (float)pUIChild->GetImage()->GetHeight()));
	pUIChild->SetScaleRate(Vec2(2.f, 2.f));
	pUIChild->SetPos(Vec2(127, 15));
	pUI->AddChild(pUIChild);
	CREATEOBJECT(pUI);

	pUI = new CUIImage(OBJ_TYPE::UI, L"TimerUI", L"texture\\ui\\Timer_Frame.png");
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

	pUI = new CUIImage(OBJ_TYPE::UI, L"MiniMap", L"texture\\ui\\minimap_3.png");
	pUI->SetScale(Vec2((float)pUI->GetImage()->GetWidth(), (float)pUI->GetImage()->GetHeight()));
	pUI->SetScaleRate(Vec2(1.f, 1.f));
	pUI->SetPos(Vec2(WINSIZEX - (float)pUI->GetImage()->GetWidth(), WINSIZEY - (float)pUI->GetImage()->GetHeight()));

	pTimer = new CUIText(OBJ_TYPE::UI);
	pTimer->SetPos(Vec2(145, 0));
	pTimer->SetScale(Vec2(100, 30));
	pTimer->SetText(L"0");
	pTimer->SetFontSize(30.f);
	SINGLE(CGameManager)->SetRemainEnemy(pTimer);
	pUI->AddChild(pTimer);
	CREATEOBJECT(pUI);
}
