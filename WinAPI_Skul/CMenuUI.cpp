#include "pch.h"
#include "CMenuUI.h"
#include "CUIImage.h"
#include "CUIText.h"
#include "CD2DImage.h"
#include "CUIButton.h"
#include "CScene.h"

CMenuUI::CMenuUI():
	CUI(OBJ_TYPE::UI)
{
}

CMenuUI::~CMenuUI()
{
	//delete 
}


void CALLBACK BtnBackToGame(DWORD_PTR _param1, DWORD_PTR _param2)
{
	SINGLE(CGameManager)->ActiveMenu();
}


void CALLBACK BtnNewGame(DWORD_PTR _param1, DWORD_PTR _param2)
{
	SINGLE(CSceneManager)->GetCurScene()->DeleteGroup(OBJ_TYPE::PLAYER);
	SINGLE(CGameManager)->Player_Reset();
	SINGLE(CGameManager)->UI_Reset();
	SINGLE(CSceneManager)->GetCurScene()->ChangeNextScene(SCENE_TYPE::STAGE_01);
}

void CALLBACK BtnBossStage(DWORD_PTR _param1, DWORD_PTR _param2)
{
	SINGLE(CGameManager)->UI_Reset();
	SINGLE(CSceneManager)->GetCurScene()->ChangeNextScene(SCENE_TYPE::BOSS);
}

void CALLBACK BtnTitle(DWORD_PTR _param1, DWORD_PTR _param2)
{
	SINGLE(CSceneManager)->GetCurScene()->DeleteGroup(OBJ_TYPE::PLAYER);
	SINGLE(CSceneManager)->GetCurScene()->ChangeNextScene(SCENE_TYPE::START);
	SINGLE(CGameManager)->Player_Reset();
	SINGLE(CGameManager)->UI_Reset();
}

void CALLBACK BtnGameExit(DWORD_PTR _param1, DWORD_PTR _param2)
{
	CGameManager::GetInst()->GameExit();
}

void CMenuUI::Init()
{

	SINGLE(CGameManager)->m_pMenuUI = this;
	SetActive(false);
	SetScale(Vec2(WINSIZEX, WINSIZEY));
	// 비네팅 효과 이미지
	CUIImage* pBackgound = new CUIImage(OBJ_TYPE::UI, L"MenuUI_Vignette", L"texture\\ui\\menu_vignette.png");
	pBackgound->SetScale(Vec2((float)pBackgound->GetImage()->GetWidth(), (float)pBackgound->GetImage()->GetHeight()));
	AddChild(pBackgound);

	// 메인 프레임
	CUIImage* pPanel = new CUIImage(OBJ_TYPE::UI,L"MenuUI", L"texture\\ui\\Pause_Frame.png");
	pPanel->SetScale(Vec2((float)pPanel->GetImage()->GetWidth(), (float)pPanel->GetImage()->GetHeight()));
	pPanel->SetScaleRate(Vec2(2.f, 2.f));
	pPanel->SetPos(Vec2(WINSIZEX/2 - pPanel->GetImage()->GetWidth(), 0));
	

	CUIText* pText = new CUIText(OBJ_TYPE::UI);
	pText->SetPos(Vec2((float)pPanel->GetImage()->GetWidth(), 200));
	pText->SetFontSize(30.f);
	pText->SetFontColor(Color::MENUTEXT_OFF);
	pText->SetText(L"일시정지");
	pText->PositionSet();
	pPanel->AddChild(pText);

	// 메뉴창 버튼들
	CUIButton* pBtn;
	pBtn = new CUIButton(OBJ_TYPE::UI);
	pBtn->SetPos(Vec2((float)pPanel->GetImage()->GetWidth(), 250));
	pBtn->SetOnColor(Color::MENUTEXT_ON);
	pBtn->SetOffColor(Color::MENUTEXT_OFF);
	pBtn->SetText(L"돌아가기", 25.f);
	pBtn->PositionSet();
	pBtn->SetClickCallBack(BtnBackToGame, 0, 0);
	pPanel->AddChild(pBtn);

	pBtn = new CUIButton(OBJ_TYPE::UI);
	pBtn->SetPos(Vec2((float)pPanel->GetImage()->GetWidth(), 300));
	pBtn->SetOnColor(Color::MENUTEXT_ON);
	pBtn->SetOffColor(Color::MENUTEXT_OFF);
	pBtn->SetText(L"새 게임", 25.f);
	pBtn->PositionSet();
	pBtn->SetClickCallBack(BtnNewGame, 0, 0);
	pPanel->AddChild(pBtn);

	pBtn = new CUIButton(OBJ_TYPE::UI);
	pBtn->SetPos(Vec2((float)pPanel->GetImage()->GetWidth(), 350));
	pBtn->SetOnColor(Color::MENUTEXT_ON);
	pBtn->SetOffColor(Color::MENUTEXT_OFF);
	pBtn->SetText(L"메인화면", 25.f);
	pBtn->PositionSet();
	pBtn->SetClickCallBack(BtnTitle, 0, 0);
	pPanel->AddChild(pBtn);

	pBtn = new CUIButton(OBJ_TYPE::UI);
	pBtn->SetPos(Vec2((float)pPanel->GetImage()->GetWidth(), 400));
	pBtn->SetOnColor(Color::MENUTEXT_ON);
	pBtn->SetOffColor(Color::MENUTEXT_OFF);
	pBtn->SetText(L"보스전", 25.f);
	pBtn->PositionSet();
	pBtn->SetClickCallBack(BtnBossStage, 0, 0);
	pPanel->AddChild(pBtn);

	pBtn = new CUIButton(OBJ_TYPE::UI);
	pBtn->SetPos(Vec2((float)pPanel->GetImage()->GetWidth(), 450));
	pBtn->SetOnColor(Color::MENUTEXT_ON);
	pBtn->SetOffColor(Color::MENUTEXT_OFF);
	pBtn->SetText(L"게임종료", 25.f);
	pBtn->PositionSet();
	pBtn->SetClickCallBack(BtnGameExit, 0, 0);
	pPanel->AddChild(pBtn);


	AddChild(pPanel);
	CREATEOBJECT(this);
}

void CMenuUI::Update()
{
	if (!IsActive()) return;

	CUI::Update();
}

void CMenuUI::FinalUpdate()
{
	if (!IsActive()) return;

	CUI::FinalUpdate();
}

void CMenuUI::Render()
{
	if (!IsActive()) return;

	CUI::Render();
}
