#include"GameOverScene.h"
#include"DxLib.h"
#include"SceneManager.h"

/*
*�ϐ��錾
*/

int GameOverImage;

int GameOverSE;

int GameOverFlag;


/*
*�v���g�^�C�v�錾
*/

/*
*�Q�[���I�[�o�[��ʁF����������
* ���@���F�Ȃ�
* �߂�l�F�G���[���
*/

int GemeOverScene_Initialize(void)
{
	int ret = 0;

	//�摜�ǂݍ���

	GameOverImage = LoadGraph("images/gameover.png");

	//�����ǂݍ���

	GameOverSE = LoadSoundMem("sounds/gameover_se.mp3");

	GameOverFlag = FALSE;


	//�G���[�`�F�b�N
	if (GameOverImage == -1)
	{
		ret = -1;
	}

	if (GameOverSE == -1)
	{
		ret = -1;
	}


	return ret;
}

/*
*�Q�[���I�[�o�[��ʁF�X�V����
* ���@���F�Ȃ�
* �߂�l�F�Ȃ�
*/











