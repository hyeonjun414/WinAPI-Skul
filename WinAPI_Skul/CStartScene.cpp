#include "pch.h"
#include "CStartScene.h"
#include "CSound.h"
#include "CImageObj.h"
#include "CUICursor.h"

CStartScene::CStartScene()
{
	m_strName = L"";
	m_eType = SCENE_TYPE::NONE;
}

CStartScene::CStartScene(wstring _sceneName, SCENE_TYPE _sceneType):
	CScene(_sceneName, _sceneType)
{
}

CStartScene::~CStartScene()
{
}


void CStartScene::Update()
{
	CScene::Update();
	// 스페이스바를 누르면 게임 시작
	if (KEYTAP(KEY::SPACE))
	{
		ChangeNextScene(SCENE_TYPE::STAGE_01);
	}
	if (KEYTAP(KEY::ESC))
	{
		ChangeNextScene(SCENE_TYPE::TOOL);
	}
	if (KEYTAP(KEY::C))
	{
		SINGLE(CCameraManager)->FadeIn(1.0f);
	}
	if (KEYTAP(KEY::V))
	{
		SINGLE(CCameraManager)->FadeOut(1.0f);
	}
}

void CStartScene::Render()
{
	CScene::Render();
	
}

void CStartScene::Enter()
{
	GAMEPLAY(true);
	SINGLE(CCameraManager)->FadeIn(1.f);

	CImageObj* imageObj = nullptr;
	imageObj = new CImageObj(OBJ_TYPE::IMAGE, L"StartSceneBG", L"texture\\Title_Art.png", false);
	CREATEOBJECT(imageObj);

	imageObj = new CImageObj(OBJ_TYPE::IMAGE, L"StartSceneLogo", L"texture\\Title_Logo.png", false);
	imageObj->SetPos(Vec2(WINSIZEX / 2 - imageObj->GetScale().x / 2, WINSIZEY / 2 - imageObj->GetScale().y / 2));
	CREATEOBJECT(imageObj);

	imageObj = new CImageObj(OBJ_TYPE::IMAGE, L"StartSceneText", L"texture\\startscene_text.png", false);
	imageObj->SetEffectType(IMG_EFFECT::FLICKER);
	imageObj->SetPos(Vec2(WINSIZEX / 2 - imageObj->GetScale().x / 2, WINSIZEY / 2 - imageObj->GetScale().y / 2+150));
	CREATEOBJECT(imageObj);

	CUICursor* cursor = new CUICursor(OBJ_TYPE::UI);
	CREATEOBJECT(cursor);

	CCameraManager::GetInst()->SetLookAt(Vec2(WINSIZEX / 2.f, WINSIZEY / 2.f));
}

void CStartScene::Exit()
{
	ClearObject();
}
