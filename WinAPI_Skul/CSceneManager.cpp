#include "pch.h"
#include "CSceneManager.h"
#include "CScene.h"
#include "CStartScene.h"
#include "CToolScene.h"
#include "CInGameScene.h"

CSceneManager::CSceneManager():
	m_arrScene{},
	m_pCurScene(nullptr)
{
	for (int i = 0; i < (int)SCENE_TYPE::SIZE; i++)
		m_arrScene[i] = nullptr;
}

CSceneManager::~CSceneManager()
{
	// �� �Ŵ����� ������ �ִ� ��� ���� �����ش�.
	Safe_Delete_Array(m_arrScene, (int)SCENE_TYPE::SIZE);
}

void CSceneManager::Update()
{
	m_pCurScene->Update();

	m_pCurScene->FinalUpdate();
}

void CSceneManager::Render()
{
	m_pCurScene->Render();
}

void CSceneManager::Init()
{

	m_arrScene[(int)SCENE_TYPE::START] = new CStartScene(L"StartScene", SCENE_TYPE::START);
	m_arrScene[(int)SCENE_TYPE::TOOL] = new CToolScene(L"ToolScene", SCENE_TYPE::TOOL);
	m_arrScene[(int)SCENE_TYPE::STAGE_01] = new CInGameScene(L"Stage_01", SCENE_TYPE::STAGE_01);

	m_pCurScene = m_arrScene[(int)SCENE_TYPE::START];
	m_pCurScene->Enter();
}

void CSceneManager::ChangeScene(SCENE_TYPE _sceneType)
{
	m_pCurScene->Exit();						// ���� ���� ������
	m_pCurScene = m_arrScene[(int)_sceneType];	// �� ��ȯ
	m_pCurScene->Enter();						// ���ο� ���� ����
}

