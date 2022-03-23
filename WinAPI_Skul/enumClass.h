#pragma once


// 오브젝트 그룹
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

// 몬스터 그룹
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

// 장면 그룹
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

// 키 상태
enum class KEY_STATE
{
	NONE,	// 눌리지 않았고, 이전에도 눌리지 않은 상태
	TAP,	// 막 누른 시점	
	HOLD,	// 누르고 있는 상태
	AWAY,	// 막 뗀 시점
};

// 키 종류
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

// 이벤트 타입
enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	PLAY_AND_PAUSE,

	SIZE
};

// 카메라 효과
enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	LODING_IMAGE,
	SHAKING,


	NONE,
};

// 이미지 효과
enum class IMG_EFFECT
{
	FLICKER,
	
	NONE,
};

// 텍스트 효과
enum class TEXT_EFFECT
{
	BOUNCE,

	NONE,
};

// 공격 타입
enum class ATTACK_TYPE
{
	MELEE,
	RANGE,

	NONE,
};