#pragma once
#include "CFuncObj.h"


class CFuncAttack :
    public CFuncObj
{
private:
	CD2DImage*	m_pImg;
	float		m_fCurTime;	// 오브젝트 생성되고 지나간 시간
	float		m_fDuration;	// 오브젝트 지속시간
	 
	Vec2		m_vVelocity; // 투사체의 경우 속도를 가져야함.
	bool		m_bIsGround;
	bool		m_bIsHit; // 맞고 떨어지는 투사체의 경우
public:
	CFuncAttack(OBJ_TYPE _eType, const wstring& _strImgName, const wstring& _strImgPath, float _fDuration, float _fPlayTime, int  _imgSize, bool _dir);
	virtual ~CFuncAttack();

	virtual void Update();
	virtual void Render();

	void CreateAttackArea(CObject* _pObj, Vec2 _vPos, Vec2 _vScale);
	void CreateProjectile(CObject* _pObj, const wstring& _strObjName, Vec2 _vPos, Vec2 _vScale, Vec2 _vVelocity);
		 
	virtual void	OnCollision(CCollider* _pOther) {};
	virtual void	OnCollisionEnter(CCollider* _pOther);
	virtual void	OnCollisionExit(CCollider* _pOther) {};
};

