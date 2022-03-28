#include "pch.h"
#include "CStatusHUD.h"
#include "CUIImage.h"
#include "CUIText.h"
#include "CD2DImage.h"

CStatusHUD::CStatusHUD(): 
	CUI(OBJ_TYPE::UI)
{
}

CStatusHUD::~CStatusHUD()
{
}

void CStatusHUD::Init()
{
	// ����â ������
	CUIImage* pHUDFrame = new CUIImage(OBJ_TYPE::UI, L"PlayerUI", L"texture\\ui\\Player_Normal_Frame.png");
	pHUDFrame->SetScale(Vec2((float)pHUDFrame->GetImage()->GetWidth(), (float)pHUDFrame->GetImage()->GetHeight()));
	pHUDFrame->SetScaleRate(Vec2(2.f, 2.f));
	pHUDFrame->SetPos(Vec2(0, WINSIZEY - pHUDFrame->GetImage()->GetHeight() * pHUDFrame->GetScaleRate().y));

	// ü�¹� -> ������ ����
	CUIImage* pImgHpBar = new CUIImage(OBJ_TYPE::UI, L"HealthBar", L"texture\\ui\\Player_HealthBar.png", Vec2(232.f, 2.f));
	pImgHpBar->SetScale(Vec2((float)pImgHpBar->GetImage()->GetWidth(), (float)pImgHpBar->GetImage()->GetHeight()));
	SINGLE(CGameManager)->m_pCurHealth = pImgHpBar;
	pImgHpBar->SetPos(Vec2(88, 90));
	pHUDFrame->AddChild(pImgHpBar);
	// ü���ؽ�Ʈ -> ü�¹� ����
	CUIText* pTextHpBar = new CUIText(OBJ_TYPE::UI);
	pTextHpBar->SetPos(Vec2(0, 8));
	pTextHpBar->SetScale(Vec2(250, 0));
	pTextHpBar->SetFontSize(24.f);
	SINGLE(CGameManager)->m_pCurHealthText = pTextHpBar;
	pImgHpBar->AddChild(pTextHpBar);

	// �ʻ�ȭ -> ������ ����
	CUIImage* pImgPortrait = new CUIImage(OBJ_TYPE::UI);
	pImgPortrait->SetImage(L"Portrait_Empty", L"texture\\icon\\Portrait_Empty.png");
	pImgPortrait->SetScale(Vec2((float)pImgPortrait->GetImage()->GetWidth(), (float)pImgPortrait->GetImage()->GetHeight()));
	pImgPortrait->SetScaleRate(Vec2(2.f, 2.f));
	pImgPortrait->SetPos(Vec2(11, 2));
	SINGLE(CGameManager)->m_pPortrait = pImgPortrait;
	pHUDFrame->AddChild(pImgPortrait);

	// ��ų A �̹��� -> ������ ����
	CUIImage* pImgSkillA = new CUIImage(OBJ_TYPE::UI);
	pImgSkillA->SetImage(L"Skill_Empty", L"texture\\icon\\Skill_Empty.png");
	pImgSkillA->SetScale(Vec2((float)pImgSkillA->GetImage()->GetWidth(), (float)pImgSkillA->GetImage()->GetHeight()));
	pImgSkillA->SetScaleRate(Vec2(2.f, 2.f));
	pImgSkillA->SetPos(Vec2(116, 30));
	SINGLE(CGameManager)->m_pSkillA = pImgSkillA;
	pHUDFrame->AddChild(pImgSkillA);

	// ��ư A �̹��� -> ������ ����
	CUIImage* pImgBtnA = new CUIImage(OBJ_TYPE::UI, L"PlayerUI_Btn_A", L"texture\\ui\\A.png");
	pImgBtnA->SetScale(Vec2((float)pImgBtnA->GetImage()->GetWidth(), (float)pImgBtnA->GetImage()->GetHeight()));
	pImgBtnA->SetScaleRate(Vec2(2.f, 2.f));
	pImgBtnA->SetPos(Vec2(127, 15));
	pHUDFrame->AddChild(pImgBtnA);

	// ��ų B ������ -> ������ ����
	CUIImage* pImgSkillBFrame = new CUIImage(OBJ_TYPE::UI, L"SkillB", L"texture\\ui\\Player_Skill2_Frame.png");
	pImgSkillBFrame->SetScale(Vec2((float)pImgSkillBFrame->GetImage()->GetWidth(), (float)pImgSkillBFrame->GetImage()->GetHeight()));
	pImgSkillBFrame->SetScaleRate(Vec2(2.f, 2.f));
	pImgSkillBFrame->SetPos(Vec2(165, 22));
	pHUDFrame->AddChild(pImgSkillBFrame);

	// ��ų B �̹��� -> ��ų B ������ ����
	CUIImage* pImgSkillB = new CUIImage(OBJ_TYPE::UI);
	pImgSkillB->SetImage(L"Skill_Empty", L"texture\\icon\\Skill_Empty.png");
	pImgSkillB->SetScale(Vec2((float)pImgSkillB->GetImage()->GetWidth(), (float)pImgSkillB->GetImage()->GetHeight()));
	pImgSkillB->SetScaleRate(Vec2(2.f, 2.f));
	pImgSkillB->SetPos(Vec2(12, 8));
	SINGLE(CGameManager)->m_pSkillB = pImgSkillB;
	pImgSkillBFrame->AddChild(pImgSkillB);

	// ��ư B �̹��� -> ��ų B ������ ����
	CUIImage* pImgBtnB = new CUIImage(OBJ_TYPE::UI, L"PlayerUI_Btn_S", L"texture\\ui\\S.png");
	pImgBtnB->SetScale(Vec2((float)pImgBtnB->GetImage()->GetWidth(), (float)pImgBtnB->GetImage()->GetHeight()));
	pImgBtnB->SetScaleRate(Vec2(2.f, 2.f));
	pImgBtnB->SetPos(Vec2(23, -8));
	pImgSkillBFrame->AddChild(pImgBtnB);

	// ���� ��ų UI -> ������ ����
	CUIImage* pSubSkill = new CUIImage(OBJ_TYPE::UI);
	pSubSkill->SetPos(Vec2(238, 42));
	pSubSkill->SetActive(false);
	SINGLE(CGameManager)->m_pSubSkillFrame = pSubSkill;
	pHUDFrame->AddChild(pSubSkill);
	// ���� ��ų A -> ���� ��ų UI ����
	CUIImage* pImgSubSkillAFrame= new CUIImage(OBJ_TYPE::UI, L"SubSkillAFrame", L"texture\\ui\\Player_Subskill1_Frame.png");
	pImgSubSkillAFrame->SetScale(Vec2((float)pImgSubSkillAFrame->GetImage()->GetWidth(), (float)pImgSubSkillAFrame->GetImage()->GetHeight()));
	pImgSubSkillAFrame->SetScaleRate(Vec2(2.f, 2.f));
	pSubSkill->AddChild(pImgSubSkillAFrame);
	// ���� ��ų A �̹��� -> ���� ��ų A ����
	CUIImage* pImgSubSkillA = new CUIImage(OBJ_TYPE::UI, L"Skill_Empty", L"texture\\icon\\Skill_Empty.png");
	pImgSubSkillA->SetScale(Vec2((float)pImgSubSkillA->GetImage()->GetWidth(), (float)pImgSubSkillA->GetImage()->GetHeight()));
	pImgSubSkillA->SetScaleRate(Vec2(1.4f, 1.4f));
	pImgSubSkillA->SetPos(Vec2(7, 7));
	SINGLE(CGameManager)->m_pSubSkillA = pImgSubSkillA;
	pImgSubSkillAFrame->AddChild(pImgSubSkillA);
	// ���� ��ų B -> ���� ��ų UI ����
	CUIImage* pImgSubSkillBFrame = new CUIImage(OBJ_TYPE::UI, L"SubSkillBFrame", L"texture\\ui\\Player_Subskill2_Frame.png");
	pImgSubSkillBFrame->SetScale(Vec2((float)pImgSubSkillBFrame->GetImage()->GetWidth(), (float)pImgSubSkillBFrame->GetImage()->GetHeight()));
	pImgSubSkillBFrame->SetScaleRate(Vec2(2.f, 2.f));
	pImgSubSkillBFrame->SetPos(Vec2(38, 0));
	pSubSkill->AddChild(pImgSubSkillBFrame);
	// ���� ��ų B �̹��� -> ���� ��ų B ����
	CUIImage* pImgSubSkillB = new CUIImage(OBJ_TYPE::UI, L"Skill_Empty", L"texture\\icon\\Skill_Empty.png");
	pImgSubSkillB->SetScale(Vec2((float)pImgSubSkillB->GetImage()->GetWidth(), (float)pImgSubSkillB->GetImage()->GetHeight()));
	pImgSubSkillB->SetScaleRate(Vec2(1.4f, 1.4f));
	pImgSubSkillB->SetPos(Vec2(11, 7));
	SINGLE(CGameManager)->m_pSubSkillB = pImgSubSkillB;
	pImgSubSkillBFrame->AddChild(pImgSubSkillB);

	// ���� ���� ������ -> ������ ����
	CUIImage* pImgSubSkulFrame = new CUIImage(OBJ_TYPE::UI, L"SubSkul", L"texture\\ui\\Player_Subskull_Frame.png");
	pImgSubSkulFrame->SetScale(Vec2((float)pImgSubSkulFrame->GetImage()->GetWidth(), (float)pImgSubSkulFrame->GetImage()->GetHeight()));
	pImgSubSkulFrame->SetScaleRate(Vec2(2.f, 2.f));
	pImgSubSkulFrame->SetPos(Vec2(8, 62));
	pImgSubSkulFrame->SetActive(false);
	SINGLE(CGameManager)->m_pSubSkulFrame = pImgSubSkulFrame;
	pHUDFrame->AddChild(pImgSubSkulFrame);
	// ���� ���� �ʻ�ȭ -> ���� ���� ������ ����
	CUIImage* pImgSubSkul = new CUIImage(OBJ_TYPE::UI, L"SubSkul_Empty", L"texture\\icon\\Portrait_mini_Empty.png");
	pImgSubSkul->SetScale(Vec2((float)pImgSubSkul->GetImage()->GetWidth(), (float)pImgSubSkul->GetImage()->GetHeight()));
	pImgSubSkul->SetScaleRate(Vec2(2.f, 2.f));
	pImgSubSkul->SetPos(Vec2(6, 7));
	SINGLE(CGameManager)->m_pSubSkul = pImgSubSkul;
	pImgSubSkulFrame->AddChild(pImgSubSkul);
	CUIImage* pImgBtnSpace = new CUIImage(OBJ_TYPE::UI, L"PlayerUI_Btn_Space", L"texture\\ui\\Space.png");
	pImgBtnSpace->SetScale(Vec2((float)pImgBtnSpace->GetImage()->GetWidth(), (float)pImgBtnSpace->GetImage()->GetHeight()));
	pImgBtnSpace->SetScaleRate(Vec2(2.f, 2.f));
	pImgBtnSpace->SetPos(Vec2(0, 40));
	pImgSubSkulFrame->AddChild(pImgBtnSpace);



	CREATEOBJECT(this);
	AddChild(pHUDFrame);
}

void CStatusHUD::Update()
{
	CUI::Update();
}

void CStatusHUD::FinalUpdate()
{
	CUI::FinalUpdate();
}

void CStatusHUD::Render()
{
	CUI::Render();
}
