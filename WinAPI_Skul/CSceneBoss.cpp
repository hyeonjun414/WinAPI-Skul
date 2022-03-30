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
#include "CStatusHUD.h"
#include "CMenuUI.h"


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
	CreateUI();

	CPlayer* obj = SINGLE(CGameManager)->GetCurSkul();
	obj->SetPos(Vec2(1600.f, 700.f));
	SINGLE(CCameraManager)->SetWorldSize(Vec2(3200.f, 1600.f));
	SINGLE(CCameraManager)->SetCurLookAt(Vec2(1600.f, 700.f));
	SINGLE(CCameraManager)->SetTarget(obj);

	CImageObj* BgObj = new CImageObj(OBJ_TYPE::BACKGOUNRD, L"StageBoss1", L"texture\\background\\bossbg_1.png", true);
	BgObj->SetDepth(3.f);
	CREATEOBJECT(BgObj);

	CEnemyBoss* pBoss = new CEnemyBoss(OBJ_TYPE::ENEMY, ENEMY_TYPE::ELDER_ENT);
	pBoss->SetPos(Vec2(1600.f, 800.f));
	CREATEOBJECT(pBoss);
	// Ÿ�ϸ� ���
	BgObj = new CImageObj(OBJ_TYPE::IMAGE,
		L"StageBoss",
		L"texture\\stageBoss.png", true);
	CREATEOBJECT(BgObj);
	
	// ������ Ÿ�� �浹ü �ҷ�����
	wstring strPath = SINGLE(CPathManager)->GetContentPath();
	strPath += L"texture\\tile\\Map\\stageBoss.tile";
	LoadTile(strPath);

	

	// ���� ����
	SINGLE(CSoundManager)->AddSound(L"Hit", L"sound\\arrow_hit.wav", false);
	SINGLE(CSoundManager)->AddSound(L"Ch1BossBgm", L"sound\\Chapter1_Boss.wav", true);
	SINGLE(CSoundManager)->Play(L"Ch1BossBgm");

	// � ������Ʈ �׷쳢�� �浹�Ұ����� �̸� ����
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::TILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::ENEMY, OBJ_TYPE::TILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::MAPOBJECT);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::ENEMY);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER_ATTACK, OBJ_TYPE::ENEMY);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER_ATTACK, OBJ_TYPE::TILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::PROJECTILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::ENEMY, OBJ_TYPE::PROJECTILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::TILE, OBJ_TYPE::PROJECTILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::TILE, OBJ_TYPE::MELEE_ATTACK);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::MELEE_ATTACK);
}

void CSceneBoss::Exit()
{
	ClearObject();
	SINGLE(CSoundManager)->Stop(L"Ch1BossBgm");
	// ������ �浹 �׸��� �������Ѿ��Ѵ�.
	SINGLE(CCollisionManager)->Reset();
}

void CSceneBoss::CreateUI()
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

	
	pUI = new CUIImage(OBJ_TYPE::UI, L"BossStatusFrame", L"texture\\ui\\bossStatus.png");
	pUI->SetScale(Vec2((float)pUI->GetImage()->GetWidth(), (float)pUI->GetImage()->GetHeight()));
	pUI->SetScaleRate(Vec2(2.f, 2.f));
	pUI->SetPos(Vec2(WINSIZEX/2 - pUI->GetImage()->GetWidth()+20, 0));
	CUIImage* pUIChild = new CUIImage(OBJ_TYPE::UI, L"HealthBar", L"texture\\ui\\Player_HealthBar.png", Vec2(550.f, 2.5f));
	pUIChild->SetScale(Vec2((float)pUIChild->GetImage()->GetWidth(), (float)pUIChild->GetImage()->GetHeight()));
	pUIChild->SetPos(Vec2(45, 57));
	SINGLE(CGameManager)->m_pBossStatus = pUIChild;
	pUI->AddChild(pUIChild);


	CUIText* pUIChildText = new CUIText(OBJ_TYPE::UI);
	pUIChildText->SetPos(Vec2(pUI->GetImage()->GetWidth()/2+35, 20));
	pUIChildText->SetScale(Vec2(250, 40));
	pUIChildText->SetFontSize(18.f);
	pUIChildText->SetText(L"���׵���");
	pUI->AddChild(pUIChildText);
	pUIChildText = new CUIText(OBJ_TYPE::UI);
	pUIChildText->SetPos(Vec2(pUI->GetImage()->GetWidth()/2+33,78));
	pUIChildText->SetScale(Vec2(250, 40));
	pUIChildText->SetFontSize(15.f);
	pUIChildText->SetText(L"��� ��Ʈ");
	pUI->AddChild(pUIChildText);
	CREATEOBJECT(pUI);

	CMenuUI* pMenuUI = new CMenuUI();
	pMenuUI->Init();
}
