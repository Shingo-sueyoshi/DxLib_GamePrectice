#include "DxLib.h"

int global = 30;


void Func(void);



int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdiLine, _In_ int nShowCmd)
{
	int num = 10;


	//�E�B���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);

	//Dx���C�u�����̏���������
	if (DxLib_Init() == -1)
	{
		return-1;

	}

	DrawFormatString(20, 20, GetColor(255, 255, 255), "���C���֐��̃��[�J���ϐ�num�F%d", num);

	Func();

	DrawFormatString(20, 80, GetColor(255, 255, 255), "�O���[�o���ϐ�global:%d", global);


	//���͑ҋ@

	WaitKey();


	//Dx���C�u�����g�p�̏I������
	DxLib_End();


	return 0;
}

void Func(void)
{
	int num = 20;

	DrawFormatString(20, 40, GetColor(255, 255, 255), "Func�֐��̃��[�J���ϐ�num:%d", num);



	DrawFormatString(20, 60, GetColor(255, 255, 255), "�O���[�o���ϐ�global:%d", global);

	global = 40;
}


