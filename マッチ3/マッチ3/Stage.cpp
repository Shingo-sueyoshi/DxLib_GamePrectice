#include"Stage.h"

#include"DxLib.h"

#include"InputControl.h"


/*
*�}�N����`
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
*�^��`
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
*�ϐ��錾
*/





