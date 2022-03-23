#include "pch.h"
#include "CSceneBoss.h"
#include "CPlayer.h"
#include "CImageObj.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CEffect.h"
#include "CGate.h"
#include "CEnemy.h"
#include "CUIImage.h"
#include "CUIText.h"
#include "CEnemyBoss.h"


CSceneBoss::CSceneBoss(wstring _sceneName, SCENE_TYPE _sceneType) :
	CScene(_sceneName, _sceneType)
{
}

CSceneBoss::~CSceneBoss()
{
}

void CSceneBoss::Update()
{
	CScene::Update();
}

void CSceneBoss::Enter()
{
	GAMEPLAY(true);
	SINGLE(CCameraManager)->FadeIn(1.f);

	CObject* obj = new CPlayer(OBJ_TYPE::PLAYER);
	obj->SetName(L"Player");
	obj->SetPos(Vec2(1600.f, 700.f));
	CREATEOBJECT(obj);
	SINGLE(CGameManager)->SetPlayer(obj);

	SINGLE(CCameraManager)->SetWorldSize(Vec2(3200.f, 1600.f));
	SINGLE(CCameraManager)->SetCurLookAt(Vec2(1600.f, 700.f));
	SINGLE(CCameraManager)->SetTarget(obj);

	CImageObj* BgObj = new CImageObj(OBJ_TYPE::BACKGOUNRD, L"StageBoss1", L"texture\\background\\bossbg_1.png", true);
	BgObj->SetDepth(3.f);
	CREATEOBJECT(BgObj);

	CEnemyBoss* pBoss = new CEnemyBoss(OBJ_TYPE::ENEMY, ENEMY_TYPE::ELDER_ENT);
	pBoss->SetPos(Vec2(1600.f, 800.f));
	CREATEOBJECT(pBoss);
	// 타일맵 출력
	BgObj = new CImageObj(OBJ_TYPE::IMAGE,
		L"StageBoss",
		L"texture\\stageBoss.png", true);
	CREATEOBJECT(BgObj);
	
	// 저장한 타일 충돌체 불러오기
	wstring strPath = SINGLE(CPathManager)->GetContentPath();
	strPath += L"texture\\tile\\Map\\stageBoss.tile";
	LoadTile(strPath);

	

	CreateUI();

	// 사운드 설정
	SINGLE(CSoundManager)->AddSound(L"Hit", L"sound\\arrow_hit.wav", false);
	SINGLE(CSoundManager)->AddSound(L"Ch1Bgm", L"sound\\Chapter1.wav", true);
	//SINGLE(CSoundManager)->Play(L"Ch1Bgm");

	// 어떤 오브젝트 그룹끼리 충돌할것인지 미리 정함
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::TILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::ENEMY, OBJ_TYPE::TILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::MAPOBJECT);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::ENEMY);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER_ATTACK, OBJ_TYPE::ENEMY);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::PROJECTILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::ENEMY, OBJ_TYPE::PROJECTILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::TILE, OBJ_TYPE::PROJECTILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::TILE, OBJ_TYPE::BOSS_ATTACK);

}

void CSceneBoss::Exit()
{
	ClearObject();

	// 기존의 충돌 그릅을 해제시켜야한다.
	SINGLE(CCollisionManager)->Reset();
}

void CSceneBoss::CreateUI()
{
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
