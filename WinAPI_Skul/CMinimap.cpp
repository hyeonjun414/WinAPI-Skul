#include "pch.h"
#include "CMinimap.h"
#include "CUIImage.h"
#include "CUIText.h"
#include "CD2DImage.h"
#include "CScene.h"

CMinimap::CMinimap():
	CUI(OBJ_TYPE::UI)
{
}

CMinimap::~CMinimap()
{
}

void CMinimap::Init()
{
	CUIImage* pImgMinimapFrame = new CUIImage(OBJ_TYPE::UI, L"MiniMap", L"texture\\ui\\minimap_3.png");
	pImgMinimapFrame->SetScale(Vec2((float)pImgMinimapFrame->GetImage()->GetWidth(), (float)pImgMinimapFrame->GetImage()->GetHeight()));
	pImgMinimapFrame->SetScaleRate(Vec2(1.f, 1.f));
	pImgMinimapFrame->SetPos(Vec2(0, 0));
	SetPos(Vec2(WINSIZEX - (float)pImgMinimapFrame->GetImage()->GetWidth(), WINSIZEY - (float)pImgMinimapFrame->GetImage()->GetHeight()));
	SetScale(Vec2((float)pImgMinimapFrame->GetImage()->GetWidth(), (float)pImgMinimapFrame->GetImage()->GetHeight()));
	CUIText* pTextRemainEnemyNum = new CUIText(OBJ_TYPE::UI);
	pTextRemainEnemyNum->SetPos(Vec2(145, 0));
	pTextRemainEnemyNum->SetScale(Vec2(100, 30));
	pTextRemainEnemyNum->SetText(L"0");
	pTextRemainEnemyNum->SetFontSize(30.f);
	SINGLE(CGameManager)->SetRemainEnemy(pTextRemainEnemyNum);

	AddChild(pImgMinimapFrame);
	AddChild(pTextRemainEnemyNum);

	CREATEOBJECT(this);
}

void CMinimap::Update()
{
	CUI::Update();
}

void CMinimap::FinalUpdate()
{
	CUI::FinalUpdate();
}

void CMinimap::Render()
{
	CUI::Render();
	
}
