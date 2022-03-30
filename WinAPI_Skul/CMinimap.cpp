#include "pch.h"
#include "CMinimap.h"
#include "CUIImage.h"
#include "CUIText.h"
#include "CD2DImage.h"
#include "CScene.h"
#include "CCollider.h"

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

	if (!SINGLE(CGameManager)->GetGamePlay()) return;

	const vector<CObject*>* vecObject = SINGLE(CSceneManager)->GetCurScene()->GetAllObject();
	for (size_t i = (UINT)OBJ_TYPE::TILE; i < (UINT)OBJ_TYPE::PLAYER_ATTACK; i++)
	{
		for (size_t j = 0; j < vecObject[i].size(); j++)
		{
			if (!vecObject[i][j]->IsActive() || nullptr == vecObject[i][j]->GetCollider()) continue;
			Vec2 vPos = vecObject[i][j]->GetCollider()->GetFinalPos();
			vPos = SINGLE(CCameraManager)->GetRenderPos(vPos);
			Vec2 vScale = vecObject[i][j]->GetScale();
			float length = (vPos - PLAYERPOS).Length();
			vPos.x *= 0.07f;
			vPos.y *= 0.08f;
			vScale.y /= 2.f;
			vScale.y *= 0.07f;
			vPos += Vec2(WINSIZEX - GetScale().x/2 -50, WINSIZEY - GetScale().y/2- 30);

			if (GetPos().x + 10 < vPos.x && vPos.x <= GetPos().x + GetScale().x -20 &&
				GetPos().y + 30 < vPos.y && vPos.y <= GetPos().y + GetScale().y - 20)
			{
				switch (i)
				{
				case (UINT)OBJ_TYPE::PLAYER:
				{
					RENDER->RenderFillRectangle(
						vPos.x,
						vPos.y - 5,
						vPos.x + 5,
						vPos.y,
						RGB(0, 255, 0));
					break;
				}
				case (UINT)OBJ_TYPE::MAPOBJECT:
				{
					RENDER->RenderFillRectangle(
						vPos.x,
						vPos.y - 5,
						vPos.x + 5,
						vPos.y,
						RGB(255, 127, 0));
					break;
				}

				case (UINT)OBJ_TYPE::ENEMY:
				{
					RENDER->RenderFillRectangle(
						vPos.x,
						vPos.y - 5,
						vPos.x + 5,
						vPos.y,
						RGB(255, 0, 0));
					break;
				}

				default:
				{
					RENDER->RenderFillRectangle(
						vPos.x,
						vPos.y - 5,
						vPos.x + 5,
						vPos.y,
						RGB(255, 255, 255));
					break;
				}
				}
			}
			
		}
	}
}
