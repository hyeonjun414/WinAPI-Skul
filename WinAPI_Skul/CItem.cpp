#include "pch.h"
#include "CItem.h"

CItem::CItem() :
	CObject(OBJ_TYPE::ITEM),
	m_bIsUsed(false)
{
}

CItem::~CItem()
{
}
