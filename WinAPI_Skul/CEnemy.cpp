#include "pch.h"
#include "CEnemy.h"
#include "CEnemyBoss.h"
#include "CEnemyMelee.h"
#include "CEnemyRange.h"
#include "CAnimator.h"

#include "CStateIdle.h"


CEnemy::CEnemy(OBJ_TYPE _eType, ENEMY_TYPE _eMonsterType):
	CObject(_eType),
	m_eEnemyType(_eMonsterType),
	m_vVelocity{}
{

}

CEnemy::~CEnemy()
{
	delete m_pState;
}

void CEnemy::Init()
{
	//switch (GetObjGroup())
	//{
	//case OBJ_TYPE::ENEMY_MELEE:
	//	CEnemyMelee* enemy =  new CEnemyMelee(GetObjGroup(), );
	//	CREATEOBJECT(enemy);
	//	break;
	//case OBJ_TYPE::ENEMY_RANGE:
	//	CEnemyRange* enemy = new CEnemyRange();
	//	break;
	//case OBJ_TYPE::ENEMY_BOSS:
	//	CEnemyBoss* enemy = new CEnemyBoss();
	//	break;
	//}
}

void CEnemy::Update()
{
	CState* pState = m_pState->HandleInput(this);
	if (nullptr != pState)
	{
		m_pState->Exit(this);
		delete m_pState;
		m_pState = pState;
		m_pState->Enter(this);
	}

	m_pState->Update(this);

	if(nullptr != m_pAnimator)
		m_pAnimator->Update();
}

void CEnemy::Render()
{
	ComponentRender();
}
