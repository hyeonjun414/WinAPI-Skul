#pragma once



struct iPoint
{
	int x;
	int y;
};

typedef struct Vector2
{
	float x;
	float y;

	Vector2()
	{
		x = 0;
		y = 0;
	}
	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	Vector2& operator=(POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
		return *this;
	}
	Vector2& operator=(int _i)
	{
		x = (float)_i;
		y = (float)_i;
		return *this;
	}

	Vector2 operator+(const Vector2& _other)
	{
		return Vector2(this->x + _other.x, this->y + _other.y);
	}
	Vector2 operator-(const Vector2& _other)
	{
		return Vector2(this->x - _other.x, this->y - _other.y);
	}
	Vector2 operator*(const Vector2& _other)
	{
		return Vector2(this->x * _other.x, this->y * _other.y);
	}
	Vector2 operator*(int _i)
	{
		return Vector2(this->x * (float)_i, this->y * (float)_i);
	}
	Vector2 operator*(float _f)
	{
		return Vector2(this->x * _f, this->y * _f);
	}
	Vector2 operator/(const Vector2& _other)
	{
		assert(!(0.f == _other.x || 0.f == _other.y));
		return Vector2(this->x / _other.x, this->y / _other.y);
	}
	Vector2 operator/(const int& _i)
	{
		assert(!(0.f == _i));
		return Vector2(this->x / _i, this->y / _i);
	}

	Vector2& operator+=(const Vector2& _other)
	{
		x += _other.x;
		y += _other.y;
		return *this;
	}
	Vector2& operator-=(const Vector2& _other)
	{
		x -= _other.x;
		y -= _other.y;
		return *this;
	}
	Vector2& operator*=(const Vector2& _other)
	{
		x *= _other.x;
		y *= _other.y;
		return *this;
	}
	Vector2& operator*=(float _f)
	{
		x *= _f;
		y *= _f;
		return *this;
	}

	Vector2& operator/=(const Vector2& _other)
	{
		assert(!(0.f == _other.x || 0.f == _other.y));
		x /= _other.x;
		y /= _other.y;
		return *this;
	}


	float Length()
	{
		return sqrt(x * x + y * y);
	}

	Vector2& Normalize() // 벡터의 정규화
	{
		float fLen = Length();

		assert(fLen != 0.f);

		x /= fLen;
		y /= fLen;
		return *this;
	}

} Vec2;

struct tKeyInfo
{
	KEY_STATE	eState; // 키의 상태 값
	bool		bPrevPush;	// 이전 프레임에 해당 키가 눌렸는지
};

struct tEvent
{
	EVENT_TYPE	eEvent;

	// 오브젝트에 대한 데이터
	DWORD_PTR	lParam;
	DWORD_PTR	wParam;
};

struct tAnimFrame
{
	Vec2	vLT;			// 프레임 좌상단 정보
	Vec2	vSliceSize;		// 프레임 크기
	Vec2	vOffset;		// 프레임 상대 위치
	float	fFrameTime;		// 프레임 재생 시간
};

struct tPlayer_Info
{
	wstring m_strName;
	int     m_iMaxHp;
	int     m_iHp;
	int     m_iDamage;
	int     m_iSkillDamage;
	Vec2    m_vVelocity;
};
