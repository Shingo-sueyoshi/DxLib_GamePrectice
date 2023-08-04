#include"Stage.h"

#include"DxLib.h"

#include"InputControl.h"


/*
*マクロ定義
*/

#define HEIGHT

#define WIDTH

#define BLOCKSIZE

#define BLOCK_IMAGE_MAX

#define ITEM_MAX

#define SELECT_CURSOR

#define NEXT_CURSOR

#define TMP_CURSOR



/*
*型定義
*/

typedef struct
{
	int flg;

	int x, y;

	int width, heigth;

	int image;

	int backup;

}T_Object;


typedef struct
{
	int x;

	int y;

}T_CURSOR;


enum

{
	E_NONE,

	E_ONCE,

	E_SECOND
};

/*
*変数宣言
*/

T_Object Block[HEIGHT][WIDTH];               //ブロックオブジェクトデータ

T_CURSOR Select[3];                          //セレクトカーソル座標

int Item[ITEM_MAX];

int ClickStatus;

int Stage_State;

int Stage_Mission;

int stage_Score;

int ClearFlag;


int BlockImage[BLOCK_IMAGE_MAX];        //ブロック画像

int StageImage;                                  //背景用画像

int ClickSE;                           //クリックSE

int FadeOutSE;                                   //フェードアウトSE

int MoveBlockSE;                        //ブロック移動SE



/*
*プロトタイプ宣言
*/


int combo_check(int x, int y);

void combo_check_h(int y, int x, int* cnt, int* col);

void combo_check_w(int y, int x, int* cnt, int* col);

void save_block(void);

void restore_block(void);




/*
*ステージ制御機能：初期化処理
* 引　数：なし
* 戻り値：エラー情報
*/


int StageInitialize(void)
{
	int ret = 0;

	int i;


	//画像読み込み

	LoadDivGraph("images/block.png", BLOCK_IMAGE_MAX, BLOCK_IMAGE_MAX, 1, BLOCKSIZE, BLOCKSIZE, BlockImage);

	StageImage = LoadGraph("images/stage.png");

	//音源読み込み

	ClickSE = LoadSoundMem("sounds/click_se.mp3");

	FadeOutSE = LoadSoundMem("sounds/fadeout_se.mp3");

	MoveBlockSE = LoadSoundMem("sounds/moveblock_se.mp3");
}