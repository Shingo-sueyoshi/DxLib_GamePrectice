#include "DxLib.h"

int global = 30;


void Func(void);



int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdiLine, _In_ int nShowCmd)
{
	int num = 10;


	//ウィンドウモードで起動
	ChangeWindowMode(TRUE);

	//Dxライブラリの初期化処理
	if (DxLib_Init() == -1)
	{
		return-1;

	}

	DrawFormatString(20, 20, GetColor(255, 255, 255), "メイン関数のローカル変数num：%d", num);

	Func();

	DrawFormatString(20, 80, GetColor(255, 255, 255), "グローバル変数global:%d", global);


	//入力待機

	WaitKey();


	//Dxライブラリ使用の終了処理
	DxLib_End();


	return 0;
}

void Func(void)
{
	int num = 20;

	DrawFormatString(20, 40, GetColor(255, 255, 255), "Func関数のローカル変数num:%d", num);



	DrawFormatString(20, 60, GetColor(255, 255, 255), "グローバル変数global:%d", global);

	global = 40;
}


