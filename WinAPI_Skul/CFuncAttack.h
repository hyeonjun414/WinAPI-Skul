#pragma once
#include "CFuncObj.h"
class CFuncAttack :
    public CFuncObj
{
private:
	float m_fCurTime;	// ������Ʈ �����ǰ� ������ �ð�
	float m_fDuration;	// ������Ʈ ���ӽð�
public:
	CFuncAttack(OBJ_TYPE _eType, wstring _strImgName, wstring _strImgPath, float _fDuration, float _fPlayTime, int  _imgSize, bool _dir);
	virtual ~CFuncAttack();

	virtual void Update();
	virtual void Render();

	void CreateAttackArea(CObject* _pObj, Vec2 _vPos, Vec2 _vScale);

	virtual void	OnCollision(CCollider* _pOther) {};
	virtual void	OnCollisionEnter(CCollider* _pOther);
	virtual void	OnCollisionExit(CCollider* _pOther) {};
};

