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
	// ���� DC ����
	ReleaseDC(hWnd, m_hDC);

	// ������ ���� ��� �������ش�.
	for (int i = 0; i < (UINT)PEN_TYPE::SIZE; i++)
		DeleteObject(m_arrPen[i]);
}

void CCore::Init()
{
	// ���� ����� ��, �귯�� ����
	CreateBrushPen();

	// �ھ��� ������ DC �Ҵ�
	m_hDC = GetDC(hWnd);

	// �Ŵ��� Ŭ���� �ʱ�ȭ ( Ÿ��, Ű, ���, ����, ���, �浹, ī�޶� )
	SINGLE(CTimeManager)->Init();
	SINGLE(CKeyManager)->Init();
	SINGLE(CPathManager)->Init();
	SINGLE(CSoundManager)->Init();
	SINGLE(CSceneManager)->Init();
	SINGLE(CCollisionManager)->Init();
	SINGLE(CCameraManager)->Init();

	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����.
	m_pMemTex = SINGLE(CResourceManager)->CreateTexture(L"CoreTex", WINSIZEX, WINSIZEY);

	// ��Ʈ�� �ؽ�Ʈ ���� ����
	SetBkMode(m_pMemTex->GetDC(), 1);
	SetTextColor(m_pMemTex->GetDC(), RGB(0, 0, 0));
	HFONT	hFont, oldFont;
	hFont = CreateFont(16, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("�������"));
	oldFont = (HFONT)SelectObject(m_pMemTex->GetDC(), hFont);
}

void CCore::Update()
{
	// �Ŵ��� Ŭ���� ������Ʈ ( �̺�Ʈ, Ÿ��, Ű, ����, ���, �浹, ī�޶�, UI )
	SINGLE(CEventManager)->Update();

	SINGLE(CTimeManager)->Update();
	SINGLE(CKeyManager)->Update();
	SINGLE(CSoundManager)->Update();

	SINGLE(CSceneManager)->Update();
	SINGLE(CCollisionManager)->Update();
	SINGLE(CCameraManager)->Update();
	SINGLE(CUIManager)->Update();
	
	// ����� ��� Ű ( �ݶ��̴� �׸��� ���θ� ���� )
	if (KEYTAP(KEY::CTRL))
		m_bDebugMode = !m_bDebugMode;
}


void CCore::Render()
{
	// ȭ�� Clear
	Rectangle(m_pMemTex->GetDC(), -1, -1, WINSIZEX + 1, WINSIZEY + 1);

	// �Ŵ��� Ŭ���� ���� ( ���, ī�޶� )
	SINGLE(CSceneManager)->Render(m_pMemTex->GetDC());
	SINGLE(CCameraManager)->Render(m_pMemTex->GetDC());

	// FPS ���
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::GetInst()->GetFPS());
	TextOutW(m_pMemTex->GetDC(), WINSIZEX - 60, 10, strFPS, 5);

	// m_hMemDC�� ��� �׸� ������ m_hDC�� �ѹ��� �ٽ� �׸�.
	BitBlt(m_hDC, 0, 0, WINSIZEX, WINSIZEY, m_pMemTex->GetDC(), 0, 0, SRCCOPY);
}


void CCore::CreateBrushPen()
{
	// �귯��
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	// ��
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}