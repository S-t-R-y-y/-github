#include "DxLib.h"
#include "resource.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600
#define GAME_WIDTH	800
#define GAME_HEIGHT	600
#define GAME_COLOR	32

#define GAME_WINDOW_BAR	0
#define GAME_WINDOW_NAME	"CrossRoads"

#define GAME_FPS		60

#define MOUSE_BUTTON_CODE	129

#define PATH_MAX			255
#define NAME_MAX			255

#define FONT_PATH_MAX			255

#define FONT_TANU_PATH			TEXT(".\\font\\851CHIKARA-DZUYOKU_kanaB_004.ttf")
#define FONT_TANU_NAME			TEXT("851チカラヅヨク-かなB")

#define FONT_PARCHM_PATH			TEXT(".\\font\\PARCHM.ttf")
#define FONT_PARCHM_NAME			TEXT("Parchment")

#define FONT_INSTALL_ERR_TITLE	TEXT("フォントインストールエラー")
#define FONT_CREATE_ERR_TITLE	TEXT("フォント作成エラー")

#define MRK_SIZE_WIDTH 32
#define MRK_SIZE_WIDTH 28
#define GN_SIZE_WIDTH 130
#define GN_SIZE_HEIGHT 100

#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")

#define IMAGE_TITLE_BK_PATH			TEXT(".\\IMAGE\\doukutsu.png")
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

#define IMAGE_BACK_PATH			TEXT(".\\IMAGE\\iseki1.png")
#define IMAGE_BACK_REV_PATH		TEXT(".\\IMAGE\\iseki2.png")
#define IMAGE_BACK_NUM			4

#define IMAGE_BACK_PATH_END		TEXT(".\\IMAGE\\titlelogo.png")
#define IMAGE_PLAYER_PATH		TEXT(".\\IMAGE\\player.png")

#define IMAGE_ENEMY_PATH		TEXT(".\\IMAGE\\enemy.png")

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
#define TAMA_MAX			16

#define TAMA_RED_PATH			TEXT(".\\IMAGE\\TAMA\\red.png")
#define TAMA_GREEN_PATH			TEXT(".\\IMAGE\\TAMA\\green.png")
#define TAMA_BLUE_PATH			TEXT(".\\IMAGE\\TAMA\\blue.png")
#define TAMA_YELLOW_PATH		TEXT(".\\IMAGE\\TAMA\\yellow.png")

#define TAMA_DIV_WIDTH		16
#define TAMA_DIV_HEIGHT		16

#define TAMA_DIV_TATE		3
#define TAMA_DIV_YOKO		1

#define TAMA_DIV_NUM	TAMA_DIV_TATE * TAMA_DIV_YOKO

#define ENEMY_MAX			15

#define GAME_MAP_TATE_MAX	9
#define GAME_MAP_YOKO_MAX	13
#define GAME_MAP_KIND_MAX	2
#define GAME_MAP_KAISO_MAX	2
#define GAME_MAP_WARP_MAX	10

#define GAME_TIME_LIMIT		40

#define GAME_MAP_PATH			TEXT(".\\IMAGE\\MAP\\my_map.png")

#define GAME_PLAYER_HP_MAX	100
#define GAME_ENEMY_DAMAGE	15

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

enum GAME_MAP_KIND
{
	n = -1,		//無
	k = 10,		//壁
	t = 12,		//通路
	s = 5,		//スタート
	g = 11,		//ゴール
	e = 13,		//敵
	i = 1,		//階層移動
	o = 2		//階層移動先
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
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGH = 3
};

enum CHARA_RELOAD {
	CHARA_RELOAD_LOW = 60,
	CHARA_RELOAD_MIDI = 30,
	CHARA_RELOAD_HIGH = 15
};

typedef struct STRUCT_I_POINT
{
	int x = -1;
	int y = -1;
	int kaiso = -1;
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
	BOOL IsDraw;
	int nowImageKind;
	int changeImageCnt;
	int changeImageCntMAX;
	int speedX;
	int speedY;
	RECT coll;
}TAMA;

typedef struct STRUCT_CHARA
{
	IMAGE image;
	int speed;
	int CenterX;
	int CenterY;

	int Kaiso;
	int Muki;		//0：上　1：右　2：下　3：左

	MUSIC musicShot[MUSIC_PLAYER_SHOT_MAX];
	int SeCou = 0;

	BOOL CanShot;
	int ShotReLoadCnt;
	int ShotReLoadCntMAX;

	TAMA tama[TAMA_MAX];

	RECT coll;
}CHARA;

typedef struct STRUCT_ENEMY
{
	MUSIC die;
	IMAGE image;
	int speed;
	int CenterX;
	int CenterY;
	int Kaiso;
	int MoveAdd;

	bool view;

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

int GraHandle;
int Gra2Handle;
int Gra3Handle;
int GraX;
int GraY;

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

int GameEndKind;
RECT GoalRect = { -1,-1, -1, -1 };

IMAGE Image_RULE;

IMAGE ImageBack_END;
CHARA player;
int playerHP;

iPOINT FromWarp[GAME_MAP_WARP_MAX];
int FromWarpCou = 0;
iPOINT ToWarp[GAME_MAP_WARP_MAX];
int ToWarpCou = 0;

ENEMY enemy[ENEMY_MAX];
iPOINT enemyPt[ENEMY_MAX] = { { -1,-1 } };
int enemyCnt = 0;

IMAGE_BACK ImageBack[IMAGE_BACK_NUM];

IMAGE ImageTitleBK;

IMAGE ImageTitleButtonPlay;
IMAGE ImageTitleButtonRule;
IMAGE ImageTitleButtonEnd;
IMAGE ImageTitleButtonNow;
int NowChoice = 0;

int GoalKaiso;

IMAGE_ROTA ImageTitleROGO;

IMAGE_BLINK ImageEndCOMP;
IMAGE_BLINK ImageEndFAIL;

MUSIC BGM;
MUSIC BGM_TITLE;
MUSIC BGM_COMP;
MUSIC BGM_FAIL;

GAME_MAP_KIND mapData[GAME_MAP_KAISO_MAX][GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX] =
{
	{
		k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,k,t,e,t,t,t,t,t,t,k,
		k,t,t,k,t,k,g,k,t,k,t,e,k,
		k,t,t,e,t,k,e,t,t,k,o,t,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,e,t,t,t,t,t,t,o,t,t,t,k,
		k,k,k,k,k,t,k,t,k,t,k,t,k,
		k,e,t,o,t,i,t,t,t,t,t,t,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,
	},
	{
		k,k,k,k,k,k,k,k,k,k,k,k,k,
		k,t,t,t,t,e,t,e,t,t,t,i,k,
		k,e,t,t,t,k,t,k,k,k,k,k,k,
		k,t,t,t,t,t,e,t,t,t,t,t,k,
		k,k,k,k,k,k,k,k,k,k,t,k,k,
		k,e,t,t,t,o,t,t,t,t,t,e,k,
		k,o,k,k,k,t,k,k,k,t,k,t,k,
		k,e,t,t,t,t,s,t,t,t,t,o,k,
		k,k,k,k,k,k,k,k,k,k,k,k,k,
	}
};


GAME_MAP_KIND mapDataInit[GAME_MAP_KAISO_MAX][GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

MAPCHIP mapChip;

MAP map[GAME_MAP_KAISO_MAX][GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

iPOINT startPt{ -1, -1, -1};

RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

VOID MY_FPS_UPDATE(VOID);
VOID MY_FPS_DRAW(VOID);
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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);	
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_COLOR);
	SetWindowStyleMode(GAME_WINDOW_BAR);
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));

	SetWindowIconID(IDI_ICON1);

	if (DxLib_Init() == -1) { return -1; }

	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	player.CanShot = TRUE;
	player.ShotReLoadCnt = 0;
	player.ShotReLoadCntMAX = CHARA_RELOAD_LOW;

	SetMouseDispFlag(TRUE);

	GraHandle = LoadGraph(TEXT("./GN.png"));
	Gra2Handle = LoadGraph(TEXT("./GN_END.png"));
	Gra3Handle = LoadGraph(TEXT("./MRK.png"));
	GNSound = LoadSoundMem(TEXT("./GN.wav"));

	DDNSound = LoadSoundMem(TEXT("./ddn.wav"));

	BGHandle1 = LoadGraph(TEXT("./01.png"));
	BGHandle2 = LoadGraph(TEXT("./02.png"));
	BGHandle3 = LoadGraph(TEXT("./03.png"));

	GameScene = GAME_SCENE_START;

	SetDrawScreen(DX_SCREEN_BACK);

	for (int kai = 0; kai < GAME_MAP_KAISO_MAX; kai++)
	{
		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
			{
				if (mapData[kai][tate][yoko] == s)
				{
					startPt.x = mapChip.width * yoko + mapChip.width / 2;
					startPt.y = mapChip.height * tate + mapChip.height / 2;
					startPt.kaiso = kai;
				}

				if (mapData[kai][tate][yoko] == g)
				{
					GoalRect.left = mapChip.width * yoko;
					GoalRect.top = mapChip.height * tate;
					GoalRect.right = mapChip.width * (yoko + 1);
					GoalRect.bottom = mapChip.height * (tate + 1);

					GoalKaiso = kai;
				}

				if (mapData[kai][tate][yoko] == e && enemyCnt < ENEMY_MAX)
				{
					enemyPt[enemyCnt].x = mapChip.width * yoko + mapChip.width / 2;
					enemyPt[enemyCnt].y = mapChip.height * tate + mapChip.height / 2;
					enemyPt[enemyCnt].kaiso = kai;
					enemy[enemyCnt].view = TRUE;
					enemyCnt++;
				}

				if (mapData[kai][tate][yoko] == i && FromWarpCou < GAME_MAP_WARP_MAX)
				{
					FromWarp[FromWarpCou].x = mapChip.width * yoko;
					FromWarp[FromWarpCou].y = mapChip.height * tate;
					FromWarp[FromWarpCou].kaiso = kai;
					FromWarpCou++;
				}

				if (mapData[kai][tate][yoko] == o && ToWarpCou < GAME_MAP_WARP_MAX)
				{
					ToWarp[ToWarpCou].x = mapChip.width * yoko + mapChip.width / 2;
					ToWarp[ToWarpCou].y = mapChip.height * tate + mapChip.height / 2;
					ToWarp[ToWarpCou].kaiso = kai;
					ToWarpCou++;
				}
			}
		}
	}

	if (startPt.x == -1 || startPt.y == -1 || startPt.kaiso == -1)
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

	DrawGraph(GraX, GraY + 10, Gra2Handle, TRUE);
	ScreenFlip();

	DeleteGraph(GraHandle);
	DeleteGraph(Gra2Handle);
	DeleteGraph(Gra3Handle);
	DeleteSoundMem(GNSound);

	DeleteSoundMem(DDNSound);;

	MY_DELETE_IMAGE();

	MY_DELETE_MUSIC();

	DxLib_End();

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

	return;
}


VOID MY_FPS_DRAW(VOID)
{
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
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

		player.CenterX = startPt.x;
		player.CenterY = startPt.y;
		player.Kaiso = startPt.kaiso;

		playerHP = GAME_PLAYER_HP_MAX;

		player.image.x = player.CenterX;
		player.image.y = player.CenterY;

		player.Muki = 0;

		player.SeCou = 0;

		for (int cnt = 0; cnt < TAMA_MAX; cnt++)player.tama[cnt].IsDraw = FALSE;

		SetMousePoint(player.image.x, player.image.y);

		for (int i = 0; i < enemyCnt; i++) 
		{
			enemy[i].MoveAdd = GetRand(2) - 1;

			enemy[i].view = TRUE;

			enemy[i].CenterX = enemyPt[i].x;
			enemy[i].CenterY = enemyPt[i].y;

			enemy[i].image.x = enemy[i].CenterX;
			enemy[i].image.y = enemy[i].CenterY;

			enemy[i].Kaiso = enemyPt[i].kaiso;
		}

		TimeLim = 0;
		TimeCou = 0;

		for (int kai = 0; kai < GAME_MAP_KAISO_MAX; kai++)
		{
			ImageBack[kai].image.x = GAME_WIDTH / 2 - ImageBack[kai].image.width / 2;
			ImageBack[kai].image.y = GAME_HEIGHT / 2 - ImageBack[kai].image.height / 2;
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

	//DrawString(0, 0, "スタート画面(エンターキーを押して下さい)", GetColor(255, 255, 255));
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

	//DrawString(0, 0, "スタート画面(エンターキーを押して下さい)", GetColor(255, 255, 255));
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

	if (MY_KEY_DOWN(KEY_INPUT_UP) || MY_KEY_DOWN(KEY_INPUT_W)) 
	{
		player.CenterY -= CHARA_SPEED_MIDI;
		player.coll.left = player.CenterX - mapChip.width / 2 + 5;
		player.coll.top = player.CenterY - mapChip.height / 2 + 5;
		player.coll.right = player.CenterX + mapChip.width / 2 - 5;
		player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;
		player.Muki = 0;
		if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
		{
			player.CenterY += CHARA_SPEED_MIDI;
		}
	}
	if (MY_KEY_DOWN(KEY_INPUT_DOWN) || MY_KEY_DOWN(KEY_INPUT_S)) 
	{
		player.CenterY += CHARA_SPEED_MIDI;
		player.coll.left = player.CenterX - mapChip.width / 2 + 5;
		player.coll.top = player.CenterY - mapChip.height / 2 + 5;
		player.coll.right = player.CenterX + mapChip.width / 2 - 5;
		player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;
		player.Muki = 2;
		if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
		{
			player.CenterY -= CHARA_SPEED_MIDI;
		}
	}
	if (MY_KEY_DOWN(KEY_INPUT_RIGHT) || MY_KEY_DOWN(KEY_INPUT_D)) 
	{
		player.CenterX += CHARA_SPEED_MIDI;
		player.coll.left = player.CenterX - mapChip.width / 2 + 5;
		player.coll.top = player.CenterY - mapChip.height / 2 + 5;
		player.coll.right = player.CenterX + mapChip.width / 2 - 5;
		player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;
		player.Muki = 1;
		if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
		{
			player.CenterX -= CHARA_SPEED_MIDI;
		}
	}
	if (MY_KEY_DOWN(KEY_INPUT_LEFT) || MY_KEY_DOWN(KEY_INPUT_A))
	{
		player.CenterX -= CHARA_SPEED_MIDI;
		player.coll.left = player.CenterX - mapChip.width / 2 + 5;
		player.coll.top = player.CenterY - mapChip.height / 2 + 5;
		player.coll.right = player.CenterX + mapChip.width / 2 - 5;
		player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;
		player.Muki = 3;
		if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
		{
			player.CenterX += CHARA_SPEED_MIDI;
		}
	}

	player.coll.left = player.CenterX - mapChip.width / 2 + 5;
	player.coll.top = player.CenterY - mapChip.height / 2 + 5;
	player.coll.right = player.CenterX + mapChip.width / 2 - 5;
	player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;

	if (player.image.x >= 0 && player.image.x <= GAME_WIDTH)
	{
		player.image.x = player.CenterX - player.image.width / 2;
		player.image.y = player.CenterY - player.image.height / 2;
	}

	RECT PlayerRect;
	PlayerRect.left = player.image.x + 40;
	PlayerRect.top = player.image.y + 40;
	PlayerRect.right = player.image.x + player.image.width - 40;
	PlayerRect.bottom = player.image.y + player.image.height - 40;

	if (player.Kaiso == GoalKaiso && MY_CHECK_RECT_COLL(PlayerRect, GoalRect) == TRUE)
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

	for (int i = 0; i < FromWarpCou; i++)
	{
		RECT From;
		From.left = FromWarp[i].x;
		From.top = FromWarp[i].y;
		From.right = mapChip.width + FromWarp[i].x;
		From.bottom = mapChip.height + FromWarp[i].y;

		if (player.Kaiso == FromWarp[i].kaiso && MY_CHECK_RECT_COLL(PlayerRect, From) == TRUE)
		{
			int work = GetRand(ToWarpCou - 1);

			player.Kaiso = ToWarp[work].kaiso;
			player.CenterX = ToWarp[work].x;
			player.CenterY = ToWarp[work].y;
			player.coll.left = player.CenterX - mapChip.width / 2 + 5;
			player.coll.top = player.CenterY - mapChip.height / 2 + 5;
			player.coll.right = player.CenterX + mapChip.width / 2 - 5;
			player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;

			for (int cnt = 0; cnt < TAMA_MAX; cnt++)player.tama[cnt].IsDraw = FALSE;
		}
	}

	for (int i = 0; i < enemyCnt; i++)
	{
		if (enemy[i].view == TRUE && enemy[i].Kaiso == player.Kaiso)
		{
			enemy[i].CenterX += enemy[i].MoveAdd;
			if (MY_CHECK_MAP1_PLAYER_COLL(enemy[i].coll) == TRUE)
			{
				enemy[i].CenterX -= enemy[i].MoveAdd * 2;
				enemy[i].MoveAdd *= -1;
			}
			enemy[i].coll.left = enemy[i].CenterX - mapChip.width / 2 + 5;
			enemy[i].coll.top = enemy[i].CenterY - mapChip.height / 2 + 5;
			enemy[i].coll.right = enemy[i].CenterX + mapChip.width / 2 - 5;
			enemy[i].coll.bottom = enemy[i].CenterY + mapChip.height / 2 - 5;

			if (enemy[i].image.x >= 0 && enemy[i].image.x <= GAME_WIDTH)
			{
				enemy[i].image.x = enemy[i].CenterX - enemy[i].image.width / 2;
				enemy[i].image.y = enemy[i].CenterY - enemy[i].image.height / 2;
			}

			if (MY_CHECK_RECT_COLL(PlayerRect, enemy[i].coll) == TRUE)
			{
				playerHP -= GAME_ENEMY_DAMAGE;

				if (playerHP <= 0)
				{
					if (CheckSoundMem(BGM.handle) != 0)
					{
						StopSoundMem(BGM.handle);
					}

					SetMouseDispFlag(TRUE);

					playerHP = 0;

					GameEndKind = GAME_END_FAIL;

					GameScene = GAME_SCENE_END;
				}
				else
				{
					PlaySoundMem(enemy[i].die.handle, DX_PLAYTYPE_BACK);
					enemy[i].view = FALSE;
				}

				return;
			}
		}
	}


	if (player.image.x > GAME_WIDTH || player.image.y > GAME_HEIGHT
		|| player.image.x + player.image.width < 0 || player.image.y + player.image.height < 0)
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

	if (MY_MOUSE_DOWN(MOUSE_INPUT_LEFT) == TRUE)
	{
		if (player.CanShot == TRUE)
		{
			ChangeVolumeSoundMem(255 * 75 / 100, player.musicShot[player.SeCou].handle);
			PlaySoundMem(player.musicShot[player.SeCou].handle, DX_PLAYTYPE_BACK);
			player.SeCou = (player.SeCou + 1) % 4;

			player.CanShot = FALSE;

			for (int cnt = 0; cnt < TAMA_MAX; cnt++)
			{
				if (player.tama[cnt].IsDraw == FALSE)
				{
					player.tama[cnt].x = player.CenterX - player.tama[cnt].width / 2;

					player.tama[cnt].y = player.CenterY - player.tama[cnt].height / 2;

					player.tama[cnt].coll.left = player.tama[cnt].x;
					player.tama[cnt].coll.right = player.tama[cnt].x + player.tama[cnt].width;
					player.tama[cnt].coll.top = player.tama[cnt].y;
					player.tama[cnt].coll.bottom = player.tama[cnt].y + player.tama[cnt].height;

					player.tama[cnt].IsDraw = TRUE;

					switch (player.Muki)
					{
					case 0:
						player.tama[cnt].speedX = 0;
						player.tama[cnt].speedY = -CHARA_SPEED_HIGH;
						break;
					case 1:
						player.tama[cnt].speedX = CHARA_SPEED_HIGH;
						player.tama[cnt].speedY = 0;
						break;
					case 2:
						player.tama[cnt].speedX = 0;
						player.tama[cnt].speedY = CHARA_SPEED_HIGH;
						break;
					case 3:
						player.tama[cnt].speedX = -CHARA_SPEED_HIGH;
						player.tama[cnt].speedY = 0;
						break;
					}

					break;
				}
			}
		}
	}

	if (player.CanShot == FALSE)
	{
		if (player.ShotReLoadCnt == player.ShotReLoadCntMAX)
		{
			player.ShotReLoadCnt = 0;
			player.CanShot = TRUE;
		}

		player.ShotReLoadCnt++;
	}

	return;
}

VOID MY_PLAY_DRAW(VOID)
{
	DrawGraph(ImageBack[player.Kaiso].image.x, ImageBack[player.Kaiso].image.y, ImageBack[player.Kaiso].image.handle, TRUE);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			DrawGraph(
				map[player.Kaiso][tate][yoko].x,
				map[player.Kaiso][tate][yoko].y,
				mapChip.handle[map[player.Kaiso][tate][yoko].kind],
				TRUE);
		}
	}

	DrawRotaGraph(
		player.image.x + player.image.width / 2, player.image.y + player.image.height / 2, 1.0, M_PI / 2 * player.Muki, player.image.handle, TRUE);

	for (int i = 0; i < enemyCnt; i++)
	{
		if (enemy[i].view == TRUE && enemy[i].Kaiso == player.Kaiso) {
			DrawGraph(enemy[i].image.x, enemy[i].image.y, enemy[i].image.handle, TRUE);
		}
	}

	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{
		if (player.tama[cnt].IsDraw == TRUE)
		{
			DrawGraph(
				player.tama[cnt].x,
				player.tama[cnt].y,
				player.tama[cnt].handle[player.tama[cnt].nowImageKind],	TRUE);

			if (player.tama[cnt].changeImageCnt < player.tama[cnt].changeImageCntMAX)
			{
				player.tama[cnt].changeImageCnt++;
			}
			else
			{
				if (player.tama[cnt].nowImageKind < TAMA_DIV_NUM - 1)
				{
					player.tama[cnt].nowImageKind++;
				}
				else
				{
					player.tama[cnt].nowImageKind = 0;
				}

				player.tama[cnt].changeImageCnt = 0;
			}

			if (player.tama[cnt].y < 0 || player.tama[cnt].y > GAME_HEIGHT || player.tama[cnt].x < 0 || player.tama[cnt].x > GAME_WIDTH)
			{
				player.tama[cnt].IsDraw = FALSE;
			}
			else
			{
				player.tama[cnt].x += player.tama[cnt].speedX;
				player.tama[cnt].y += player.tama[cnt].speedY;
				player.tama[cnt].coll.top += player.tama[cnt].speedY;
				player.tama[cnt].coll.bottom += player.tama[cnt].speedY;
				player.tama[cnt].coll.left += player.tama[cnt].speedX;
				player.tama[cnt].coll.right += player.tama[cnt].speedX;
			}
			for (int i = 0; i < enemyCnt; i++)
			{
				if (enemy[i].view == TRUE && MY_CHECK_RECT_COLL(player.tama[cnt].coll, enemy[i].coll) == TRUE)
				{
					player.tama[cnt].IsDraw = FALSE;
					enemy[i].view = FALSE;

					PlaySoundMem(enemy[i].die.handle, DX_PLAYTYPE_BACK);
				}
			}
		}
	}

	DrawBox(GAME_WIDTH, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0,0,0), TRUE);

	SetFontSize(30);
	DrawFormatString(GAME_WIDTH + (WINDOW_WIDTH - GAME_WIDTH) / 2 - 50, 20, GetColor(255, 255, 255), "TimeLimit");
	DrawFormatString(GAME_WIDTH + (WINDOW_WIDTH - GAME_WIDTH) / 2 - 50, 60, GetColor(255, 255, 255), "   %d", TimeLim);

	DrawFormatString(GAME_WIDTH + (WINDOW_WIDTH - GAME_WIDTH) / 2 - 50, 120, GetColor(255, 255, 255), " HP：%d", playerHP);

	DrawFormatString(GAME_WIDTH + (WINDOW_WIDTH - GAME_WIDTH) / 2, WINDOW_HEIGHT - 60, GetColor(255, 255, 255), "第%d層", player.Kaiso + 1);

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

	//DrawString(0, 0, "エンド画面(エスケープキーを押して下さい)", GetColor(255, 255, 255));
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

	//--------------------------------------------------------------------------

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

	//--------------------------------------------------------------------------

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


	strcpy_s(player.image.path, IMAGE_PLAYER_PATH);
	player.image.handle = LoadGraph(player.image.path);
	if (player.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}
	GetGraphSize(player.image.handle, &player.image.width, &player.image.height);
	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;
	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;
	player.CenterX = player.image.x + player.image.width / 2;
	player.CenterY = player.image.y + player.image.height / 2;
	player.speed = CHARA_SPEED_LOW;

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		strcpy_s(enemy[i].image.path, IMAGE_ENEMY_PATH);
		enemy[i].image.handle = LoadGraph(enemy[i].image.path);
		if (enemy[i].image.handle == -1)
		{
			MessageBox(GetMainWindowHandle(), IMAGE_ENEMY_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
			return(FALSE);
		}
		GetGraphSize(enemy[i].image.handle, &enemy[i].image.width, &enemy[i].image.height);
		enemy[i].image.x = GAME_WIDTH / 2 - enemy[i].image.width / 2;
		enemy[i].image.y = GAME_HEIGHT / 2 - enemy[i].image.height / 2;
		enemy[i].CenterX = enemy[i].image.x + enemy[i].image.width / 2;
		enemy[i].CenterY = enemy[i].image.y + enemy[i].image.height / 2;
		enemy[i].speed = CHARA_SPEED_LOW;
	}

	int tamaRedRes = LoadDivGraph(TAMA_RED_PATH, TAMA_DIV_NUM, TAMA_DIV_TATE, TAMA_DIV_YOKO, TAMA_DIV_WIDTH, TAMA_DIV_HEIGHT,	&player.tama[0].handle[0]);

	if (tamaRedRes == -1)
	{
		MessageBox(GetMainWindowHandle(), TAMA_RED_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}

	GetGraphSize(player.tama[0].handle[0], &player.tama[0].width, &player.tama[0].height);

	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{
		strcpyDx(player.tama[cnt].path, TEXT(TAMA_RED_PATH));

		for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++)
		{
			player.tama[cnt].handle[i_num] = player.tama[0].handle[i_num];
		}

		player.tama[cnt].width = player.tama[0].width;

		player.tama[cnt].height = player.tama[0].height;

		player.tama[cnt].x = player.CenterX - player.tama[cnt].width / 2;

		player.tama[cnt].y = player.image.y;

		player.tama[cnt].IsDraw = FALSE;

		player.tama[cnt].changeImageCnt = 0;

		player.tama[cnt].changeImageCntMAX = TAMA_CHANGE_MAX;

		player.tama[cnt].nowImageKind = 0;

		player.tama[cnt].speedX = CHARA_SPEED_HIGH;
		player.tama[cnt].speedY = CHARA_SPEED_HIGH;
	}

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

	for (int kai = 0; kai < GAME_MAP_KAISO_MAX; kai++)
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

	for (int i = 0; i < ENEMY_MAX; i++)DeleteGraph(enemy[i].image.handle);

	DeleteGraph(ImageTitleBK.handle);
	DeleteGraph(ImageTitleROGO.image.handle);
	DeleteGraph(ImageTitleButtonPlay.handle);
	DeleteGraph(ImageTitleButtonRule.handle);
	DeleteGraph(ImageTitleButtonEnd.handle);
	DeleteGraph(ImageTitleButtonNow.handle);

	DeleteGraph(ImageEndCOMP.image.handle);
	DeleteGraph(ImageEndFAIL.image.handle);

	for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++) { DeleteGraph(player.tama[0].handle[i_num]); }

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

	strcpy_s(player.musicShot[0].path, MUSIC_PLAYER_SHOT_PATH_1);
	player.musicShot[0].handle = LoadSoundMem(player.musicShot[0].path);
	if (player.musicShot[0].handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_PLAYER_SHOT_PATH_1, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}
	strcpy_s(player.musicShot[1].path, MUSIC_PLAYER_SHOT_PATH_2);
	player.musicShot[1].handle = LoadSoundMem(player.musicShot[1].path);
	if (player.musicShot[1].handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_PLAYER_SHOT_PATH_2, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}
	strcpy_s(player.musicShot[2].path, MUSIC_PLAYER_SHOT_PATH_3);
	player.musicShot[2].handle = LoadSoundMem(player.musicShot[2].path);
	if (player.musicShot[2].handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_PLAYER_SHOT_PATH_3, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}
	strcpy_s(player.musicShot[3].path, MUSIC_PLAYER_SHOT_PATH_4);
	player.musicShot[3].handle = LoadSoundMem(player.musicShot[3].path);
	if (player.musicShot[3].handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_PLAYER_SHOT_PATH_4, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return(FALSE);
	}

	for (int i = 0; i < ENEMY_MAX; i++) {
		strcpy_s(enemy[i].die.path, MUSIC_ENEMY_DIE_PATH);
		enemy[i].die.handle = LoadSoundMem(enemy[i].die.path);
		if (enemy[i].die.handle == -1)
		{
			MessageBox(GetMainWindowHandle(), MUSIC_ENEMY_DIE_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
			return(FALSE);
		}
	}

	return TRUE;
}

VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(BGM.handle);
	DeleteSoundMem(BGM_TITLE.handle);
	DeleteSoundMem(BGM_COMP.handle);
	DeleteSoundMem(BGM_FAIL.handle);
	for (int i = 0; i < 4; i++)DeleteSoundMem(player.musicShot[i].handle);
	for (int i = 0; i < ENEMY_MAX; i++)DeleteSoundMem(enemy[i].die.handle);

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
				if (map[player.Kaiso][tate][yoko].kind == k) { return(TRUE); }
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
