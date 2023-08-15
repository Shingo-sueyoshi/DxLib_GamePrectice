#include"Stage.h"

#include"DxLib.h"

#include"InputControl.h"


/*
*ƒ}ƒNƒ’è‹`
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
*Œ^’è‹`
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
*•Ï”éŒ¾
*/

T_Object Block[HEIGHT][WIDTH];               //ƒuƒƒbƒNƒIƒuƒWƒFƒNƒgƒf[ƒ^

T_CURSOR Select[3];                          //ƒZƒŒƒNƒgƒJ[ƒ\ƒ‹À•W

int Item[ITEM_MAX];

int ClickStatus;

int Stage_State;

int Stage_Mission;

int stage_Score;

int ClearFlag;


int BlockImage[BLOCK_IMAGE_MAX];        //ƒuƒƒbƒN‰æ‘œ

int StageImage;                                  //”wŒi—p‰æ‘œ

int ClickSE;                           //ƒNƒŠƒbƒNSE

int FadeOutSE;                                   //ƒtƒF[ƒhƒAƒEƒgSE

int MoveBlockSE;                        //ƒuƒƒbƒNˆÚ“®SE



/*
*ƒvƒƒgƒ^ƒCƒvéŒ¾
*/


int combo_check(int x, int y);

void combo_check_h(int y, int x, int* cnt, int* col);

void combo_check_w(int y, int x, int* cnt, int* col);

void save_block(void);

void restore_block(void);




/*
*ƒXƒe[ƒW§Œä‹@”\F‰Šú‰»ˆ—
* ˆø@”F‚È‚µ
* –ß‚è’lFƒGƒ‰[î•ñ
*/


int StageInitialize(void)
{
	int ret = 0;

	int i;


	//‰æ‘œ“Ç‚İ‚İ

	LoadDivGraph("images/block.png", BLOCK_IMAGE_MAX, BLOCK_IMAGE_MAX, 1, BLOCKSIZE, BLOCKSIZE, BlockImage);

	StageImage = LoadGraph("images/stage.png");

	//‰¹Œ¹“Ç‚İ‚İ

	ClickSE = LoadSoundMem("sounds/click_se.mp3");

	FadeOutSE = LoadSoundMem("sounds/fadeout_se.mp3");

	MoveBlockSE = LoadSoundMem("sounds/moveblock_se.mp3");


	//ƒuƒƒbƒN¶¬ˆ—

	CreateBlock();


	ClickStatus = E_NONE;

	Stage_Stage = 0;

	Stage_Score = 0;

	ClearFlag = FALSE;


	for (i = 0; i < 3; i++)
	{
		Select[i].x = 0;

		Select[i].y = 0;
	}


	//ƒGƒ‰[ƒ`ƒFƒbƒN

	for (i = 0; i < BLOCK_IMAGE_MAX; i++)
	{
		if (BlockImage[i] == -1)
		{
			ret = -1;

			break;
		}
	}


	if (StageImage == -1)
	{
		ret = -1;
	}

	if (ClickSE == -1)
	{
		ret = -1;
	}

	if (FadeOutSE == -1)
	{
		ret = -1;
	}

	if (MoveBlockSE == -1)
	{
		ret = -1;
	}




	return ret;

}


/*
*ƒXƒe[ƒW§Œä‹@”\FƒXƒe[ƒW•`‰æ
* ˆø@”F‚È‚µ
* –ß‚è’lF‚È‚µ
*/

void StageDraw(void) 
{
	DrawGraph(0, 0, StageImage, FALSE);


	//ƒAƒCƒeƒ€‚Ìæ“¾ŒÂ”‚ğ•`‰æ

	for (int i = 0; i < ITEM_MAX; i++)
	{
		DrawRotaGraph(540, 245 + i * 30, 0.5f, 0, BlockImage[i + 1], TRUE, 0);

		DrawFormatString(580, 235 + i * 30, 0xffffff, "%3d", Item[i]);
	}

	//ƒuƒƒbƒN‚ğ•`‰æ

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++) 
		{
			if (Block[i][j].flg == TRUE && Block[i][j].image != NULL)
			{
				DrawGraph(Block[i][j].x, Block[i][j].y, BlockImage [[i][j].image], TRUE);
			}
		}
	}


	//‘I‘ğƒuƒƒbƒN‚ğ•`‰æ

	DrawGraph(Select[SELECT_CURSOR].x * BLOCKSIZE, Select[SELECT_CURSOR].y * BLOCKSIZE, BlockImage[9], TRUE);

	if (ClickStatus != E_NONE)
	{
		DrawGraph(Select[NEXT_CURSOR].x * BLOCKSIZE, Select[NEXT_CURSOR].y * BLOCKSIZE, BlockImage[9], TRUE);
	}


	//ƒ~ƒbƒVƒ‡ƒ“‚ğ•`‰æ

	SetFontSize(20);

	DrawFormatString(590, 211, GetColor(255, 255, 255), "%3d", Stage_Mission);

	//ƒAƒCƒeƒ€‚Ìæ“¾ŒÂ”‚ğ•`‰æ

	for (int i = 0; i < ITEM_MAX; i++)
	{
		DrawRotaGraph(540, 245 + i * 30, 0.5f, 0, BlockImage[i + 1], TRUE, 0);

		DrawFormatString(580, 235 + i * 30, GetColor(255, 255, 255), "%3d", Item[i]);
	}
}



/*
*ƒXƒe[ƒW§Œä‹@”\FƒuƒƒbƒN¶¬ˆ—
* ˆø@”F‚È‚µ
* –ß‚è’lF‚È‚µ
*/

void CreateBlock(void)
{
	int Check = 0;

	int i, j;

	do
	{
		Check = 0;

		for (i = 0; i < HEIGHT; i++)
		{
			for (j = 0; j < WIDTH; j++)
			{
				if (j == 0 || j == WIDTH - 1 || i == HEIGHT - 1 || i == 0)
				{
					Block[i][j].flg = FALSE;

					Block[i][j].image = NULL;
				}

				else
				{
					Block[i][j].flg = TRUE;

					Block[i][j].x = (j - 1) * BLOCKSIZE;

					Block[i][j].y = (j - 1) * BLOCKSIZE;

					Block[i][j].width = BLOCKSIZE;

					Block[i][j].height = BLOCKSIZE;

					Block[i][j].image = GetRand(7) + 1;//1`8‚Ì—”
				}
			}
		}


		/*for(i=1;i<HEIGHT-1;i++)
		{
		      for(j=1;j<WIDTH-1;j++)
			  {
			     if(Block[i][j].image==NULL)
				 {
				 Block[i][j].image=GetRand(7)+1;
				 }
			  }
		}*/
		
		//ƒuƒƒbƒN˜A½ƒ`ƒFƒbƒN

		for (i = 1; i < HEIGHT - 1; i++)
		{
			for (j = 1; j < WIDTH - 1; j++)
			{
				Check += combo_check(i, j);
			}
		}
	} while (Check != 0);


	for (i = 0; i < ITEM_MAX; i++)
	{
		Item[i] = 0;
	}
}


/*
*ƒXƒe[ƒW§Œä‹@”\FƒuƒƒbƒN‘I‘ğˆ—
* ˆø@”G‚È‚µ
* –ß‚è’lF‚È‚µ
*/

void SelectBlock(void)
{
	int TmpBlock;

	int Result;


	//ƒJ[ƒ\ƒ‹À•W‚Ìæ“¾
	Select[SELECT_CURSOR].x = GetMousePositionX() / BLOCKSIZE;

	Select[SELECT_CURSOR].y = GetMousePositionY() / BLOCKSIZE;


	//‘I‘ğƒuƒƒbƒN‚Ì”ÍˆÍ‚ğ§Œä

	if (Select[SELECT_CURSOR].x < 0)
	{
		Select[SELECT_CURSOR].x = 0;
	}

	if (Select[SELECT_CURSOR].x > WIDTH - 3)
	{
		Select[SELECT_CURSOR].x = WIDTH - 3;
	}

	if (Select[SELECT_CURSOR].y < 0)
	{
		Select[SELECT_CURSOR].y = 0;
	}

	if (Select[SELECT_CURSOR].y > HEIGHT - 3)
	{
		Select[SELECT_CURSOR].y = HEIGHT - 3;
	}


	//ƒNƒŠƒbƒv‚ÅƒuƒƒbƒN‚ğ‘I‘ğ

	if (GetKeyFlg(MOUSE_INPUT_LEFT)) {
		//ƒNƒŠƒbƒvŒø‰Ê‰¹

		PlaySoundMem(ClickSE, DX_PLAYTYPE_BACK);


		if (ClickStatus == E_NONE) {

			Select[NEXT_CURSOR].x = Select[SELECT_CURSOR].x;

			Select[NEXT_CURSOR].y = Select[SELECT_CURSOR].y;

			ClickStatus = E_ONCE;
		}
		else if (ClickStatus == E_ONCE &&
			((abs(Select[NEXT_CURSOR].x - Select[SELECT_CURSOR].x)
				== 1 &&
				(abs(Select[NEXT_CURSOR].y - Select[SELECT_CURSOR].y)
					== 0)) ||
				(abs(Select[NEXT_CURSOR].x - Select[SELECT_CURSOR].x)
					== 0 &&
					abs(Select[NEXT_CURSOR].y - Select[SELECT_CURSOR].y)
					== 1)))
		{

			Select[TMP_CURSOR].x = Select[SELECT_CURSOR].x;

			Select[TMP_CURSOR].y = Select[SELECT_CURSOR].y;

			ClickStatus = E_SECOND;

		}

	}

	//ï¿½Iï¿½ï¿½ï¿½uï¿½ï¿½ï¿½bï¿½Nï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½B

	if (ClickStatus == E_SECOND)
	{
		TmpBlock = Block[Select[NEXT_CURSOR].y + 1][Select[NEXT_CURSOR].x + 1].image;

		Block[Select[NEXT_CURSOR].y + 1][Select[NEXT_CURSOR].x + 1].image =
			Block[Select[TMP_CURSOR].y + 1][Select[TMP_CURSOR].x + 1].image;
		
		Block[Select[TMP_CURSOR].y + 1][Select[TMP_CURSOR].x + 1].image =
			TmpBlock;


		//ï¿½Aï¿½ï¿½ï¿½ï¿½ï¿½Rï¿½ÂˆÈã‚©ï¿½ï¿½ï¿½×‚ï¿½B

		Result = 0;

		Result += combo_check(Select[NEXT_CURSOR].y + 1,
			Select[NEXT_CURSOR].x + 1);

		Result += combo_check(Select[TMP_CURSOR].y + 1,
			Select[TMP_CURSOR].x + 1);

		//ï¿½Aï¿½ï¿½ï¿½ï¿½ï¿½Rï¿½ï¿½ï¿½ï¿½ï¿½È‚ï¿½Iï¿½ï¿½ï¿½uï¿½ï¿½ï¿½bï¿½Nï¿½ï¿½ï¿½ï¿½ï¿½É–ß‚ï¿½

		if (Result == 0)
		{

			int TmpBlock = Block[Select[NEXT_CURSOR].y + 1][Select[NEXT_CURSOR].x + 1].image;

			Block[Select[NEXT_CURSOR].y + 1][Select[NEXT_CURSOR].x + 1].image
				= Block[Select[TMP_CURSOR].y + 1][Select[TMP_CURSOR].x + 1].image;

			Block[Select[TMP_CURSOR].y + 1][Select[TMP_CURSOR].x + 1].image = TmpBlock;

		}

		else
		{
			//ï¿½Aï¿½ï¿½ï¿½ï¿½ï¿½Rï¿½ÂˆÈï¿½È‚ï¿½uï¿½ï¿½ï¿½bï¿½Nï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½uï¿½ï¿½ï¿½bï¿½Nï¿½Ú“ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ÖˆÚsï¿½ï¿½ï¿½ï¿½

			Stage_State = 1;

		}

		//ï¿½Aï¿½ï¿½ï¿½ï¿½ï¿½Rï¿½ÂˆÈï¿½È‚ï¿½uï¿½ï¿½ï¿½bï¿½Nï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½uï¿½ï¿½ï¿½bï¿½Nï¿½Ú“ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ÖˆÚsï¿½ï¿½ï¿½ï¿½


	}

}


/*
*ï¿½Xï¿½eï¿½[ï¿½Wï¿½ï¿½ï¿½ï¿½@ï¿½\ï¿½Fï¿½tï¿½Fï¿½[ï¿½hï¿½Aï¿½Eï¿½gï¿½ï¿½ï¿½ï¿½
*ï¿½ï¿½ï¿½@ï¿½ï¿½ï¿½Fï¿½È‚ï¿½
*ï¿½ß‚ï¿½lï¿½Fï¿½È‚ï¿½
*/

void FadeOutBlock(void)
{
	static int BlendMode = 255;

	int i, j;

	//ï¿½tï¿½Fï¿½[ï¿½hï¿½Aï¿½Eï¿½gï¿½ï¿½ï¿½Ê‰ï¿½
	if (CheckSoundMem(FadeOutSE) == 0)
	{
		PlaySoundMem(FadeOutSE, DX_PLAYTYPE_BACK);
	}


	//ï¿½`ï¿½æƒ‚ï¿½[ï¿½hï¿½ï¿½ï¿½Aï¿½ï¿½ï¿½tï¿½@ï¿½uï¿½ï¿½ï¿½ï¿½ï¿½hï¿½É‚ï¿½ï¿½ï¿½

	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, BlendMode);

	for (i = 1; i < HEIGHT - 1; i++)
	{
		for (j = 1; j < WIDTH - 1; j++)
		{
			if (Block[i][j].image == 0)
			{
				DrawGraph(Block[i][j].x, Block[i][j].y,
					Block[Block[i][j].backup], TRUE);
			}
		}
	}

	//ï¿½`ï¿½æƒ‚ï¿½[ï¿½hï¿½ï¿½ï¿½mï¿½[ï¿½uï¿½ï¿½ï¿½Cï¿½ï¿½ï¿½É‚ï¿½ï¿½ï¿½




















}











