// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h"


#pragma comment(lib, "Msimg32.lib")

// STL
#include <vector>
#include <list>
#include <map>
#include <chrono>
#include <random>
#include <assert.h>
using namespace std; // --> 같은 이름을 지닌 기능과 겹치지 않도록 유의

// 사용자 정의 클래스
#include "Logger.h"
#include "enumClass.h"
#include "struct.h"
#include "function.h"

#include "CSingleton.h"
#include "CCore.h"

#include "CGameManager.h"
#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CCollisionManager.h"
#include "CResourceManager.h"
#include "CSceneManager.h"
#include "CPathManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CUIManager.h"
#include "CSoundManager.h"
#include "CRenderManager.h"
#include "CallBackFunc.h"

// 정의
#define WINSTARTX 100     
#define WINSTARTY 100         
#define WINSIZEX 1280         
#define WINSIZEY 720
#define WINSTYLE WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX
#define PI	3.141592f
#define DEG(value) value * PI / 180
#define GRAVITY 9.8f;

// 매크로
#define SINGLE(manager) manager::GetInst()
#define DT (float)CTimeManager::GetInst()->GetDT()
#define KEYCHECK(vk_Key) CKeyManager::GetInst()->GetKeyState(vk_Key)
#define KEYHOLD(vk_key) KEYCHECK(vk_key) == KEY_STATE::HOLD
#define KEYAWAY(vk_key)   KEYCHECK(vk_key) == KEY_STATE::AWAY
#define KEYTAP(vk_key)  KEYCHECK(vk_key) == KEY_STATE::TAP
#define PATH			SINGLE(CPathManager)->GetContentPath()
#define RELATIVEPATH	SINGLE(CPathManager)->GetRelativePath()
#define LOG(str) Logger::debug(str);
#define CLONE(type) type* Clone() {return new type(*this);}
#define RENDER		SINGLE(CRenderManager)
#define MOUSEPOS	SINGLE(CKeyManager)->GetMousePos()

// 이벤트
#define CREATEOBJECT(type)	CEventManager::GetInst()->EventCreateObject(type)
#define DELETEOBJECT(type)	CEventManager::GetInst()->EventDeleteObject(type)
#define CHANGESCENE(type)	CEventManager::GetInst()->EventChangeScene(type)
#define GAMEPLAY(type)	CEventManager::GetInst()->EventGamePlay(type)
#define SWITCHSKUL		CEventManager::GetInst()->EventSwitchSkul()
#define PLAYERPOS		CGameManager::GetInst()->GetPlayer()->GetPos()

// 외부 변수 참조 -> 외부 클래스에 변수가 존재함을 알림.
extern HINSTANCE	hInst;
extern HWND			hWnd;




#endif //PCH_H
