//=======================================================================================
//
//  [ KeyPad ] Wii sample program
//  Wii �R���g���[���[�T���v���v���O����
//
//=======================================================================================

#include <revolution.h>
#include <math.h>
#include <stdio.h>
#include <revolution/wpad.h>     // WPAD library
#include <revolution/kpad.h>     // KPAD library
#include <revolution/mem.h> 

#include "MEMAllocator.h"
#include "KeyPad.h"


//-------------------------------------------------------------
//  ��������
//-------------------------------------------------------------
static f32 pointing_scale   = 200.0f;  // ��ʃ|�C���e�B���O�X�P�[��

static f32 obj_interval     = 0.20f;   // �s�u���̔����_�ݒu�Ԋu (���[�g��)

static f32 pos_play_radius  = 0.00f;   // pos ������ݒ�
static f32 pos_sensitivity  = 1.00f;
static f32 pos_play_mode    = (f32)KPAD_PLAY_MODE_LOOSE;

static f32 hori_play_radius = 0.00f;   // horizon ������ݒ�
static f32 hori_sensitivity = 1.00f;
static f32 hori_play_mode   = (f32)KPAD_PLAY_MODE_LOOSE;

static f32 dist_play_radius = 0.00f;   // dist ������ݒ�
static f32 dist_sensitivity = 1.00f;
static f32 dist_play_mode   = KPAD_PLAY_MODE_LOOSE;

static f32 acc_play_radius  = 0.00f;   // acc ������ݒ�
static f32 acc_sensitivity  = 1.00f;
static f32 acc_play_mode    = KPAD_PLAY_MODE_LOOSE;

static f32 repeat_delay_sec = 0.75f;   // �L�[���s�[�g�ݒ�
static f32 repeat_pulse_sec = 0.25f;



#define EDIT_DATA_MAX 16 // �ҏW�f�[�^��



typedef struct {
    f32 *vp;   // �ϐ��ւ̃|�C���^
    f32 min;   // �ϐ��̍ŏ��l
    f32 max;   // �ϐ��̍ő�l
    u8  y;     // �x�J�[�\���ʒu
    u8  x[3];  // ���ꂼ��̌��̂w�J�[�\���ʒu
    f32 v[3];  // ���ꂼ��̌��ł̐��l�ω���
} EditData;

static EditData  edit_data[ EDIT_DATA_MAX ] = {
    { &pointing_scale,   0.0f,900.0f,  3, {10,11,12}, {100.0f, 10.0f, 1.0f} },
    { &obj_interval,     0.00f,9.00f,  5, { 9,11,12}, {1.00f, 0.10f, 0.01f} },
    { &pos_play_radius,  0.00f,9.00f,  8, { 4, 6, 7}, {1.00f, 0.10f, 0.01f} },
    { &pos_sensitivity,  0.00f,1.00f,  8, { 9,11,12}, {1.00f, 0.10f, 0.01f} },
    { &pos_play_mode,    0.00f,1.00f,  8, {14,14,14}, {1.00f, 1.00f, 1.00f} },
    { &hori_play_radius, 0.00f,9.00f,  9, { 4, 6, 7}, {1.00f, 0.10f, 0.01f} },
    { &hori_sensitivity, 0.00f,1.00f,  9, { 9,11,12}, {1.00f, 0.10f, 0.01f} },
    { &hori_play_mode,   0.00f,1.00f,  9, {14,14,14}, {1.00f, 1.00f, 1.00f} },
    { &dist_play_radius, 0.00f,9.00f, 10, { 4, 6, 7}, {1.00f, 0.10f, 0.01f} },
    { &dist_sensitivity, 0.00f,1.00f, 10, { 9,11,12}, {1.00f, 0.10f, 0.01f} },
    { &dist_play_mode,   0.00f,1.00f, 10, {14,14,14}, {1.00f, 1.00f, 1.00f} },
    { &acc_play_radius,  0.00f,9.00f, 11, { 4, 6, 7}, {1.00f, 0.10f, 0.01f} },
    { &acc_sensitivity,  0.00f,1.00f, 11, { 9,11,12}, {1.00f, 0.10f, 0.01f} },
    { &acc_play_mode,    0.00f,1.00f, 11, {14,14,14}, {1.00f, 1.00f, 1.00f} },
    { &repeat_delay_sec, 0.00f,9.00f, 14, { 4, 6, 7}, {1.00f, 0.10f, 0.01f} },
    { &repeat_pulse_sec, 0.00f,9.00f, 14, { 9,11,12}, {1.00f, 0.10f, 0.01f} },
};


//-------------------------------------------------------------
//  �ϐ�
//-------------------------------------------------------------
s32              MyCallbackLatestIdx[ MY_CALLBACK_MAX ] = { -1, -1 };
MyCallbackStatus MyCallbackStatusBuf[ MY_CALLBACK_MAX ][ MY_START_COUNTS_MAX ];
vu32             MySamplingCount;


//-------------------------------------------------------------
//  �L�[���͏��
//-------------------------------------------------------------
KPADStatus kpads[ WPAD_MAX_CONTROLLERS ][ KPAD_BUF_SIZE * 2 ];              // �L�[�f�[�^�o�b�t�@
s32        kpad_reads[ WPAD_MAX_CONTROLLERS ];                              // �L�[�f�[�^��
s32        kpad_err;                                                        // �L�[�f�[�^�G���[



//-------------------------------------------------------------
//  �R���g���[��������
//-------------------------------------------------------------
void init_KPAD( void )
{
    // �p�b�h�֘A�̏����ݒ�
    WPADRegisterAllocator( alloc32, free32 );           // ���[�N�������擾�E����p�̃A���P�[�^�֐��o�^

    KPADInit();                                         // �R���g���[��������
    KPADSetControlDpdCallback ( 0, dpd_callback );      // DPD              �R�[���o�b�N�ݒ�
    KPADSetControlMplsCallback( 0, mpls_callback );     // ���[�V�����v���X �R�[���o�b�N�ݒ�
    KPADSetSamplingCallback   ( 0, sampling_callback ); // �T���v�����O     �R�[���o�b�N�ݒ�

    // �A�v���P�[�V�����̏����ݒ�
    init_controller();
}


//-------------------------------------------------------------
//  KPAD callback
//-------------------------------------------------------------
static void work_callback( int idx, s32 reason )
{
    u32 i;
    u32 smallest = MY_START_COUNT_DEFAULT;
    u32 smallestIdx = 0;

    for( i=0; i<MY_START_COUNTS_MAX; i++ )
    {
        if( MyCallbackStatusBuf[ idx ][ i ].count == 0 )
        {
            break;
        }
        else
        {
            if( smallest > MyCallbackStatusBuf[ idx ][ i ].count )
            {
                smallest = MyCallbackStatusBuf[ idx ][ i ].count;
                smallestIdx = i;
            }
        }
    }

    if ( i == MY_START_COUNTS_MAX )
    {
        i = smallestIdx;
    }

    MyCallbackStatusBuf[ idx ][ i ].count = MY_START_COUNT_DEFAULT;
    MyCallbackStatusBuf[ idx ][ i ].reason = reason;
    MyCallbackLatestIdx[ idx ] = (s32)i;
}

void dpd_callback( s32 chan, s32 reason )
{
#pragma unused(chan)
    work_callback( 0, reason );
}

void mpls_callback( s32 chan, s32 reason )
{
#pragma unused(chan)
    work_callback( 1, reason );
}

void sampling_callback( s32 chan )
{
#pragma unused(chan)
    MySamplingCount++;
}


//-------------------------------------------------------------
//  �������֐�
//-------------------------------------------------------------
void init_controller( void )
{
    s32 i;

    // �R���g���[�������ݒ�
    KPADReset();

    for( i=0; i<WPAD_MAX_CONTROLLERS; i++ )
    {
        KPADSetPosParam ( i, pos_play_radius,  pos_sensitivity  );
        KPADSetHoriParam( i, hori_play_radius, hori_sensitivity );
        KPADSetDistParam( i, dist_play_radius, dist_sensitivity );
        KPADSetAccParam ( i, acc_play_radius,  acc_sensitivity  );
        KPADSetBtnRepeat( i, repeat_delay_sec, repeat_pulse_sec );
    }
}


//-------------------------------------------------------------
//  �R���g���[���[�����֐�
//-------------------------------------------------------------
void work_controller( void )
{
    u8  btn  = KPAD_BUTTON_PROC_MODE_LOOSE;

    s32 i;

    int init = 0;

    // ���擾
    for( i=0; i<WPAD_MAX_CONTROLLERS; i++ )
    {
        // �o�b�t�@�ɃT���v�����O���ꂽ�f�[�^���V�������Ɋi�[����Ă���
        kpad_reads[ i ] = KPADReadEx( i, &kpads[ i ][ 0 ], (u32)( KPAD_BUF_SIZE * ( init + 1 ) ), &kpad_err );
        if( kpad_err == KPAD_READ_ERR_NO_DATA )
        {
            kpad_reads[ i ] = -1;
        }
    }


}
