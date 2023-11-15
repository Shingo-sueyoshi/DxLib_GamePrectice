#include "SceneManager.h"
#include "TitleScene.h"
#include "GameMainScene.h"
#include "RankingScene.h"
#include "EndScene.h"
#include "DxLib.h"

/*
マクロ定義
*/

/*
型定義
*/

/*
変巣宣言
*/
GAME_MODE game_mode;             //ゲームモード情報
GAME_MODE next_mode;             //次のゲームモード
int read_error;                  //読込みエラー確認


/*
プロトタイプ宣言
*/

/*
シーン管理機能：初期化処理
引数：ゲームモード情報
戻り値：なし
*/
void SceneManeger_Initialize(GAME_MODE mode)
{
	read_error=
}
