#include "DxLib.h"

int global = 30;

void Func1(int a[]);

void Func2(int* a);




int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdiLine, _In_ int nShowCmd)
{

	int num[] = {1,2,3};


	//�E�B���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);

	//Dx���C�u�����̏���������
	if (DxLib_Init() == -1)
	{
		return-1;

	}
	
	Func1(num);

	//DrawFormatString(20, 60, GetColor(255, 255, 255), "%d",num);


	Func2(num);

	//DrawFormatString(20, 80, GetColor(255, 255, 255), "%d", num);


	//���͑ҋ@

	WaitKey();


	//Dx���C�u�����g�p�̏I������
	DxLib_End();


	return 0;
}

void Func1(int a[])
{
	int i;

	for (i = 0; i < 3; i++)
	{
		DrawFormatString(20, (20 + (20 * i)), GetColor(255, 255, 255), "%d", a[i]);
	}



	/*DrawFormatString(20, 20, GetColor(255, 255, 255), "%d", a);
	a += 10;
	DrawFormatString(20, 40, GetColor(255, 255, 255), "%d", a);*/

}

void Func2(int* a)
{
	int i;

	for (i = 0; i < 3; i++)
	{
		DrawFormatString(20, (80+ (20 * i)), GetColor(255, 255, 255), "%d", *(a + i));
	}




	/*DrawFormatString(20, 80, GetColor(255, 255, 255), "%d", *a);
	*a += 10;
	DrawFormatString(20, 100, GetColor(255, 255, 255), "%d", *a);*/

}






