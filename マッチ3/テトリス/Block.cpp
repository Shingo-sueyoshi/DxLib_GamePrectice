#include "Block.h"
#include "DxLib.h"
#include "InputControl.h"


/*
マクロ定義
*/

#define FIELD_HEIGHT   (21)
#define FIELD_WIDTH    (12)
#define BLOCK_TROUT_SIZE  (4)
#define BLOCK_SIZE     (36)
#define BLOCK_TYPE_MAX    (7)
#define BLOCK_NEXT_POS_X   (700)
#define BLOCK_NEXT_POS_Y   (500)
#define BLOCK_STOCK_POS_X  (500)
#define BLOCK_STOCK_POS_Y  (350)
#define DROP_BLOCK_INIT_X  (4)
#define DROP_BLOCK_INIT_Y  (-1)
#define DROP_SPEED         (60)
#define TURN_CROCKWICE     (0)
#define TURN_ANTICROCKWICE (1)

/*
型定義
*/

enum BLOCK_STATE
{
	E_BLOCK_EMPTY,          //空ブロック
	E_BLOCK_LIGHT_BLUE,     //水色
	E_BLOCK_YELLOW_GREEN,   //黄緑
	E_BLOCK_YELLOW,         //黄色
	E_BLOCK_ORANGE,         //オレンジ
	E_BLOCK_BLUE,           //青
	E_BLOCK_PINK,           //ピンク
	E_BLOCK_RED,            //赤
	E_BLOCK_GLAY,           //灰色
	E_BLOCK_WALL,           //壁
	E_BLOCK_IMAGE_MAX,
	
};

/*
定数定義
*/

const int C_BLOCK_TABLE[BLOCK_TYPE_MAX][BLOCK_TROUT_SIZE][BLOCK_TROUT_SIZE] =
{
	{

	{0,0,0,0},
	{0,1,1,0},
	{0,1,1,0},
	{0,0,0,0}

	},

	{

	{0,0,0,0},
	{0,0,0,0},
	{2,2,2,2},
	{0,0,0,0}

	},

	{

	{0,0,0,0},
	{3,0,0,0},
	{3,3,3,0},
	{0,0,0,0}

	},

	{

	{0,0,0,0},
	{0,0,0,4},
	{0,4,4,4},
	{0,0,0,0}
	},

	{

	{0,0,0,0},
	{0,5,5,0},
	{0,0,5,5},
	{0,0,0,0}
	},

	{
	{0,0,0,0},
	{0,6,6,0},
	{6,6,0,0},
	{0,0,0,0}
	},

	{
	{0,0,0,0},
	{0,7,0,0},
	{7,7,7,0},
	{0,0,0,0}

	}

};

/*
変数宣言
*/

int BlockImage[E_BLOCK_IMAGE_MAX];        //ブロック画像
BLOCK_STATE Field[FIELD_HEIGHT][FIELD_WIDTH];   //フィールド配列
BLOCK_STATE Next[BLOCK_TROUT_SIZE][BLOCK_TROUT_SIZE];   //待機状態のブロック
BLOCK_STATE Stock[BLOCK_TROUT_SIZE][BLOCK_TROUT_SIZE];  //ストックのブロック
BLOCK_STATE DropBlock[BLOCK_TROUT_SIZE][BLOCK_TROUT_SIZE];   //落ちるブロック
int DropBlock_X;     //落ちるブロックのX座標
int DropBlock_Y;     //落ちるブロックのY座標

int WaitTime;     //待機時間
int Stock_Flg;    //ストックフラグ
int Generate_Flg;  //生成フラグ


