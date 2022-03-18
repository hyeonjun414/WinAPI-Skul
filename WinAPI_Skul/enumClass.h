#pragma once


// ������Ʈ �׷�
enum class OBJ_TYPE
{
	DEFAULT,

	IMAGE,
	TEXT,
	TILE,
	
	MAPOBJECT,
	MONSTER,
	MONSTER_MELEE,
	MONSTER_RANGE,
	MONSTER_BOSS,
	PLAYER,
	EFFECT,


	UI,
	SIZE,
};

// ��� �׷�
enum class SCENE_TYPE
{
	NONE,
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	SIZE,
};

enum class TILE_TYPE
{
	NONE,
	GROUND,
	PLATFORM,
	WALL,

	SIZW,
};

// Ű ����
enum class KEY_STATE
{
	NONE,	// ������ �ʾҰ�, �������� ������ ���� ����
	TAP,	// �� ���� ����	
	HOLD,	// ������ �ִ� ����
	AWAY,	// �� �� ����
};

// Ű ����
enum class KEY
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	Q,W,E,R,T,Y,U,I,O,P,
	A,S,D,F,G,Z,X,C,V,B,
	ALT,LSHIFT,CTRL,
	SPACE,ENTER,ESC,

	LBTN,
	RBTN,

	SIZE
};

// �̺�Ʈ Ÿ��
enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	PLAY_AND_PAUSE,

	SIZE
};

// ī�޶� ȿ��
enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	LODING_IMAGE,


	NONE,
};

// �̹��� ȿ��
enum class IMG_EFFECT
{
	FLICKER,
	
	NONE,
};