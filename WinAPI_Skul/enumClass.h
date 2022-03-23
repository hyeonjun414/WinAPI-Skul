#pragma once


// ������Ʈ �׷�
enum class OBJ_TYPE
{
	DEFAULT,
	BACKGOUNRD,
	LINE,
	IMAGE,
	TILE,
	
	MAPOBJECT,
	ENEMY,
	PLAYER,
	PLAYER_ATTACK,
	BOSS_ATTACK,
	PROJECTILE,
	EFFECT,
	ATTACK,
	TEXT,
	HUD,
	UI,
	SIZE,
};

// ���� �׷�
enum class ENEMY_TYPE
{
	ENEMY_MELEE,
	ENEMY_RANGE,
	ENEMY_BOSS,
	BIG_KNIGHT,
	WIZARD,
	ELDER_ENT,

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
	BOSS,

	SIZE,
};

enum class TILE_TYPE
{
	NONE,
	GROUND,
	FLOATING,
	WALL,

	SIZE,
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
	SHAKING,


	NONE,
};

// �̹��� ȿ��
enum class IMG_EFFECT
{
	FLICKER,
	
	NONE,
};

// �ؽ�Ʈ ȿ��
enum class TEXT_EFFECT
{
	BOUNCE,

	NONE,
};

// ���� Ÿ��
enum class ATTACK_TYPE
{
	MELEE,
	RANGE,

	NONE,
};