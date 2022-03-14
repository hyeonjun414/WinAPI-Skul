#pragma once

class CGameObject;

class CEventManager
{
	SINGLETON(CEventManager);

private:
	vector<tEvent> m_vecEvent;			// �߻��� �̺�Ʈ�� �����صδ� ����
	vector<CGameObject*> m_vecDead;		// ���� ���� ������Ʈ�� ��Ƶδ� ����

private:
	void Excute(const tEvent& _event);	// �������� �̺�Ʈ�� �����ϴ� �Լ�

public:
	// ���� ���� ������Ʈ�� ����� ������Ʈ�� ó���ϴ� �Լ�
	void Update(); 

	// �̺�Ʈ �߰� �Լ� : �ܺο��� ���ȴ�.
	void AddEvent(const tEvent& _event) { m_vecEvent.push_back(_event); }

	// ����� ���� �̺�Ʈ ó�� �Լ���
	void EventCreateObject(CGameObject* _pObj);
	void EventDeleteObject(CGameObject* _pObj);
	void EventChangeScene(SCENE_TYPE _eSceneType);


};

