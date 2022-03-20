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
#include "CUIImage.h"
#include "CUIText.h"

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
	GAMEPLAY(true);
	SINGLE(CCameraManager)->FadeIn(1.f);

	CObject* obj = new CPlayer(OBJ_TYPE::PLAYER);
	obj->SetName(L"Player");
	obj->SetPos(Vec2(400.f, 1000.f));
	obj->SetScale(Vec2(50, 50));
	CREATEOBJECT(obj);
	SINGLE(CGameManager)->SetPlayer(obj);

	SINGLE(CCameraManager)->SetWorldSize(Vec2(3200.f, 1600.f));
	SINGLE(CCameraManager)->SetCurLookAt(Vec2(400.f, 1140.f));
	SINGLE(CCameraManager)->SetTarget(obj);
	
	
	CImageObj* BgObj = nullptr;

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

	BgObj = new CImageObj(OBJ_TYPE::IMAGE,
		L"InGameSceneTile",
		L"texture\\stage01.png", true);
	CREATEOBJECT(BgObj);

	CEnemy* monsterMelee = new CEnemyMelee(OBJ_TYPE::ENEMY_MELEE, ENEMY_TYPE::BIG_KNIGHT);
	monsterMelee->SetPos(Vec2(600.f, 1100.f));
	CREATEOBJECT(monsterMelee);


	//CEffect* EftObj = new CEffect(OBJ_TYPE::EFFECT,L"Hit_Normal", L"texture\\effect\\hit_normal.png", 100, 0.5, 96, true);
	//EftObj->SetPos(Vec2(100, 800));
	//CREATEOBJECT(EftObj);

	//EftObj = new CEffect(OBJ_TYPE::EFFECT, L"Enemy_Appearance", L"texture\\effect\\Enemy_Appearance.png", 100, 0.5, 128, true);
	//EftObj->SetPos(Vec2(250, 800));
	//CREATEOBJECT(EftObj);

	//EftObj = new CEffect(OBJ_TYPE::EFFECT, L"Enemy_Dead", L"texture\\effect\\Enemy_Dead.png", 100, 0.5, 128, true);
	//EftObj->SetPos(Vec2(400, 800));
	//CREATEOBJECT(EftObj);


	CGate* gateObj = new CGate(OBJ_TYPE::MAPOBJECT);
	gateObj->SetPos(Vec2(250, 1105));
	CREATEOBJECT(gateObj);

	gateObj = new CGate(OBJ_TYPE::MAPOBJECT);
	gateObj->SetPos(Vec2(2800, 1230));
	CREATEOBJECT(gateObj);

	wstring strPath = SINGLE(CPathManager)->GetContentPath();
	strPath += L"texture\\tile\\Map\\stage01.tile";
	LoadTile(strPath);

	SINGLE(CSoundManager)->AddSound(L"Attack", L"sound\\arrow_hit.wav", false);
	SINGLE(CSoundManager)->AddSound(L"Ch1Bgm", L"sound\\Chapter1.wav", true);
	//SINGLE(CSoundManager)->Play(L"Ch1Bgm");

	CUIImage* pUI = new CUIImage(OBJ_TYPE::UI, L"PlayerUI", L"texture\\ui\\Player_Normal_Frame.png");
	pUI->SetScale(Vec2((float)pUI->GetImage()->GetWidth(), (float)pUI->GetImage()->GetHeight()));
	pUI->SetScaleRate(Vec2(2.f, 2.f));
	pUI->SetPos(Vec2(0, WINSIZEY - pUI->GetImage()->GetHeight() * pUI->GetScaleRate().y));
	CUIImage* pUIChild = new CUIImage(OBJ_TYPE::UI, L"HealthBar", L"texture\\ui\\Player_HealthBar.png");
	pUIChild->SetScale(Vec2((float)pUIChild->GetImage()->GetWidth(), (float)pUIChild->GetImage()->GetHeight()));
	pUIChild->SetScaleRate(Vec2(232.f, 2.f));
	pUIChild->SetPos(Vec2(88, 90));
	pUI->AddChild(pUIChild);
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
	pUI->SetPos(Vec2(0,0));
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
	pUI->SetPos(Vec2(WINSIZEX- (float)pUI->GetImage()->GetWidth(), WINSIZEY- (float)pUI->GetImage()->GetHeight()));

	pTimer = new CUIText(OBJ_TYPE::UI);
	pTimer->SetPos(Vec2(145, 0));
	pTimer->SetScale(Vec2(100, 30));
	pTimer->SetText(L"0");
	pTimer->SetFontSize(30.f);
	SINGLE(CGameManager)->SetRemainEnemy(pTimer);
	pUI->AddChild(pTimer);
	CREATEOBJECT(pUI);


	// 어떤 오브젝트 그룹끼리 충돌할것인지 미리 정함
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::TILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::ENEMY_MELEE, OBJ_TYPE::TILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::MAPOBJECT);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::ENEMY_MELEE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER_ATTACK, OBJ_TYPE::ENEMY_MELEE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::PROJECTILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::ENEMY_MELEE, OBJ_TYPE::PROJECTILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::TILE, OBJ_TYPE::PROJECTILE);
}

void CSceneInGame::Exit()
{
	ClearObject();

	// 기존의 충돌 그릅을 해제시켜야한다.
	SINGLE(CCollisionManager)->Reset();
}
