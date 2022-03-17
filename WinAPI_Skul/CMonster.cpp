#include "pch.h"
#include "CMonster.h"

CMonster::CMonster()
{
}

CMonster::CMonster(OBJ_TYPE _eType):
	CObject(_eType)
{
}

CMonster::~CMonster()
{
}

void CMonster::Init()
{
}

void CMonster::Update()
{
}

void CMonster::Render()
{
}

void CMonster::OnCollision(CCollider* _pOther)
{
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
}

void CMonster::OnCollisionExit(CCollider* _pOther)
{
}
