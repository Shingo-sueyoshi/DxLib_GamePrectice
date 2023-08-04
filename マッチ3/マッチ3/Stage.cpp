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

T_Object Block[HEIGHT][WIDTH];               //�u���b�N�I�u�W�F�N�g�f�[�^

T_CURSOR Select[3];                          //�Z���N�g�J�[�\�����W

int Item[ITEM_MAX];

int ClickStatus;

int Stage_State;

int Stage_Mission;

int stage_Score;

int ClearFlag;


int BlockImage[BLOCK_IMAGE_MAX];        //�u���b�N�摜

int StageImage;                                  //�w�i�p�摜

int ClickSE;                           //�N���b�NSE

int FadeOutSE;                                   //�t�F�[�h�A�E�gSE

int MoveBlockSE;                        //�u���b�N�ړ�SE



/*
*�v���g�^�C�v�錾
*/


int combo_check(int x, int y);

void combo_check_h(int y, int x, int* cnt, int* col);

void combo_check_w(int y, int x, int* cnt, int* col);

void save_block(void);

void restore_block(void);




/*
*�X�e�[�W����@�\�F����������
* ���@���F�Ȃ�
* �߂�l�F�G���[���
*/


int StageInitialize(void)
{
	int ret = 0;

	int i;


	//�摜�ǂݍ���

	LoadDivGraph("images/block.png", BLOCK_IMAGE_MAX, BLOCK_IMAGE_MAX, 1, BLOCKSIZE, BLOCKSIZE, BlockImage);

	StageImage = LoadGraph("images/stage.png");

	//�����ǂݍ���

	ClickSE = LoadSoundMem("sounds/click_se.mp3");

	FadeOutSE = LoadSoundMem("sounds/fadeout_se.mp3");

	MoveBlockSE = LoadSoundMem("sounds/moveblock_se.mp3");
}