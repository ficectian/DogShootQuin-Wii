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
#define ENEMYTEX TEXT("image/enemy.png")
#define BOOWTEX TEXT("image/BOOW.png")
#define CLOUDTEX "Cloud.tpl"
#define ENEMYBOOWTEX TEXT("image/EnemyBOOW.png")
#define SHOOTTEX	"Shoot.tpl"

#define ENEMYSHOOTTEX	TEXT("image/EnemyShoot.png")
#define HEAT1TEX	"Heat1.tpl"
#define HEAT2TEX "Heat2.tpl"
#define	INVINCIBLETEX	 TEXT("image/Invincible.png")
#define	WINTEX	 TEXT("image/WIN.png")
#define	LOSETEX	 TEXT("image/LOSE.png")