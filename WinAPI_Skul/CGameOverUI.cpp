#include "pch.h"
#include "CGameOverUI.h"
#include "CUIImage.h"
#include "CUIText.h"
#include "CD2DImage.h"
#include "CUIButton.h"
#include "CScene.h"

CGameOverUI::CGameOverUI() :
	CUI(OBJ_TYPE::UI)
{
}

CGameOverUI::~CGameOverUI()
{
}

void CALLBACK BtnGameOver_NewGame(DWORD_PTR _param1, DWORD_PTR _param2)
{
	SINGLE(CSceneManager)->GetCurScene()->DeleteGroup(OBJ_TYPE::PLAYER);
	SINGLE(CGameManager)->Player_Reset();
	SINGLE(CGameManager)->UI_Reset();
	SINGLE(CSceneManager)->GetCurScene()->ChangeNextScene(SCENE_TYPE::LOBBY_INNER);
}


void CALLBACK BtnGameOver_Title(DWORD_PTR _param1, DWORD_PTR _param2)
{
	SINGLE(CSceneManager)->GetCurScene()->DeleteGroup(OBJ_TYPE::PLAYER);
	SINGLE(CSceneManager)->GetCurScene()->ChangeNextScene(SCENE_TYPE::START);
	SINGLE(CGameManager)->Player_Reset();
	SINGLE(CGameManager)->UI_Reset();
}

void CALLBACK BtnGameOver_GameExit(DWORD_PTR _param1, DWORD_PTR _param2)
{
	CGameManager::GetInst()->GameExit();
}


void CGameOverUI::Init()
{
	SetScale(Vec2(WINSIZEX, WINSIZEY));
	// 비네팅 효과 이미지
	CUIImage* pBackgound = new CUIImage(OBJ_TYPE::UI, L"Gameover_Vignette", L"texture\\ui\\gameover_vignette.png");
	pBackgound->SetScale(Vec2((float)pBackgound->GetImage()->GetWidth(), (float)pBackgound->GetImage()->GetHeight()));
	AddChild(pBackgound);

	CUIImage* pPopup = new CUIImage(OBJ_TYPE::UI, L"GameOver_Popup", L"texture\\ui\\Popup_Frame02.png");
	pPopup->SetPos(Vec2(WINSIZEX / 2 - pPopup->GetImage()->GetWidth() * 1.5f, 150.f));
	pPopup->SetScale(Vec2((float)pPopup->GetImage()->GetWidth()*3, (float)pPopup->GetImage()->GetHeight()*2));
	AddChild(pPopup);

	CUIText* pText = new CUIText(OBJ_TYPE::UI);
	pText->SetPos(Vec2((float)pPopup->GetImage()->GetWidth() * 1.5f,80));
	pText->SetFontSize(40.f);
	pText->SetFontColor(Color::MENUTEXT_ON);
	pText->SetText(L"스컬의 여정은 막을 내렸습니다");
	pText->PositionSet();
	pPopup->AddChild(pText);

	// 게임오버창 버튼들
	CUIButton* pBtn;
	pBtn = new CUIButton(OBJ_TYPE::UI);
	pBtn->SetPos(Vec2((float)WINSIZEX / 2, 370));
	pBtn->SetOnColor(Color::MENUTEXT_ON);
	pBtn->SetOffColor(Color::MENUTEXT_OFF);
	pBtn->SetText(L"다음 스컬로 시작", 30.f);
	pBtn->PositionSet();
	pBtn->SetClickCallBack(BtnGameOver_NewGame, 0, 0);
	AddChild(pBtn);

	pBtn = new CUIButton(OBJ_TYPE::UI);
	pBtn->SetPos(Vec2((float)WINSIZEX/2, 420));
	pBtn->SetOnColor(Color::MENUTEXT_ON);
	pBtn->SetOffColor(Color::MENUTEXT_OFF);
	pBtn->SetText(L"타이틀 창으로", 30.f);
	pBtn->PositionSet();
	pBtn->SetClickCallBack(BtnGameOver_Title, 0, 0);
	AddChild(pBtn);

	pBtn = new CUIButton(OBJ_TYPE::UI);
	pBtn->SetPos(Vec2((float)WINSIZEX / 2, 470));
	pBtn->SetOnColor(Color::MENUTEXT_ON);
	pBtn->SetOffColor(Color::MENUTEXT_OFF);
	pBtn->SetText(L"게임 종료", 30.f);
	pBtn->PositionSet();
	pBtn->SetClickCallBack(BtnGameOver_GameExit, 0, 0);
	AddChild(pBtn);
}

void CGameOverUI::Update()
{
	CUI::Update();
}

void CGameOverUI::FinalUpdate()
{
	CUI::FinalUpdate();
}

void CGameOverUI::Render()
{
	CUI::Render();
}
