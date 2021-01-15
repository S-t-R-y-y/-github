#include "resource.h"
#include "NoDxLib.h"
#include <windows.h>
#include <vector>
#include <queue>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define GAME_WIDTH	1200
#define GAME_HEIGHT	800
#define GAME_COLOR	32

#define GAME_WINDOW_BAR	0
#define GAME_WINDOW_NAME	"CrossRoads"

#define GAME_FPS		60

#define MOUSE_BUTTON_CODE	129

#define PATH_MAX			255
#define NAME_MAX			255

#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")

#define IMAGE_TITLE_BK_PATH			TEXT(".\\IMAGE\\forest2.png")
#define IMAGE_TITLE_ROGO_PATH		TEXT(".\\IMAGE\\titlelogo.png")
#define IMAGE_TITLE_ROGO_ROTA		0.005
#define IMAGE_TITLE_ROGO_ROTA_MAX	1.0
#define IMAGE_TITLE_ROGO_X_SPEED	1
#define IMAGE_TITLE_BUTTON_PLAY_PATH		TEXT(".\\IMAGE\\playbutton2.png")
#define IMAGE_TITLE_BUTTON_RULE_PATH		TEXT(".\\IMAGE\\rulebutton2.png")
#define IMAGE_TITLE_BUTTON_END_PATH		TEXT(".\\IMAGE\\endbutton2.png")
#define IMAGE_TITLE_BUTTON_NOW_PATH		TEXT(".\\IMAGE\\nowbutton2.png")
#define IMAGE_TITLE_BUTTON_SPAN		30

#define IMAGE_RULE_PATH		TEXT(".\\IMAGE\\rule.png")

#define IMAGE_END_COMP_PATH		TEXT(".\\IMAGE\\gameclear.png")
#define IMAGE_END_COMP_CNT		1
#define IMAGE_END_COMP_CNT_MAX	30

#define IMAGE_END_FAIL_PATH		TEXT(".\\IMAGE\\gameover.png")
#define IMAGE_END_FAIL_CNT		1
#define IMAGE_END_FAIL_CNT_MAX	30

#define IMAGE_BACK_PATH			TEXT(".\\IMAGE\\forest.png")
#define IMAGE_BACK_REV_PATH		TEXT(".\\IMAGE\\shiba.png")
#define IMAGE_BACK_NUM			4

#define IMAGE_BACK_PATH_END		TEXT(".\\IMAGE\\titlelogo.png")
#define IMAGE_PLAYER_PATH_YOKO		TEXT(".\\IMAGE\\player_tate.png")

#define IMAGE_PLAYER_PATH_RED		TEXT(".\\IMAGE\\player_tate_red.png")

#define IMAGE_ENEMY_PATH		TEXT(".\\IMAGE\\enemy.png")

#define IMAGE_ITEM_SPEED_PATH		TEXT(".\\IMAGE\\speed.png")
#define IMAGE_ITEM_MUTEKI_PATH		TEXT(".\\IMAGE\\muteki.png")
#define IMAGE_ITEM_STOP_PATH		TEXT(".\\IMAGE\\stop.png")

#define MUSIC_LOAD_ERR_TITLE	TEXT("音楽読み込みエラー")

#define MUSIC_BGM_PATH_TITLE		TEXT(".\\MUSIC\\働くオバケ.mp3")
#define MUSIC_BGM_PATH				TEXT(".\\MUSIC\\Atomic_World.mp3")
#define MUSIC_BGM_COMP_PATH			TEXT(".\\MUSIC\\Faster_Snow_Wing.mp3")
#define MUSIC_BGM_FAIL_PATH			TEXT(".\\MUSIC\\Streets_of_Dawn.mp3")

#define MUSIC_PLAYER_SHOT_MAX	4
#define MUSIC_PLAYER_SHOT_PATH_1	TEXT(".\\MUSIC\\ショット音.mp3")
#define MUSIC_PLAYER_SHOT_PATH_2	TEXT(".\\MUSIC\\beamgun-shot1.mp3")
#define MUSIC_PLAYER_SHOT_PATH_3	TEXT(".\\MUSIC\\ショット音.mp3")
#define MUSIC_PLAYER_SHOT_PATH_4	TEXT(".\\MUSIC\\beamgun-shot1.mp3")

#define MUSIC_ENEMY_DIE_PATH	TEXT(".\\MUSIC\\dead.mp3")

#define TAMA_CHANGE_MAX		 5

#define TAMA_RED_PATH			TEXT(".\\IMAGE\\TAMA\\red.png")
#define TAMA_GREEN_PATH			TEXT(".\\IMAGE\\TAMA\\green.png")
#define TAMA_BLUE_PATH			TEXT(".\\IMAGE\\TAMA\\blue.png")
#define TAMA_YELLOW_PATH		TEXT(".\\IMAGE\\TAMA\\yellow.png")

#define TAMA_DIV_WIDTH		16
#define TAMA_DIV_HEIGHT		16

#define TAMA_DIV_TATE		3
#define TAMA_DIV_YOKO		1

#define TAMA_DIV_NUM	TAMA_DIV_TATE * TAMA_DIV_YOKO

#define GAME_MAP_TATE_MAX	26
#define GAME_MAP_YOKO_MAX	38
#define GAME_MAP_KIND_MAX	2
#define GAME_MAP_PART_MAX	5

#define GAME_TIME_LIMIT		180

#define GAME_MAP_PATH			TEXT(".\\IMAGE\\MAP\\my_map.png")

#define GAME_TENMETSU_SPAN		2

#define GAME_GRAVITY		0.1
#define GAME_JUMP_HEIGHT	2.0
#define GAME_JUMP_SPEED		0.1

#define GAME_ENEMY_SHOT_SPAN	1

#define GAME_ITEM_USE_TIME		6
#define GAME_ITEM_MAX			3
#define GAME_ITEM_SPEED_UP		3

#define MAP_DIV_WIDTH		64
#define MAP_DIV_HEIGHT		64
#define MAP_DIV_TATE		10
#define MAP_DIV_YOKO		4
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO

#define START_ERR_TITLE		TEXT("スタート位置エラー")
#define START_ERR_CAPTION	TEXT("スタート位置が決まっていません")

#define GOAL_ERR_TITLE		TEXT("ゴール位置エラー")
#define GOAL_ERR_CAPTION	TEXT("ゴール位置が決まっていません")

#define MOUSE_R_CLICK_TITLE		TEXT("ゲーム中断")
#define MOUSE_R_CLICK_CAPTION	TEXT("ゲームを中断し、タイトル画面に戻りますか？")

#define M_PI 3.14159265358979323846

using namespace std;

enum GAME_MAP_KIND
{
	n = -1,		//無
	k = 10,		//壁
	t = 13,		//通路
	s = 5,		//スタート
	g = 11,		//ゴール
	e = 14,		//敵移動
	h = 19,		//敵固定
	i = 1,		//階層移動
	o = 2,		//階層移動先
	d = 12,		//即死
	b = 18,		//点滅ブロック
	u = 15,		//スピードアップアイテム
	m = 16,		//無敵アイテム
	p = 17		//ストップアイテム
};

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
	GAME_SCENE_RULE
};

enum GAME_END {
	GAME_END_COMP,
	GAME_END_FAIL
};

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 3,
	CHARA_SPEED_HIGH = 5
};

enum CHARA_RELOAD {
	CHARA_RELOAD_LOW = 60,
	CHARA_RELOAD_MIDI = 30,
	CHARA_RELOAD_HIGH = 15
};

enum SCROLL
{
	YOKO_SCROLL,
	TATE_SCROLL
};

enum ITEM_TYPE
{
	ITEM_NONE = -1,
	ITEM_SPEED = 0,
	ITEM_MUTEKI = 1,
	ITEM_STOP = 2
};

typedef struct STRUCT_I_POINT
{
	int x = -1;
	int y = -1;
	int part = -1;
}iPOINT;

typedef struct STRUCT_MOUSE
{
	int InputValue = 0;	
	int WheelValue = 0;
	iPOINT Point;
	iPOINT OldPoint;
	int OldButton[MOUSE_BUTTON_CODE] = { 0 };
	int Button[MOUSE_BUTTON_CODE] = { 0 };
}MOUSE;

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];
	int handle;
	int x;
	int y;
	int width;
	int height;
}IMAGE;

typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];
	int handle;
}MUSIC;

typedef struct STRUCT_TAMA
{
	char path[PATH_MAX];
	int handle[TAMA_DIV_NUM];
	int x;
	int y;
	int width;
	int height;
	int nowImageKind;
	int changeImageCnt;
	int changeImageCntMAX;
	int speedY;
	RECT coll;
}TAMA;

typedef struct STRUCT_ITEM
{
	int type;
	bool view;

	IMAGE image;
	int CenterX;
	int CenterY;
	int Part;
}ITEM;

typedef struct STRUCT_CHARA
{
	IMAGE image;
	int speed;
	int CenterX;
	int CenterY;

	int Part;
	double Muki;		//0：前　+1：右　-1：左

	bool Item[GAME_ITEM_MAX];

	BOOL JumpFlg;
	BOOL JumpCan;
	float JumpCou;

	RECT coll;
}CHARA;

typedef struct STRUCT_USE_ITEM
{
	bool Use;
	int Up;
	int Cou;
	queue<CHARA> Plog;
}USE_ITEM;

typedef struct STRUCT_ENEMY
{
	IMAGE image;
	int speed;
	int CenterX;
	int CenterY;
	int Part;
	int MoveAdd;

	bool view;

	vector<TAMA> tama;

	RECT coll;

}ENEMY;

typedef struct STRUCT_IMAGE_BACK
{
	IMAGE image;
	BOOL IsDraw;
}IMAGE_BACK;

typedef struct STRUCT_IMAGE_ROTA
{
	IMAGE image;
	double angle;
	double angleMAX;
	double rate;
	double rateMAX;
}IMAGE_ROTA;

typedef struct STRUCT_IMAGE_BLINK
{
	IMAGE image;
	int Cnt;
	int CntMAX;
	BOOL IsDraw;
}IMAGE_BLINK;

typedef struct STRUCT_MAP_IMAGE
{
	char path[PATH_MAX];
	int handle[MAP_DIV_NUM];
	int kind[MAP_DIV_NUM];
	int width;
	int height;
}MAPCHIP;

typedef struct STRUCT_MAP
{
	GAME_MAP_KIND kind;
	int x;
	int y;
	int width;
	int height;
}MAP;

int StartTimeFps;
int CountFps;
float CalcFps;
int SampleNumFps = GAME_FPS;

int AllKeyState[256] = { 0 };
int OldAllKeyState[256] = { 0 };

int BGHandle1;
int BGHandle2;
int BGHandle3;

int GNSound;
int DDNSound;

MOUSE mouse;

int GameScene;
int GameLoop = TRUE;

int TimeLim = GAME_TIME_LIMIT;
int TimeCou = 0;

int TenmetsuTime = 0;
int TenmetsuCou = 0;

int GameEndKind;
RECT GoalRect = { -1,-1, -1, -1 };

IMAGE Image_RULE;

IMAGE ImageBack_END;
CHARA player;

vector<iPOINT> FromWarp;
vector<iPOINT> ToWarp;
vector<iPOINT> Sokushi;
vector<iPOINT> Tenmetsu;
vector<ENEMY> enemy;
vector<iPOINT> enemyPt;
vector<int> enemyMove;

ENEMY enemyTemp;
TAMA tamaTemp;

IMAGE_BACK ImageBack[IMAGE_BACK_NUM];

IMAGE ImageTitleBK;

IMAGE ImageTitleButtonPlay;
IMAGE ImageTitleButtonRule;
IMAGE ImageTitleButtonEnd;
IMAGE ImageTitleButtonNow;
int NowChoice = 0;

IMAGE_ROTA ImageTitleROGO;

IMAGE_BLINK ImageEndCOMP;
IMAGE_BLINK ImageEndFAIL;

MUSIC BGM;
MUSIC BGM_TITLE;
MUSIC BGM_COMP;
MUSIC BGM_FAIL;

int Scroll;

ITEM itemSpeedTemp;
ITEM itemMutekiTemp;
ITEM itemStopTemp;

USE_ITEM Speed;
USE_ITEM Muteki;
USE_ITEM Stop;
IMAGE PlayerRed;

vector<ITEM> itemSpeed;
vector<ITEM> itemMuteki;
vector<ITEM> itemStop;

GAME_MAP_KIND mapData[GAME_MAP_PART_MAX][GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX] =
{
	{
		k,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,t,t,t,t,t,t,t,t,t,t,t,t,u,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,t,t,t,t,t,t,t,t,t,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,t,s,t,t,t,t,t,t,t,t,t,t,k,k,t,k,k,k,k,t,k,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,t,t,t,t,t,t,t,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		t,t,t,t,t,t,t,k,t,t,t,t,t,t,t,m,t,t,t,t,t,t,p,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,i,t,k,k,
		k,k,k,k,k,k,d,d,d,t,t,k,d,k,k,k,d,k,d,k,d,k,d,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k
	},
	{
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,t,t,t,k,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,i,t,t,k,t,t,m,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,e,t,t,k,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,t,t,t,k,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,t,t,t,k,t,t,t,t,e,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,e,t,t,t,t,t,t,t,t,k,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,t,t,t,k,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,e,e,e,t,k,t,t,t,e,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,t,t,t,k,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,k,t,k,t,k,t,t,t,t,t,k,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,k,k,k,k,k,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,t,t,t,k,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,t,t,t,k,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,k,k,t,t,e,t,t,t,k,k,k,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,e,t,t,t,t,t,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,e,t,t,t,t,t,t,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,e,t,t,k,t,t,t,k,t,k,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,u,t,t,t,t,t,t,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,o,t,t,t,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k
	},
	{
		k,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,o,t,k,k,
		k,k,m,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,k,t,k,t,t,t,t,t,t,t,t,k,b,k,t,k,t,k,t,k,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,t,t,t,t,t,t,t,t,t,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,t,t,t,t,b,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,t,t,t,t,t,t,t,k,t,t,t,b,k,k,t,k,k,k,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		t,t,t,t,t,t,t,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,u,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		t,p,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,i,t,k,k,
		k,k,k,k,k,k,d,d,d,t,t,k,d,k,d,k,d,k,d,k,d,k,d,k,t,t,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,t,t,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,t,t,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,t,t,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,t,t,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k
	},
	{
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,t,t,t,k,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,o,t,t,t,t,k,u,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,t,t,t,t,t,k,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,t,k,k,k,k,k,k,k,k,t,k,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,t,t,t,k,t,k,t,t,e,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,e,t,t,t,t,t,t,t,t,t,t,k,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,k,k,t,t,t,t,t,t,t,k,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,h,h,h,t,k,t,t,t,e,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,t,t,t,k,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,t,k,k,k,k,k,k,t,t,k,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,k,k,k,k,k,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,t,t,t,k,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,t,t,t,k,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,t,t,e,t,t,t,k,k,k,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,e,t,t,t,t,t,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,e,t,t,k,t,t,t,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,e,t,t,t,k,t,t,k,t,k,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,k,k,k,k,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,k,k,k,k,k,k,t,k,t,t,t,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,u,t,t,k,t,t,t,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,t,t,t,t,i,t,t,t,t,t,t,t,t,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k
	},
	{
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,d,t,t,t,k,k,
		k,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,t,o,t,t,k,k,k,t,t,u,t,t,t,k,t,k,b,b,k,t,t,t,t,t,t,t,t,k,k,t,t,t,t,t,k,k,
		k,k,t,t,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,t,t,t,t,t,t,t,t,k,k,
		k,k,t,t,t,t,t,t,t,t,k,d,k,d,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,g,t,k,k,
		k,k,t,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,t,k,t,k,t,t,t,t,t,t,k,k,k,k,k,
		k,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,b,t,t,t,t,k,k,
		k,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,t,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k
	}
};

int mapScroll[GAME_MAP_PART_MAX] = 
{
	YOKO_SCROLL,
	TATE_SCROLL,
	YOKO_SCROLL,
	TATE_SCROLL,
	YOKO_SCROLL
};


GAME_MAP_KIND mapDataInit[GAME_MAP_PART_MAX][GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

MAPCHIP mapChip;

MAP map[GAME_MAP_PART_MAX][GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

iPOINT startPt{ -1, -1, -1};

RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

VOID MY_FPS_UPDATE(VOID);
VOID MY_FPS_WAIT(VOID);

VOID MY_ALL_KEYDOWN_UPDATE(VOID);
BOOL MY_KEY_DOWN(int);
BOOL MY_KEY_UP(int);
BOOL MY_KEYDOWN_KEEP(int, int);

VOID MY_MOUSE_UPDATE(VOID);
BOOL MY_MOUSE_DOWN(int);
BOOL MY_MOUSE_UP(int);
BOOL MY_MOUSEDOWN_KEEP(int, int);

VOID MY_START(VOID);
VOID MY_START_PROC(VOID);
VOID MY_START_DRAW(VOID);

VOID MY_RULE(VOID);
VOID MY_RULE_PROC(VOID);
VOID MY_RULE_DRAW(VOID);

VOID MY_PLAY(VOID);
VOID MY_PLAY_PROC(VOID);
VOID MY_PLAY_DRAW(VOID);

VOID MY_END(VOID);
VOID MY_END_PROC(VOID);
VOID MY_END_DRAW(VOID);

BOOL MY_LOAD_IMAGE(VOID);
VOID MY_DELETE_IMAGE(VOID);

BOOL MY_LOAD_MUSIC(VOID);
VOID MY_DELETE_MUSIC(VOID);

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT);
BOOL MY_CHECK_RECT_COLL(RECT, RECT);

//-------------------------------------------------------


//-------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);	
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_COLOR);
	SetWindowStyleMode(GAME_WINDOW_BAR);
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));

	SetWindowIconID(IDI_ICON1);

	//if (DxLib_Init() == -1) { return(-1); }
	if (MY_LOAD_IMAGE() == -1) { return(-1); }
	if (MY_LOAD_MUSIC() == -1) { return(-1); }

	SetMouseDispFlag(TRUE);

	GameScene = GAME_SCENE_START;

	SetDrawScreen(DX_SCREEN_BACK);

	for (int part = 0; part < GAME_MAP_PART_MAX; part++)
	{
		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
			{
				if (mapData[part][tate][yoko] == s)
				{
					startPt.x = mapChip.width * yoko + mapChip.width / 2;
					startPt.y = mapChip.height * tate + mapChip.height / 2;
					startPt.part = part;
				}

				if (mapData[part][tate][yoko] == g)
				{
					GoalRect.left = mapChip.width * yoko;
					GoalRect.top = mapChip.height * tate;
					GoalRect.right = mapChip.width * (yoko + 1);
					GoalRect.bottom = mapChip.height * (tate + 1);
				}

				if (mapData[part][tate][yoko] == e)
				{
					iPOINT work;
					work.x = mapChip.width * yoko;
					work.y = mapChip.height * tate;
					work.part = part;
					enemyPt.push_back(work);
					enemyMove.push_back(1);
				}

				if (mapData[part][tate][yoko] == h)
				{
					iPOINT work;
					work.x = mapChip.width * yoko;
					work.y = mapChip.height * tate;
					work.part = part;
					enemyPt.push_back(work);
					enemyMove.push_back(0);
				}

				if (mapData[part][tate][yoko] == i)
				{
					iPOINT work;
					work.x = mapChip.width * yoko;
					work.y = mapChip.height * tate;
					work.part = part;
					FromWarp.push_back(work);
				}

				if (mapData[part][tate][yoko] == o)
				{
					iPOINT work;
					work.x = mapChip.width * yoko;
					work.y = mapChip.height * tate;
					work.part = part;
					ToWarp.push_back(work);
				}

				if (mapData[part][tate][yoko] == d)
				{
					iPOINT work;
					work.x = mapChip.width * yoko;
					work.y = mapChip.height * tate;
					work.part = part;
					Sokushi.push_back(work);
				}

				if (mapData[part][tate][yoko] == b)
				{
					iPOINT work;
					work.x = mapChip.width * yoko;
					work.y = mapChip.height * tate;
					work.part = part;
					Tenmetsu.push_back(work);
				}

				if (mapData[part][tate][yoko] == u)
				{
					ITEM work = itemSpeedTemp;
					work.type = ITEM_SPEED;
					work.CenterX = mapChip.width * yoko - work.image.width/2;
					work.CenterY = mapChip.height * tate - work.image.height/2;
					work.image.x = mapChip.width * yoko;
					work.image.y = mapChip.height * tate;
					work.Part = part;
					work.view = true;
					itemSpeed.push_back(work);
				}

				if (mapData[part][tate][yoko] == m)
				{
					ITEM work = itemMutekiTemp;
					work.type = ITEM_MUTEKI;
					work.CenterX = mapChip.width * yoko - work.image.width / 2;
					work.CenterY = mapChip.height * tate - work.image.height / 2;
					work.image.x = mapChip.width * yoko;
					work.image.y = mapChip.height * tate;
					work.Part = part;
					work.view = true;
					itemMuteki.push_back(work);
				}

				if (mapData[part][tate][yoko] == p)
				{
					ITEM work = itemStopTemp;
					work.type = ITEM_SPEED;
					work.CenterX = mapChip.width * yoko - work.image.width / 2;
					work.CenterY = mapChip.height * tate - work.image.height / 2;
					work.image.x = mapChip.width * yoko;
					work.image.y = mapChip.height * tate;
					work.Part = part;
					work.view = true;
					itemStop.push_back(work);
				}
			}
		}
	}


	if (startPt.x == -1 || startPt.y == -1 || startPt.part == -1)
	{
		MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK);	return -1;
	}

	if (GoalRect.left == -1)
	{
		MessageBox(GetMainWindowHandle(), GOAL_ERR_CAPTION, GOAL_ERR_TITLE, MB_OK);	return -1;
	}

	while (GameLoop)
	{
		if (ProcessMessage() != 0) { break; }

		if (ClearDrawScreen() != 0) { break; }

		MY_ALL_KEYDOWN_UPDATE();

		MY_MOUSE_UPDATE();

		MY_FPS_UPDATE();

		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();
			break;
		case GAME_SCENE_END:
			MY_END();
			break;
		case GAME_SCENE_RULE:
			MY_RULE();
			break;
		}

		ScreenFlip();

		MY_FPS_WAIT();
	}

	ScreenFlip();

	enemyMove.clear();
	enemyPt.clear();

	MY_DELETE_IMAGE();

	MY_DELETE_MUSIC();

	//DxLib_End();

	return 0;
}

VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0)
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps)
	{
		int now = GetNowCount();

		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	TimeCou++;
	if (!Stop.Use)TenmetsuCou++;
	if (Speed.Use)Speed.Cou++;
	if (Muteki.Use)Muteki.Cou++;
	if (Stop.Use)Stop.Cou++;

	return;
}

VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;

	if (waitTime > 0)
	{
		WaitTimer(waitTime);
	}
	return;
}

VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	char TempKey[256];

	for (int i = 0; i < 256; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey);

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)
		{
			AllKeyState[i]++;
		}
		else
		{
			AllKeyState[i] = 0;
		}
	}
	return;
}

BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return(TRUE);
	}
	else
	{
		return(FALSE);
	}
}

BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (OldAllKeyState[KEY_INPUT_] >= 1	&& AllKeyState[KEY_INPUT_] == 0)
	{
		return(TRUE);
	}
	else
	{
		return(FALSE);
	}
}

BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int DownTime)
{
	int UpdateTime = DownTime * GAME_FPS;

	if (AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return(TRUE);
	}
	else
	{
		return(FALSE);
	}
}

VOID MY_MOUSE_UPDATE(VOID)
{
	mouse.OldPoint = mouse.Point;

	for (int i = 0; i < MOUSE_BUTTON_CODE; i++) { mouse.OldButton[i] = mouse.Button[i]; }

	GetMousePoint(&mouse.Point.x, &mouse.Point.y);

	mouse.InputValue = GetMouseInput();

	if ((mouse.InputValue & MOUSE_INPUT_LEFT) == MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT]++; }
	if ((mouse.InputValue & MOUSE_INPUT_LEFT) != MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT] = 0; }

	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) == MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE]++; }
	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) != MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE] = 0; }

	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) == MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT]++; }
	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) != MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT] = 0; }

	mouse.WheelValue = GetMouseWheelRotVol();

	return;
}

BOOL MY_MOUSE_DOWN(int MOUSE_INPUT_)
{
	if (mouse.Button[MOUSE_INPUT_] != 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL MY_MOUSE_UP(int MOUSE_INPUT_)
{
	if (mouse.OldButton[MOUSE_INPUT_] >= 1
		&& mouse.Button[MOUSE_INPUT_] == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL MY_MOUSEDOWN_KEEP(int MOUSE_INPUT_, int DownTime)
{
	int UpdateTime = DownTime * GAME_FPS;

	if (mouse.Button[MOUSE_INPUT_] > UpdateTime)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

VOID MY_START(VOID)
{
	MY_START_PROC();
	MY_START_DRAW();

	return;
}

VOID MY_START_PROC(VOID)
{
	if (CheckSoundMem(BGM_TITLE.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 75 / 100, BGM_TITLE.handle);
		PlaySoundMem(BGM_TITLE.handle, DX_PLAYTYPE_LOOP);
	}

	if (MY_KEY_UP(KEY_INPUT_W) == TRUE || MY_KEY_UP(KEY_INPUT_UP) == TRUE)
	{
		NowChoice--;
		NowChoice += 3;
		NowChoice %= 3;
	}
	if (MY_KEY_UP(KEY_INPUT_S) == TRUE || MY_KEY_UP(KEY_INPUT_DOWN) == TRUE)
	{
		NowChoice++;
		NowChoice %= 3;
	}

	switch (NowChoice)
	{
	case 0:
		ImageTitleButtonNow.y = ImageTitleButtonPlay.y;
		break;
	case 1:
		ImageTitleButtonNow.y = ImageTitleButtonRule.y;
		break;
	case 2:
		ImageTitleButtonNow.y = ImageTitleButtonEnd.y;
		break;
	}

	if (MY_KEY_UP(KEY_INPUT_RETURN) == TRUE)
	{
		if (CheckSoundMem(BGM_TITLE.handle) != 0)
		{
			StopSoundMem(BGM_TITLE.handle);
		}

		SetMouseDispFlag(FALSE);

		Scroll = mapScroll[0];

		player.CenterX = startPt.x;
		player.CenterY = startPt.y;
		player.Part = startPt.part;

		player.image.x = player.CenterX;
		player.image.y = player.CenterY;

		player.JumpCou = 0;
		player.JumpFlg = FALSE;
		player.JumpCan = FALSE;

		player.Muki = 0;

		for (int i = 0; i < GAME_ITEM_MAX; i++)player.Item[i] = FALSE;

		for (int i = 0; i < (int)itemSpeed.size(); i++)itemSpeed[i].view = TRUE;
		for (int i = 0; i < (int)itemMuteki.size(); i++)itemMuteki[i].view = TRUE;
		for (int i = 0; i < (int)itemStop.size(); i++)itemStop[i].view = TRUE;

		Speed.Cou = 0;
		Speed.Up = 1;
		Speed.Use = FALSE;
		while (!Speed.Plog.empty())Speed.Plog.pop();

		Muteki.Cou = 0;
		Muteki.Up = 1;
		Muteki.Use = FALSE;
		while (!Muteki.Plog.empty())Muteki.Plog.pop();

		Stop.Cou = 0;
		Stop.Up = 1;
		Stop.Use = FALSE;
		while (!Stop.Plog.empty())Stop.Plog.pop();

		SetMousePoint(player.image.x, player.image.y);

		for (int i = 0; i < (int)enemyPt.size(); i++) 
		{
			ENEMY work = enemyTemp;
			work.MoveAdd = - 2 * enemyMove[i];

			work.view = TRUE;

			work.CenterX = enemyPt[i].x;
			work.CenterY = enemyPt[i].y;

			work.image.x = work.CenterX;
			work.image.y = work.CenterY;

			work.Part = enemyPt[i].part;

			work.tama.clear();

			enemy.push_back(work);
		}

		TimeLim = 0;
		TimeCou = 0;

		TenmetsuCou = 0;
		TenmetsuTime = 0;

		for (int part = 0; part < GAME_MAP_PART_MAX; part++)
		{
			ImageBack[part].image.x = GAME_WIDTH / 2 - ImageBack[part].image.width / 2;
			ImageBack[part].image.y = GAME_HEIGHT / 2 - ImageBack[part].image.height / 2;
		}

		switch (NowChoice)
		{
		case 0:
			GameEndKind = GAME_END_FAIL;
			GameScene = GAME_SCENE_PLAY;
			break;

		case 1:
			GameScene = GAME_SCENE_RULE;
			break;

		case 2:
			ImageTitleButtonNow.y = ImageTitleButtonEnd.y;
			GameLoop = FALSE;
			itemSpeed.clear();
			itemMuteki.clear();
			itemStop.clear();
			break;
		}

		return;
	}

	if (ImageTitleROGO.rate < ImageTitleROGO.rateMAX)
	{
		ImageTitleROGO.rate += IMAGE_TITLE_ROGO_ROTA;
	}
	if (ImageTitleROGO.image.x < WINDOW_WIDTH / 2)
	{
		ImageTitleROGO.image.x += IMAGE_TITLE_ROGO_X_SPEED;
	}

	return;
}

VOID MY_START_DRAW(VOID)
{
	DrawGraph(ImageTitleBK.x, ImageTitleBK.y, ImageTitleBK.handle, TRUE);

	DrawRotaGraph(
		ImageTitleROGO.image.x, ImageTitleROGO.image.y,
		ImageTitleROGO.rate,
		ImageTitleROGO.angle,
		ImageTitleROGO.image.handle, TRUE);

	DrawGraph(ImageTitleButtonPlay.x, ImageTitleButtonPlay.y, ImageTitleButtonPlay.handle, TRUE);
	DrawGraph(ImageTitleButtonRule.x, ImageTitleButtonRule.y, ImageTitleButtonRule.handle, TRUE);
	DrawGraph(ImageTitleButtonEnd.x, ImageTitleButtonEnd.y, ImageTitleButtonEnd.handle, TRUE);
	DrawGraph(ImageTitleButtonNow.x, ImageTitleButtonNow.y, ImageTitleButtonNow.handle, TRUE);

	return;
}

VOID MY_RULE(VOID)
{
	MY_RULE_PROC();
	MY_RULE_DRAW();

	return;
}

VOID MY_RULE_PROC(VOID)
{
	if (CheckSoundMem(BGM_TITLE.handle) == 0)
	{
		PlaySoundMem(BGM_TITLE.handle, DX_PLAYTYPE_LOOP);
	}

	if (MY_KEY_UP(KEY_INPUT_RETURN) == TRUE)
	{
		if (CheckSoundMem(BGM_TITLE.handle) != 0)
		{
			StopSoundMem(BGM_TITLE.handle);
		}

		SetMouseDispFlag(FALSE);

		GameScene = GAME_SCENE_START;

		return;
	}

	return;
}

VOID MY_RULE_DRAW(VOID)
{
	DrawGraph(Image_RULE.x, Image_RULE.y, Image_RULE.handle, TRUE);
	return;
}

VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();
	MY_PLAY_DRAW();

	return;
}

VOID MY_PLAY_PROC(VOID)
{
	if (CheckSoundMem(BGM.handle) == 0)
	{
		ChangeVolumeSoundMem(255 * 75 / 100, BGM.handle);

		PlaySoundMem(BGM.handle, DX_PLAYTYPE_LOOP);
	}

	player.Muki = 0.0;

	TenmetsuTime = TenmetsuCou / GAME_FPS;

	TimeLim = GAME_TIME_LIMIT - TimeCou / GAME_FPS;
	if (TimeLim <= 0)
	{
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);
		}

		SetMouseDispFlag(TRUE);
		GameEndKind = GAME_END_FAIL;
		GameScene = GAME_SCENE_END;

		return;
	}

	if (GAME_ITEM_USE_TIME - Speed.Cou / GAME_FPS <= 0)
	{
		Speed.Use = FALSE;
		Speed.Up = 1;
		Speed.Cou = 0;
		while (!Speed.Plog.empty())Speed.Plog.pop();
	}
	if (GAME_ITEM_USE_TIME - Muteki.Cou / GAME_FPS <= 0)
	{
		Muteki.Use = FALSE;
		Muteki.Up = 1;
		Muteki.Cou = 0;
		while (!Muteki.Plog.empty())Muteki.Plog.pop();
	}
	if (GAME_ITEM_USE_TIME - Stop.Cou / GAME_FPS <= 0)
	{
		Stop.Use = FALSE;
		Stop.Up = 1;
		Stop.Cou = 0;
		while (!Stop.Plog.empty())Stop.Plog.pop();
	}


	for (int SpeedCnt = 0; SpeedCnt < Speed.Up; SpeedCnt++)
	{
		if (mouse.Button[MOUSE_INPUT_RIGHT] == TRUE)
		{
			iPOINT R_ClickPt = mouse.Point;

			SetMouseDispFlag(TRUE);

			int Ret = MessageBox(GetMainWindowHandle(), MOUSE_R_CLICK_CAPTION, MOUSE_R_CLICK_TITLE, MB_YESNO);

			if (Ret == IDYES)
			{
				if (CheckSoundMem(BGM.handle) != 0)
				{
					StopSoundMem(BGM.handle);
				}

				SetMouseDispFlag(TRUE);

				GameScene = GAME_SCENE_START;
				return;

			}
			else if (Ret == IDNO)
			{
				SetMousePoint(R_ClickPt.x, R_ClickPt.y);

				SetMouseDispFlag(FALSE);
			}
		}

		if (MY_KEY_DOWN(KEY_INPUT_1) && player.Item[ITEM_SPEED] == TRUE)
		{
			player.Item[ITEM_SPEED] = FALSE;
			Speed.Use = TRUE;
			Speed.Up = GAME_ITEM_SPEED_UP;
			Speed.Cou = 0;
			while (!Speed.Plog.empty())Speed.Plog.pop();
		}
		if (MY_KEY_DOWN(KEY_INPUT_2) && player.Item[ITEM_MUTEKI] == TRUE)
		{
			player.Item[ITEM_MUTEKI] = FALSE;
			Muteki.Use = TRUE;
			Muteki.Up = 1;
			Muteki.Cou = 0;
			while (!Muteki.Plog.empty())Muteki.Plog.pop();
		}
		if (MY_KEY_DOWN(KEY_INPUT_3) && player.Item[ITEM_STOP] == TRUE)
		{
			player.Item[ITEM_STOP] = FALSE;
			Stop.Use = TRUE;
			Stop.Up = 1;
			Stop.Cou = 0;
			while (!Stop.Plog.empty())Stop.Plog.pop();
		}

		if (MY_KEY_DOWN(KEY_INPUT_UP) || MY_KEY_DOWN(KEY_INPUT_W))
		{

			if (Scroll == YOKO_SCROLL)
			{
				if (player.JumpFlg == FALSE && player.JumpCan == TRUE)
				{
					player.JumpCan = FALSE;
					player.JumpFlg = TRUE;
					player.JumpCou = 0.0;
				}
			}
			if (Scroll == TATE_SCROLL)
			{
				player.CenterY -= CHARA_SPEED_MIDI;
				player.coll.left = player.CenterX - player.image.width / 2 + 5;
				player.coll.top = player.CenterY - player.image.height / 2 + 5;
				player.coll.right = player.CenterX + player.image.width / 2 - 5;
				player.coll.bottom = player.CenterY + player.image.height / 2 - 5;
				if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
				{
					player.CenterY += CHARA_SPEED_MIDI;
				}
			}
		}
		if ((MY_KEY_DOWN(KEY_INPUT_DOWN) || MY_KEY_DOWN(KEY_INPUT_S)) && Scroll == TATE_SCROLL)
		{
			player.CenterY += CHARA_SPEED_MIDI;
			player.coll.left = player.CenterX - player.image.width / 2 + 5;
			player.coll.top = player.CenterY - player.image.height / 2 + 5;
			player.coll.right = player.CenterX + player.image.width / 2 - 5;
			player.coll.bottom = player.CenterY + player.image.height / 2 - 5;
			if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
			{
				player.CenterY -= CHARA_SPEED_MIDI;
			}
		}
		if (MY_KEY_DOWN(KEY_INPUT_RIGHT) || MY_KEY_DOWN(KEY_INPUT_D))
		{
			player.CenterX += CHARA_SPEED_MIDI;
			player.coll.left = player.CenterX - player.image.width / 2 + 5;
			player.coll.top = player.CenterY - player.image.height / 2 + 5;
			player.coll.right = player.CenterX + player.image.width / 2 - 5;
			player.coll.bottom = player.CenterY + player.image.height / 2 - 5;
			player.Muki = 1.0;
			if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE || player.CenterX - player.image.width / 2 < 0 || player.CenterX + player.image.width / 2 > GAME_MAP_YOKO_MAX * mapChip.width)
			{
				player.CenterX -= CHARA_SPEED_MIDI;
			}

			if (TenmetsuTime % GAME_TENMETSU_SPAN != 0)
			{
				RECT PlayerRect = player.coll;
				for (int i = 0; i < (int)Tenmetsu.size(); i++)
				{
					RECT Work;
					Work.left = Tenmetsu[i].x;
					Work.top = Tenmetsu[i].y;
					Work.right = mapChip.width + Tenmetsu[i].x;
					Work.bottom = mapChip.height + Tenmetsu[i].y;

					if (player.Part == Tenmetsu[i].part && MY_CHECK_RECT_COLL(PlayerRect, Work) == TRUE)
					{
						player.CenterX -= CHARA_SPEED_MIDI;
					}
				}
			}
		}
		if (MY_KEY_DOWN(KEY_INPUT_LEFT) || MY_KEY_DOWN(KEY_INPUT_A))
		{
			player.CenterX -= CHARA_SPEED_MIDI;
			player.coll.left = player.CenterX - player.image.width / 2 + 5;
			player.coll.top = player.CenterY - player.image.height / 2 + 5;
			player.coll.right = player.CenterX + player.image.width / 2 - 5;
			player.coll.bottom = player.CenterY + player.image.height / 2 - 5;
			player.Muki = -1.0;
			if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE || player.CenterX - player.image.width / 2 < 0 || player.CenterX + player.image.width / 2 > GAME_MAP_YOKO_MAX * mapChip.width)
			{
				player.CenterX += CHARA_SPEED_MIDI;
			}

			if (TenmetsuTime % GAME_TENMETSU_SPAN != 0)
			{
				RECT PlayerRect = player.coll;
				for (int i = 0; i < (int)Tenmetsu.size(); i++)
				{
					RECT Work;
					Work.left = Tenmetsu[i].x;
					Work.top = Tenmetsu[i].y;
					Work.right = mapChip.width + Tenmetsu[i].x;
					Work.bottom = mapChip.height + Tenmetsu[i].y;

					if (player.Part == Tenmetsu[i].part && MY_CHECK_RECT_COLL(PlayerRect, Work) == TRUE)
					{
						player.CenterX += CHARA_SPEED_MIDI;
					}
				}
			}
		}
		if (Scroll == YOKO_SCROLL && SpeedCnt == 0)
		{
			if (player.JumpFlg == TRUE)
			{

				bool flg = FALSE;

				player.JumpCou += GAME_JUMP_SPEED;
				player.CenterY -= GAME_JUMP_SPEED * player.image.height;
				player.coll.left = player.CenterX - player.image.width / 2 + 5;
				player.coll.top = player.CenterY - player.image.height / 2 + 5;
				player.coll.right = player.CenterX + player.image.width / 2 - 5;
				player.coll.bottom = player.CenterY + player.image.height / 2 - 5;

				if (TenmetsuTime % GAME_TENMETSU_SPAN != 0)
				{
					RECT PlayerRect = player.coll;
					for (int i = 0; i < (int)Tenmetsu.size(); i++)
					{
						RECT Work;
						Work.left = Tenmetsu[i].x;
						Work.top = Tenmetsu[i].y;
						Work.right = mapChip.width + Tenmetsu[i].x;
						Work.bottom = mapChip.height + Tenmetsu[i].y;

						if (player.Part == Tenmetsu[i].part && MY_CHECK_RECT_COLL(PlayerRect, Work) == TRUE)
						{
							flg = TRUE;
							player.CenterY += GAME_JUMP_SPEED * player.image.height;
							player.JumpFlg = FALSE;
						}
					}
				}

				if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE && flg == FALSE)
				{
					player.CenterY += GAME_JUMP_SPEED * player.image.height;
					player.JumpFlg = FALSE;
				}
				if (player.JumpCou > GAME_JUMP_HEIGHT && flg == FALSE)
				{
					player.JumpFlg = FALSE;
				}
			}
			if (player.JumpFlg == FALSE)
			{
				bool flg = FALSE;

				player.CenterY += GAME_GRAVITY * player.image.height;
				player.coll.left = player.CenterX - player.image.width / 2 + 5;
				player.coll.top = player.CenterY - player.image.height / 2 + 5;
				player.coll.right = player.CenterX + player.image.width / 2 - 5;
				player.coll.bottom = player.CenterY + player.image.height / 2 - 5;

				if (TenmetsuTime % GAME_TENMETSU_SPAN != 0)
				{
					RECT PlayerRect = player.coll;
					for (int i = 0; i < (int)Tenmetsu.size(); i++)
					{
						RECT Work;
						Work.left = Tenmetsu[i].x;
						Work.top = Tenmetsu[i].y;
						Work.right = mapChip.width + Tenmetsu[i].x;
						Work.bottom = mapChip.height + Tenmetsu[i].y;

						if (player.Part == Tenmetsu[i].part && MY_CHECK_RECT_COLL(PlayerRect, Work) == TRUE)
						{
							flg = TRUE;
							player.CenterY -= GAME_GRAVITY * player.image.height;
							player.JumpCan = TRUE;
						}
					}
				}

				if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE && flg == FALSE)
				{
					player.CenterY -= GAME_GRAVITY * player.image.height;
					player.JumpCan = TRUE;
				}
				else if(flg == FALSE)
				{
					player.JumpCan = FALSE;
				}
			}
		}

		player.coll.left = player.CenterX - player.image.width / 2 + 5;
		player.coll.top = player.CenterY - player.image.height / 2 + 5;
		player.coll.right = player.CenterX + player.image.width / 2 - 5;
		player.coll.bottom = player.CenterY + player.image.height / 2 - 5;

		player.image.x = player.CenterX - player.image.width / 2;
		player.image.y = player.CenterY - player.image.height / 2;

		if (Speed.Use && (int)Speed.Plog.size() < GAME_ITEM_SPEED_UP)
		{
			CHARA work = player;
			work.image = PlayerRed;
			work.image.x = player.image.x;
			work.image.y = player.image.y;
			Speed.Plog.push(work);
		}

		RECT PlayerRect;
		PlayerRect.left = player.image.x + 20;
		PlayerRect.top = player.image.y + 20;
		PlayerRect.right = player.image.x + player.image.width - 20;
		PlayerRect.bottom = player.image.y + player.image.height - 20;

		if (player.Part == GAME_MAP_PART_MAX - 1 && MY_CHECK_RECT_COLL(PlayerRect, GoalRect) == TRUE)
		{
			if (CheckSoundMem(BGM.handle) != 0)
			{
				StopSoundMem(BGM.handle);
			}

			SetMouseDispFlag(TRUE);

			GameEndKind = GAME_END_COMP;

			GameScene = GAME_SCENE_END;

			return;
		}

		for (int i = 0; i < (int)FromWarp.size(); i++)
		{
			RECT From;
			From.left = FromWarp[i].x;
			From.top = FromWarp[i].y;
			From.right = mapChip.width + FromWarp[i].x;
			From.bottom = mapChip.height + FromWarp[i].y;

			if (player.Part == FromWarp[i].part && MY_CHECK_RECT_COLL(PlayerRect, From) == TRUE)
			{
				player.Part = ToWarp[FromWarp[i].part].part;
				player.CenterX = ToWarp[FromWarp[i].part].x;
				player.CenterY = ToWarp[FromWarp[i].part].y;
				player.coll.left = player.CenterX - player.image.width / 2 + 5;
				player.coll.top = player.CenterY - player.image.height / 2 + 5;
				player.coll.right = player.CenterX + player.image.width / 2 - 5;
				player.coll.bottom = player.CenterY + player.image.height / 2 - 5;

				player.image.x = player.CenterX - player.image.width / 2;
				player.image.y = player.CenterY - player.image.height / 2;

				Scroll = mapScroll[player.Part];

				for (int i = 0; i < (int)enemy.size(); i++)enemy[i].tama.clear();
			}
		}

		for (int i = 0; i < (int)Sokushi.size(); i++)
		{
			RECT Work;
			Work.left = Sokushi[i].x;
			Work.top = Sokushi[i].y;
			Work.right = mapChip.width + Sokushi[i].x;
			Work.bottom = mapChip.height + Sokushi[i].y;

			if (player.Part == Sokushi[i].part && MY_CHECK_RECT_COLL(PlayerRect, Work) == TRUE && !Muteki.Use)
			{
				if (CheckSoundMem(BGM.handle) != 0)
				{
					StopSoundMem(BGM.handle);
				}

				SetMouseDispFlag(TRUE);

				GameEndKind = GAME_END_FAIL;

				GameScene = GAME_SCENE_END;

				return;
			}
		}

		for (int i = 0; i < (int)itemSpeed.size(); i++)
		{
			RECT Work;
			Work.left = itemSpeed[i].image.x;
			Work.top = itemSpeed[i].image.y;
			Work.right = mapChip.width + itemSpeed[i].image.x;
			Work.bottom = mapChip.height + itemSpeed[i].image.y;

			if (player.Part == itemSpeed[i].Part && MY_CHECK_RECT_COLL(PlayerRect, Work) == TRUE && itemSpeed[i].view && !Speed.Use)
			{
				player.Item[ITEM_SPEED] = TRUE;
				itemSpeed[i].view = FALSE;
			}
		}

		for (int i = 0; i < (int)itemMuteki.size(); i++)
		{
			RECT Work;
			Work.left = itemMuteki[i].image.x;
			Work.top = itemMuteki[i].image.y;
			Work.right = mapChip.width + itemMuteki[i].image.x;
			Work.bottom = mapChip.height + itemMuteki[i].image.y;

			if (player.Part == itemMuteki[i].Part && MY_CHECK_RECT_COLL(PlayerRect, Work) == TRUE && itemMuteki[i].view && !Muteki.Use)
			{
				player.Item[ITEM_MUTEKI] = TRUE;
				itemMuteki[i].view = FALSE;
			}
		}

		for (int i = 0; i < (int)itemStop.size(); i++)
		{
			RECT Work;
			Work.left = itemStop[i].image.x;
			Work.top = itemStop[i].image.y;
			Work.right = mapChip.width + itemStop[i].image.x;
			Work.bottom = mapChip.height + itemStop[i].image.y;

			if (player.Part == itemStop[i].Part && MY_CHECK_RECT_COLL(PlayerRect, Work) == TRUE && itemStop[i].view && !Stop.Use)
			{
				player.Item[ITEM_STOP] = TRUE;
				itemStop[i].view = FALSE;
			}
		}

		for (int i = 0; i < (int)enemy.size(); i++)
		{
			if (enemy[i].view == TRUE && enemy[i].Part == player.Part)
			{
				if(SpeedCnt == 0 && !Stop.Use)enemy[i].CenterX += enemy[i].MoveAdd;
				if (MY_CHECK_MAP1_PLAYER_COLL(enemy[i].coll) == TRUE)
				{
					enemy[i].CenterX -= enemy[i].MoveAdd * 2;
					enemy[i].MoveAdd *= -1;
				}
				enemy[i].coll.left = enemy[i].CenterX - enemy[i].image.width / 2;
				enemy[i].coll.top = enemy[i].CenterY - enemy[i].image.height / 2;
				enemy[i].coll.right = enemy[i].CenterX + enemy[i].image.width / 2;
				enemy[i].coll.bottom = enemy[i].CenterY + enemy[i].image.height / 2;

				if (enemy[i].image.x >= 0 && enemy[i].image.x <= GAME_WIDTH)
				{
					enemy[i].image.x = enemy[i].CenterX - enemy[i].image.width / 2;
					enemy[i].image.y = enemy[i].CenterY - enemy[i].image.height / 2;
				}

				if (MY_CHECK_RECT_COLL(PlayerRect, enemy[i].coll) == TRUE && !Muteki.Use)
				{
					if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}
					SetMouseDispFlag(TRUE);

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;

					return;
				}

				if (TimeCou % (GAME_ENEMY_SHOT_SPAN * GAME_FPS) == 0 && SpeedCnt == 0 && !Stop.Use)
				{
					TAMA work = tamaTemp;
					work.x = enemy[i].CenterX - work.width / 2;
					work.y = enemy[i].CenterY - work.height / 2;

					work.coll.left = work.x;
					work.coll.right = work.x + work.width;
					work.coll.top = work.y;
					work.coll.bottom = work.y + work.height;

					work.speedY = CHARA_SPEED_HIGH;

					enemy[i].tama.push_back(work);
				}
			}
		}


		if (Scroll == YOKO_SCROLL && player.image.y > GAME_HEIGHT)
		{
			if (CheckSoundMem(BGM.handle) != 0)
			{
				StopSoundMem(BGM.handle);
			}

			SetMouseDispFlag(TRUE);

			GameEndKind = GAME_END_FAIL;

			GameScene = GAME_SCENE_END;

			return;
		}
	}

	return;
}

VOID MY_PLAY_DRAW(VOID)
{
	DrawGraph(ImageBack[player.Part % IMAGE_BACK_NUM].image.x, ImageBack[player.Part % IMAGE_BACK_NUM].image.y, ImageBack[player.Part % IMAGE_BACK_NUM].image.handle, TRUE);

	if (Scroll == YOKO_SCROLL)
	{
		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
			{
				if (player.CenterX > (GAME_WIDTH / 2) && player.CenterX <= (GAME_MAP_YOKO_MAX * mapChip.width) - (GAME_WIDTH / 2))
				{
					if (player.CenterX - (GAME_WIDTH / 2) - mapChip.width <= map[player.Part][tate][yoko].x &&
						map[player.Part][tate][yoko].x <= player.CenterX + (GAME_WIDTH / 2) &&
						0 <= map[player.Part][tate][yoko].y &&
						map[player.Part][tate][yoko].y < GAME_HEIGHT + mapChip.height)
					{
						if(map[player.Part][tate][yoko].kind != b || (map[player.Part][tate][yoko].kind == b && TenmetsuTime % GAME_TENMETSU_SPAN != 0))
						DrawGraph(
							map[player.Part][tate][yoko].x - (player.CenterX - (GAME_WIDTH / 2)),
							map[player.Part][tate][yoko].y,
							mapChip.handle[map[player.Part][tate][yoko].kind],
							TRUE);

						for(int i = 0; i < (int)itemSpeed.size(); i++)
							if(itemSpeed[i].view && itemSpeed[i].Part == player.Part)
							DrawGraph(
								itemSpeed[i].image.x - (player.CenterX - (GAME_WIDTH / 2)),
								itemSpeed[i].image.y,
								itemSpeed[i].image.handle,
								TRUE);
						for (int i = 0; i < (int)itemMuteki.size(); i++)
							if (itemMuteki[i].view && itemMuteki[i].Part == player.Part)
								DrawGraph(
									itemMuteki[i].image.x - (player.CenterX - (GAME_WIDTH / 2)),
									itemMuteki[i].image.y,
									itemMuteki[i].image.handle,
									TRUE);
						for (int i = 0; i < (int)itemStop.size(); i++)
							if (itemStop[i].view && itemStop[i].Part == player.Part)
								DrawGraph(
									itemStop[i].image.x - (player.CenterX - (GAME_WIDTH / 2)),
									itemStop[i].image.y,
									itemStop[i].image.handle,
									TRUE);

						for (int i = 0; i < (int)Speed.Plog.size(); i++)
						{
							CHARA work = Speed.Plog.front();
							Speed.Plog.pop();
							Speed.Plog.push(work);
							if(work.Part == player.Part)
								DrawRotaGraph(work.image.x - (player.CenterX - (GAME_WIDTH / 2)) + work.image.width / 2,
									work.image.y + work.image.height / 2,
									1.0,
									work.Muki / 18 * M_PI,
									work.image.handle, TRUE);
						}
						if(!Speed.Plog.empty())Speed.Plog.pop();

						DrawRotaGraph(player.image.x - (player.CenterX - (GAME_WIDTH / 2)) + player.image.width/2, player.image.y + player.image.height / 2, 1.0, player.Muki / 18 * M_PI, player.image.handle, TRUE);

						if (Muteki.Use)
						{
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
							DrawBox(player.image.x - (player.CenterX - (GAME_WIDTH / 2)) - player.image.width/2,
								player.image.y,
								player.image.x - (player.CenterX - (GAME_WIDTH / 2)) + player.image.width + player.image.width / 2,
								player.image.y + player.image.height,
								GetColor(200, 200, 255),
								TRUE);
							SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
						}
					}
				}
				else if (player.CenterX > (GAME_MAP_YOKO_MAX * mapChip.width) - (GAME_WIDTH / 2))
				{
					if ((GAME_MAP_YOKO_MAX) * mapChip.width - GAME_WIDTH - mapChip.width <= map[player.Part][tate][yoko].x &&
						map[player.Part][tate][yoko].x <= (GAME_MAP_YOKO_MAX + 1) * mapChip.width &&
						0 <= map[player.Part][tate][yoko].y &&
						map[player.Part][tate][yoko].y < GAME_HEIGHT + mapChip.height)
					{
						if (map[player.Part][tate][yoko].kind != b || (map[player.Part][tate][yoko].kind == b && TenmetsuTime % GAME_TENMETSU_SPAN != 0))
						DrawGraph(
							map[player.Part][tate][yoko].x - (GAME_MAP_YOKO_MAX * mapChip.width - GAME_WIDTH),
							map[player.Part][tate][yoko].y,
							mapChip.handle[map[player.Part][tate][yoko].kind],
							TRUE);

						for (int i = 0; i < (int)itemSpeed.size(); i++)
							if (itemSpeed[i].view && itemSpeed[i].Part == player.Part)
							DrawGraph(
								itemSpeed[i].image.x - (GAME_MAP_YOKO_MAX * mapChip.width - GAME_WIDTH),
								itemSpeed[i].image.y,
								itemSpeed[i].image.handle,
								TRUE);
						for (int i = 0; i < (int)itemMuteki.size(); i++)
							if (itemMuteki[i].view && itemMuteki[i].Part == player.Part)
								DrawGraph(
									itemMuteki[i].image.x - (GAME_MAP_YOKO_MAX * mapChip.width - GAME_WIDTH),
									itemMuteki[i].image.y,
									itemMuteki[i].image.handle,
									TRUE);
						for (int i = 0; i < (int)itemStop.size(); i++)
							if (itemStop[i].view && itemStop[i].Part == player.Part)
								DrawGraph(
									itemStop[i].image.x - (GAME_MAP_YOKO_MAX * mapChip.width - GAME_WIDTH),
									itemStop[i].image.y,
									itemStop[i].image.handle,
									TRUE);

						for (int i = 0; i < (int)Speed.Plog.size(); i++)
						{
							CHARA work = Speed.Plog.front();
							Speed.Plog.pop();
							Speed.Plog.push(work);
							if (work.Part == player.Part)
								DrawRotaGraph(work.image.x - (GAME_MAP_YOKO_MAX * mapChip.width - GAME_WIDTH) + work.image.width / 2,
									work.image.y + work.image.height / 2,
									1.0,
									work.Muki / 18 * M_PI,
									work.image.handle, TRUE);
						}
						if (!Speed.Plog.empty())Speed.Plog.pop();

						DrawRotaGraph(player.image.x - (GAME_MAP_YOKO_MAX * mapChip.width - GAME_WIDTH) + player.image.width / 2, player.image.y + player.image.height / 2, 1.0, player.Muki / 18 * M_PI, player.image.handle, TRUE);

						if (Muteki.Use)
						{
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
							DrawBox(player.image.x - (GAME_MAP_YOKO_MAX * mapChip.width - GAME_WIDTH) - player.image.width / 2,
								player.image.y,
								player.image.x - (GAME_MAP_YOKO_MAX * mapChip.width - GAME_WIDTH) + player.image.width + player.image.width / 2,
								player.image.y + player.image.height,
								GetColor(200, 200, 255),
								TRUE);
							SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
						}
					}
				}
				else
				{
				if (map[player.Part][tate][yoko].kind != b || (map[player.Part][tate][yoko].kind == b && TenmetsuTime % GAME_TENMETSU_SPAN != 0))
					DrawGraph(
						map[player.Part][tate][yoko].x,
						map[player.Part][tate][yoko].y,
						mapChip.handle[map[player.Part][tate][yoko].kind],
						TRUE);

					for (int i = 0; i < (int)itemSpeed.size(); i++)
						if (itemSpeed[i].view && itemSpeed[i].Part == player.Part)
							DrawGraph(
								itemSpeed[i].image.x,
								itemSpeed[i].image.y,
								itemSpeed[i].image.handle,
								TRUE);
					for (int i = 0; i < (int)itemMuteki.size(); i++)
						if (itemMuteki[i].view && itemMuteki[i].Part == player.Part)
							DrawGraph(
								itemMuteki[i].image.x,
								itemMuteki[i].image.y,
								itemMuteki[i].image.handle,
								TRUE);
					for (int i = 0; i < (int)itemStop.size(); i++)
						if (itemStop[i].view && itemStop[i].Part == player.Part)
							DrawGraph(
								itemStop[i].image.x,
								itemStop[i].image.y,
								itemStop[i].image.handle,
								TRUE);

					for (int i = 0; i < (int)Speed.Plog.size(); i++)
					{
						CHARA work = Speed.Plog.front();
						Speed.Plog.pop();
						Speed.Plog.push(work);
						if (work.Part == player.Part)
							DrawRotaGraph(work.image.x + work.image.width / 2,
								work.image.y + work.image.height / 2,
								1.0,
								work.Muki / 18 * M_PI,
								work.image.handle, TRUE);
					}
					if (!Speed.Plog.empty())Speed.Plog.pop();

					DrawRotaGraph(player.image.x + player.image.width / 2, player.image.y + player.image.height / 2, 1.0, player.Muki / 18 * M_PI, player.image.handle, TRUE);

					if (Muteki.Use)
					{
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
						DrawBox(player.image.x - player.image.width / 2,
							player.image.y,
							player.image.x + player.image.width + player.image.width / 2,
							player.image.y + player.image.height,
							GetColor(200, 200, 255),
							TRUE);
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					}
				}
			}
		}
	}

	if (Scroll == TATE_SCROLL)
	{
		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
			{

				if (player.CenterY > (GAME_HEIGHT / 2) && player.CenterY <= (GAME_MAP_TATE_MAX * mapChip.height) - (GAME_HEIGHT / 2))
				{
					if (player.CenterY - (GAME_HEIGHT / 2) - mapChip.height <= map[player.Part][tate][yoko].y &&
						map[player.Part][tate][yoko].y <= player.CenterY + (GAME_HEIGHT / 2) &&
						0 <= map[player.Part][tate][yoko].x &&
						map[player.Part][tate][yoko].x < GAME_WIDTH + mapChip.width)
					{
						DrawGraph(
							map[player.Part][tate][yoko].x,
							map[player.Part][tate][yoko].y - (player.CenterY - (GAME_HEIGHT / 2)),
							mapChip.handle[map[player.Part][tate][yoko].kind],
							TRUE);

						for (int i = 0; i < (int)itemSpeed.size(); i++)
							if (itemSpeed[i].view && itemSpeed[i].Part == player.Part)
							DrawGraph(
								itemSpeed[i].image.x,
								itemSpeed[i].image.y - (player.CenterY - (GAME_HEIGHT / 2)),
								itemSpeed[i].image.handle,
								TRUE);
						for (int i = 0; i < (int)itemMuteki.size(); i++)
							if (itemMuteki[i].view && itemMuteki[i].Part == player.Part)
								DrawGraph(
									itemMuteki[i].image.x,
									itemMuteki[i].image.y - (player.CenterY - (GAME_HEIGHT / 2)),
									itemMuteki[i].image.handle,
									TRUE);
						for (int i = 0; i < (int)itemStop.size(); i++)
							if (itemStop[i].view && itemStop[i].Part == player.Part)
								DrawGraph(
									itemStop[i].image.x,
									itemStop[i].image.y - (player.CenterY - (GAME_HEIGHT / 2)),
									itemStop[i].image.handle,
									TRUE);

						for (int i = 0; i < (int)Speed.Plog.size(); i++)
						{
							CHARA work = Speed.Plog.front();
							Speed.Plog.pop();
							Speed.Plog.push(work);
							if (work.Part == player.Part)
								DrawGraph(work.image.x,
									work.image.y - (player.CenterY - (GAME_HEIGHT / 2)),
									work.image.handle, TRUE);
						}
						if (!Speed.Plog.empty())Speed.Plog.pop();

						DrawGraph(player.image.x, player.image.y - (player.CenterY - (GAME_HEIGHT / 2)), player.image.handle, TRUE);

						if (Muteki.Use)
						{
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
							DrawBox(player.image.x - player.image.width / 2,
								player.image.y - (player.CenterY - (GAME_HEIGHT / 2)),
								player.image.x + player.image.width + player.image.width / 2,
								player.image.y - (player.CenterY - (GAME_HEIGHT / 2)) + player.image.height,
								GetColor(200, 200, 255),
								TRUE);
							SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
						}

						for (int i = 0; i < (int)enemy.size(); i++)
						{
							if (enemy[i].view == TRUE && enemy[i].Part == player.Part) {
								DrawGraph(enemy[i].image.x,
									enemy[i].image.y - (player.CenterY - (GAME_HEIGHT / 2)),
									enemy[i].image.handle, TRUE);
							}
						}
					}
				}
				else if (player.CenterY > (GAME_MAP_TATE_MAX * mapChip.height) - (GAME_HEIGHT / 2))
				{
					if ((GAME_MAP_TATE_MAX) * mapChip.height - GAME_HEIGHT - mapChip.height <= map[player.Part][tate][yoko].y &&
						map[player.Part][tate][yoko].y <= (GAME_MAP_TATE_MAX + 1) * mapChip.height &&
						0 <= map[player.Part][tate][yoko].x &&
						map[player.Part][tate][yoko].x < GAME_WIDTH + mapChip.width)
					{
						DrawGraph(
							map[player.Part][tate][yoko].x,
							map[player.Part][tate][yoko].y - (GAME_MAP_TATE_MAX * mapChip.height - GAME_HEIGHT),
							mapChip.handle[map[player.Part][tate][yoko].kind],
							TRUE);

						for (int i = 0; i < (int)itemSpeed.size(); i++)
							if (itemSpeed[i].view && itemSpeed[i].Part == player.Part)
							DrawGraph(
								itemSpeed[i].image.x,
								itemSpeed[i].image.y - (GAME_MAP_TATE_MAX * mapChip.height - GAME_HEIGHT),
								itemSpeed[i].image.handle,
								TRUE);
						for (int i = 0; i < (int)itemMuteki.size(); i++)
							if (itemMuteki[i].view && itemMuteki[i].Part == player.Part)
								DrawGraph(
									itemMuteki[i].image.x,
									itemMuteki[i].image.y - (GAME_MAP_TATE_MAX * mapChip.height - GAME_HEIGHT),
									itemMuteki[i].image.handle,
									TRUE);
						for (int i = 0; i < (int)itemStop.size(); i++)
							if (itemStop[i].view && itemStop[i].Part == player.Part)
								DrawGraph(
									itemStop[i].image.x,
									itemStop[i].image.y - (GAME_MAP_TATE_MAX * mapChip.height - GAME_HEIGHT),
									itemStop[i].image.handle,
									TRUE);

						for (int i = 0; i < (int)Speed.Plog.size(); i++)
						{
							CHARA work = Speed.Plog.front();
							Speed.Plog.pop();
							Speed.Plog.push(work);
							if (work.Part == player.Part)
								DrawGraph(work.image.x,
									work.image.y - (GAME_MAP_TATE_MAX * mapChip.height - GAME_HEIGHT),
									work.image.handle, TRUE);
						}
						if (!Speed.Plog.empty())Speed.Plog.pop();

						DrawGraph(player.image.x, player.image.y - (GAME_MAP_TATE_MAX * mapChip.height - GAME_HEIGHT), player.image.handle, TRUE);

						if (Muteki.Use)
						{
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
							DrawBox(player.image.x - player.image.width / 2,
								player.image.y - (GAME_MAP_TATE_MAX * mapChip.height - GAME_HEIGHT),
								player.image.x + player.image.width + player.image.width / 2,
								player.image.y - (GAME_MAP_TATE_MAX * mapChip.height - GAME_HEIGHT) + player.image.height,
								GetColor(200, 200, 255),
								TRUE);
							SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
						}

						for (int i = 0; i < (int)enemy.size(); i++)
						{
							if (enemy[i].view == TRUE && enemy[i].Part == player.Part) {
								DrawGraph(enemy[i].image.x,
									enemy[i].image.y - (GAME_MAP_TATE_MAX * mapChip.height - GAME_HEIGHT),
									enemy[i].image.handle,
									TRUE);
							}
						}
					}
				}
				else
				{
					DrawGraph(
						map[player.Part][tate][yoko].x,
						map[player.Part][tate][yoko].y,
						mapChip.handle[map[player.Part][tate][yoko].kind],
						TRUE);

					for (int i = 0; i < (int)itemSpeed.size(); i++)
						if (itemSpeed[i].view && itemSpeed[i].Part == player.Part)
						DrawGraph(
							itemSpeed[i].image.x,
							itemSpeed[i].image.y,
							itemSpeed[i].image.handle,
							TRUE);
					for (int i = 0; i < (int)itemMuteki.size(); i++)
						if (itemMuteki[i].view && itemMuteki[i].Part == player.Part)
							DrawGraph(
								itemMuteki[i].image.x,
								itemMuteki[i].image.y,
								itemMuteki[i].image.handle,
								TRUE);
					for (int i = 0; i < (int)itemStop.size(); i++)
						if (itemStop[i].view && itemStop[i].Part == player.Part)
							DrawGraph(
								itemStop[i].image.x,
								itemStop[i].image.y,
								itemStop[i].image.handle,
								TRUE);

					for (int i = 0; i < (int)Speed.Plog.size(); i++)
					{
						CHARA work = Speed.Plog.front();
						Speed.Plog.pop();
						Speed.Plog.push(work);
						if (work.Part == player.Part)
							DrawGraph(work.image.x,
								work.image.y,
								work.image.handle, TRUE);
					}
					if (!Speed.Plog.empty())Speed.Plog.pop();

					DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

					if (Muteki.Use)
					{
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
						DrawBox(player.image.x - player.image.width / 2,
							player.image.y,
							player.image.x + player.image.width + player.image.width / 2,
							player.image.y + player.image.height,
							GetColor(200, 200, 255),
							TRUE);
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
					}

					for (int i = 0; i < (int)enemy.size(); i++)
					{
						if (enemy[i].view == TRUE && enemy[i].Part == player.Part) {
							DrawGraph(enemy[i].image.x,
								enemy[i].image.y,
								enemy[i].image.handle,
								TRUE);
						}
					}
				}
			}
		}

		for (int i = 0; i < (int)enemy.size(); i++)
		{
			for (int cnt = 0; cnt < (int)enemy[i].tama.size(); cnt++)
			{
				if (player.CenterY > (GAME_HEIGHT / 2) && player.CenterY <= (GAME_MAP_TATE_MAX * mapChip.height) - (GAME_HEIGHT / 2))
				{
					DrawGraph(
						enemy[i].tama[cnt].x,
						enemy[i].tama[cnt].y - (player.CenterY - (GAME_HEIGHT / 2)),
						enemy[i].tama[cnt].handle[enemy[i].tama[cnt].nowImageKind], TRUE);
				}
				else if (player.CenterY > (GAME_MAP_TATE_MAX * mapChip.height) - (GAME_HEIGHT / 2))
				{
					DrawGraph(
						enemy[i].tama[cnt].x,
						enemy[i].tama[cnt].y - (GAME_MAP_TATE_MAX * mapChip.height - GAME_HEIGHT),
						enemy[i].tama[cnt].handle[enemy[i].tama[cnt].nowImageKind], TRUE);
				}
				else
				{
					DrawGraph(
						enemy[i].tama[cnt].x,
						enemy[i].tama[cnt].y,
						enemy[i].tama[cnt].handle[enemy[i].tama[cnt].nowImageKind], TRUE);
				}

				if (enemy[i].tama[cnt].changeImageCnt < enemy[i].tama[cnt].changeImageCntMAX && !Stop.Use)
				{
					enemy[i].tama[cnt].changeImageCnt++;
				}
				else if (!Stop.Use)
				{
					if (enemy[i].tama[cnt].nowImageKind < TAMA_DIV_NUM - 1)
					{
						enemy[i].tama[cnt].nowImageKind++;
					}
					else
					{
						enemy[i].tama[cnt].nowImageKind = 0;
					}

					enemy[i].tama[cnt].changeImageCnt = 0;
				}

				if (enemy[i].tama[cnt].y < 0 || enemy[i].tama[cnt].y > GAME_MAP_TATE_MAX * mapChip.height)
				{
					enemy[i].tama.erase(enemy[i].tama.begin() + cnt);
					cnt--;
				}
				else
				{
					if (!Stop.Use)
					{
						enemy[i].tama[cnt].y += enemy[i].tama[cnt].speedY;
						enemy[i].tama[cnt].coll.top += enemy[i].tama[cnt].speedY;
						enemy[i].tama[cnt].coll.bottom += enemy[i].tama[cnt].speedY;
					}

					if (enemy[i].Part == player.Part && MY_CHECK_RECT_COLL(enemy[i].tama[cnt].coll, player.coll) == TRUE && !Muteki.Use)
					{
						if (CheckSoundMem(BGM.handle) != 0)
						{
							StopSoundMem(BGM.handle);
						}

						SetMouseDispFlag(TRUE);

						GameEndKind = GAME_END_FAIL;

						GameScene = GAME_SCENE_END;

						return;
					}
				}
			}
		}
	}

	for (int i = 0; i < GAME_ITEM_MAX; i++)
	{
		DrawBox(45 + 64 * i, 15, 119 + 64 * i, 89, GetColor(0, 0, 0), TRUE);
		DrawBox(50 + 64 * i, 20, 114 + 64 * i, 84, GetColor(110, 110, 110), TRUE);
		if (player.Item[i])
		{
			if (i == ITEM_SPEED)
				DrawGraph(
					50 + 64 * i,
					20,
					itemSpeedTemp.image.handle,
					TRUE);

			if (i == ITEM_MUTEKI)
				DrawGraph(
					50 + 64 * i,
					20,
					itemMutekiTemp.image.handle,
					TRUE);

			if (i == ITEM_STOP)
				DrawGraph(
					50 + 64 * i,
					20,
					itemStopTemp.image.handle,
					TRUE);
		}
	}

	if (Speed.Use)
	{
		SetFontSize(60);
		DrawFormatString(
			50,
			20,
			GetColor(255, 255, 255),
			"%d",
			GAME_ITEM_USE_TIME - Speed.Cou / GAME_FPS,
			TRUE);
	}

	if (Muteki.Use)
	{
		SetFontSize(60);
		DrawFormatString(
			50 + 64,
			20,
			GetColor(255, 255, 255),
			"%d",
			GAME_ITEM_USE_TIME - Muteki.Cou / GAME_FPS,
			TRUE);
	}

	if (Stop.Use)
	{
		SetFontSize(60);
		DrawFormatString(
			50 + 128,
			20,
			GetColor(255, 255, 255),
			"%d",
			GAME_ITEM_USE_TIME - Stop.Cou / GAME_FPS,
			TRUE);
	}

	if (Stop.Use)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
		DrawBox(0, 0, mapChip.width * GAME_MAP_YOKO_MAX, mapChip.height * GAME_MAP_TATE_MAX, GetColor(200, 200, 200), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	DrawBox(WINDOW_WIDTH - 155, 15, WINDOW_WIDTH - 45, 75, GetColor(0, 0, 0), TRUE);
	DrawBox(WINDOW_WIDTH - 150, 20, WINDOW_WIDTH - 50, 70, GetColor(110, 110, 110), TRUE);
	SetFontSize(48);
	DrawFormatString(WINDOW_WIDTH - 137, 21, GetColor(255, 255, 255), "%d", TimeLim);

	return;
}

VOID MY_END(VOID)
{
	MY_END_PROC();
	MY_END_DRAW();

	return;
}

VOID MY_END_PROC(VOID)
{
	if (MY_KEY_UP(KEY_INPUT_RETURN) == TRUE)
	{
		if (CheckSoundMem(BGM_COMP.handle) != 0)
		{
			StopSoundMem(BGM_COMP.handle);
		}

		if (CheckSoundMem(BGM_FAIL.handle) != 0)
		{
			StopSoundMem(BGM_FAIL.handle);
		}

		SetMouseDispFlag(TRUE);

		GameScene = GAME_SCENE_START;

		enemy.clear();

		return;
	}

	switch (GameEndKind)
	{
	case GAME_END_COMP:

		if (CheckSoundMem(BGM_COMP.handle) == 0)
		{
			ChangeVolumeSoundMem(255 * 50 / 100, BGM_COMP.handle);
			PlaySoundMem(BGM_COMP.handle, DX_PLAYTYPE_LOOP);
		}

		if (ImageEndCOMP.Cnt < ImageEndCOMP.CntMAX)
		{
			ImageEndCOMP.Cnt += IMAGE_END_COMP_CNT;
		}
		else
		{
			if (ImageEndCOMP.IsDraw == FALSE)
			{
				ImageEndCOMP.IsDraw = TRUE;
			}
			ImageEndCOMP.Cnt = 0;
		}
		break;

	case GAME_END_FAIL:

		if (CheckSoundMem(BGM_FAIL.handle) == 0)
		{
			ChangeVolumeSoundMem(255 * 50 / 100, BGM_FAIL.handle);

			PlaySoundMem(BGM_FAIL.handle, DX_PLAYTYPE_LOOP);
		}

		if (ImageEndFAIL.Cnt < ImageEndFAIL.CntMAX)
		{
			ImageEndFAIL.Cnt += IMAGE_END_FAIL_CNT;
		}
		else
		{
			if (ImageEndFAIL.IsDraw == FALSE)
			{
				ImageEndFAIL.IsDraw = TRUE;
			}
			ImageEndFAIL.Cnt = 0;
		}
		break;
	}

	return;
}

VOID MY_END_DRAW(VOID)
{
	DrawGraph(ImageBack_END.x, ImageBack_END.y, ImageBack_END.handle, TRUE);

	MY_PLAY_DRAW();

	switch (GameEndKind)
	{
	case GAME_END_COMP:
		if (ImageEndCOMP.IsDraw == TRUE)
		{
			DrawGraph(ImageEndCOMP.image.x, ImageEndCOMP.image.y, ImageEndCOMP.image.handle, TRUE);
		}
		break;

	case GAME_END_FAIL:
		if (ImageEndFAIL.IsDraw == TRUE)
		{
			DrawGraph(ImageEndFAIL.image.x, ImageEndFAIL.image.y, ImageEndFAIL.image.handle, TRUE);
		}
		break;

	}

	return;
}

BOOL MY_LOAD_IMAGE(VOID)
{
	strcpy_s(ImageTitleBK.path, IMAGE_TITLE_BK_PATH);
	ImageTitleBK.handle = LoadGraph(ImageTitleBK.path);
	if (ImageTitleBK.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleBK.handle, &ImageTitleBK.width, &ImageTitleBK.height);
	ImageTitleBK.x = WINDOW_WIDTH / 2 - ImageTitleBK.width / 2;
	ImageTitleBK.y = WINDOW_HEIGHT / 2 - ImageTitleBK.height / 2;

	strcpy_s(ImageTitleROGO.image.path, IMAGE_TITLE_ROGO_PATH);
	ImageTitleROGO.image.handle = LoadGraph(ImageTitleROGO.image.path);
	if (ImageTitleROGO.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}
	GetGraphSize(ImageTitleROGO.image.handle, &ImageTitleROGO.image.width, &ImageTitleROGO.image.height);
	ImageTitleROGO.image.x = WINDOW_WIDTH - ImageTitleROGO.image.width;
	ImageTitleROGO.image.y = GAME_HEIGHT / 4;
	ImageTitleROGO.angle = DX_PI * 2;
	ImageTitleROGO.angleMAX = DX_PI * 2;
	ImageTitleROGO.rate = 0.0;
	ImageTitleROGO.rateMAX = IMAGE_TITLE_ROGO_ROTA_MAX;

	strcpy_s(ImageTitleButtonPlay.path, IMAGE_TITLE_BUTTON_PLAY_PATH);
	ImageTitleButtonPlay.handle = LoadGraph(ImageTitleButtonPlay.path);
	if (ImageTitleButtonPlay.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BUTTON_PLAY_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}
	GetGraphSize(ImageTitleButtonPlay.handle, &ImageTitleButtonPlay.width, &ImageTitleButtonPlay.height);
	ImageTitleButtonPlay.x = WINDOW_WIDTH / 2 - ImageTitleButtonPlay.width / 2;
	ImageTitleButtonPlay.y = ImageTitleROGO.image.y + ImageTitleROGO.image.height / 2 + IMAGE_TITLE_BUTTON_SPAN;

	strcpy_s(ImageTitleButtonRule.path, IMAGE_TITLE_BUTTON_RULE_PATH);
	ImageTitleButtonRule.handle = LoadGraph(ImageTitleButtonRule.path);
	if (ImageTitleButtonRule.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BUTTON_RULE_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}
	GetGraphSize(ImageTitleButtonRule.handle, &ImageTitleButtonRule.width, &ImageTitleButtonRule.height);
	ImageTitleButtonRule.x = WINDOW_WIDTH / 2 - ImageTitleButtonRule.width / 2;
	ImageTitleButtonRule.y = ImageTitleButtonPlay.y + ImageTitleButtonPlay.height + IMAGE_TITLE_BUTTON_SPAN;

	strcpy_s(ImageTitleButtonEnd.path, IMAGE_TITLE_BUTTON_END_PATH);
	ImageTitleButtonEnd.handle = LoadGraph(ImageTitleButtonEnd.path);
	if (ImageTitleButtonEnd.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BUTTON_END_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}
	GetGraphSize(ImageTitleButtonEnd.handle, &ImageTitleButtonEnd.width, &ImageTitleButtonEnd.height);
	ImageTitleButtonEnd.x = WINDOW_WIDTH / 2 - ImageTitleButtonEnd.width / 2;
	ImageTitleButtonEnd.y = ImageTitleButtonRule.y + ImageTitleButtonRule.height + IMAGE_TITLE_BUTTON_SPAN;

	strcpy_s(ImageTitleButtonNow.path, IMAGE_TITLE_BUTTON_NOW_PATH);
	ImageTitleButtonNow.handle = LoadGraph(ImageTitleButtonNow.path);
	if (ImageTitleButtonNow.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BUTTON_NOW_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}
	GetGraphSize(ImageTitleButtonNow.handle, &ImageTitleButtonNow.width, &ImageTitleButtonNow.height);
	ImageTitleButtonNow.x = WINDOW_WIDTH / 2 - ImageTitleButtonNow.width / 2;
	ImageTitleButtonNow.y = ImageTitleButtonPlay.y;

	strcpy_s(Image_RULE.path, IMAGE_RULE_PATH);
	Image_RULE.handle = LoadGraph(Image_RULE.path);
	if (Image_RULE.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_RULE_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}
	GetGraphSize(Image_RULE.handle, &Image_RULE.width, &Image_RULE.height);
	Image_RULE.x = WINDOW_WIDTH / 2 - Image_RULE.width / 2;
	Image_RULE.y = 0;

	strcpy_s(ImageBack[0].image.path, IMAGE_BACK_PATH);
	strcpy_s(ImageBack[1].image.path, IMAGE_BACK_REV_PATH);
	strcpy_s(ImageBack[2].image.path, IMAGE_BACK_PATH);
	strcpy_s(ImageBack[3].image.path, IMAGE_BACK_REV_PATH);

	strcpy_s(ImageEndCOMP.image.path, IMAGE_END_COMP_PATH);
	ImageEndCOMP.image.handle = LoadGraph(ImageEndCOMP.image.path);
	if (ImageEndCOMP.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_END_COMP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}
	GetGraphSize(ImageEndCOMP.image.handle, &ImageEndCOMP.image.width, &ImageEndCOMP.image.height);
	ImageEndCOMP.image.x = WINDOW_WIDTH / 2 - ImageEndCOMP.image.width / 2;

	ImageEndCOMP.image.y = WINDOW_HEIGHT / 2 - ImageEndCOMP.image.height / 2;
	ImageEndCOMP.Cnt = 0.0;
	ImageEndCOMP.CntMAX = IMAGE_END_COMP_CNT_MAX;
	ImageEndCOMP.IsDraw = FALSE;

	strcpy_s(ImageEndFAIL.image.path, IMAGE_END_FAIL_PATH);
	ImageEndFAIL.image.handle = LoadGraph(ImageEndFAIL.image.path);
	if (ImageEndFAIL.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_END_FAIL_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}
	GetGraphSize(ImageEndFAIL.image.handle, &ImageEndFAIL.image.width, &ImageEndFAIL.image.height);
	ImageEndFAIL.image.x = WINDOW_WIDTH / 2 - ImageEndFAIL.image.width / 2;
	ImageEndFAIL.image.y = WINDOW_HEIGHT / 2 - ImageEndFAIL.image.height / 2;
	ImageEndFAIL.Cnt = 0.0;
	ImageEndFAIL.CntMAX = IMAGE_END_FAIL_CNT_MAX;
	ImageEndFAIL.IsDraw = FALSE;

	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{
		ImageBack[num].image.handle = LoadGraph(ImageBack[num].image.path);
		if (ImageBack[num].image.handle == -1)
		{
			MessageBox(GetMainWindowHandle(), IMAGE_BACK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
			return(FALSE);
		}
		GetGraphSize(ImageBack[num].image.handle, &ImageBack[num].image.width, &ImageBack[num].image.height);
	}
	ImageBack[0].image.x = GAME_WIDTH / 2 - ImageBack[0].image.width / 2;
	ImageBack[0].image.y = 0 - ImageBack[0].image.height * 0;
	ImageBack[0].IsDraw = FALSE;

	ImageBack[1].image.x = GAME_WIDTH / 2 - ImageBack[1].image.width / 2;
	ImageBack[1].image.y = 0 - ImageBack[0].image.height * 1;
	ImageBack[1].IsDraw = FALSE;

	ImageBack[2].image.x = GAME_WIDTH / 2 - ImageBack[2].image.width / 2;
	ImageBack[2].image.y = 0 - ImageBack[0].image.height * 2;
	ImageBack[2].IsDraw = FALSE;

	ImageBack[3].image.x = GAME_WIDTH / 2 - ImageBack[2].image.width / 2;
	ImageBack[3].image.y = 0 - ImageBack[0].image.height * 3;
	ImageBack[3].IsDraw = FALSE;

	strcpy_s(ImageBack_END.path, IMAGE_BACK_PATH_END);
	ImageBack_END.handle = LoadGraph(ImageBack_END.path);
	if (ImageBack_END.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_BACK_PATH_END, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}
	GetGraphSize(ImageBack_END.handle, &ImageBack_END.width, &ImageBack_END.height);
	ImageBack_END.x = GAME_WIDTH / 2 - ImageBack_END.width / 2;
	ImageBack_END.y = GAME_HEIGHT / 2 - ImageBack_END.height / 2;


	strcpy_s(player.image.path, IMAGE_PLAYER_PATH_YOKO);
	player.image.handle = LoadGraph(player.image.path);
	if (player.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH_YOKO, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}
	GetGraphSize(player.image.handle, &player.image.width, &player.image.height);
	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;
	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;
	player.CenterX = player.image.x + player.image.width / 2;
	player.CenterY = player.image.y + player.image.height / 2;
	player.speed = CHARA_SPEED_HIGH;

	strcpy_s(PlayerRed.path, IMAGE_PLAYER_PATH_RED);
	PlayerRed.handle = LoadGraph(PlayerRed.path);
	if (PlayerRed.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH_RED, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}
	GetGraphSize(PlayerRed.handle, &PlayerRed.width, &PlayerRed.height);

	strcpy_s(enemyTemp.image.path, IMAGE_ENEMY_PATH);
	enemyTemp.image.handle = LoadGraph(enemyTemp.image.path);
	if (enemyTemp.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_ENEMY_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}
	GetGraphSize(enemyTemp.image.handle, &enemyTemp.image.width, &enemyTemp.image.height);
	enemyTemp.image.x = GAME_WIDTH / 2 - enemyTemp.image.width / 2;
	enemyTemp.image.y = GAME_HEIGHT / 2 - enemyTemp.image.height / 2;
	enemyTemp.CenterX = enemyTemp.image.x + enemyTemp.image.width / 2;
	enemyTemp.CenterY = enemyTemp.image.y + enemyTemp.image.height / 2;
	enemyTemp.speed = CHARA_SPEED_LOW;

	strcpy_s(itemSpeedTemp.image.path, IMAGE_ITEM_SPEED_PATH);
	itemSpeedTemp.image.handle = LoadGraph(itemSpeedTemp.image.path);
	if (itemSpeedTemp.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_ENEMY_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}
	GetGraphSize(itemSpeedTemp.image.handle, &itemSpeedTemp.image.width, &itemSpeedTemp.image.height);

	strcpy_s(itemMutekiTemp.image.path, IMAGE_ITEM_MUTEKI_PATH);
	itemMutekiTemp.image.handle = LoadGraph(itemMutekiTemp.image.path);
	if (itemMutekiTemp.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_ENEMY_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}
	GetGraphSize(itemMutekiTemp.image.handle, &itemMutekiTemp.image.width, &itemMutekiTemp.image.height);

	strcpy_s(itemStopTemp.image.path, IMAGE_ITEM_STOP_PATH);
	itemStopTemp.image.handle = LoadGraph(itemStopTemp.image.path);
	if (itemStopTemp.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_ENEMY_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}
	GetGraphSize(itemStopTemp.image.handle, &itemStopTemp.image.width, &itemStopTemp.image.height);

	int tamaRedRes = LoadDivGraph(TAMA_RED_PATH, TAMA_DIV_NUM, TAMA_DIV_TATE, TAMA_DIV_YOKO, TAMA_DIV_WIDTH, TAMA_DIV_HEIGHT,	&tamaTemp.handle[0]);

	if (tamaRedRes == -1)
	{
		MessageBox(GetMainWindowHandle(), TAMA_RED_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}

	GetGraphSize(tamaTemp.handle[0], &tamaTemp.width, &tamaTemp.height);
	strcpyDx(tamaTemp.path, TEXT(TAMA_RED_PATH));

	tamaTemp.width = tamaTemp.width;
	tamaTemp.height = tamaTemp.height;
	tamaTemp.x = enemyTemp.CenterX - tamaTemp.width / 2;
	tamaTemp.y = enemyTemp.image.y;
	tamaTemp.changeImageCnt = 0;
	tamaTemp.changeImageCntMAX = TAMA_CHANGE_MAX;
	tamaTemp.nowImageKind = 0;

	tamaTemp.speedY = CHARA_SPEED_HIGH;

	int mapRes = LoadDivGraph(
		GAME_MAP_PATH,
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,
		&mapChip.handle[0]);

	if (mapRes == -1)
	{
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}

	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	for (int kai = 0; kai < GAME_MAP_PART_MAX; kai++)
	{
		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
			{
				mapDataInit[kai][tate][yoko] = mapData[kai][tate][yoko];

				map[kai][tate][yoko].kind = mapData[kai][tate][yoko];

				map[kai][tate][yoko].width = mapChip.width;
				map[kai][tate][yoko].height = mapChip.height;

				map[kai][tate][yoko].x = yoko * map[kai][tate][yoko].width;
				map[kai][tate][yoko].y = tate * map[kai][tate][yoko].height;
			}
		}
	}

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}

	return(TRUE);
}

VOID MY_DELETE_IMAGE(VOID)
{
	for (int num = 0; num < IMAGE_BACK_NUM; num++)
	{
		DeleteGraph(ImageBack[0].image.handle);
	}

	DeleteGraph(ImageBack_END.handle);
	DeleteGraph(player.image.handle);

	DeleteGraph(PlayerRed.handle);

	DeleteGraph(enemyTemp.image.handle);
	for (int i = 0; i < (int)enemy.size(); i++)DeleteGraph(enemy[i].image.handle);

	DeleteGraph(ImageTitleBK.handle);
	DeleteGraph(ImageTitleROGO.image.handle);
	DeleteGraph(ImageTitleButtonPlay.handle);
	DeleteGraph(ImageTitleButtonRule.handle);
	DeleteGraph(ImageTitleButtonEnd.handle);
	DeleteGraph(ImageTitleButtonNow.handle);

	DeleteGraph(ImageEndCOMP.image.handle);
	DeleteGraph(ImageEndFAIL.image.handle);

	DeleteGraph(itemSpeedTemp.image.handle);
	DeleteGraph(itemMutekiTemp.image.handle);
	DeleteGraph(itemStopTemp.image.handle);

	for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++) { DeleteGraph(tamaTemp.handle[i_num]); }

	for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++) { DeleteGraph(mapChip.handle[i_num]); }

	return;
}

BOOL MY_LOAD_MUSIC(VOID)
{
	strcpy_s(BGM.path, MUSIC_BGM_PATH);
	BGM.handle = LoadSoundMem(BGM.path);
	if (BGM.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}

	strcpy_s(BGM_TITLE.path, MUSIC_BGM_PATH_TITLE);
	BGM_TITLE.handle = LoadSoundMem(BGM_TITLE.path);
	if (BGM_TITLE.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_PATH_TITLE, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}

	strcpy_s(BGM_COMP.path, MUSIC_BGM_COMP_PATH);
	BGM_COMP.handle = LoadSoundMem(BGM_COMP.path);
	if (BGM_COMP.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_COMP_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}

	strcpy_s(BGM_FAIL.path, MUSIC_BGM_FAIL_PATH);
	BGM_FAIL.handle = LoadSoundMem(BGM_FAIL.path);
	if (BGM_FAIL.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_FAIL_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}

	return TRUE;
}

VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(BGM.handle);
	DeleteSoundMem(BGM_TITLE.handle);
	DeleteSoundMem(BGM_COMP.handle);
	DeleteSoundMem(BGM_FAIL.handle);

	return;
}

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT player_rect)
{
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			if (MY_CHECK_RECT_COLL(player_rect, mapColl[tate][yoko]) == TRUE)
			{
				if (map[player.Part][tate][yoko].kind == k) { return(TRUE); }
			}
		}
	}

	return(FALSE);
}

BOOL MY_CHECK_RECT_COLL(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top
		)
	{
		return(TRUE);
	}

	return(FALSE);
}
