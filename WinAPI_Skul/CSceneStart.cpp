#include "pch.h"
#include "CSceneStart.h"
#include "CSound.h"
#include "CImageObj.h"
#include "CUICursor.h"

CSceneStart::CSceneStart()
{
	m_strName = L"";
	m_eType = SCENE_TYPE::NONE;
}

CSceneStart::CSceneStart(wstring _sceneName, SCENE_TYPE _sceneType):
	CScene(_sceneName, _sceneType)
{
}

CSceneStart::~CSceneStart()
{
}


void CSceneStart::Update()
{
	CScene::Update();
	// 스페이스바를 누르면 게임 시작
	if (KEYTAP(KEY::SPACE))
	{
		ChangeNextScene(SCENE_TYPE::STAGE_01);
	}
	if (KEYTAP(KEY::B))
	{
		ChangeNextScene(SCENE_TYPE::BOSS);
	}
	if (KEYTAP(KEY::ESC))
	{
		ChangeNextScene(SCENE_TYPE::TOOL);
	}
}

void CSceneStart::Render()
{
	CScene::Render();
	
}

void CSceneStart::Enter()
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
	SINGLE(CSoundManager)->AddSound(L"Title", L"sound\\MainTitle.wav", true);
	SINGLE(CSoundManager)->Play(L"Title");

	CCameraManager::GetInst()->SetLookAt(Vec2(WINSIZEX / 2.f, WINSIZEY / 2.f));
	
}

void CSceneStart::Exit()
{
	ClearObject();
	SINGLE(CSoundManager)->Stop(L"Title");
}
