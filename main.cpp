//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		�C���N���[�h�t�@�C��
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include	<revolution.h>
#include	<demo.h>
#include<revolution/wpad.h>
#include<revolution/kpad.h>
#include "MEMAllocator.h"
#include "KeyPad.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		�萔��`
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#define	SCREEN_WIDTH		(640)						//�X�N���[����
#define	SCREEN_HEIGHT	(480)						//�X�N���[������
#define	LAND_WIDTH		(1024)						//�X�N���[����
#define	LAND_HEIGHT	(512)						//�X�N���[������
#define	RIGHTUP			(0)							//�E��ړ�����
#define	LEFTUP			(1)							//����ړ�����
#define	LEFTDOWN		(2)							//�����ړ�����
#define	RIGHTDOWN		(3)							//�E���ړ�����
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

#define ENEMYSHOOTTEX	"image/EnemyShoot.tpl"
#define HEAT1TEX	"Heat1.tpl"
#define HEAT2TEX "Heat2.tpl"
#define	INVINCIBLETEX	 "image/Invincible.tpl"
#define	WINTEX	 TEXT("image/WIN.png")
#define	LOSETEX	 TEXT("image/LOSE.png")

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		�O���[�o���ϐ�
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
//		�O���[�o���ϐ�
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct {
	TPLPalettePtr Tex;
	GXTexObj TexObj;
	TPLPalettePtr DeadTex;
	GXTexObj DeadTexObj;
	TPLPalettePtr InvincibleTex;
	GXTexObj InvincibleTexObj;
	f32 X;	//�N��
	f32 Y;	//�U����
	f32 Width;
	f32 Height;
	f32 Ustart;
	f32 Vstart;
	f32 Uwidth;
	f32 Vheight;
	u8	nHp;	//�̗�
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
	u8	nHp;	//�̗�
	f32 Flg;
}CHARACTER;
typedef struct {
	TPLPalettePtr Tex;
	GXTexObj TexObj;
	f32 X;	
	f32 Y;	
	f32 Width;
	f32 Height;
	f32 Ustart;
	f32 Vstart;
	f32 Uwidth;
	f32 Vheight;
	u8 nHp;	//�̗�
	f32 Flg;
	void Init(int);
	void Update(int);
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
	u8		Flag;
	f32	X;
	f32	DefX;
	f32	Y;
	bool	Disp;
}SHOOT;

static f32 LandUMove = 0.0f;



f32	Kei2W = 32.0f;										//��`�̕�
f32	Kei2H = 32.0f;										//��`�̍���





f32	KeiSpeed = 5.5f;								//�ړ��̏�������

f32 Kei2X =	SCREEN_WIDTH/2;
f32	Kei2Y = SCREEN_HEIGHT/2;




u8	ShootFlag[SHOOTNUM] = {HITOFF,HITOFF,HITOFF,HITOFF,HITOFF};
f32 ShootX[SHOOTNUM];	// = {5.0f,10.0f,15.0f,20.0f,25.0f};
f32	DefShotX[SHOOTNUM];
f32 ShootY[SHOOTNUM];// = {DEFSHOTY,DEFSHOTY,DEFSHOTY,DEFSHOTY,DEFSHOTY};

u8	HitSwitch = HITOFF;
GXColor	BG_COLOR = {0xfe,0xf2,0x63};	//�w�i�F- 
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		�v���g�^�C�v�錾
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
extern PLAYER Player;
extern ENEMY	Enemy[ENEMYNUM];
IMAGE Cloud;
SHOOT Shoot[SHOOTNUM];
SHOOT EnemyShoot[ENEMYSHOOTMAX];
u8 EnemyShootNum = 0;
const u8 Anime1[64] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,0xff };//0xff�F�I���R�[�h
const u8 Anime2[16] = { 8,8,9,9,0xff };
const u8 *Anime_data[2] = { Anime1,Anime2 };
u8 Anime_style;// = 0;
const u8 *Animept = Anime_data[Anime_style];
u8 cnt;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		�֐��錾
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
f32		UpMove(f32 ,f32 ,f32 ,f32 );				//��ړ��֐�
f32		RightMove(f32 ,f32 ,f32 ,f32 );			//���ړ��֐�
f32		LeftMove(f32 ,f32 ,f32 ,f32  );				//���ړ��֐�
f32		DownMove(f32 ,f32 ,f32 ,f32 );				//���ړ��֐�
bool	HitTest(f32 ,f32 ,f32 ,f32 ,f32 ,f32 , f32 ,f32 );
void	ScreenInitialization();
void	Draw2DCharacter(GXTexObj, f32, f32, f32, f32, f32, f32, f32, f32);
//==========================================================================================================
//		�v���O�����{��
//==========================================================================================================
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//		�G���g���[�|�C���g
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void){
//	GXColor	BG_COLOR = {0x30,0x28,0x33};	//�w�i�F- 

	//		�e�평����
	DEMOInit(NULL);						//��v���W���[���������ŏ���������܂��oos,pad,gx,vi}
	init_memory2();	//�������m��
	init_KPAD();	//�����R��������
	TPLGetPalette(&texLand, LANDTEX);           //2017.5.19�ǉ�
	TPLGetPalette(&texScren, SCRENTEX);
	TPLGetPalette(&texShoot, SHOOTTEX);
	TPLGetPalette(&Cloud.Tex,CLOUDTEX);
	TPLGetPalette(&texHeat1,HEAT1TEX);
	TPLGetPalette(&texHeat2,HEAT2TEX);

	TPLGetGXTexObjFromPalette(texScren, &texScrenObj, 0);
	TPLGetGXTexObjFromPalette(texLand, &texLandObj, 0);   //2017.5.19�ǉ�
	
	TPLGetGXTexObjFromPalette(texShoot, &texShootObj, 0);   //2017.5.19�ǉ�
	TPLGetGXTexObjFromPalette(texHeat1,&texHeat1Obj,0);
	TPLGetGXTexObjFromPalette(texHeat2,&texHeat2Obj,0);
	TPLGetGXTexObjFromPalette(Cloud.Tex,&Cloud.TexObj,0);
	for(u8 i = 0;i < SHOOTNUM;i++){
		DefShotX[i] = SHOOTGAP*i + 5.0f;
		ShootX[i] = DefShotX[i];
		ShootY[i] = DEFSHOTY;
	}
	Player.Init();
	for (u8 i = 0; i < ENEMYNUM; i++) {Enemy[i].Init(i);}

	for (u8 i = 0; i < SHOOTNUM; i++) {
		Shoot[i].DefX = SHOOTGAP*i + 20.0f;
		Shoot[i].X = Shoot[i].DefX;
		Shoot[i].Y = DEFSHOTY;
		Shoot[i].Flag = HITOFF;
		Shoot[i].Disp = false;
	}
	Cloud.Width =695;
	Cloud.Height =164;
	Cloud.X =SCREEN_WIDTH;
	Cloud.Y = (SCREEN_HEIGHT-70-Cloud.Height/2);

	//		�Q�[�����[�u
	while(1)
	{
		
		
		work_controller();
		Player.Update();
		if (Player.nHp > 0) {
			if (kpads[0][0].trig & (KPAD_BUTTON_1 | KPAD_BUTTON_2)) {
				for (u8 i = 0; i < SHOOTNUM; i++) {
					if (Shoot[i].Flag == HITOFF) {
						Shoot[i].X = Player.X + Player.Width / 2;
						Shoot[i].Y = Player.Y + 15;
						Shoot[i].Flag = HITON;
						Shoot[i].Disp = true;
						break;
					}
				}
			}
		}
		//Shooting Move
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
		for (int i = 0; i < ENEMYNUM; i++) { Enemy[i].Update(i); }//�G�ړ�	
		Cloud.X -= 1.0f;
		if (Cloud.X + Cloud.Width / 2 < 0) {
			Cloud.X = SCREEN_WIDTH + Cloud.Width;
		}
		LandUMove += 0.0003f;//land
	
	
	
		ScreenInitialization();//��ʏ�����

		//		�v���~�e�B�u���_���o�^�J�n
		Draw2DCharacter(texScrenObj, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1, 1);//sky
		Draw2DCharacter(texLandObj, LAND_WIDTH / 2, SCREEN_HEIGHT - LAND_HEIGHT / 2, LAND_WIDTH, LAND_HEIGHT, 0 + LandUMove, 0, 1, 1);
	
		
		Draw2DCharacter(Cloud.TexObj, Cloud.X, Cloud.Y, Cloud.Width, Cloud.Height, 0, 0, 1, 1);//sky
	
	//	Player.Draw();
		Draw2DCharacter(Player.TexObj, Player.X, Player.Y, Player.Width, Player.Height, Player.Ustart, Player.Vstart, Player.Uwidth, Player.Vheight);
		for (int i = 0; i < ENEMYNUM; i++) {Enemy[i].Draw();}
		
		for (int i = 0; i < Player.nHp; i++) {
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
		
		//shooting
		for(u8 i = 0; i < SHOOTNUM;i++)
		{
			Draw2DCharacter(texShootObj, Shoot[i].X, Shoot[i].Y, SHOOTSIZE, SHOOTSIZE, 0, 0, 1, 1);	
		}
			
			

		
	
		
		//		�����_�����O�I��
		DEMODoneRender();
		
		
	}
	
	//		�Q�[���I��
	OSHalt("End of sample");
}


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
