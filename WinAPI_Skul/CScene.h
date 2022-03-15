#pragma once

class CObject;

class CScene
{
protected:
	vector<CObject*>	m_vecObjectList[(int)OBJ_TYPE::SIZE]; // ���� ������Ʈ�� �׷캰�� ������ ����
	wstring					m_strName;		// ���� �̸�
	SCENE_TYPE				m_eType;		// ���� Ÿ��
	SCENE_TYPE				m_eNextScene;		// ������ ��ȯ�� ��

	UINT					m_iTileX;		// �ش� ���� Ÿ�� ���� ����
	UINT					m_iTileY;		// �ش� ���� Ÿ�� ���� ����

	unsigned int			m_iTime;
	bool					m_bIsChange;

public:
	CScene();
	CScene(wstring _strName, SCENE_TYPE _eType);
	virtual ~CScene();

	virtual void	Update();
	virtual void	FinalUpdate();
	virtual void	Render();

	virtual void	Enter() = 0;
	virtual void	Exit() = 0;

	void			SetChange(bool _flag) { m_bIsChange = _flag; }
	void			SetName(const wstring& _strName) { m_strName = _strName; }

	wstring			GetName() { return m_strName; }
	UINT			GetTileX() { return m_iTileX; }
	UINT			GetTileY() { return m_iTileY; }
	const vector<CObject*>& GetGroupObject(OBJ_TYPE _eType) { return m_vecObjectList[(UINT)_eType]; }
	vector<CObject*>& GetUIGroup() { return m_vecObjectList[(UINT)OBJ_TYPE::UI]; }

	void			AddObject(CObject* _pObj);
	void			EraseObject(CObject* _pObj);
	void			DeleteGroup(OBJ_TYPE _group);

	void			CreateTile(UINT _xSize, UINT _ySize);
	void			LoadTile(const wstring& _strPath);
	void			RenderTile();

	void			ChangeNextScene(SCENE_TYPE _eType);
	void			DelayChange(UINT _iTime);
protected:
	void			ClearObject();
};