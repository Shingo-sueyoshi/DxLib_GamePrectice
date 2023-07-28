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





