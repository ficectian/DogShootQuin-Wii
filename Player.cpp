//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		インクルードファイル
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include	<revolution.h>
#include	<demo.h>
#include<revolution/wpad.h>
#include<revolution/kpad.h>
#include "MEMAllocator.h"
#include "KeyPad.h"



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
	Draw2DCharacter(TexObj, X, Y, Width, Height, Ustart, Vstart, Uwidth, Vheight);//Player
	/*
	if (InvincibleState > 0 && Player.nHp > 0) {
		Draw2DCharacter(InvincibleTexObj, X, Y, INVINCIBLE_SIZE, INVINCIBLE_SIZE, 0.0f, 0.0f, 1.0f, 1.0f);//Player
	}
	if (Player.nHp > 0) {
		Draw2DCharacter(TexObj, X, Y, Width, Height, Ustart, Vstart, Uwidth, Vheight);//Player
//player
	}
	else if (Player.nHp > -10) {
			Draw2DCharacter(DeadTexObj, X, Y, Width, Height, Ustart, Vstart, Uwidth, Vheight);//Player
		Player.nHp -= 1;
	}
	*/
}



void ENEMY::Init(int i) {
	TPLGetPalette(&Tex,ENEMYTEX);

	TPLGetGXTexObjFromPalette(Tex, &TexObj, 0);
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

void ENEMY::Update(int i) {
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
}
void ENEMY::Draw() {
	if (nHp > 0) {
		Draw2DCharacter(TexObj,X, Y, Width, Height, Ustart, Vstart, Uwidth,Vheight);
	}
//	else if (nHp > -5)
//	{
//		DXDrawPolygon(X, Y, 0, Width, Height, D3DCOLOR_RGBA(255, 255, 255, 255), DeadTex);
//		nHp -= 1;
//	}
//	else
//	{
//		X = -100.0f;
//		Y = -100.0f;
//	}
}
