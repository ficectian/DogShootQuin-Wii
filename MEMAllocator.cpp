//=======================================================================================
//
//  [ MEMAllocator ] Wii sample program
//  Wii �������[�A���P�[�V�����v���O����
//
//=======================================================================================

#include    <revolution.h>
#include    <math.h>

#include    <revolution/mem.h> 

#include    "MEMAllocator.h"

void         *arenaLo, *arenaHi;

//-------------------------------------------------------------
//  �������̏�����
//-------------------------------------------------------------
void init_memory( void )
{
    OSHeapHandle  heap;


    //----- �󂫗̈�𒲂ׂ�
    arenaLo = OSGetArenaLo();
    arenaHi = OSGetArenaHi();

    //----- �󂫗̈悢���ς��Ƀq�[�v���P��邱�Ƃ�錾
    arenaLo = OSInitAlloc( arenaLo, arenaHi, 1 );
    OSSetArenaLo( arenaLo );    // �󂫗̈悪�ω�����̂ōăZ�b�g


    //----- �󂫗̈悢���ς��Ƀq�[�v������ăJ�����g�ɐݒ肷��
    heap = OSCreateHeap( arenaLo, arenaHi );
    (void)OSSetCurrentHeap( heap );
    //----- �󂫗̈���g���ʂ��������Ƃ��n�b�L�������Ă���
    arenaLo = arenaHi;


    OSSetArenaLo( arenaLo );
}



//-------------------------------------------------------------
//  �������̏�����(MEM2)
//  
//  �t���[���q�[�v���烁�����̊m�ۂƉ�����s���悤�ɃA���P�[�^������������B
//  �A���P�[�^��ʂ��Ċm�ۂ����S�Ẵ������u���b�N�̃A���C�����g�l���w�肷��B
//-------------------------------------------------------------
static MEMAllocator  s_mem2Allocator;
static MEMHeapHandle s_handle;

void init_memory2( void )
{
    void *lo = OSGetMEM2ArenaLo();
    void *hi = OSGetMEM2ArenaHi();
//    s_handle = MEMCreateFrmHeap( lo, (u32)hi - (u32)lo );
    s_handle = MEMCreateFrmHeap( lo, 0x100000 );
    if ( s_handle == MEM_HEAP_INVALID_HANDLE )
    {
        OSHalt("MEM2 heap allocation error.\n");
    }
    else
    {
        OSSetMEM2ArenaLo((void *)((u32)lo+0x100000));
        // �A���C�����g�ݒ�
        MEMInitAllocatorForFrmHeap( &s_mem2Allocator, s_handle, 32 );   // buffer requies 32byte alignment.
    }
    
}

void* alloc32( u32 size )
{
    return MEMAllocFromAllocator( &s_mem2Allocator, size );
}

u8 free32( void *addr )
{
    MEMFreeToAllocator( &s_mem2Allocator, addr );
    return 1;
}

