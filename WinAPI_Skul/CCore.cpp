#include "pch.h"
#include "CCore.h"
#include "CScene.h"
#include "CObject.h"
#include "CTexture.h"

CCore::CCore() :
	m_hDC(0),
	m_bDebugMode(false)
{
}
CCore::~CCore()
{
	// 메인 DC 해제
	ReleaseDC(hWnd, m_hDC);

}

void CCore::Init()
{
	// 코어의 변수에 DC 할당
	m_hDC = GetDC(hWnd);

	// 매니저 클래스 초기화 ( 타임, 키, 경로, 사운드, 장면, 충돌, 카메라 )
	SINGLE(CGameManager)->Init();
	SINGLE(CTimeManager)->Init();
	SINGLE(CKeyManager)->Init();
	SINGLE(CPathManager)->Init();
	SINGLE(CSoundManager)->Init();
	SINGLE(CRenderManager)->Init();
	SINGLE(CSceneManager)->Init();
	SINGLE(CCollisionManager)->Init();
	SINGLE(CCameraManager)->Init();

	srand((UINT)time(NULL));
}

void CCore::Update()
{
	// 매니저 클래스 업데이트 ( 이벤트, 타임, 키, 사운드, 장면, 충돌, 카메라, UI )
	SINGLE(CEventManager)->Update();

	SINGLE(CTimeManager)->Update();
	SINGLE(CKeyManager)->Update();
	SINGLE(CSoundManager)->Update();
	SINGLE(CSceneManager)->Update();
	SINGLE(CCollisionManager)->Update();

	SINGLE(CCameraManager)->Update();
	
	SINGLE(CUIManager)->Update();

	SINGLE(CGameManager)->Update();
	
	// 디버그 모드 키 ( 콜라이더 그리기 여부를 결정 )
	if (KEYTAP(KEY::CTRL))
		m_bDebugMode = !m_bDebugMode;
}


void CCore::Render()
{
	RENDER->GetRenderTarget()->BeginDraw();

	RENDER->RenderFillRectangle(-1, -1, WINSIZEX + 1, WINSIZEY + 1, RGB(255, 255, 255));

	SINGLE(CSceneManager)->Render();
	CCameraManager::GetInst()->Render();

	// 오른쪽 상단에 FPS 표시
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::GetInst()->GetFPS());
	RENDER->RenderText(strFPS, WINSIZEX - 100, 20, WINSIZEX, 50, 20, RGB(0, 0, 0));

	RENDER->GetRenderTarget()->EndDraw();
}
