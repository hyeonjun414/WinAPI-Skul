#pragma once

class CScene;

class CSceneManager
{
	friend class CEventManager;

	SINGLETON(CSceneManager);

private:
	CScene*		m_arrScene[(int)SCENE_TYPE::SIZE];	// ������� ��� ���� ����.
	CScene*		m_pCurScene;						// ���� Ȱ��ȭ�� ����� ������.

	void		ChangeScene(SCENE_TYPE _sceneType); // �ش� �� Ÿ�Կ� �ش��ϴ� ������ ��ȯ

public:
	void		Init();
	void		Update();
	void		Render();

	CScene*		GetCurScene(){ return m_pCurScene; }
};

