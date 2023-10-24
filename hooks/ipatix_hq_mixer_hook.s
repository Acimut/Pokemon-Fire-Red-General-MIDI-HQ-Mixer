//-------------------------------------------------------------------------------
//      Ipatix HQ-Mixer rev 4.0
//-------------------------------------------------------------------------------


//      Aumentar PCM_DMA_BUF_SIZE:
//-------------------------------------------------------------------------------

/*03005f50 g 00000fb0 gSoundInfo*/
//50 5f 00 03
//gSoundInfo = 0x0203C990;

/*


//      cambiar PCM_DMA_BUF_SIZE 1584

	struct_field o_SoundInfo_pcmBuffer, PCM_DMA_BUF_SIZE * 2
50 03 00 00
o_SoundInfo_pcmBuffer = 00000350


03005f50 g 00000fb0 gSoundInfo size:
13379Hz: 0x350 + (1584 x 2) = 0x350 + 0xC60  = 0xFB0
21024Hz: 0x350 + (2480 x 2) = 0x350 + 0x1640 = 0x1990
26758Hz: 0x350 + (3136 x 2) = 0x350 + 0x1880 = 0x1BD0
31536Hz: 0x350 + (3696 x 2) = 0x350 + 0x1CE0 = 0x2030

cambiar el valor de PCM_DMA_BUF_SIZE pode defecto en include/gba/m4a_internal.h y constants/m4a_constants.inc
#define PCM_DMA_BUF_SIZE 1584 // size of Direct Sound buffer

5734Hz: 672
7884Hz: 924 (This mode is not aligned to the buffer length and is not supported by the mixer)
10512Hz: 1232
13379Hz: 1568 (As mentioned, the actual value used by the default mixer adds 16 to this)
15768Hz: 1848
18157Hz: 2128
21024Hz: 2464 // +16 = 2480
26758Hz: 3136
31536Hz: 3696
36314Hz: 4256
40137Hz: 4704
42048Hz: 4928

*/

//VBlankIntr
.org 0x080007B4
    .word gSoundInfo

//m4aSoundInit
.org 0x081DD0C0
    .word gSoundInfo


//PCM_DMA_BUF_SIZE
//081dd598 g 000000a4 SampleFreqSet FR
/*
DEFAULT: 13379Hz: 1568 +16 = 1584
mov r0, #0xC6
lsl r0, r0, #3

//31536Hz: 3696
//    mov r0, #0xE7
//    lsl r0, r0, #0x04
*/
.org 0x081DD5B8
//21024Hz: 2464 +16 = 2480
    mov r0, #0x9B
    lsl r0, r0, #0x04



//SOUND_MODE_FREQ_31536
//PCM_DMA_BUF_SIZE
//sizeof(struct SoundInfo)
//081dd4a0 g 000000f8 SoundInit FR
/*
13379Hz: 0x350 + 1584 = 2432 = 0x980
    mov r2, #0x98
    lsl r2, r2, #0x04

21024Hz: 0x350 + 2480 = 3328 = 0xD00
26758Hz: 0x350 + 3136 = 3984 = 0xF90
31536Hz: 0x350 + 3696 = 4544 = 0x11C0
    mov r2, #0x8E
    lsl r2, r2, #0x05 //4544 = 0x11C0
*/
.org 0x081DD506
    mov r2, #0xD0
//    lsl r2, r2, #0x04 //0xD00

/*
13379Hz: 0x050003EC
21024Hz: 0x05000664
26758Hz: 0x050006F4
31536Hz: 0x0500080C
*/
.org 0x081DD584
    .word 0x05000664


//PCM_DMA_BUF_SIZE
//sizeof soundInfo->pcmBuffer
//081dd728 g 0000007c m4aSoundVSyncOff FR
/*
sizeof = 3168 = 0xC60
default: 0x05000318

CpuFill32(0, soundInfo->pcmBuffer, sizeof(soundInfo->pcmBuffer));
#define CpuFill32(value, dest, size) CPU_FILL(value, dest, size, 32)

CPU_FILL(0, soundInfo->pcmBuffer, sizeof(soundInfo->pcmBuffer), 32)

vu32 tmp = 0;
CpuSet((void *)&tmp, soundInfo->pcmBuffer, CPU_SET_32_BIT| CPU_SET_SRC_FIXED | (size/(32/8)) & 0x1FFFFF)

#define CPU_SET_SRC_FIXED 0x01000000
#define CPU_SET_16BIT     0x00000000
#define CPU_SET_32BIT     0x04000000

CpuSet(0, soundInfo->pcmBuffer, 0x04000000 | 0x01000000 | (size/(4))  & 0x1FFFFF)
CpuSet(0, soundInfo->pcmBuffer, 0x05000000 | (size/(4))  & 0x1FFFFF)
CpuSet(0, soundInfo->pcmBuffer, 0x05000000 | (0xC60/(4))  & 0x1FFFFF)
CpuSet(0, soundInfo->pcmBuffer, 0x05000000 | 0x318  & 0x1FFFFF)
CpuSet(0, soundInfo->pcmBuffer, 0x05000318  & 0x1FFFFF)


13379Hz: 0x05000318
21024Hz: 0x05000590
26758Hz: 0x05000620
31536Hz: 0x05000738
*/
.org 0x081DD7A0
    .word 0x05000590



//      Cambiar la frecuencia a ~(26758Hz)~> 31536Hz:
//-------------------------------------------------------------------------------
//original: C0 02
//nuevo:    00 03
//SOUND_MODE_FREQ_26758   0x00080000
////26758Hz
//.org 0x081dd546
//    lsl r0, r0, #0x0C

//SOUND_MODE_FREQ_31536   0x00090000
//31536Hz
//.org 0x081dd544
//    mov r0, #0x90
//    lsl r0, r0, #0x0C

//SOUND_MODE_FREQ_21024   0x00070000
//21024Hz
.org 0x081dd544
    mov r0, #0x70
    lsl r0, r0, #0x0C


//En 0x081dd0c8 cambiar
//0x0094C500 por 0x0098C500
//Para habilitar 12 canales de audio, cambiar a:
//0x0098CC00

//original  [5 canales   13379Hz]   :   00 C5 94 00
//nuevo     [12 canales  13379Hz]   :   00 CC 94 00
//nuevo     [12 canales  26758Hz]   :   00 CC 98 00
//nuevo     [12 canales  31536Hz]   :   00 CC 99 00

.org 0x081dd0c8
//    .word 0x0094CC00    //12 canales  13379Hz
//    .word 0x0098CC00    //12 canales  26758Hz
//    .word 0x0099CC00    //12 canales  31536Hz
    .word 0x0097CC00    //12 canales  21024Hz


//      Quitar el sistema de ayuda:
//-------------------------------------------------------------------------------
//      Se quita la siguiente función:
//      0813b870 g 000002c8 RunHelpSystemCallback
//      en
//08000510 l 00000034 CallCallbacks
//static void CallCallbacks(void)
.org 0x0800051a
    b   0x08000524

//      Quitar comprobador de memoria de gf_rfu_REQ_api:
//-------------------------------------------------------------------------------
//081e05b0 g 0000013c rfu_initializeAPI
.org 0x081e05be
    b   0x081e05d0

//      repuntear gf_rfu_REQ_api:
//-------------------------------------------------------------------------------
//03001190 l 00000e64 gf_rfu_REQ_api
//90 11 00 03
.org 0x080F8728
    .word gf_rfu_REQ_api

//      repuntear SoundMainRAM_Buffer:
//-------------------------------------------------------------------------------
//030028e0 g 00000800 SoundMainRAM_Buffer
//e0 28 00 03
.org 0x081DD0B8
    .word SoundMainRAM_Buffer

//e1 28 00 03
.org 0x081DC094
    .word (SoundMainRAM_Buffer + 1)

//      expandir el tamaño de SoundMainRAM_Buffer de 0x800 a 0xB40:
//-------------------------------------------------------------------------------
//en void m4aSoundInit(void)
//081dd034 g 000000b4 m4aSoundInit
//0x800/4 = 0x200   0xB40/4 = 0x2D0     0x04000200 -> 0x040002D0
.org 0x081DD0BC
    .word 0x040002D0

//-------------------------------------------------------------------------------
//      m4a_1.s
//-------------------------------------------------------------------------------

//  in  081dcf90 g 00000064 MidiKeyToFreq
//081dc010 g 00000010 umul3232H32
.org 0x081dc010
.area 0x10, 0xFF
    push {lr}
    ldr r3, =umul3232H32|1
    bl bx_r3_umul
    pop {pc}
bx_r3_umul:
    bx r3
.pool
.endarea

//  in  081dd0e8 g 0000000a m4aSoundMain
//081dc020 g 00000084 SoundMain
.org 0x081dc020
.area 0x84, 0xFF
    push {lr}
    ldr r3, =SoundMain|1
    bl bx_r3_SoundMain
    pop {pc}
bx_r3_SoundMain:
    bx r3
.pool
.endarea

//  in  081dd034 g 000000b4 m4aSoundInit
//081dc0a4 g 000003bc SoundMainRAM
.org 0x081dd0b4
    .word SoundMainRAM|1

//  in  081dd4a0 g 000000f8 SoundInit
//081dccfc g 00000204 ply_note
//fd cc 1d 08
.org 0x081dd588
    .word ply_note|1

//081dc810 g 00000016 MPlayJumpTableCopy
.org 0x081dc810
.area 0x16, 0xFF
    push {lr}
    ldr r3, =MPlayJumpTableCopy|1
    bl bx_r3_MPlayJumpTableCopy
    pop {pc}
bx_r3_MPlayJumpTableCopy:
    bx r3
.pool
.endarea

//  in  0800080c l 00000038 VCountIntr
//081dc9d4 g 0000004c m4aSoundVSync
.org 0x081dc9d4
.area 0x4C, 0xFF
    push {lr}
    ldr r3, =m4aSoundVSync|1
    bl bx_r3_m4aSoundVSync
    pop {pc}
bx_r3_m4aSoundVSync:
    bx r3
.pool
.endarea

//  in  081dd7e0 g 00000078 MPlayOpen
//081dca20 g 00000268 MPlayMain
//21 ca 1d 08
.org 0x081dd854
    .word MPlayMain|1

//081dcc88 g 00000044 TrackStop
.org 0x081dcc88
.area 0x44, 0xFF
    push {lr}
    ldr r3, =TrackStop|1
    bl bx_r3_TrackStop
    pop {pc}
bx_r3_TrackStop:
    bx r3
.pool
.endarea

//  in  081dd35c g 00000118 MPlayExtender
//081dcc88 g 00000044 TrackStop
//89 cc 1d 08
.org 0x081dd454
    .word TrackStop|1

//081dcf00 g 00000040 ply_endtie
//01 cf 1d 08
.org 0x081dd44c
    .word ply_endtie|1

//081dcf68 g 00000012 ply_lfos
//69 cf 1d 08
.org 0x081dd440
    .word ply_lfos|1

//081dcf7c g 00000012 ply_mod
//7d cf 1d 08
.org 0x081dd444
    .word ply_mod|1


