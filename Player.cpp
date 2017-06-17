//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		�C���N���[�h�t�@�C��
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include	<revolution.h>
#include	<demo.h>
#include<revolution/wpad.h>
#include<revolution/kpad.h>
#include "MEMAllocator.h"
#include "KeyPad.h"



//==========================================================================================================
//		�֐���`
//==========================================================================================================

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		��ړ��֐���`
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
f32	UpMove(f32 X1, f32 Y1, f32 W1, f32 H1) {
	//�e���_�̈ړ�
	if (Y1 - H1 / 2 > 0)
	{
		Y1 -= PLAYERSPEED;
	}
	return Y1;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		���ړ��֐���`
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
f32	LeftMove(f32 X1, f32 Y1, f32 W1, f32 H1) {
	//�e���_�̈ړ�
	if (X1 - W1 / 2 > 0)
	{
		X1 -= PLAYERSPEED;
	}
	return X1;

}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		�E�ړ��֐���`
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
f32	RightMove(f32 X1, f32 Y1, f32 W1, f32 H1) {
	//�e���_�̈ړ�
	if (X1 + W1 / 2 < SCREEN_WIDTH)
	{
		X1 += PLAYERSPEED;
	}
	return X1;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		���ړ��֐���`
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
f32	DownMove(f32 X1, f32 Y1, f32 W1, f32 H1) {
	//�e���_�̈ړ�
	if (Y1 + H1 / 2 <SCREEN_HEIGHT)
	{
		Y1 += PLAYERSPEED;
	}
	return Y1;
		
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		�����蔻�菈���֐���`
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
//		Character�\���֐���`
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void		Draw2DCharacter(GXTexObj TexObj,f32 X,f32 Y,f32 Width,f32 Height,f32 Ustart,f32 Vstart,f32 Uwidth,f32 Vheight)
{
	GXLoadTexObj(&TexObj, GX_TEXMAP0);
	GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 4);

	//		��`�p���̂P�i���_0�j
	GXPosition3f32(X - Width / 2, Y + Height / 2, 0.0f);	//���W
	GXColor3u8(0xff, 0xff, 0xff);
	GXTexCoord2f32(Ustart, Vstart+ Vheight);            //2017.5.19�ǉ�
														
	//		��`�p���̂P�i���_1�j
	GXPosition3f32(X - Width / 2, Y - Height / 2, 0.0f);	//���W
	GXColor3u8(0xff, 0xff, 0xff);
	GXTexCoord2f32(Ustart, Vstart);            //2017.5.19�ǉ�

	 //		��`�p���̂P�i���_2�j
	GXPosition3f32(X + Width / 2, Y - Height / 2, 0.0f);	//���W
	GXColor3u8(0xff, 0xff, 0xff);
	GXTexCoord2f32(Ustart+ Uwidth, Vstart);            //2017.5.19�ǉ�

	 //		��`�p���̂P�i���_3�j
	GXPosition3f32(X + Width / 2, Y + Height / 2, 0.0f);	//���W
	GXColor3u8(0xff, 0xff, 0xff);
	GXTexCoord2f32(Ustart+ Uwidth, Vstart + Vheight);            //2017.5.19�ǉ�

	GXEnd();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		��ʏ������֐���`
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void		ScreenInitialization() {
	//		�v���W�F�N�V�����s��̐ݒ�
	Mtx44	projMatrix;	//	�v���W�F�N�V�����s��

						//		���ˉe�s��̍쐬
	MTXOrtho(projMatrix, 0, SCREEN_HEIGHT, 0, SCREEN_WIDTH, 0.0f, 1.0f);

	//		���ˉe�s����v���W�F�N�V�����s��Ƃ��Đݒ�
	GXSetProjection(projMatrix, GX_ORTHOGRAPHIC);

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//		�`�揈��
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//		��ʃN���A
	GXSetCopyClear(BG_COLOR, GX_MAX_Z24);

	//		�����_�����O�J�n
	DEMOBeforeRender();

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//		���_�����ݒ�
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	GXClearVtxDesc();																												//���_�������N���A
																																	//GXSetVtxDesc(GX_VA_POS,GX_DIRECT);
																																	//GXSetVtxDesc(GX_VA_CLR0,GX_DIRECT);																	//���W�̓_�C���N�g�Q��
																																	//GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS,GX_POS_XYZ,GX_F32,0);		//���_���W�����t�H�[�}�b�g�ݒ�
																																	//GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_CLR0,GX_CLR_RGB,GX_RGB8,0);
																																	//GXSetNumChans(1);
																																	//GXSetNumTevStages(1);
																																	//GXSetTevOrder(GX_TEVSTAGE0,GX_TEXCOORD_NULL,GX_TEXMAP_NULL,GX_COLOR0A0);
																																	//GXSetTevOp(GX_TEVSTAGE0,GX_PASSCLR);

	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);     //���W�̓_�C���N�g�Q��
	GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);    //�P��̑����i�F�j�Ƃ��̑����ɑ΂���Q�Ƃ̎d�����w��
	GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);    //2017.5.19 �e�N�X�`���̐ݒ�
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);	//���_���W�����t�H�[�}�b�g�̐ݒ�
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGB, GX_RGB8, 0);//���_�F�����t�H�[�}�b�g�̐ݒ�
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);  //���_�����̐ݒ�   2017.5.19�ǉ�
	GXSetNumChans(1);            //�J���[�`�����l���̐ݒ�
	GXSetNumTevStages(1);        //TEV�X�e�[�W���̐ݒ�
	GXSetNumTexGens(1);          //2017.5.19�ǉ�
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);  //�F�E�e�N�X�`���̍������� 2017.5.19�C��
																		 //	GXSetTevOp(GX_TEVSTAGE0,GX_PASSCLR);  //TEV�̃J���[�̍����ݒ�
	GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);  //2017.5.19�C��
	GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);  //2017.5.19�ǉ�
																				  //	GXLoadTexObj(&texObj, GX_TEXMAP0);     //2017.5.19�ǉ�
}

//==========================================================================================================
//		End of sample
//==========================================================================================================
PLAYER Player;
ENEMY Enemy[ENEMYNUM];

void PLAYER::Init() {
	TPLGetPalette(&Player.Tex, PLAYERTEX);
	TPLGetGXTexObjFromPalette(Player.Tex, &Player.TexObj, 0);   //2017.5.19�ǉ�
	TPLGetPalette(&Player.DeadTex, BOOWTEX);
	TPLGetGXTexObjFromPalette(Player.DeadTex, &Player.DeadTexObj, 0);   //2017.5.19�ǉ�
	TPLGetPalette(&Player.InvincibleTex, INVINCIBLETEX);
	TPLGetGXTexObjFromPalette(Player.InvincibleTex, &Player.InvincibleTexObj, 0);   //2017.5.19�ǉ�
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
	
	//const int PlayerAnime1[16] = { 0,0,0,1,1,1,2,2,2,3,3,3,0xff };//0xff�F�I���R�[�h
	Anime_style = 0;
	cnt = 0;
}

void PLAYER::Update() {
	if (InvincibleState > 0) {
		InvincibleState -= 1;
	}
	if (nHp > 0) {
		if (kpads[0][0].hold & KPAD_BUTTON_RIGHT) {
				Y = UpMove(X, Y, Width, Height);					//�E��ړ�
			}
			if (kpads[0][0].hold & KPAD_BUTTON_LEFT) {
				Y = DownMove(X, Y, Width, Height);			//�����ړ�
			}
			if (kpads[0][0].hold & KPAD_BUTTON_UP) {
				X = LeftMove(X, Y, Width, Height);							//����ړ�
			}
			if (kpads[0][0].hold & KPAD_BUTTON_DOWN) {
				X = RightMove(X,Y, Width, Height);			//�E���ړ�
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
