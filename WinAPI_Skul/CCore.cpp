#include "pch.h"
#include "CCore.h"
#include "CScene.h"
#include "CGameObject.h"
#include "CTexture.h"

CCore::CCore() :
	m_hDC(0),
	m_pMemTex(nullptr),
	m_arrBrush{},
	m_arrPen{},
	m_bDebugMode(false)
{
}
CCore::~CCore()
{
	// 메인 DC 해제
	ReleaseDC(hWnd, m_hDC);

	// 생성한 펜을 모두 삭제해준다.
	for (int i = 0; i < (UINT)PEN_TYPE::SIZE; i++)
		DeleteObject(m_arrPen[i]);
}

void CCore::Init()
{
	// 자주 사용할 펜, 브러쉬 생성
	CreateBrushPen();

	// 코어의 변수에 DC 할당
	m_hDC = GetDC(hWnd);

	// 매니저 클래스 초기화 ( 타임, 키, 경로, 사운드, 장면, 충돌, 카메라 )
	SINGLE(CTimeManager)->Init();
	SINGLE(CKeyManager)->Init();
	SINGLE(CPathManager)->Init();
	SINGLE(CSoundManager)->Init();
	SINGLE(CSceneManager)->Init();
	SINGLE(CCollisionManager)->Init();
	SINGLE(CCameraManager)->Init();

	// 더블 버퍼링 용도의 비트맵과 DC를 만든다.
	m_pMemTex = SINGLE(CResourceManager)->CreateTexture(L"CoreTex", WINSIZEX, WINSIZEY);

	// 폰트와 텍스트 배경색 변경
	SetBkMode(m_pMemTex->GetDC(), 1);
	SetTextColor(m_pMemTex->GetDC(), RGB(0, 0, 0));
	HFONT	hFont, oldFont;
	hFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("맑은고딕"));
	oldFont = (HFONT)SelectObject(m_pMemTex->GetDC(), hFont);
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
	
	// 디버그 모드 키 ( 콜라이더 그리기 여부를 결정 )
	if (KEYTAP(KEY::CTRL))
		m_bDebugMode = !m_bDebugMode;
}


void CCore::Render()
{
	// 화면 Clear
	Rectangle(m_pMemTex->GetDC(), -1, -1, WINSIZEX + 1, WINSIZEY + 1);

	// 매니저 클래스 렌더 ( 장면, 카메라 )
	SINGLE(CSceneManager)->Render(m_pMemTex->GetDC());
	SINGLE(CCameraManager)->Render(m_pMemTex->GetDC());

	// FPS 출력
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::GetInst()->GetFPS());
	TextOutW(m_pMemTex->GetDC(), WINSIZEX - 60, 10, strFPS, 5);

	// m_hMemDC에 모아 그린 정보를 m_hDC로 한번에 다시 그림.
	BitBlt(m_hDC, 0, 0, WINSIZEX, WINSIZEY, m_pMemTex->GetDC(), 0, 0, SRCCOPY);
}


void CCore::CreateBrushPen()
{
	// 브러쉬
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	// 펜
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}