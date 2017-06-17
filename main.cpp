//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		インクルードファイル
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include	<revolution.h>
#include	<demo.h>
#include<revolution/wpad.h>
#include<revolution/kpad.h>
#include "MEMAllocator.h"
#include "KeyPad.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		定数定義
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define	SCREEN_WIDTH		(640)						//スクリーン幅
#define	SCREEN_HEIGHT	(480)						//スクリーン高さ
#define	LAND_WIDTH		(1024)						//スクリーン幅
#define	LAND_HEIGHT	(512)						//スクリーン高さ
#define	RIGHTUP			(0)							//右上移動方向
#define	LEFTUP			(1)							//左上移動方向
#define	LEFTDOWN		(2)							//左下移動方向
#define	RIGHTDOWN		(3)							//右下移動方向
#define	HITOFF			(0)							//
#define	HITON			(1)							//
#define DEFSHOTY		(5.0f)
#define PLAYER_HEIGHT	(64)
#define	PLAYER_WIDTH	(80)
#define PLAYERTEXUSIZE  (0.25f)
#define SHOOTNUM		(7)
#define SHOOTSIZE		(10)
#define ENEMYSHOOTSIZE		(6)
#define SHOOTGAP		(15)
#define INVINCIBLE_SIZE (90)
#define ENEMYNUM (3)
#define ENEMY_HEIGHT	(50)
#define	ENEMY_WIDTH	(70)
#define ENEMY0DEFY (SCREEN_HEIGHT / 2 - 150)
#define ENEMY1DEFY  (SCREEN_HEIGHT / 2)
#define ENEMY2DEFY (SCREEN_HEIGHT / 2 + 150)
#define ENEMYSHOOTMAX (255)
#define PLAYERSPEED (5)
#define HEATSIZE		(20.0f)
#define HEATGAP		(30.0f)

#define PLAYERTEX "Player.tpl"
#define SCRENTEX	"scren.tpl"
#define LANDTEX		"land.tpl"
#define ENEMYTEX "enemy.tpl"
#define BOOWTEX "BOOW.tpl"
#define CLOUDTEX "Cloud.tpl"
#define ENEMYBOOWTEX "EnemyBOOW.tpl"
#define SHOOTTEX	"Shoot.tpl"

#define ENEMYSHOOTTEX	"EnemyShoot.tpl"
#define HEAT1TEX	"Heat1.tpl"
#define HEAT2TEX "Heat2.tpl"
#define	INVINCIBLETEX	 "Invincible.tpl"
#define	WINTEX	 "WIN.tpl"
#define	LOSETEX	 "LOSE.tpl"

#define	TITLETEX	 "title.tpl"
#define	TITLEINTTEX		"titleint.tpl"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		グローバル変数
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
TPLPalettePtr texLand;
TPLPalettePtr texScren;
TPLPalettePtr texShoot;
TPLPalettePtr texHeat1;
TPLPalettePtr texHeat2;
GXTexObj texLandObj;
GXTexObj texScrenObj;
GXTexObj texShootObj;
GXTexObj texHeat1Obj;
GXTexObj texHeat2Obj;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		グローバル変数
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct {
	TPLPalettePtr Tex;
	GXTexObj TexObj;
	TPLPalettePtr DeadTex;
	GXTexObj DeadTexObj;
	TPLPalettePtr InvincibleTex;
	GXTexObj InvincibleTexObj;
	f32 X;	//年齢
	f32 Y;	//攻撃力
	f32 Width;
	f32 Height;
	f32 Ustart;
	f32 Vstart;
	f32 Uwidth;
	f32 Vheight;
	int	nHp;	//体力
	u8 InvincibleState;
	f32 Flg;
	void Init();
	void Update();
	void Draw();
}PLAYER;

typedef struct {
	f32 X;	
	f32 Y;
	f32 Width;
	f32 Height;
	f32 Ustart;
	f32 Vstart;
	f32 Uwidth;
	f32 Vheight;
	TPLPalettePtr Tex;
	GXTexObj TexObj;
	u8	nHp;	//体力
	f32 Flg;
}CHARACTER;
typedef struct {
	TPLPalettePtr Tex;
	GXTexObj TexObj;
	TPLPalettePtr DeadTex;
	GXTexObj DeadTexObj;
	f32 X;	
	f32 Y;	
	f32 Width;
	f32 Height;
	f32 Ustart;
	f32 Vstart;
	f32 Uwidth;
	f32 Vheight;
	int nHp;	//体力
	f32 Flg;
	u8 Hitting;
	void Init(u8);
	void Update(u8);
	void Draw();
	u8 cnt;
}ENEMY;
typedef struct {
	f32 X;
	f32 Y;
	f32 Width;
	f32 Height;
	f32 Ustart;
	f32 Vstart;
	f32 Uwidth;
	f32 Vheight;
	TPLPalettePtr Tex;
	GXTexObj TexObj;
}IMAGE;
typedef struct {
	TPLPalettePtr Tex;
	GXTexObj TexObj;
	u8		Flag;
	f32	X;
	f32	DefX;
	f32	Y;
	bool	Disp;
	bool notshooting;
	void Init(u8);
	void Update(u8);
	void Hit(u8);
	void Draw();
}SHOOT;

typedef struct {
TPLPalettePtr Tex;
	GXTexObj TexObj;
	u8		Flag;
	f32	X;
	f32	Y;
	bool	Disp;
	u8 Loop;
	void Init();
	void Update();
	void Hit();
	void Draw();
}ENEMYSHOOT;
enum {
	TITLE,
	GAME_START,
	GAME_PLAY,
	RESULT,
	GAME_OVER,
	GAME_WIN
};

static f32 LandUMove = 0.0f;



f32	Kei2W = 32.0f;										//矩形の幅
f32	Kei2H = 32.0f;										//矩形の高さ





f32	KeiSpeed = 5.5f;								//移動の初期速さ

f32 Kei2X =	SCREEN_WIDTH/2;
f32	Kei2Y = SCREEN_HEIGHT/2;




u8	ShootFlag[SHOOTNUM] = {HITOFF,HITOFF,HITOFF,HITOFF,HITOFF};
f32 ShootX[SHOOTNUM];	// = {5.0f,10.0f,15.0f,20.0f,25.0f};
f32	DefShotX[SHOOTNUM];
f32 ShootY[SHOOTNUM];// = {DEFSHOTY,DEFSHOTY,DEFSHOTY,DEFSHOTY,DEFSHOTY};

u8	HitSwitch = HITOFF;
GXColor	BG_COLOR = {0xfe,0xf2,0x63};	//背景色- 
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		プロトタイプ宣言
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
extern PLAYER Player;
extern ENEMY	Enemy[ENEMYNUM];
extern SHOOT Shoot[SHOOTNUM];
extern ENEMYSHOOT EnemyShoot[ENEMYSHOOTMAX];
IMAGE Cloud;
IMAGE Title;
IMAGE Titleint;
IMAGE WIN;
IMAGE LOSE;
//SHOOT Shoot[SHOOTNUM];
//SHOOT EnemyShoot[ENEMYSHOOTMAX];
u8 EnemyShootNum = 0;
const u8 Anime1[64] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,0xff };//0xff：終了コード
const u8 Anime2[16] = { 8,8,9,9,0xff };
const u8 *Anime_data[2] = { Anime1,Anime2 };
u8 Anime_style;// = 0;
const u8 *Animept = Anime_data[Anime_style];
u8 cnt;
u8 fcnt;
u8 Status;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		関数宣言
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
f32		UpMove(f32 ,f32 ,f32 ,f32 );				//上移動関数
f32		RightMove(f32 ,f32 ,f32 ,f32 );			//左移動関数
f32		LeftMove(f32 ,f32 ,f32 ,f32  );				//左移動関数
f32		DownMove(f32 ,f32 ,f32 ,f32 );				//下移動関数
bool	HitTest(f32 ,f32 ,f32 ,f32 ,f32 ,f32 , f32 ,f32 );
void	ScreenInitialization();
void	Draw2DCharacter(GXTexObj, f32, f32, f32, f32, f32, f32, f32, f32);
//==========================================================================================================
//		プログラム本編
//==========================================================================================================
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		エントリーポイント
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void){
//	GXColor	BG_COLOR = {0x30,0x28,0x33};	//背景色- 

	//		各種初期化
	DEMOInit(NULL);						//主要モジュールも内部で初期化されます｛os,pad,gx,vi}
	init_memory2();	//メモリ確保
	init_KPAD();	//リモコン初期化
	Status = TITLE;
	fcnt =0;
	TPLGetPalette(&texLand, LANDTEX);           //2017.5.19追加
	TPLGetPalette(&texScren, SCRENTEX);
	TPLGetPalette(&Cloud.Tex,CLOUDTEX);
	TPLGetPalette(&texHeat1,HEAT1TEX);
	TPLGetPalette(&texHeat2,HEAT2TEX);
	
	TPLGetPalette(&Title.Tex,TITLETEX);
	TPLGetGXTexObjFromPalette(Title.Tex, &Title.TexObj, 0);
	
	TPLGetPalette(&Titleint.Tex,TITLEINTTEX);
	TPLGetGXTexObjFromPalette(Titleint.Tex, &Titleint.TexObj, 0);
	
	TPLGetPalette(&WIN.Tex,WINTEX);
	TPLGetGXTexObjFromPalette(WIN.Tex, &WIN.TexObj, 0);
	
	TPLGetPalette(&LOSE.Tex,LOSETEX);
	TPLGetGXTexObjFromPalette(LOSE.Tex, &LOSE.TexObj, 0);

	TPLGetGXTexObjFromPalette(texScren, &texScrenObj, 0);
	TPLGetGXTexObjFromPalette(texLand, &texLandObj, 0);   //2017.5.19追加
	
	TPLGetGXTexObjFromPalette(texHeat1,&texHeat1Obj,0);
	TPLGetGXTexObjFromPalette(texHeat2,&texHeat2Obj,0);
	TPLGetGXTexObjFromPalette(Cloud.Tex,&Cloud.TexObj,0);
	Title.Width = SCREEN_WIDTH;
	Title.Height = SCREEN_HEIGHT;
	Title.X = Title.Width / 2;
	Title.Y = Title.Height / 2;
	
	Titleint.Width = 219;
	Titleint.Height = 65;
	Titleint.X = 130;
	Titleint.Y = 400;
	Cloud.Width =695;
	Cloud.Height =164;

	
	

	//		ゲームルーブ
	while(1)
	{
		
		fcnt += 1;
		if (fcnt > 60) { fcnt = 0; }
		work_controller();
		switch(Status){
		case TITLE:
			if (kpads[0][0].trig & KPAD_BUTTON_A){Status = GAME_START;}
			break;
		case GAME_START:
			Player.Init();
			for (u8 i = 0; i < ENEMYNUM; i++) {Enemy[i].Init(i);}
			EnemyShoot->Init();
			for (u8 i = 0; i < SHOOTNUM; i++) { Shoot[i].Init(i); }
			Cloud.X =SCREEN_WIDTH;
			Cloud.Y = (SCREEN_HEIGHT-70-Cloud.Height/2);
			Status = GAME_PLAY;
			break;
		case GAME_PLAY:
			Player.Update();
			Shoot->Update(fcnt);
			EnemyShoot->Update();
			EnemyShoot->Hit();
			for (u8 i = 0; i < SHOOTNUM; i++) { Shoot[i].Hit(i); }
			for (u8 i = 0; i < ENEMYNUM; i++) { Enemy[i].Update(i); }//敵移動	
			for (u8 i = 0; i< ENEMYNUM; i++) {
				if (HitTest(Player.X, Player.Y, Player.Width, Player.Height, Enemy[i].X, Enemy[i].Y, Enemy[i].Width, Enemy[i].Height) && Enemy[i].nHp >0 && Player.InvincibleState <= 0) {
					Player.X -= 30;
					Player.nHp -= 1;
					Player.InvincibleState = 60;
				}
			}
			Cloud.X -= 1.0f;
			if (Cloud.X + Cloud.Width / 2 < 0) {
				Cloud.X = SCREEN_WIDTH + Cloud.Width;
			}
			LandUMove += 0.0003f;//land
			if (Player.nHp <= -10) { Status = GAME_OVER; }
			if (Enemy[0].nHp <= -5 && Enemy[1].nHp <= -5 && Enemy[2].nHp <= -5) { Status = GAME_WIN; }
			break;
		case GAME_OVER:
			if (kpads[0][0].trig & KPAD_BUTTON_A) { Status = TITLE; }
			break;
		case GAME_WIN:
			if (kpads[0][0].trig & KPAD_BUTTON_A){ Status = TITLE; }
			break;
		}
		
		
	
	
		ScreenInitialization();//画面初期化
		
		switch(Status){
		case TITLE:
			Draw2DCharacter(Title.TexObj, Title.X, Title.Y, Title.Width, Title.Height, 0, 0, 1, 1);
			
			if (fcnt >30 == 0) {
				Draw2DCharacter(Titleint.TexObj, Titleint.X, Titleint.Y, Titleint.Width, Titleint.Height, 0, 0, 1, 1);
			}
			break;
		case GAME_PLAY:
				Draw2DCharacter(texScrenObj, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1, 1);//sky
			Draw2DCharacter(texLandObj, LAND_WIDTH / 2, SCREEN_HEIGHT - LAND_HEIGHT / 2, LAND_WIDTH, LAND_HEIGHT, 0 + LandUMove, 0, 1, 1);
		
			
			Draw2DCharacter(Cloud.TexObj, Cloud.X, Cloud.Y, Cloud.Width, Cloud.Height, 0, 0, 1, 1);//sky
		
			Player.Draw();
		//	Draw2DCharacter(Player.TexObj, Player.X, Player.Y, Player.Width, Player.Height, Player.Ustart, Player.Vstart, Player.Uwidth, Player.Vheight);
			for (u8 i = 0; i < ENEMYNUM; i++) {Enemy[i].Draw();}
			
			for (u8 i = 0; i < Player.nHp; i++) {
				if (Player.nHp >= 3) {
					for (int n = 0; n < 3; n++) {
						Draw2DCharacter(texHeat1Obj, 500 + n*HEATGAP, 15, HEATSIZE, HEATSIZE, 0, 0, 1, 1);
					}
					for (int n = 0; n < Player.nHp - 3; n++) {
						Draw2DCharacter(texHeat2Obj, 500 + n*HEATGAP, 15, HEATSIZE, HEATSIZE, 0, 0, 1, 1);
					}
				}else{
					for (int n = 0; n < Player.nHp; n++) {
						Draw2DCharacter(texHeat1Obj, 500 + n*HEATGAP, 15, HEATSIZE, HEATSIZE, 0, 0, 1, 1);
					}
				}
			}
			Shoot->Draw();
			EnemyShoot->Draw();
			break;
		case GAME_OVER:
			Draw2DCharacter(texScrenObj, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1, 1);//sky
			Draw2DCharacter(LOSE.TexObj, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1, 1);
			if (fcnt >30 == 0) {
				Draw2DCharacter(Titleint.TexObj, Titleint.X, Titleint.Y, Titleint.Width, Titleint.Height, 0, 0, 1, 1);
			}
			break;
		case GAME_WIN:
			Draw2DCharacter(texScrenObj, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1, 1);//sky
			Draw2DCharacter(WIN.TexObj, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1, 1);
			if (fcnt >30 == 0) {
				Draw2DCharacter(Titleint.TexObj, Titleint.X, Titleint.Y, Titleint.Width, Titleint.Height, 0, 0, 1, 1);
			}
			break;
		}

	
		
		//		レンダリング終了
		DEMODoneRender();
		
		
	}
	
	//		ゲーム終了
	OSHalt("End of sample");
}


//==========================================================================================================
//		関数定義
//==========================================================================================================

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		上移動関数定義
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
f32	UpMove(f32 X1, f32 Y1, f32 W1, f32 H1) {
	//各頂点の移動
	if (Y1 - H1 / 2 > 0)
	{
		Y1 -= PLAYERSPEED;
	}
	return Y1;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		左移動関数定義
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
f32	LeftMove(f32 X1, f32 Y1, f32 W1, f32 H1) {
	//各頂点の移動
	if (X1 - W1 / 2 > 0)
	{
		X1 -= PLAYERSPEED;
	}
	return X1;

}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		右移動関数定義
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
f32	RightMove(f32 X1, f32 Y1, f32 W1, f32 H1) {
	//各頂点の移動
	if (X1 + W1 / 2 < SCREEN_WIDTH)
	{
		X1 += PLAYERSPEED;
	}
	return X1;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		下移動関数定義
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
f32	DownMove(f32 X1, f32 Y1, f32 W1, f32 H1) {
	//各頂点の移動
	if (Y1 + H1 / 2 <SCREEN_HEIGHT)
	{
		Y1 += PLAYERSPEED;
	}
	return Y1;
		
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		当たり判定処理関数定義
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool			HitTest(f32 X1,f32 Y1,f32 W1,f32 H1,f32 X2,f32 Y2, f32 W2,f32 H2)
{
	f32 XX1 =X1-W1/2;
	f32	XX2 =X2-W2/2;
	f32 YY1 = Y1-H1/2;
	f32 YY2 = Y2-H2/2;

	if(((YY1+H1 >= YY2) && (YY1 -H2<= YY2)) && ((XX1+ W1 >= XX2) && (XX1-W2 <= XX2)))
	{
		return true;
	}
	else
	{
		return	 false;
	}

}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		Character表示関数定義
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void		Draw2DCharacter(GXTexObj TexObj,f32 X,f32 Y,f32 Width,f32 Height,f32 Ustart,f32 Vstart,f32 Uwidth,f32 Vheight)
{
	GXLoadTexObj(&TexObj, GX_TEXMAP0);
	GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 4);

	//		矩形角その１（頂点0）
	GXPosition3f32(X - Width / 2, Y + Height / 2, 0.0f);	//座標
	GXColor3u8(0xff, 0xff, 0xff);
	GXTexCoord2f32(Ustart, Vstart+ Vheight);            //2017.5.19追加
														
	//		矩形角その１（頂点1）
	GXPosition3f32(X - Width / 2, Y - Height / 2, 0.0f);	//座標
	GXColor3u8(0xff, 0xff, 0xff);
	GXTexCoord2f32(Ustart, Vstart);            //2017.5.19追加

	 //		矩形角その１（頂点2）
	GXPosition3f32(X + Width / 2, Y - Height / 2, 0.0f);	//座標
	GXColor3u8(0xff, 0xff, 0xff);
	GXTexCoord2f32(Ustart+ Uwidth, Vstart);            //2017.5.19追加

	 //		矩形角その１（頂点3）
	GXPosition3f32(X + Width / 2, Y + Height / 2, 0.0f);	//座標
	GXColor3u8(0xff, 0xff, 0xff);
	GXTexCoord2f32(Ustart+ Uwidth, Vstart + Vheight);            //2017.5.19追加

	GXEnd();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		画面初期化関数定義
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void		ScreenInitialization() {
	//		プロジェクション行列の設定
	Mtx44	projMatrix;	//	プロジェクション行列

						//		正射影行列の作成
	MTXOrtho(projMatrix, 0, SCREEN_HEIGHT, 0, SCREEN_WIDTH, 0.0f, 1.0f);

	//		正射影行列をプロジェクション行列として設定
	GXSetProjection(projMatrix, GX_ORTHOGRAPHIC);

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//		描画処理
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//		画面クリア
	GXSetCopyClear(BG_COLOR, GX_MAX_Z24);

	//		レンダリング開始
	DEMOBeforeRender();

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//		頂点属性設定
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	GXClearVtxDesc();																												//頂点属性情報クリア
																																	//GXSetVtxDesc(GX_VA_POS,GX_DIRECT);
																																	//GXSetVtxDesc(GX_VA_CLR0,GX_DIRECT);																	//座標はダイレクト参照
																																	//GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS,GX_POS_XYZ,GX_F32,0);		//頂点座標属性フォーマット設定
																																	//GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_CLR0,GX_CLR_RGB,GX_RGB8,0);
																																	//GXSetNumChans(1);
																																	//GXSetNumTevStages(1);
																																	//GXSetTevOrder(GX_TEVSTAGE0,GX_TEXCOORD_NULL,GX_TEXMAP_NULL,GX_COLOR0A0);
																																	//GXSetTevOp(GX_TEVSTAGE0,GX_PASSCLR);

	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);     //座標はダイレクト参照
	GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);    //単一の属性（色）とその属性に対する参照の仕方を指定
	GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);    //2017.5.19 テクスチャの設定
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);	//頂点座標属性フォーマットの設定
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGB, GX_RGB8, 0);//頂点色属性フォーマットの設定
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);  //頂点属性の設定   2017.5.19追加
	GXSetNumChans(1);            //カラーチャンネルの設定
	GXSetNumTevStages(1);        //TEVステージ数の設定
	GXSetNumTexGens(1);          //2017.5.19追加
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);  //色・テクスチャの合成準備 2017.5.19修正
																		 //	GXSetTevOp(GX_TEVSTAGE0,GX_PASSCLR);  //TEVのカラーの合成設定
	GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);  //2017.5.19修正
	GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);  //2017.5.19追加
																				  //	GXLoadTexObj(&texObj, GX_TEXMAP0);     //2017.5.19追加
}

//==========================================================================================================
//		End of sample
//==========================================================================================================
PLAYER Player;
ENEMY Enemy[ENEMYNUM];
SHOOT Shoot[SHOOTNUM];
ENEMYSHOOT EnemyShoot[ENEMYSHOOTMAX];

void PLAYER::Init() {
	TPLGetPalette(&Player.Tex, PLAYERTEX);
	TPLGetGXTexObjFromPalette(Player.Tex, &Player.TexObj, 0);   //2017.5.19追加
	TPLGetPalette(&Player.DeadTex, BOOWTEX);
	TPLGetGXTexObjFromPalette(Player.DeadTex, &Player.DeadTexObj, 0);   //2017.5.19追加
	TPLGetPalette(&Player.InvincibleTex, INVINCIBLETEX);
	TPLGetGXTexObjFromPalette(Player.InvincibleTex, &Player.InvincibleTexObj, 0);   //2017.5.19追加
	X = 100;
	Y = SCREEN_HEIGHT / 2;
	Width = 80;
	Height = 64;
	nHp = 6;
	InvincibleState = 0;
	Ustart = 0.0f;
	Uwidth = 0.25f;
	Vstart = 0.0f;
	Vheight = 1.0f;
	
	//const int PlayerAnime1[16] = { 0,0,0,1,1,1,2,2,2,3,3,3,0xff };//0xff：終了コード
	Anime_style = 0;
	cnt = 0;
}

void PLAYER::Update() {
	if (InvincibleState > 0) {
		InvincibleState -= 1;
	}
	if (nHp > 0) {
		if (kpads[0][0].hold & KPAD_BUTTON_RIGHT) {
				Y = UpMove(X, Y, Width, Height);					//右上移動
			}
			if (kpads[0][0].hold & KPAD_BUTTON_LEFT) {
				Y = DownMove(X, Y, Width, Height);			//左下移動
			}
			if (kpads[0][0].hold & KPAD_BUTTON_UP) {
				X = LeftMove(X, Y, Width, Height);							//左上移動
			}
			if (kpads[0][0].hold & KPAD_BUTTON_DOWN) {
				X = RightMove(X,Y, Width, Height);			//右下移動
			}
			
	}
	Ustart = ((*(Animept + cnt))%int(1/Uwidth))*Uwidth;
	cnt += 1;
	if (*(Animept + cnt) == 0xff) { cnt = 0; }

}


void PLAYER::Draw() {
//	Draw2DCharacter(TexObj, X, Y, Width, Height, Ustart, Vstart, Uwidth, Vheight);//Player

	if (InvincibleState > 0 && Player.nHp > 0) {
		Draw2DCharacter(InvincibleTexObj, X, Y, INVINCIBLE_SIZE, INVINCIBLE_SIZE, 0.0f, 0.0f, 1.0f, 1.0f);//Player
	}
	if (Player.nHp > 0) {
		Draw2DCharacter(TexObj, X, Y, Width, Height, Ustart, Vstart, Uwidth, Vheight);//Player
//player
	}
	else if (Player.nHp > -10) {
		Draw2DCharacter(DeadTexObj, X, Y, Width, Height,  0.0f, 0.0f, 1.0f, 1.0f);//Player
		Player.nHp -= 1;
	}

}



void ENEMY::Init(u8 i) {
	TPLGetPalette(&Tex,ENEMYTEX);

	TPLGetGXTexObjFromPalette(Tex, &TexObj, 0);
	TPLGetPalette(&DeadTex,ENEMYBOOWTEX);

	TPLGetGXTexObjFromPalette(DeadTex, &DeadTexObj, 0);
//	bool bret = DXLoadTexture(ENEMYTEX, &Tex);
//	bret = DXLoadTexture(ENEMYBOOWTEX, &DeadTex);
	Height = 50;
	Width = 70;
	Flg = 0.0f;
	nHp = 3;
	Ustart = 0.0f;
	Uwidth = 1.0f;
	Vstart = 0.0f;
	Vheight = 1.0f;
	Hitting = 0;
	cnt = 0;
	switch (i)
	{
	case 0:
		X = 550;
		Y = ENEMY0DEFY;
		break;
	case 1:
		X = 400;
		Y = ENEMY1DEFY;
		break;
	case 2:
		X = 550;
		Y = ENEMY2DEFY;
		break;
	}
}

void ENEMY::Update(u8 i) {
	if (nHp > 0) {
		switch (i + int(Flg))
		{
		case 0:
			X -= 2.0f;
			Y += 2.0f;
			if (Y == ENEMY1DEFY) { Flg = 1.0f - i; }
			break;
		case 1:
			X += 2.0f;
			Y += 2.0f;
			if (Y == ENEMY2DEFY) { Flg = 2.0f - i;; }
			break;
		case 2:
			Y -= 4.0f;
			if (Y == ENEMY0DEFY) { Flg = 0.0f - i;; }
			break;
		default:
			break;
		}
	}
	if (Hitting > 0) { Hitting -= 1; }
}

void ENEMY::Draw() {
	if (nHp > 0) {
		if(Hitting <= 0){	Draw2DCharacter(TexObj,X, Y, Width, Height, Ustart, Vstart, Uwidth,Vheight);}
	}
	else if (nHp > -5)
	{
	
		Draw2DCharacter(DeadTexObj,X, Y, Width, Height, Ustart, Vstart, Uwidth,Vheight);
	//	DXDrawPolygon(X, Y, 0, Width, Height, D3DCOLOR_RGBA(255, 255, 255, 255), DeadTex);
		nHp -= 1;
	}
	else
	{
		X = -100.0f;
		Y = -100.0f;
	}
}

void SHOOT::Init(u8 i){
	TPLGetPalette(&Tex,SHOOTTEX);
	TPLGetGXTexObjFromPalette(Tex, &TexObj, 0);
	Shoot[i].DefX = SHOOTGAP*i + 20.0f;
	Shoot[i].X = Shoot[i].DefX;
	Shoot[i].Y = DEFSHOTY;
	Shoot[i].Flag = HITOFF;
	Shoot[i].Disp = false;
	notshooting = true;
}


void SHOOT::Update(u8 fcnt) {
	if (Player.nHp > 0) 
	{
		if (kpads[0][0].trig & KPAD_BUTTON_1)
		{
			for (u8 i = 0; i < SHOOTNUM; i++) 
			{
			if (Shoot[i].Flag == HITOFF) 
				{
						Shoot[i].X = Player.X + Player.Width / 2;
						Shoot[i].Y = Player.Y + 15;
						Shoot[i].Flag = HITON;
						Shoot[i].Disp = true;
						break;
				}
			}
		}
		if (kpads[0][0].hold & KPAD_BUTTON_2) 
		{
				for (int i = 0; i < SHOOTNUM; i++) {
					if (Shoot[i].Flag == HITOFF & notshooting) {
						Shoot[i].X = Player.X + Player.Width / 2;
						Shoot[i].Y = Player.Y + 15;
						Shoot[i].Flag = HITON;
						Shoot[i].Disp = true;
						notshooting = false;
						break;
					}
				}
		}
	}
		


	if (fcnt % 10 == 0) { notshooting = true; }
	
	for (u8 i = 0; i < SHOOTNUM; i++)
	{
		if (Shoot[i].Flag == HITON) {
			Shoot[i].X += 6.0f;
		}
		if (Shoot[i].X > SCREEN_WIDTH) {
			Shoot[i].Flag = HITOFF;
			Shoot[i].X = Shoot[i].DefX;
			Shoot[i].Y = DEFSHOTY;
			Shoot[i].Disp = false;
		}
	}
}

void SHOOT::Hit(u8 i) {
	if (Shoot[i].Disp) {
		for (int n = 0; n < ENEMYNUM; n++) {
			if (HitTest(Shoot[i].X, Shoot[i].Y, SHOOTSIZE, SHOOTSIZE, Enemy[n].X, Enemy[n].Y, Enemy[n].Width, Enemy[n].Height) && Enemy[n].nHp > 0 && Enemy[n].Hitting <= 0) {
				Shoot[i].Disp = false;
				Enemy[n].nHp -= 1;
				Enemy[n].Hitting = 5;
			}
		}
	}
}
void SHOOT::Draw() {
	for (int i = 0; i < SHOOTNUM; i++)
	{
		if (Shoot[i].Disp || Shoot[i].Flag == HITOFF) {
			Draw2DCharacter(Shoot[i].TexObj, Shoot[i].X, Shoot[i].Y, SHOOTSIZE, SHOOTSIZE, 0, 0, 1, 1);	
		}
	}
}

void ENEMYSHOOT::Init(){
	TPLGetPalette(&Tex,ENEMYSHOOTTEX);
	TPLGetGXTexObjFromPalette(Tex, &TexObj, 0);
	Loop = 0;
}

void ENEMYSHOOT::Update() {
	for (u8 i = 0; i < EnemyShootNum; i++)
	{
		if (EnemyShoot[i].Flag == HITON) {
			EnemyShoot[i].X -= 7.0f;
		}
		if (EnemyShoot[i].X <0) {
			EnemyShoot[i].Flag = HITOFF;
			EnemyShoot[i].X = 0;
			EnemyShoot[i].Y = 0;
			EnemyShoot[i].Disp = false;
		}
	}
	if (Loop == 120) {
		Loop = 0;
		EnemyShootNum = 0;
		for (int i = 0; i < ENEMYNUM; i++) {
			EnemyShootNum += 2;
			if (Enemy[i].nHp > 0) {
				EnemyShoot[2 * i].X = Enemy[i].X - Enemy[i].Width / 2;
				EnemyShoot[2 * i].Y = Enemy[i].Y - 6;
				EnemyShoot[2 * i].Flag = HITON;
				EnemyShoot[2 * i].Disp = true;
				EnemyShoot[2 * i + 1].X = Enemy[i].X - Enemy[i].Width / 2;
				EnemyShoot[2 * i + 1].Y = Enemy[i].Y + 10;
				EnemyShoot[2 * i + 1].Flag = HITON;
				EnemyShoot[2 * i + 1].Disp = true;
			}
		}
	}
	else
	{
		Loop += 1;
	}
}

void ENEMYSHOOT::Hit() {
	for (u8 i = 0; i < EnemyShootNum; i++) {
		if (EnemyShoot[i].Disp) {
			for (int n = 0; n < ENEMYNUM; n++) {
				if (HitTest(EnemyShoot[i].X, EnemyShoot[i].Y, ENEMYSHOOTSIZE, ENEMYSHOOTSIZE, Player.X, Player.Y, Player.Width, Player.Height) && Player.nHp >0 && Player.InvincibleState <= 0) {
					Shoot[i].Disp = false;
					Player.X -= 30;
					Player.nHp -= 1;
					Player.InvincibleState = 10;
				}
			}
		}
	}
}

void ENEMYSHOOT::Draw() {
	for (u8 i = 0; i < EnemyShootNum; i++)
	{
		if (EnemyShoot[i].Disp && EnemyShoot[i].Flag == HITON) {
			Draw2DCharacter(TexObj, EnemyShoot[i].X, EnemyShoot[i].Y, ENEMYSHOOTSIZE, ENEMYSHOOTSIZE, 0, 0, 1, 1);
		}
	}
}
