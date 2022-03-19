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
	// ���� DC ����
	ReleaseDC(hWnd, m_hDC);

}

void CCore::Init()
{
	// �ھ��� ������ DC �Ҵ�
	m_hDC = GetDC(hWnd);

	// �Ŵ��� Ŭ���� �ʱ�ȭ ( Ÿ��, Ű, ���, ����, ���, �浹, ī�޶� )
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
	// �Ŵ��� Ŭ���� ������Ʈ ( �̺�Ʈ, Ÿ��, Ű, ����, ���, �浹, ī�޶�, UI )
	SINGLE(CEventManager)->Update();

	SINGLE(CTimeManager)->Update();
	SINGLE(CKeyManager)->Update();
	SINGLE(CSoundManager)->Update();
	SINGLE(CSceneManager)->Update();
	SINGLE(CCollisionManager)->Update();

	SINGLE(CCameraManager)->Update();
	
	SINGLE(CUIManager)->Update();

	SINGLE(CGameManager)->Update();
	
	// ����� ��� Ű ( �ݶ��̴� �׸��� ���θ� ���� )
	if (KEYTAP(KEY::CTRL))
		m_bDebugMode = !m_bDebugMode;
}


void CCore::Render()
{
	RENDER->GetRenderTarget()->BeginDraw();

	RENDER->RenderFillRectangle(-1, -1, WINSIZEX + 1, WINSIZEY + 1, RGB(255, 255, 255));

	SINGLE(CSceneManager)->Render();
	CCameraManager::GetInst()->Render();

	// ������ ��ܿ� FPS ǥ��
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::GetInst()->GetFPS());
	RENDER->RenderText(strFPS, WINSIZEX - 100, 20, WINSIZEX, 50, 20, RGB(0, 0, 0));

	RENDER->GetRenderTarget()->EndDraw();
}
