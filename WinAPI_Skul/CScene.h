#pragma once

class CGameObject;

class CScene
{
protected:
	vector<CGameObject*>	m_vecObjectList[(int)OBJ_TYPE::SIZE]; // 게임 오브젝트를 그룹별로 저장할 벡터
	wstring					m_strName;		// 씬의 이름
	SCENE_TYPE				m_eType;		// 씬의 타입

	UINT					m_iTileX;		// 해당 씬의 타일 가로 개수
	UINT					m_iTileY;		// 해당 씬의 타일 세로 개수

public:
	CScene();
	CScene(wstring _strName, SCENE_TYPE _eType);
	virtual ~CScene();

	virtual void	Update();
	virtual void	FinalUpdate();
	virtual void	Render(HDC _hDC);

	virtual void	Enter() = 0;
	virtual void	Exit() = 0;

	void			SetName(const wstring& _strName)	{ m_strName = _strName; }

	wstring			GetName()							{ return m_strName; }
	UINT			GetTileX()							{ return m_iTileX; }
	UINT			GetTileY()							{ return m_iTileY; }
	const vector<CGameObject*>& GetGroupObject(OBJ_TYPE _eType) { return m_vecObjectList[(UINT)_eType]; }
	vector<CGameObject*>&		GetUIGroup()					{ return m_vecObjectList[(UINT)OBJ_TYPE::UI]; }

	void			AddObject(CGameObject* _pObj);
	void			EraseObject(CGameObject* _pObj);
	void			DeleteGroup(OBJ_TYPE _group);

	void			CreateTile(UINT _xSize, UINT _ySize);
	void			LoadTile(const wstring& _strPath);
	void			RenderTile(HDC _hDC);

protected:
	void			ClearObject();
};

