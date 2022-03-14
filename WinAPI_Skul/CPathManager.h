#pragma once
class CPathManager
{
	SINGLETON(CPathManager);

private:
	wchar_t		m_strContentPath[255]; // ������ ��ü�� ��� ���� ���� 255���ڷ� ���ѵǾ�����.

public:
	void			Init(); // �ʱ�ȭ �ܰ迡�� ���� ȯ�濡���� ���� ��θ� ���´�.

	// ��θ� ��ȯ�ϴ� �Լ��� ( ����, ��� )
	const wchar_t*	GetContentPath() { return m_strContentPath; }
	const wchar_t*	GetContextRelativePath();
};

