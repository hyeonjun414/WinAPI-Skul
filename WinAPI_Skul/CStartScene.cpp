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
	// �����̽��ٸ� ������ ���� ����
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
	RENDER->RenderText(L"�����̽��ٸ� ������ �����մϴ�",
		WINSIZEX,
		WINSIZEY+300,
		0,
		0,
		20,
		RGB(255,255,255));
}

void CStartScene::Enter()
{
	SINGLE(CCameraManager)->FadeIn(1.f);

	CImageObj* imageObj = new CImageObj();
	imageObj->SetObjGroup(OBJ_TYPE::IMAGE);
	CREATEOBJECT(imageObj);

	CUICursor* cursor = new CUICursor(OBJ_TYPE::UI);
	CREATEOBJECT(cursor);

	CCameraManager::GetInst()->SetLookAt(Vec2(WINSIZEX / 2.f, WINSIZEY / 2.f));
}

void CStartScene::Exit()
{
	ClearObject();
}
