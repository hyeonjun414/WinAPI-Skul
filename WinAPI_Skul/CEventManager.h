#pragma once

class CObject;

class CEventManager
{
	SINGLETON(CEventManager);

private:
	vector<tEvent> m_vecEvent;			// 발생한 이벤트를 저장해두는 벡터
	vector<CObject*> m_vecDead;		// 삭제 예정 오브젝트를 모아두는 벡터

private:
	void Excute(const tEvent& _event);	// 실직적인 이벤트를 실행하는 함수

public:
	// 삭제 예정 오브젝트와 저장된 오브젝트를 처리하는 함수
	void Update(); 

	// 이벤트 추가 함수 : 외부에서 사용된다.
	void AddEvent(const tEvent& _event) { m_vecEvent.push_back(_event); }

	// 사용자 지정 이벤트 처리 함수들
	void EventCreateObject(CObject* _pObj);
	void EventDeleteObject(CObject* _pObj);
	void EventChangeScene(SCENE_TYPE _eSceneType);


};

