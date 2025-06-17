#include "Main.h"
#include "Game.h"
#include "Float2.h"
#include "Random.h"
#include "Hit.h"
#include <iostream>
//	砂漠の背景画像アニメーション10枚
#define BG_MAX 10
//	砂漠の背景画像の変数
int bg_image[BG_MAX];
int bg_f = 0;
#define SABAK_MAX 26
int bg_sabaku[SABAK_MAX];
int bg2_f = 0;

//	砂漠の川の背景画像アニメーション20枚
#define BG1_MAX 20
//	砂漠の川の背景画像の変数
int bg1_i[BG1_MAX];
//	砂漠の川の背景画像のフレーム変数
int bg1_f = 0;

//	わざと読み込みを遅くするためにテストファイルをたくさん読み込みます
#define TEST_MAX	500
//	テストファイル用の変数
int test_image[TEST_MAX];
float x_speed;
float y_speed;
//	シーンの定義
enum {
	SCENE_LOAD,		//	ロード中
	SCENE_TAITOL,	//	タイトル中 		
	SCENE_GAME1,	//	ステージ１
	SCENE_GAME2,	//	ステージ２
	SCENE_GAMEOVER,	//	ゲームオーバー
	SCENE_GAME3,	//	ステージ３
	SCENE_GAMEOVER2,//	ゲームオーバー2
	SCENE_GAMECRIA,	//	ゲームクリア
};
enum {
	MODE_WAIT,			//	０：飛んでいない（待ち状態）
	MODE_MOVE,			//	１：飛んでいる　（移動状態）
};


//	今どこのシーンか
int scene_num;


//	今読み込み中のファイル数を入れる用の変数
int loadfile_count;
int loadfile_max;

//	プレイヤーの当たり判定のサイズ
#define MARIO_SAIZ 30
//	プレイヤーの変数
int mario_i;
//	プレイヤーの座標用の変数
float mario_x;		//	X座標
float mario_y;		//	Y座標
int mario_hp = 3;
//	プレイヤーのスピード用の変数
float mario_speed;
//	プレイヤーのジャンプカウント用の変数
int cnt;
//	実装未定
#define BLOCK_SAIZ 20
int block_i;
int block_x;
int block_y;
//	障害物のアニメーション画像14枚
#define DONSOK_MAX 14
//	障害物のサイズ
#define DONSOKU_SAIZ 30
//	障害物の数
#define DONSOKU_KAZU 3
//	障害物のアニメーション画像用の変数
int donsok_i[DONSOK_MAX];
int donsoku_x[DONSOKU_KAZU];
int donsoku_y[DONSOKU_KAZU];
int donsok_f = 0;
//	ロード画面のアニメーション画像102枚
#define LOOD_MAX 102
//	ロード画面のアニメーション画像の変数
int lood_i[LOOD_MAX];
int lood_f = 0;
//	コインのアニメーション画像22枚
#define COIN_MAX 22
#define COIN_SAIZ 30
//	コインの画像用の変数
int coin_i[COIN_MAX];
//	コインの画像の座標
float coin_x1;		//	コインのＸ座標
float coin_y1;		//	コインのＹ座標
float coin_x2;
float coin_y2;
float coin_x3;
float coin_y3;

int coin_f = 0;
int coin_speed;
//	サボテンのサイズ
#define SABOTEN_SAIZ  50
//	踊るサボテンのアニメーション画像41枚
#define SABOTEN_MAX 41
int saboten_i[SABOTEN_MAX];
int saboten_x;
int saboten_y;
int saboten_x2[4];
int saboten_y2[4];
int saboten_hp;
int saboten_f = 0;

//	砂漠の葉のアニメーション画像34枚
#define SABAKUNOHA_MAX 34
//	砂漠の葉のサイズ
#define SABAKUNOHA_SAIZ 50
#define SABAKUNOHA_KAZU 1000
#define SABAKUNOHA_KAZU2 2
//	砂漠の葉を描画する為の画像用変数
int sabakunoha_i[SABAKUNOHA_MAX];
float sabakunoha_x[SABAKUNOHA_KAZU];
float sabakunoha_y[SABAKUNOHA_KAZU];
float sabakunoha_x2[SABAKUNOHA_KAZU2];
float sabakunoha_y2[SABAKUNOHA_KAZU2];
int sabakunoha_m[SABAKUNOHA_KAZU];
int sabakunoha_f = 0;
int sabakunoha_shotf=0;
float sabakunoha_speed;
//	操作方法用の変数
float setumei_x;
float setumei_y;
float jyanpu_y;
float jyanpu_speed;
int jyanpu_SE;
#define GAMEORVER_MAX 76
int gameover_bg[GAMEORVER_MAX];
int gameover_f = 0;
int shot_num = 0;

#define PRAMID_MAX 32
int pramid_bg[PRAMID_MAX];
int pramid_f = 0;

#define MEISON_SAIZ 30
int meison1_i;
int meison2_i;
int meison3_i;
float meison_x;
float meison_y;
float meisob_speed;
int meison_hp=3;
//	SE
int coin_SE;
int butukaru_SE;

#define ENN_MAX 24
#define ENN_SAIZ 50
#define ENN_KAUZ 1000
int enn_i[ENN_MAX];
float enn_x[ENN_KAUZ];
float enn_y[ENN_KAUZ];
int enn_f = 0;
int enn_shotf = 0;
int enn_m[ENN_KAUZ];

#define CRIA_MAX 16
int cria_bg[CRIA_MAX];
int cria_f = 0;


//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	srand((unsigned)time(NULL));
	//	プレイヤーの画像の読み込み
	mario_i = LoadGraph("ranmario/f1luvt25bso44e64xS1190_0.png");
	//	プレイヤーの初期座標
	mario_x = 100.0f;
	mario_y = 400.0f;
	//	プレイヤーの初期スピード
	mario_speed = 0.0f;
	
	//	ロード画面から開始
	scene_num = SCENE_LOAD;
	//	障害物のアニメーション画像の配列0番から13番(14枚)
	donsok_i[0]  = LoadGraph("donsoku14/pgp7gc7eenfg6tfEhee977_0.png");
	donsok_i[1]  = LoadGraph("donsoku14/pgp7gc7eenfg6tfEhee977_1.png");
	donsok_i[2]  = LoadGraph("donsoku14/pgp7gc7eenfg6tfEhee977_2.png");
	donsok_i[3]  = LoadGraph("donsoku14/pgp7gc7eenfg6tfEhee977_3.png");
	donsok_i[4]  = LoadGraph("donsoku14/pgp7gc7eenfg6tfEhee977_4.png");
	donsok_i[5]  = LoadGraph("donsoku14/pgp7gc7eenfg6tfEhee977_5.png");
	donsok_i[6]  = LoadGraph("donsoku14/pgp7gc7eenfg6tfEhee977_6.png");
	donsok_i[7]  = LoadGraph("donsoku14/pgp7gc7eenfg6tfEhee977_7.png");
	donsok_i[8]  = LoadGraph("donsoku14/pgp7gc7eenfg6tfEhee977_8.png");
	donsok_i[9]  = LoadGraph("donsoku14/pgp7gc7eenfg6tfEhee977_9.png");
	donsok_i[10] = LoadGraph("donsoku14/pgp7gc7eenfg6tfEhee977_10.png");
	donsok_i[11] = LoadGraph("donsoku14/pgp7gc7eenfg6tfEhee977_11.png");
	donsok_i[12] = LoadGraph("donsoku14/pgp7gc7eenfg6tfEhee977_12.png");
	donsok_i[13] = LoadGraph("donsoku14/pgp7gc7eenfg6tfEhee977_13.png");
	
	//	ロード画面のアニメーション画像の配列0番から101番(102枚)
	lood_i[0]  = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-0.gif");
	lood_i[1]  = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-1.gif");
	lood_i[2]  = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-2.gif");
	lood_i[3]  = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-3.gif");
	lood_i[4]  = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-4.gif");
	lood_i[5]  = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-5.gif");
	lood_i[6]  = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-6.gif");
	lood_i[7]  = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-7.gif");
	lood_i[8]  = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-8.gif");
	lood_i[9]  = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-9.gif");
	lood_i[10] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-10.gif");
	lood_i[11] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-11.gif");
	lood_i[12] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-12.gif");
	lood_i[13] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-13.gif");
	lood_i[14] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-14.gif");
	lood_i[15] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-15.gif");
	lood_i[16] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-16.gif");
	lood_i[17] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-17.gif");
	lood_i[18] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-18.gif");
	lood_i[19] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-19.gif");
	lood_i[20] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-20.gif");
	lood_i[21] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-21.gif");
	lood_i[22] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-22.gif");
	lood_i[23] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-23.gif");
	lood_i[24] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-24.gif");
	lood_i[25] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-25.gif");
	lood_i[26] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-26.gif");
	lood_i[27] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-27.gif");
	lood_i[28] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-28.gif");
	lood_i[29] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-29.gif");
	lood_i[30] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-30.gif");
	lood_i[31] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-31.gif");
	lood_i[32] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-32.gif");
	lood_i[33] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-33.gif");
	lood_i[34] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-34.gif");
	lood_i[35] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-35.gif");
	lood_i[36] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-36.gif");
	lood_i[37] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-37.gif");
	lood_i[38] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-38.gif");
	lood_i[39] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-39.gif");
	lood_i[40] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-40.gif");
	lood_i[41] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-41.gif");
	lood_i[42] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-42.gif");
	lood_i[43] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-43.gif");
	lood_i[44] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-44.gif");
	lood_i[45] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-45.gif");
	lood_i[46] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-46.gif");
	lood_i[47] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-47.gif");
	lood_i[48] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-48.gif");
	lood_i[49] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-49.gif");
	lood_i[50] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-50.gif");
	lood_i[51] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-51.gif");
	lood_i[52] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-52.gif");
	lood_i[53] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-53.gif");
	lood_i[54] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-54.gif");
	lood_i[55] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-55.gif");
	lood_i[56] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-56.gif");
	lood_i[57] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-57.gif");
	lood_i[58] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-58.gif");
	lood_i[59] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-59.gif");
	lood_i[60] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-60.gif");
	lood_i[61] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-61.gif");
	lood_i[62] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-62.gif");
	lood_i[63] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-63.gif");
	lood_i[64] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-64.gif");
	lood_i[65] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-65.gif");
	lood_i[66] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-66.gif");
	lood_i[67] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-67.gif");
	lood_i[68] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-68.gif");
	lood_i[69] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-69.gif");
	lood_i[70] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-70.gif");
	lood_i[71] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-71.gif");
	lood_i[72] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-72.gif");
	lood_i[73] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-73.gif");
	lood_i[74] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-74.gif");
	lood_i[75] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-75.gif");
	lood_i[76] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-76.gif");
	lood_i[77] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-77.gif");
	lood_i[78] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-78.gif");
	lood_i[79] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-79.gif");
	lood_i[80] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-80.gif");
	lood_i[81] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-81.gif");
	lood_i[82] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-82.gif");
	lood_i[83] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-83.gif");
	lood_i[84] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-84.gif");
	lood_i[85] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-85.gif");
	lood_i[86] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-86.gif");
	lood_i[87] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-87.gif");
	lood_i[88] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-88.gif");
	lood_i[89] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-89.gif");
	lood_i[90] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-90.gif");
	lood_i[91] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-91.gif");
	lood_i[92] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-92.gif");
	lood_i[93] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-93.gif");
	lood_i[94] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-94.gif");
	lood_i[95] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-95.gif");
	lood_i[96] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-96.gif");
	lood_i[97] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-97.gif");
	lood_i[98] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-98.gif");
	lood_i[99] = LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-99.gif");
	lood_i[100]= LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-100.gif");
	lood_i[101]= LoadGraph("imageonline.co-102/n56fsOvz2a-imageonline.co-23405-101.gif");
	
	//	コインのアニメーション画像の配列０番から21番(22枚)
	for (int i = 0; i < COIN_MAX; i++) {
		char buff[256];
		sprintf(buff, "coin22/ejcos3dc6hld1qz3FQB873_%d.png", i);
		coin_i[i] = LoadGraph(buff);
	}

	
	donsoku_x[0] = 200;
	donsoku_y[0] = 200;
	donsoku_x[1] = 400;
	donsoku_y[1] = 200;
	donsoku_x[2] = 600;
	donsoku_y[2] = 200;
	coin_x1 = 760.0f;
	coin_y1 = 350.0f;
	//	１：読み込み処理を非同期にします
	//	（ここから下に書いている読み込み関数が非同期処理になります）
	SetUseASyncLoadFlag( TRUE );

	//	テストファイルの読み込み
	for( int i = 0; i < TEST_MAX; i++ ){
		test_image[i] = LoadGraph( "data/test.png" );
	}

	//	砂漠の背景アニメーション画像の配列0番から9番(10枚)
	bg_image[0] = LoadGraph("sabaku10/hujki82gofkhbGp1b0L1e7_0.gif");
	bg_image[1] = LoadGraph("sabaku10/hujki82gofkhbGp1b0L1e7_1.gif");
	bg_image[2] = LoadGraph("sabaku10/hujki82gofkhbGp1b0L1e7_2.gif");
	bg_image[3] = LoadGraph("sabaku10/hujki82gofkhbGp1b0L1e7_3.gif");
	bg_image[4] = LoadGraph("sabaku10/hujki82gofkhbGp1b0L1e7_4.gif");
	bg_image[5] = LoadGraph("sabaku10/hujki82gofkhbGp1b0L1e7_5.gif");
	bg_image[6] = LoadGraph("sabaku10/hujki82gofkhbGp1b0L1e7_6.gif");
	bg_image[7] = LoadGraph("sabaku10/hujki82gofkhbGp1b0L1e7_7.gif");
	bg_image[8] = LoadGraph("sabaku10/hujki82gofkhbGp1b0L1e7_8.gif");
	bg_image[9] = LoadGraph("sabaku10/hujki82gofkhbGp1b0L1e7_9.gif");

	
	//	砂漠の川の背景アニメーション画像の配列０番から19番(20枚)
	bg1_i[0]  = LoadGraph("kawa20/h5k8cul28f76dMv0d7j9da_0.gif");
	bg1_i[1]  = LoadGraph("kawa20/h5k8cul28f76dMv0d7j9da_1.gif");
	bg1_i[2]  = LoadGraph("kawa20/h5k8cul28f76dMv0d7j9da_2.gif");
	bg1_i[3]  = LoadGraph("kawa20/h5k8cul28f76dMv0d7j9da_3.gif");
	bg1_i[4]  = LoadGraph("kawa20/h5k8cul28f76dMv0d7j9da_4.gif");
	bg1_i[5]  = LoadGraph("kawa20/h5k8cul28f76dMv0d7j9da_5.gif");
	bg1_i[6]  = LoadGraph("kawa20/h5k8cul28f76dMv0d7j9da_6.gif");
	bg1_i[7]  = LoadGraph("kawa20/h5k8cul28f76dMv0d7j9da_7.gif");
	bg1_i[8]  = LoadGraph("kawa20/h5k8cul28f76dMv0d7j9da_8.gif");
	bg1_i[9]  = LoadGraph("kawa20/h5k8cul28f76dMv0d7j9da_9.gif");
	bg1_i[10] = LoadGraph("kawa20/h5k8cul28f76dMv0d7j9da_10.gif");
	bg1_i[11] = LoadGraph("kawa20/h5k8cul28f76dMv0d7j9da_11.gif");
	bg1_i[12] = LoadGraph("kawa20/h5k8cul28f76dMv0d7j9da_12.gif");
	bg1_i[13] = LoadGraph("kawa20/h5k8cul28f76dMv0d7j9da_13.gif");
	bg1_i[14] = LoadGraph("kawa20/h5k8cul28f76dMv0d7j9da_14.gif");
	bg1_i[15] = LoadGraph("kawa20/h5k8cul28f76dMv0d7j9da_15.gif");
	bg1_i[16] = LoadGraph("kawa20/h5k8cul28f76dMv0d7j9da_16.gif");
	bg1_i[17] = LoadGraph("kawa20/h5k8cul28f76dMv0d7j9da_17.gif");
	bg1_i[18] = LoadGraph("kawa20/h5k8cul28f76dMv0d7j9da_18.gif");
	bg1_i[19] = LoadGraph("kawa20/h5k8cul28f76dMv0d7j9da_19.gif");
	
	//	砂漠の背景アニメーション画像２の配列０番から25番(26枚)
	bg_sabaku[0] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_0.gif");
	bg_sabaku[1] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_1.gif");
	bg_sabaku[2] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_2.gif");
	bg_sabaku[3] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_3.gif");
	bg_sabaku[4] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_4.gif");
	bg_sabaku[5] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_5.gif");
	bg_sabaku[6] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_6.gif");
	bg_sabaku[7] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_7.gif");
	bg_sabaku[8] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_8.gif");
	bg_sabaku[9] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_9.gif");
	bg_sabaku[10] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_10.gif");
	bg_sabaku[11] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_11.gif");
	bg_sabaku[12] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_12.gif");
	bg_sabaku[13] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_13.gif");
	bg_sabaku[14] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_14.gif");
	bg_sabaku[15] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_15.gif");
	bg_sabaku[16] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_16.gif");
	bg_sabaku[17] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_17.gif");
	bg_sabaku[18] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_18.gif");
	bg_sabaku[19] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_19.gif");
	bg_sabaku[20] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_20.gif");
	bg_sabaku[21] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_21.gif");
	bg_sabaku[22] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_22.gif");
	bg_sabaku[23] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_23.gif");
	bg_sabaku[24] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_24.gif");
	bg_sabaku[25] = LoadGraph("sabku_26/8k4i4lo06n8g33ra65m0d5_25.gif");

	//	踊るサボテンのアニメーション画像の配列０番から40番(41枚)
	saboten_i[0] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_0.gif");
	saboten_i[1] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_1.gif");
	saboten_i[2] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_2.gif");
	saboten_i[3] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_3.gif");
	saboten_i[4] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_4.gif");
	saboten_i[5] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_5.gif");
	saboten_i[6] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_6.gif");
	saboten_i[7] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_7.gif");
	saboten_i[8] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_8.gif");
	saboten_i[9] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_9.gif");
	saboten_i[10] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_10.gif");
	saboten_i[11] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_11.gif");
	saboten_i[12] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_12.gif");
	saboten_i[13] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_13.gif");
	saboten_i[14] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_14.gif");
	saboten_i[15] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_15.gif");
	saboten_i[16] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_16.gif");
	saboten_i[17] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_17.gif");
	saboten_i[18] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_18.gif");
	saboten_i[19] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_19.gif");
	saboten_i[20] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_20.gif");
	saboten_i[21] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_21.gif");
	saboten_i[22] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_22.gif");
	saboten_i[23] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_23.gif");
	saboten_i[24] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_24.gif");
	saboten_i[25] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_25.gif");
	saboten_i[26] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_26.gif");
	saboten_i[27] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_27.gif");
	saboten_i[28] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_28.gif");
	saboten_i[29] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_29.gif");
	saboten_i[30] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_30.gif");
	saboten_i[31] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_31.gif");
	saboten_i[32] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_32.gif");
	saboten_i[33] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_33.gif");
	saboten_i[34] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_34.gif");
	saboten_i[35] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_35.gif");
	saboten_i[36] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_36.gif");
	saboten_i[37] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_37.gif");
	saboten_i[38] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_38.gif");
	saboten_i[39] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_39.gif");
	saboten_i[40] = LoadGraph("saboten_41/71mif9ebif2ve78U5Ti4d7_40.gif");
	
	//	砂漠の葉のアニメーション画像の配列０番から33番(34枚)
	sabakunoha_i[0] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_0.png");
	sabakunoha_i[1] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_1.png");
	sabakunoha_i[2] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_2.png");
	sabakunoha_i[3] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_3.png");
	sabakunoha_i[4] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_4.png");
	sabakunoha_i[5] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_5.png");
	sabakunoha_i[6] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_6.png");
	sabakunoha_i[7] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_7.png");
	sabakunoha_i[8] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_8.png");
	sabakunoha_i[9] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_9.png");
	sabakunoha_i[10] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_10.png");
	sabakunoha_i[11] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_11.png");
	sabakunoha_i[12] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_12.png");
	sabakunoha_i[13] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_13.png");
	sabakunoha_i[14] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_14.png");
	sabakunoha_i[15] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_15.png");
	sabakunoha_i[16] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_16.png");
	sabakunoha_i[17] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_17.png");
	sabakunoha_i[18] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_18.png");
	sabakunoha_i[19] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_19.png");
	sabakunoha_i[20] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_20.png");
	sabakunoha_i[21] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_21.png");
	sabakunoha_i[22] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_22.png");
	sabakunoha_i[23] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_23.png");
	sabakunoha_i[24] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_24.png");
	sabakunoha_i[25] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_25.png");
	sabakunoha_i[26] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_26.png");
	sabakunoha_i[27] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_27.png");
	sabakunoha_i[28] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_28.png");
	sabakunoha_i[29] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_29.png");
	sabakunoha_i[30] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_30.png");
	sabakunoha_i[31] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_31.png");
	sabakunoha_i[32] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_32.png");
	sabakunoha_i[33] = LoadGraph("sabakunoha_34/4pdqrl2agecg6QWloHn3f7_33.png");

	//	ゲームオーバーのアニメーション背景画像配列０番から75番(７６枚)
	gameover_bg[0] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_0.gif");
	gameover_bg[1] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_1.gif");
	gameover_bg[2] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_2.gif");
	gameover_bg[3] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_3.gif");
	gameover_bg[4] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_4.gif");
	gameover_bg[5] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_5.gif");
	gameover_bg[6] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_6.gif");
	gameover_bg[7] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_7.gif");
	gameover_bg[8] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_8.gif");
	gameover_bg[9] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_9.gif");
	gameover_bg[10] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_10.gif");
	gameover_bg[11] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_11.gif");
	gameover_bg[12] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_12.gif");
	gameover_bg[13] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_13.gif");
	gameover_bg[14] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_14.gif");
	gameover_bg[15] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_15.gif");
	gameover_bg[16] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_16.gif");
	gameover_bg[17] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_17.gif");
	gameover_bg[18] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_18.gif");
	gameover_bg[19] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_19.gif");
	gameover_bg[20] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_20.gif");
	gameover_bg[21] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_21.gif");
	gameover_bg[22] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_22.gif");
	gameover_bg[23] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_23.gif");
	gameover_bg[24] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_24.gif");
	gameover_bg[25] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_25.gif");
	gameover_bg[26] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_26.gif");
	gameover_bg[27] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_27.gif");
	gameover_bg[28] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_28.gif");
	gameover_bg[29] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_29.gif");
	gameover_bg[30] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_30.gif");
	gameover_bg[31] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_31.gif");
	gameover_bg[32] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_32.gif");
	gameover_bg[33] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_33.gif");
	gameover_bg[34] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_34.gif");
	gameover_bg[35] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_35.gif");
	gameover_bg[36] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_36.gif");
	gameover_bg[37] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_37.gif");
	gameover_bg[38] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_38.gif");
	gameover_bg[39] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_39.gif");
	gameover_bg[40] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_40.gif");
	gameover_bg[41] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_41.gif");
	gameover_bg[42] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_42.gif");
	gameover_bg[43] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_43.gif");
	gameover_bg[44] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_44.gif");
	gameover_bg[45] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_45.gif");
	gameover_bg[46] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_46.gif");
	gameover_bg[47] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_47.gif");
	gameover_bg[48] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_48.gif");
	gameover_bg[49] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_49.gif");
	gameover_bg[50] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_50.gif");
	gameover_bg[51] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_51.gif");
	gameover_bg[52] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_52.gif");
	gameover_bg[53] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_53.gif");
	gameover_bg[54] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_54.gif");
	gameover_bg[55] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_55.gif");
	gameover_bg[56] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_56.gif");
	gameover_bg[57] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_57.gif");
	gameover_bg[58] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_58.gif");
	gameover_bg[59] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_59.gif");
	gameover_bg[60] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_60.gif");
	gameover_bg[61] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_61.gif");
	gameover_bg[62] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_62.gif");
	gameover_bg[63] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_63.gif");
	gameover_bg[64] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_64.gif");
	gameover_bg[65] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_65.gif");
	gameover_bg[66] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_66.gif");
	gameover_bg[67] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_67.gif");
	gameover_bg[68] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_68.gif");
	gameover_bg[69] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_69.gif");
	gameover_bg[70] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_70.gif");
	gameover_bg[71] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_71.gif");
	gameover_bg[72] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_72.gif");
	gameover_bg[73] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_73.gif");
	gameover_bg[74] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_74.gif");
	gameover_bg[75] = LoadGraph("gameover_76/em64ft2am2vk7iJ4Cg15c4_75.gif");
	
	


	//	SE
	jyanpu_SE = LoadSoundMem("SE/se_jump_001.wav");
	coin_SE = LoadSoundMem("SE/coin07.mp3");
	butukaru_SE = LoadSoundMem("SE/Hit02-1.mp3");

	loadfile_max = GetASyncLoadNum();

	loadfile_count = 0;
	
	

	saboten_hp = 3;
	//sabakunoha_x[0] = 100;
	//sabakunoha_y[0] = 400;
	for (int i = 0; i < SABAKUNOHA_KAZU; i++) {
		sabakunoha_x[i];
		sabakunoha_y[i];
		sabakunoha_m[i] = MODE_WAIT;
	}
	

	setumei_x = 600.0f;
	setumei_y = 55.0f;

	jyanpu_y = 100.0f;
	jyanpu_speed = 0.0f;

	
	coin_x2 = -200.0f;
	coin_y2 = -200.0f;
	coin_x3 = -200.0f;
	coin_y3 = -200.0f;

	//	ピラミッドのアニメーション画像配列０番から31番(32枚)
	pramid_bg[0] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_0.gif");
	pramid_bg[1] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_1.gif");
	pramid_bg[2] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_2.gif");
	pramid_bg[3] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_3.gif");
	pramid_bg[4] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_4.gif");
	pramid_bg[5] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_5.gif");
	pramid_bg[6] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_6.gif");
	pramid_bg[7] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_7.gif");
	pramid_bg[8] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_8.gif");
	pramid_bg[9] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_9.gif");
	pramid_bg[10] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_10.gif");
	pramid_bg[11] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_11.gif");
	pramid_bg[12] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_12.gif");
	pramid_bg[13] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_13.gif");
	pramid_bg[14] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_14.gif");
	pramid_bg[15] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_15.gif");
	pramid_bg[16] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_16.gif");
	pramid_bg[17] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_17.gif");
	pramid_bg[18] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_18.gif");
	pramid_bg[19] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_19.gif");
	pramid_bg[20] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_20.gif");
	pramid_bg[21] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_21.gif");
	pramid_bg[22] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_22.gif");
	pramid_bg[23] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_23.gif");
	pramid_bg[24] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_24.gif");
	pramid_bg[25] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_25.gif");
	pramid_bg[26] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_26.gif");
	pramid_bg[27] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_27.gif");
	pramid_bg[28] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_28.gif");
	pramid_bg[29] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_29.gif");
	pramid_bg[30] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_30.gif");
	pramid_bg[31] = LoadGraph("pramid_32/520et1i1e4n03SE6PJG6c3_31.gif");

	meison1_i = LoadGraph("data/165-1651381_illuminati-confirmed-pixel-art-minecraft1.png");
	meison2_i = LoadGraph("data/165-1651381_illuminati-confirmed-pixel-art-minecraft2.png");
	meison3_i = LoadGraph("data/165-1651381_illuminati-confirmed-pixel-art-minecraft3.png");
	x_speed = 3.0f;
	y_speed = 3.0f;
	meison_x = 200.0f;
	meison_y = 200.0f;
	meisob_speed = 8.0f;
	for (int i = 0; i < SABAKUNOHA_KAZU2; i++) {
		sabakunoha_x2[i];
		sabakunoha_y2[i];
	}

	sabakunoha_x2[0] = 300.0f;
	sabakunoha_y2[0] = 400.0f;
	sabakunoha_x2[1] = 500.0f;
	sabakunoha_y2[1] = 400.0f;
	sabakunoha_speed = 3.0f;
	sabakunoha_speed = 0.0;

	//	円のアニメーション画像配列０番から23番(24枚)
	enn_i[0] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_0.png");
	enn_i[1] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_1.png");
	enn_i[2] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_2.png");
	enn_i[3] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_3.png");
	enn_i[4] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_4.png");
	enn_i[5] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_5.png");
	enn_i[6] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_6.png");
	enn_i[7] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_7.png");
	enn_i[8] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_8.png");
	enn_i[9] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_9.png");
	enn_i[10] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_10.png");
	enn_i[11] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_11.png");
	enn_i[12] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_12.png");
	enn_i[13] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_13.png");
	enn_i[14] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_14.png");
	enn_i[15] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_15.png");
	enn_i[16] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_16.png");
	enn_i[17] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_17.png");
	enn_i[18] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_18.png");
	enn_i[19] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_19.png");
	enn_i[20] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_20.png");
	enn_i[21] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_21.png");
	enn_i[22] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_22.png");
	enn_i[23] = LoadGraph("mawaru_24/68isb6c257jpflQUfjo2eb_23.png");

	for (int i = 0; i < ENN_KAUZ; i++) {
		enn_x[i];
		enn_y[i];
		enn_m[i] = MODE_WAIT;
	}

	//	クリア画面のアニメーション画像の配列０番から15番(16枚)
	for (int i = 0; i < CRIA_MAX; i++) {
		char buff2[256];
		sprintf(buff2, "nazo_16/72it2llcekph0xal7GE0cc_%d.gif", i);
		cria_bg[i] = LoadGraph(buff2);
	}
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{		

	switch( scene_num ){
	

	case SCENE_LOAD:	//	ロード中

		//	読み込み中のファイル数の取得
		loadfile_count = GetASyncLoadNum();

		//	読み込みファイル数が０になったら
		if( loadfile_count == 0 ){
			//	シーンを切り替えます
			scene_num = SCENE_TAITOL;
			PlayMusic("BGM/サンシャインビーチ.mp3", DX_PLAYTYPE_LOOP);
		}

		break;
case SCENE_TAITOL:
	if (cnt < 1) {
		if (PushHitKey(KEY_INPUT_SPACE)) {
			jyanpu_speed = -8.0f;
			PlaySoundMem(jyanpu_SE, DX_PLAYTYPE_BACK);
			cnt++;
		}
	}
	if (setumei_x > 705.0f) {
		setumei_x = 705.0f;
	}
	if (setumei_x < 500.0f) {
		setumei_x = 500.0f;
	}
	jyanpu_speed += 0.3f;
	jyanpu_y += jyanpu_speed;
	if (jyanpu_y >= 200.0f) {
		jyanpu_y = 200.0f;
		cnt = 0;
	}
	//	Aボタンを押したらゲームが開始
	if (PushHitKey(KEY_INPUT_A)) {
		scene_num = SCENE_GAME1;		
		PlayMusic("BGM/vigorous_terrain.ogg", DX_PLAYTYPE_LOOP);
		//	プレイヤーの初期座標
		mario_x = 100.0f;
		mario_y = 400.0f;
		donsoku_x[0] = 200;
		donsoku_y[0] = 200;
		donsoku_x[1] = 400;
		donsoku_y[1] = 200;
		donsoku_x[2] = 600;
		donsoku_y[2] = 200;
		for (int i = 0; i < SABAKUNOHA_KAZU2; i++) {
			sabakunoha_x2[i];
			sabakunoha_y2[i];
		}
		donsoku_y[2] = 200;
		coin_x1 = 760;
		coin_y1 = 350;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		setumei_x += 2.0f;
	}
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		setumei_x -= 2.0f;
	}
		bg_f++;  // フレームごとにbg_fをインクリメント
		if (bg1_f >= BG1_MAX) {
			bg1_f = 0;  // bg_fがBG_MAX以上になったら0にリセット
		}
		if (PushHitKey(KEY_INPUT_O)) {
			scene_num = SCENE_GAME3;
			PlayMusic("BGM/011---fever-pitch.mp3", DX_PLAYTYPE_LOOP);
		}
		break;

	case SCENE_GAME1:

		//	ジャンプカウントの数
		if (cnt < 1) {

			//	スペースを押したらジャンプする
			if (PushHitKey(KEY_INPUT_SPACE)) {
				mario_speed = -11.0f;
				PlaySoundMem(jyanpu_SE, DX_PLAYTYPE_BACK);
				mario_i = LoadGraph("ranmario/f1luvt25bso44e64xS1190_1.png");
				cnt++;
			}
			else
			{
				mario_i = LoadGraph("ranmario/f1luvt25bso44e64xS1190_0.png");

			}
		}
		//	右キーを押したら右に移動
		if (CheckHitKey(KEY_INPUT_RIGHT)) {
			mario_x += 2.0f;
			mario_i = LoadGraph("ranmario/f1luvt25bso44e64xS1190_1.png");
		}
		//	左キーを押したら左に移動
		if (CheckHitKey(KEY_INPUT_LEFT)) {
			mario_x -= 2.0f;
			mario_i = LoadGraph("ranmario/f1luvt25bso44e64xS1190_1.1.png");
		}
		//	障害物とプレイヤーの当たり判定
		for (int i = 0; i < DONSOKU_KAZU; i++) {
			if (CheckBoxHit(donsoku_x[i], donsoku_y[i], DONSOKU_SAIZ, DONSOKU_SAIZ, mario_x, mario_y, MARIO_SAIZ, MARIO_SAIZ)) {
				
				if (mario_y >= 400.0f) {
					mario_y = 400.0f;
					mario_x = 100.0f;
					cnt = 0;
				}
				else
				{
					if (mario_y >= donsoku_y[i]) {
						mario_y = donsoku_y[i];
						mario_x = donsoku_x[i];
						cnt = 0;
					}
				}

			}
		}
		//	コインとプレイヤーの当たり判定
		if (CheckBoxHit(coin_x1, coin_y1, COIN_SAIZ, COIN_SAIZ, mario_x, mario_y, MARIO_SAIZ, MARIO_SAIZ)) {
			scene_num = SCENE_GAME2;
			PlaySoundMem(coin_SE, DX_PLAYTYPE_BACK);
			saboten_x = 10;
			saboten_y = 400;
			saboten_hp = 3;
			coin_x2 = -200.0f;
			coin_y2 = -200.0f;
			for (int i = 0; i < SABAKUNOHA_KAZU; i++) {
				sabakunoha_x[i];
				sabakunoha_y[i];
				sabakunoha_m[i] = MODE_WAIT;
			}
			
		}
		for (int i = 0; i < SABAKUNOHA_KAZU2; i++) {
			if (CheckBoxHit(sabakunoha_x2[i], sabakunoha_y2[i], SABAKUNOHA_SAIZ, SABAKUNOHA_SAIZ, mario_x, mario_y, MARIO_SAIZ, MARIO_SAIZ)) {
				scene_num = SCENE_GAMEOVER;
				PlayMusic("BGM/354_BPM180.mp3", DX_PLAYTYPE_LOOP);
			}
		}
		//	プレイヤーが画面外に行かなくなる
		if (mario_x > 880.0f) {
			mario_x = 880.0f;
		}
		if (mario_x < 0.0f) {
			mario_x = 0.0f;
		}
		bg_f++;  // フレームごとにbg_fをインクリメント
		if (bg_f >= BG_MAX) {
			bg_f = 0;  // bg_fがBG_MAX以上になったら0にリセット
		}
		//	常にスピードの値を増やしていく
		mario_speed += 0.3f;

		//	プレイヤーの座標移動
		mario_y += mario_speed;
		if (mario_y >= 400.0f ) {
			mario_y = 400.0f;
			mario_x = 100.0f;
			cnt = 0;
		}

		//	障害物を動かす処理動かんどうしよう
		for (int i = 0; i < SABAKUNOHA_KAZU2; i++) {
			sabakunoha_x2[i] += sabakunoha_speed;
			if (sabakunoha_x2[i] <= 100.0f) {
				sabakunoha_speed *= -1.0f;
			}
			if (sabakunoha_x2[i] >= 300.0f) {
				sabakunoha_speed *= -1.0f;
			}
		}

		if (PushHitKey(KEY_INPUT_N)) {
			scene_num = SCENE_TAITOL;
			PlayMusic("BGM/サンシャインビーチ.mp3", DX_PLAYTYPE_LOOP);
		}
		break;
	case SCENE_GAME2:

		if (mario_x > 880.0f) {
			mario_x = 880.0f;
		}
		if (mario_x < 0.0f) {
			mario_x = 0.0f;
		}
		if (cnt < 1) {
			
			if (PushHitKey(KEY_INPUT_SPACE)) {
				mario_speed = -11.0f;
				PlaySoundMem(jyanpu_SE, DX_PLAYTYPE_BACK);
				mario_i = LoadGraph("ranmario/f1luvt25bso44e64xS1190_1.1.png");
				cnt++;
			}
			else
			{
				mario_i = LoadGraph("ranmario/f1luvt25bso44e64xS1190_0.1.png");

			}
		}
		if (CheckHitKey(KEY_INPUT_RIGHT)) {
			mario_x += 2.0f;
			mario_i = LoadGraph("ranmario/f1luvt25bso44e64xS1190_1.png");
		}

		if (CheckHitKey(KEY_INPUT_LEFT)) {
			mario_x -= 2.0f;
			mario_i = LoadGraph("ranmario/f1luvt25bso44e64xS1190_1.1.png");
		}
		bg2_f++;  // フレームごとにbg_fをインクリメント
		if (bg2_f >= SABAK_MAX) {
			bg2_f = 0;  // bg_fがBG_MAX以上になったら0にリセット
		}
		mario_speed += 0.3f;
		mario_y += mario_speed;
		if (mario_y >= 400.0f) {
			mario_y = 400.0f;
			cnt = 0;
		}
		sabakunoha_shotf--;
		if (sabakunoha_shotf < 0) {
			sabakunoha_shotf = 60;
			sabakunoha_m[shot_num] = MODE_MOVE;
			sabakunoha_x[shot_num] = saboten_x;
			sabakunoha_y[shot_num] = saboten_y;
			shot_num++;
			if (shot_num >= SABAKUNOHA_KAZU) {
				shot_num = 0;
			}
		}

		for (int i = 0; i < SABAKUNOHA_KAZU; i++) {
			sabakunoha_x[i] += 10.0f;
		}
		for (int i = 0; i < SABAKUNOHA_KAZU; i++) {
			if (CheckBoxHit(sabakunoha_x[i], sabakunoha_y[i], SABAKUNOHA_SAIZ, SABAKUNOHA_SAIZ, mario_x, mario_y, MARIO_SAIZ, MARIO_SAIZ)) {
				sabakunoha_x[i] = mario_x += 2.0f;
			}
		}
			
		if (CheckBoxHit(saboten_x, saboten_y, SABOTEN_SAIZ, SABOTEN_SAIZ, mario_x, mario_y, MARIO_SAIZ, MARIO_SAIZ)) {
			PlaySoundMem(butukaru_SE, DX_PLAYTYPE_BACK);
			mario_x = 800.0f;
			mario_y = 400.0f;
			
			saboten_hp -= 1;
			if (saboten_hp < 1) {
				saboten_x = -200;
				saboten_y = -200;
				coin_x2 = 100.0f;
				coin_y2 = 200.0f;
			}
			
		}

		//	コインとプレイヤーの当たり判定
		if (CheckBoxHit(coin_x2, coin_y2, COIN_SAIZ, COIN_SAIZ, mario_x, mario_y, MARIO_SAIZ, MARIO_SAIZ)) {
			PlaySoundMem(coin_SE, DX_PLAYTYPE_BACK);
			scene_num = SCENE_GAME3;
			meison_x = 360.0f;
			meison_y = 200.0f;
			meison_hp = 3;
			PlayMusic("BGM/251_BPM150.mp3", DX_PLAYTYPE_LOOP);
			for (int i = 0; i < ENN_KAUZ; i++) {
				enn_x[i];
				enn_y[i];
				enn_m[i] = MODE_WAIT;
			}
			mario_x = 100.0f;
			mario_y = 400.0f;
			mario_hp = 3;
			coin_x3 = -200.0f;
			coin_y3 = -200.0f;
		}
		//coin_speed += 2;
		//coin_x += coin_speed;
		mario_x += 0.8f;	
		if (PushHitKey(KEY_INPUT_N)) {
			scene_num = SCENE_TAITOL;
			PlayMusic("BGM/サンシャインビーチ.mp3", DX_PLAYTYPE_LOOP);
		}
		break;
	case SCENE_GAMEOVER:
		gameover_f++;
		if (gameover_f >= GAMEORVER_MAX) {
			gameover_f = 0;
		}
		if (PushHitKey(KEY_INPUT_N)) {
			scene_num = SCENE_TAITOL;
			PlayMusic("BGM/サンシャインビーチ.mp3", DX_PLAYTYPE_LOOP);
		}
		break;
	case SCENE_GAME3:
		if (mario_x > 880.0f) {
			mario_x = 880.0f;
		}
		if (mario_x < 0.0f) {
			mario_x = 0.0f;
		}
		//	ジャンプカウントの数
		if (cnt < 1) {

			//	スペースを押したらジャンプする
			if (PushHitKey(KEY_INPUT_SPACE)) {
				mario_speed = -10.0f;
				PlaySoundMem(jyanpu_SE, DX_PLAYTYPE_BACK);
				mario_i = LoadGraph("ranmario/f1luvt25bso44e64xS1190_1.png");
				cnt++;
			}
			else
			{
				mario_i = LoadGraph("ranmario/f1luvt25bso44e64xS1190_0.png");

			}
		}
		//	右キーを押したら右に移動
		if (CheckHitKey(KEY_INPUT_RIGHT)) {
			mario_x += 2.0f;
			mario_i = LoadGraph("ranmario/f1luvt25bso44e64xS1190_1.png");
		}
		//	左キーを押したら左に移動
		if (CheckHitKey(KEY_INPUT_LEFT)) {
			mario_x -= 2.0f;
			mario_i = LoadGraph("ranmario/f1luvt25bso44e64xS1190_1.1.png");
		}
		enn_shotf--;
		if (enn_shotf < 0) {
			enn_shotf = GetRandomI(10, 30);
			enn_m[shot_num] = MODE_MOVE;
			enn_x[shot_num] = meison_x+80.0f;
			enn_y[shot_num] = meison_y-80.0f;
			shot_num++;
			if (shot_num >= ENN_KAUZ) {
				shot_num = 0;
			}
		}
		//	ボスの移動
		meison_x += meisob_speed;
		if (meison_x < 0.0f || meison_x > 760.0f) {
			meisob_speed *= -1;
//			meison_x = GetRandomF(0.0f,750.0f);
		}

		if (CheckBoxHit(meison_x, meison_y, MEISON_SAIZ, MEISON_SAIZ, mario_x, mario_y, MARIO_SAIZ, MARIO_SAIZ)) {
			mario_x = 10.0f;
			mario_y = 400.0f;
			meison_hp -= 1;
			if (meison_hp < 1) {
				meison_x = 2200.0f;
				meison_y = 2200.0f;
				for (int i = 0; i < ENN_KAUZ; i++) {
					enn_x[i] = 2200.0f;
					enn_y[i] = 2200.0f;
					enn_m[i] = MODE_WAIT;
				}
					coin_x3 = 430.0f;
					coin_y3 = 100.0f;

			}

		}
		//	障害物とプレイヤーの当たり判定
		for (int i = 0; i < DONSOKU_KAZU; i++) {
			if (CheckBoxHit(donsoku_x[i], donsoku_y[i], DONSOKU_SAIZ, DONSOKU_SAIZ, mario_x, mario_y, MARIO_SAIZ, MARIO_SAIZ)) {

				if (mario_y >= 400.0f) {
					mario_y = 400.0f;
					mario_x = 100.0f;
					cnt = 0;
				}
				else
				{
					if (mario_y >= donsoku_y[i]) {
						mario_y = donsoku_y[i];
						mario_x = donsoku_x[i];
						cnt = 0;
					}
				}

			}

		}
		for (int i = 0;i < ENN_KAUZ;i++) {
			if (CheckBoxHit(enn_x[i], enn_y[i], MEISON_SAIZ, MEISON_SAIZ, mario_x, mario_y, MARIO_SAIZ, MARIO_SAIZ)) {
				enn_x[i] = 2000;
				enn_y[i] = 2000;
				enn_m[i] = MODE_WAIT;
				mario_hp -= 1;
				if (mario_hp < 1) {
					scene_num = SCENE_GAMEOVER2;
					PlayMusic("BGM/354_BPM180.mp3", DX_PLAYTYPE_LOOP);
				}
			
			}
		}
		if (CheckBoxHit(coin_x3, coin_y3, COIN_SAIZ, COIN_SAIZ, mario_x, mario_y, MARIO_SAIZ, MARIO_SAIZ)) {
			PlaySoundMem(coin_SE, DX_PLAYTYPE_BACK);
			scene_num = SCENE_GAMECRIA;
			PlayMusic("BGM/443_BPM120.mp3", DX_PLAYTYPE_LOOP);
		}
		donsoku_y[0] += y_speed;
		if (donsoku_y[0] <= 10.0f || donsoku_y[0] >= 400.0f) {
			y_speed *= -1;
		}
		donsoku_x[1] += x_speed;
		if (donsoku_x[1] <= 100.0f || donsoku_x[1] >= 800.0f) {
			x_speed *= -1;
		}
		donsoku_y[2] -= y_speed;
		if (donsoku_y[2] <= 10.0f || donsoku_y[2] >= 400.0f) {
			y_speed *= -1;
		}

		

		enn_f++;
		if (enn_f >= ENN_MAX) {
			enn_f = 0;
		}
		for (int i = 0; i < ENN_KAUZ; i++) {
			enn_y[i] += 10.0f;
		}
		pramid_f++;
		if (pramid_f >= PRAMID_MAX) {
			pramid_f = 0;
		}
		if (PushHitKey(KEY_INPUT_N)) {
			scene_num = SCENE_TAITOL;
			PlayMusic("BGM/サンシャインビーチ.mp3", DX_PLAYTYPE_LOOP);
		}
		//	常にスピードの値を増やしていく
		mario_speed += 0.3f;

		//	プレイヤーの座標移動
		mario_y += mario_speed;
		if (mario_y >= 400.0f) {
			mario_y = 400.0f;
			//mario_x = 100.0f;
			cnt = 0;
		}
		break;
		case SCENE_GAMEOVER2:
			gameover_f++;
			if (gameover_f >= GAMEORVER_MAX) {
				gameover_f = 0;
			}
			if (PushHitKey(KEY_INPUT_M)) {
				scene_num = SCENE_GAME3;
				mario_x = 10.0f;
				mario_y = 400.0f;
				mario_hp = 3;
				meison_x = 200.0f;
				meison_y = 200.0f;
				meison_hp = 3;
				donsoku_x[0] = 200;
				donsoku_y[0] = 200;
				donsoku_x[1] = 400;
				donsoku_y[1] = 200;
				donsoku_x[2] = 600;
				donsoku_y[2] = 200;
				coin_x3 = -200.0f;
				coin_y3 = -200.0f;
				for (int i = 0; i < ENN_KAUZ; i++) {
					enn_x[i];
					enn_y[i];
					enn_m[i] = MODE_WAIT;
				}
				PlayMusic("BGM/251_BPM150.mp3", DX_PLAYTYPE_LOOP);
			}
			break;
		case SCENE_GAMECRIA:
			cria_f++;
			if (cria_f >= CRIA_MAX) {
				cria_f = 0;
			}
			if (PushHitKey(KEY_INPUT_N)) {
				scene_num = SCENE_TAITOL;
				PlayMusic("BGM/サンシャインビーチ.mp3", DX_PLAYTYPE_LOOP);
			}
			break;
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	各シーンの描画
	switch( scene_num ){
	
	case SCENE_LOAD:
		//	ロード画面の描画
		for (int i = 0;i < LOOD_MAX-1;i++) {
			lood_f--;
			if (lood_f < 0) {
				lood_f = i;

				DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, lood_i[i], TRUE);

			}
		}
		break;
	case SCENE_TAITOL:
		for (int i = 0;i < BG1_MAX;i++) {
			bg1_f--;
			if (bg1_f < 0) {
				bg1_f = 20;
				DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, bg1_i[i], TRUE);
			}
		}
		ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
		SetFontSize(64);
		DrawString(100, 10, "砂漠の冒険", GetColor(0, 0, 0), GetColor(255, 255, 0));
		DrawString(100, 100, "Ａボタン\n　開始", GetColor(255, 255, 255),GetColor(255, 25, 25));
		SetFontSize(48);
		DrawString(600, 10, "操作方法", GetColor(255, 255, 255));
		DrawFormatStringF(setumei_x, setumei_y, GetColor(255, 255, 255), "←→：移動", TRUE);
		DrawFormatStringF(500.0f, jyanpu_y, GetColor(255, 255, 255), "スペース：ジャンプ", TRUE);
		SetFontSize(12);
		break;

	case SCENE_GAME1:
		//	背景画像の描画
		DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, bg_image[bg_f], TRUE);
		
		for (int i = 0; i < DONSOK_MAX - 1; i++) {
			donsok_f--;
			if (donsok_f < 0) {
				donsok_f = i;
				for (int d = 0; d < DONSOKU_KAZU; d++) {
					DrawGraph(donsoku_x[d], donsoku_y[d], donsok_i[i], TRUE);

				}
			}
		}		
		DrawGraphF(mario_x, mario_y, mario_i, TRUE);

		for (int i = 0;i < COIN_MAX;i++) {
			coin_f--;
			if (coin_f < 0) {
				coin_f = 22;
				DrawGraphF(coin_x1, coin_y1, coin_i[i], TRUE);
			}
		}
		sabakunoha_f++;
		if (sabakunoha_f >= SABAKUNOHA_MAX) {
			sabakunoha_f = 0;
		}
		
		DrawGraphF(sabakunoha_x2[0], sabakunoha_y2[0], sabakunoha_i[sabakunoha_f], TRUE);
		DrawGraphF(sabakunoha_x2[1], sabakunoha_y2[1], sabakunoha_i[sabakunoha_f], TRUE);
		break;

	case SCENE_GAME2:
		DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, bg_sabaku[bg2_f], TRUE);
		DrawGraphF(mario_x, mario_y, mario_i, TRUE);
		
		saboten_f++;
		if (saboten_f >= SABOTEN_MAX) {
			saboten_f = 0;
		}
		if (saboten_hp > 0) {
			DrawGraph(saboten_x, saboten_y, saboten_i[saboten_f], TRUE);
			SetFontSize(48);
			DrawFormatString(saboten_x + 30, saboten_y - 50, GetColor(25, 255, 25), "HP%d", saboten_hp);
			SetFontSize(12);
		}
		
		for (int i = 0; i < COIN_MAX; i++) {
			coin_f--;
			if (coin_f < 0) {
				coin_f = 22;
				DrawGraphF(coin_x2, coin_y2, coin_i[i], TRUE);
			}
		}
		
		sabakunoha_f++;
		if (sabakunoha_f >= SABAKUNOHA_MAX) {
			sabakunoha_f = 0;
		}
		for (int i = 0; i < SABAKUNOHA_KAZU; i++) {
			if (sabakunoha_m[i] == MODE_MOVE) {
				DrawGraphF(sabakunoha_x[i], sabakunoha_y[i], sabakunoha_i[sabakunoha_f], TRUE);
			}
		}

		break;
	case SCENE_GAMEOVER:
		DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, gameover_bg[gameover_f], TRUE);
		saboten_f++;
		if (saboten_f >= SABOTEN_MAX) {
			saboten_f = 0;
		}
		saboten_x2[0] = 10;
		saboten_y2[0] = 0;
		saboten_x2[1] = 850;
		saboten_y2[1] = 0;
		saboten_x2[2] = 10;
		saboten_y2[2] = 400;
		saboten_x2[3] = 850;
		saboten_y2[3] = 400;
		DrawGraph(saboten_x2[0], saboten_y2[0], saboten_i[saboten_f], TRUE);
		DrawGraph(saboten_x2[1], saboten_y2[1], saboten_i[saboten_f], TRUE);
		DrawGraph(saboten_x2[2], saboten_y2[2], saboten_i[saboten_f], TRUE);
		DrawGraph(saboten_x2[3], saboten_y2[3], saboten_i[saboten_f], TRUE);
		ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
		SetFontSize(64);
		DrawFormatString(200, 10, GetColor(25, 255, 25), "Nボタンでタイトルへ", GetColor(255,0,0),TRUE);
		SetFontSize(12);
		break;

	case SCENE_GAME3:
		
		DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, pramid_bg[pramid_f], TRUE);
		
		if (meison_hp >= 1) {
			DrawGraphF(meison_x, setumei_y, meison3_i, TRUE);
			SetFontSize(48);
			DrawFormatString(10, 10, GetColor(255, 25, 25), "HP%d", meison_hp);
			SetFontSize(12);
		}	
		if (meison_hp >= 2) {
			DrawGraphF(meison_x, setumei_y, meison2_i, TRUE);
			SetFontSize(48);
			DrawFormatString(10, 10, GetColor(255, 255, 25), "HP%d", meison_hp);
			SetFontSize(12);
		}
		if (meison_hp >= 3) {
			DrawGraphF(meison_x, setumei_y, meison1_i, TRUE);
			SetFontSize(48);
			DrawFormatString(10, 10, GetColor(25, 255, 25), "HP%d", meison_hp);
			SetFontSize(12);
		}
		
		for (int i = 0; i < DONSOK_MAX - 1; i++) {
			donsok_f--;
			if (donsok_f < 0) {
				donsok_f = i;
				
				DrawGraph(donsoku_x[0], donsoku_y[0], donsok_i[i], TRUE);
				DrawGraph(donsoku_x[1], donsoku_y[1], donsok_i[i], TRUE);
				DrawGraph(donsoku_x[2], donsoku_y[2], donsok_i[i], TRUE);
				
			}
		}
		for (int i = 0; i < ENN_KAUZ; i++) {
			if (enn_m[i] == MODE_MOVE) {
				DrawGraphF(enn_x[i], enn_y[i], enn_i[enn_f], TRUE);
			}
		}
		for (int i = 0;i < COIN_MAX;i++) {
			coin_f--;
			if (coin_f < 0) {
				coin_f = 22;
				DrawGraphF(coin_x3, coin_y3, coin_i[i], TRUE);
			}
		}
		DrawGraphF(mario_x, mario_y, mario_i, TRUE);
		SetFontSize(48);
		DrawFormatString(10, 490, GetColor(255, 25, 25), "HP%d", mario_hp);
		SetFontSize(12);
		break;
	case SCENE_GAMEOVER2:
		DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, gameover_bg[gameover_f], TRUE);
		saboten_f++;
		if (saboten_f >= SABOTEN_MAX) {
			saboten_f = 0;
		}
		saboten_x2[0] = 10;
		saboten_y2[0] = 0;
		saboten_x2[1] = 850;
		saboten_y2[1] = 0;
		saboten_x2[2] = 10;
		saboten_y2[2] = 400;
		saboten_x2[3] = 850;
		saboten_y2[3] = 400;
		DrawGraph(saboten_x2[0], saboten_y2[0], saboten_i[saboten_f], TRUE);
		DrawGraph(saboten_x2[1], saboten_y2[1], saboten_i[saboten_f], TRUE);
		DrawGraph(saboten_x2[2], saboten_y2[2], saboten_i[saboten_f], TRUE);
		DrawGraph(saboten_x2[3], saboten_y2[3], saboten_i[saboten_f], TRUE);
		ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
		SetFontSize(64);
		DrawFormatString(200, 10, GetColor(255, 25, 25), "Mボタンでボス戦へ", GetColor(255, 0, 0), TRUE);
		SetFontSize(12);
		break;
	case SCENE_GAMECRIA:
		DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, cria_bg[cria_f], TRUE);
		ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
		SetFontSize(64);
		DrawFormatString(300, 10, GetColor(255, 255, 25), "ゲームクリア", TRUE);
		DrawFormatString(200, 480, GetColor(25, 255, 25), "Nボタンでタイトルへ",  TRUE);
		SetFontSize(12);
		break;
	}
	
	
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	//	ロード画面の終了処理
	for (int i = 0;i < LOOD_MAX ;i++) {
		DeleteGraph(lood_i[i]);
	}
	//	テストファイルの終了処理
	for( int i = 0; i < TEST_MAX; i++ ){
		DeleteGraph( test_image[i] );
	}
	for (int i = 0;i < BG_MAX;i++) {
		DeleteGraph(bg_image[i]);
	}	
	//	ステージ１の終了処理
	for (int i = 0;i < SABAK_MAX;i++) {
		DeleteGraph(bg_sabaku[i]);
	}
	for (int i = 0;i < BG1_MAX;i++) {
		DeleteGraph(bg1_i[i]);
	}
	for (int i = 0;i < DONSOK_MAX;i++) {
		DeleteGraph(donsok_i[i]);

	}
	for (int i = 0;i < COIN_MAX;i++) {
		DeleteGraph(coin_i[i]);
	}

	for (int i = 0; i < SABOTEN_MAX; i++) {
		DeleteGraph(saboten_i[i]);
	}
	for (int i = 0; i < SABAKUNOHA_MAX; i++) {
		DeleteGraph(sabakunoha_i[i]);
	}
	for (int i = 0;i < GAMEORVER_MAX;i++) {
		DeleteGraph(gameover_bg[i]);
	}
	for (int i = 0; i < PRAMID_MAX; i++) {
		DeleteGraph(pramid_bg[i]);
	}
	for (int i = 0; i < ENN_MAX; i++) {
		DeleteGraph(enn_i[i]);
	}
	for (int i = 0; i < CRIA_MAX; i++) {
		DeleteGraph(cria_bg[i]);
	}
	DeleteGraph(mario_i);
	DeleteGraph(meison1_i);
	DeleteGraph(meison2_i);
	DeleteGraph(meison3_i);

}
