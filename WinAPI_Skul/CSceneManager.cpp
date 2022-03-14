#include "pch.h"
#include "CSceneManager.h"
#include "CScene.h"

CSceneManager::CSceneManager():
	m_arrScene{},
	m_pCurScene(nullptr)
{
	for (int i = 0; i < (int)SCENE_TYPE::SIZE; i++)
		m_arrScene[i] = nullptr;
}

CSceneManager::~CSceneManager()
{
	// 씬 매니저가 가지고 있는 모든 씬을 지워준다.
	Safe_Delete_Array(m_arrScene, (int)SCENE_TYPE::SIZE);
}

void CSceneManager::Update()
{
	m_pCurScene->Update();

	m_pCurScene->FinalUpdate();
}

void CSceneManager::Render(HDC hdc)
{
	m_pCurScene->Render(hdc);
}

void CSceneManager::Init()
{
	m_pCurScene = m_arrScene[(int)SCENE_TYPE::START];
	m_pCurScene->Enter();
}

void CSceneManager::ChangeScene(SCENE_TYPE _sceneType)
{
	m_pCurScene->Exit();						// 기존 씬의 마무리
	m_pCurScene = m_arrScene[(int)_sceneType];	// 씬 전환
	m_pCurScene->Enter();						// 새로운 씬의 시작
}

