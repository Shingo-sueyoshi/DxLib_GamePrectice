#include "EndScene.h"

#include "DxLib.h"

/*
�}�N����`
*/

/*
�^��`
*/

/*
�ϐ��錾
*/
int wait_count;

/*
�G���h��ʁF����������
�����F�Ȃ�
�߂�l�F�G���[���i-1�F�ُ�L,-1�ȊO�F����j
*/
int EndScene_Initialize(void)
{
	int ret = 0;

	wait_count = 0;

	return ret;
}

/*
�G���h��ʁF��������
�����F�Ȃ�
�߂�l�F�Ȃ�
*/

void EndScene_Update(void)
{
	wait_count++;
}

/*
�G���h��ʁF�`�揈��
�����F�Ȃ�
�߂�l�F�Ȃ�
*/

void EndScene_Draw(void)
{
	DrawString(10, 10, "�G���h��ʂł�", GetColor(255, 255, 255));
}

/*
�G���h��ʁF�C���m�F����
�����F�Ȃ�
�߂�l�F�Ȃ�
*/

int Get_EndTime(void)
{
	if (wait_count > 300)
	{
		return TRUE;
	}

	return FALSE;

}