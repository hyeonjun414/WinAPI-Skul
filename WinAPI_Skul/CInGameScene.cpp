#include "pch.h"
#include "CInGameScene.h"
#include "CPlayer.h"
#include "CImageObj.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CD2DImage.h"
#include "CEffect.h"
#include "CGate.h"

CInGameScene::CInGameScene()
{
}

CInGameScene::CInGameScene(wstring _sceneName, SCENE_TYPE _sceneType) :
	CScene(_sceneName, _sceneType)
{
}


CInGameScene::~CInGameScene()
{
}

void CInGameScene::Update()
{
	CScene::Update();

}

void CInGameScene::Enter()
{
	GAMEPLAY(true);
	SINGLE(CCameraManager)->FadeIn(1.f);

	CObject* obj = new CPlayer(OBJ_TYPE::PLAYER);
	obj->SetName(L"Player");
	obj->SetPos(Vec2(WINSIZEX / 2, WINSIZEY / 2));
	obj->SetScale(Vec2(50, 50));
	CREATEOBJECT(obj);

	SINGLE(CCameraManager)->SetWorldSize(Vec2(3200.f, 1600.f));
	SINGLE(CCameraManager)->SetTarget(obj);
	
	

	CImageObj* BgObj = new CImageObj(OBJ_TYPE::IMAGE,
		L"InGameSceneBG",
		L"texture\\bg.png", true);
	BgObj->SetDepth(100.0f);
	CREATEOBJECT(BgObj);

	BgObj = new CImageObj(OBJ_TYPE::IMAGE,
		L"InGameSceneTile",
		L"texture\\stage01.png", true);
	CREATEOBJECT(BgObj);

	CEffect* EftObj = new CEffect(OBJ_TYPE::EFFECT,L"Hit_Normal", L"texture\\effect\\hit_normal.png", 100, 0.5, 96, true);
	EftObj->SetPos(Vec2(100, 800));
	CREATEOBJECT(EftObj);

	EftObj = new CEffect(OBJ_TYPE::EFFECT, L"Enemy_Appearance", L"texture\\effect\\Enemy_Appearance.png", 100, 0.5, 128, true);
	EftObj->SetPos(Vec2(250, 800));
	CREATEOBJECT(EftObj);

	EftObj = new CEffect(OBJ_TYPE::EFFECT, L"Enemy_Dead", L"texture\\effect\\Enemy_Dead.png", 100, 0.5, 128, true);
	EftObj->SetPos(Vec2(400, 800));
	CREATEOBJECT(EftObj);


	CGate* gateObj = new CGate(OBJ_TYPE::MAPOBJECT);
	CREATEOBJECT(gateObj);

	wstring strPath = SINGLE(CPathManager)->GetContentPath();
	strPath += L"texture\\tile\\Map\\tile.tile";
	LoadTile(strPath);

	SINGLE(CSoundManager)->AddSound(L"Ch1Bgm", L"sound\\Chapter1.wav", true);
	SINGLE(CSoundManager)->Play(L"Ch1Bgm");

	// 어떤 오브젝트 그룹끼리 충돌할것인지 미리 정함
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::TILE);
	SINGLE(CCollisionManager)->CheckGroup(OBJ_TYPE::PLAYER, OBJ_TYPE::MAPOBJECT);
}

void CInGameScene::Exit()
{
	ClearObject();

	// 기존의 충돌 그릅을 해제시켜야한다.
	SINGLE(CCollisionManager)->Reset();
}
