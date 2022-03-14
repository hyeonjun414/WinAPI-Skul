#pragma once


// 오브젝트 그룹
enum class OBJ_TYPE
{
	DEFAULT,

	IMAGE,
	TEXT,
	TILE,
	
	PLAYER,
	MONSTER,
	BULLET_PLAYER,
	BULLET_ENEMY,
	MISSILE,


	UI,
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

// 그리기에 사용할 브러쉬와 펜 그룹
enum class BRUSH_TYPE
{
	HOLLOW,

	SIZE
};
enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,

	SIZE
};

// 이벤트 타입
enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,

	SIZE
};

// 카메라 효과
enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,

	NONE,
};