__aeabi_idiv        = 0x081e3b68|1;
__aeabi_idivmod     = 0x081e3b68|1;
__aeabi_uidiv       = 0x081e3b68|1;
__aeabi_uidivmod    = 0x081e3b68|1;
__divsi3            = 0x081e4018|1;
__udivsi3           = 0x081e460c|1;
__umodsi3           = 0x081e4684|1;
__modsi3            = 0x081e40f4|1;
memcpy              = 0x081e5e78|1;
memset              = 0x081e5ed8|1;
strcmp              = 0x081e5f2c|1;
strcpy              = 0x081e5f88|1;
memmove             = 0x081e8e60|1;
Sqrt                = 0x081e3b9c|1;


/* EWRAM */


/* IWRAM */
gEvIv           = 0x03007490;
sMusicPlayerUI  = 0x03007494;




/*
    ----    MIXER   ----
*/
/*
03005f50 gSoundInfo size:
13379Hz: 0x350 + (1584 x 2) = 0x350 + 0xC60  = 0xFB0
21024Hz: 0x350 + (2480 x 2) = 0x350 + 0x1640 = 0x1990
26758Hz: 0x350 + (3136 x 2) = 0x350 + 0x1880 = 0x1BD0
31536Hz: 0x350 + (3696 x 2) = 0x350 + 0x1CE0 = 0x2030
*/
/*03005f50 g 00000fb0 gSoundInfo*/
/*gSoundInfo = 0x03005f50;*/
gSoundInfo = 0x0203C990;/*0x03005f50;*/
/*end:  0x0203E320*/
/*next: 0x0203E9E0*/

/*sizeof(hq_buffer_ptr) = 0x840*/
hq_buffer_ptr   = 0x03002840;/*03002840 l 000000a0 openfiles*/
/*hq_buffer_ptr   = 0x030028e0;/* SoundMainRAM_Buffer hasta 0x030030e0 = 0x8A0*/

/*expandir el tamaño de SoundMainRAM_Buffer de 0x800 a 0xB40:*/
/*030028e0 g 00000800 SoundMainRAM_Buffer*/
SoundMainRAM_Buffer = 0x03001190;

/*Free: 0x324*/
/*expand sizeof 0x320 gMPlayTrack_BGM to 0x500
repoint gMPlayTrack_SE1 & gMPlayTrack_SE2
030020c8 g 00000320 gMPlayTrack_BGM
030023e8 g 000000f0 gMPlayTrack_SE1
030024d8 g 000002d0 gMPlayTrack_SE2
030027a8 g 00000050 gMPlayTrack_SE3
*/
gMPlayTrack_SE1 = 0x030025C8;
gMPlayTrack_SE2 = 0x03001CD0;/*03001190 + 0xB40*/


/*03001190 l 00000e64 gf_rfu_REQ_api*/
gf_rfu_REQ_api = 0x0203b174;
/*end: 0x0203BFD8*/
/* ? 0x0203BFD8 + 0x9B8 =  0x0203C990*/







UpdatePaletteFade = 0x080704d0|1;
StringCopy = 0x08008d84|1;
GetSpeciesName = 0x08040fd0|1;


BlitMoveInfoIcon                = 0x08107d68|1;
AddTextPrinterParameterized3    = 0x0812e51c|1;
AddTextPrinterParameterized4    = 0x0812e5a4|1;
PutWindowTilemap                = 0x08003fa0|1;


LoadPalette             = 0x080703ec|1;
CopyWindowToVram        = 0x08003f20|1;
FillWindowPixelBuffer   = 0x0800445c|1;


CpuSet =0x081e3b64|1;
EnableInterrupts =0x08000b68|1;
SetHBlankCallback =0x08000700|1;


PlayBGM = 0x080722a0|1;


VarGet      = 0x0806e568|1;
VarSet      = 0x0806e584|1;
FlagSet     = 0x0806e680|1;
FlagClear   = 0x0806e6a8|1;
FlagGet     = 0x0806e6d0|1;
Random      = 0x08044ec8|1;


SetMainCallback2 = 0x08000544|1;
AllocZeroed = 0x08002bb0|1;
Free = 0x08002bc4|1;

CreateTask = 0x0807741c|1;
DestroyTask = 0x08077508|1;
FindTaskIdByFunc = 0x08077688|1;
BlitBitmapRectToWindow = 0x080041f0|1;
SetGpuReg = 0x08000a38|1;
ConvertIntToDecimalStringN = 0x08008e78|1;
RemoveWindow = 0x08003e3c|1;
CopyToBgTilemapBuffer = 0x08002040|1;
CopyBgTilemapBufferToVram = 0x080020bc|1;
UnsetBgTilemapBuffer = 0x08001fd4|1;
FillBgTilemapBufferRect_Palette0 = 0x08002454|1;
ChangeBgX = 0x08001b90|1;
ChangeBgY = 0x08001d08|1;
ScanlineEffect_Stop = 0x08087e64|1;


ScriptReadHalfword = 0x080698f8|1;


SetHelpContext = 0x0812b1f0|1;
HelpSystem_Enable = 0x0812b484|1;
m4aMPlayAllStop = 0x081dd228|1;

CB2_ReturnToField = 0x080567dc|1;


CB2_ReturnToFieldContinueScriptPlayMapMusic = 0x080568e0|1;
GetVarPointer = 0x0806e454|1;
ConvertIntToHexStringN = 0x08008f18|1;
ClearStdWindowAndFrameToTransparent = 0x0810f4d8|1;
ScheduleBgCopyTilemapToVram = 0x080f67a4|1;
FreeSpritePaletteByTag = 0x08008a30|1;
AddTextPrinterParameterized = 0x08002c48|1;
DrawStdFrameWithCustomTileAndPalette = 0x0810f2e8|1;
LoadSpritePalette = 0x08008928|1;
CreateSpriteAtEnd = 0x08006fe0|1;
DestroySprite = 0x08007280|1;
DrawDialogFrameWithCustomTileAndPalette = 0x0810edc4|1;
TrySavingData = 0x080da364|1;
DoScheduledBgTilemapCopiesToVram = 0x080f67b8|1;
ResetOamRange = 0x080072e8|1;
ScanlineEffect_Clear = 0x08087ea4|1;
ClearScheduledBgCopiesToVram = 0x080f6790|1;
LoadStdWindowFrameGfx = 0x080f6e9c|1;



/*  EV-IV summary screen*/
DestroySpriteAndFreeResources               = 0x08007804|1;
GetTextWindowPalette                        = 0x08150408|1;/*stdpal_get*/
ListMenuLoadStdPalAt                        = 0x08107d38|1;
PlaySE                                      = 0x080722cc|1;
GetNature                                   = 0x08042e9c|1;
GetMonNickname                              = 0x081202e0|1;
QuestLog_CutRecording                       = 0x08112364|1;
RunTasks                                    = 0x08077578|1;
AnimateSprites                              = 0x08006b5c|1;
BuildOamBuffer                              = 0x08006ba8|1;
ResetSpriteData                             = 0x08006b10|1;
ResetPaletteFade                            = 0x08070528|1;
FreeAllSpritePalettes                       = 0x080088f0|1;
ResetTasks                                  = 0x080773bc|1;
SetVBlankCallback                           = 0x080006f4|1;
BeginNormalPaletteFade                      = 0x08070588|1;
ResetBgsAndClearDma3BusyFlags               = 0x08001618|1;
InitBgsFromTemplates                        = 0x08001658|1;
InitWindows                                 = 0x08003b24|1;
DeactivateAllTextPrinters                   = 0x08002c28|1;
SetBgTilemapBuffer                          = 0x08001fa0|1;
ShowBg                                      = 0x080019bc|1;
ResetTempTileDataBuffers                    = 0x080f6808|1;
DecompressAndCopyTileDataToVram             = 0x080f6878|1;
FreeTempTileDataBuffersIfPossible           = 0x080f682c|1;
LoadOam                                     = 0x08007320|1;
ProcessSpriteCopyRequests                   = 0x08007610|1;
TransferPlttBuffer                          = 0x08070474|1;
FreeAllWindowBuffers                        = 0x08003ecc|1;
CB2_ReturnToFieldFromDiploma                = 0x080568fc|1;
PlayCry7                                    = 0x08071f24|1;
IsCryPlaying                                = 0x08072214|1;
CreateMonSprite_FieldMove                   = 0x080839d4|1;/*static u8*/
FreeResourcesAndDestroySprite               = 0x08083a5c|1;
SpriteCallbackDummy                         = 0x0800760c|1;
GetMonSpritePalStructFromOtIdPersonality    = 0x08044180|1;
IndexOfSpritePaletteTag                     = 0x080089e8|1;
PreservePaletteInWeather                    = 0x0807b084|1;
CreateMonPicSprite_HandleDeoxys             = 0x0810c1cc|1;



/*const*/
/*gMPlayTable = 0x084a329c;*/

/*func*/
MPlayStart = 0x081dd858|1;
m4aSongNumStart = 0x081dd0f4|1;
/*m4a_1.s*/
FadeOutBody = 0x081dd97c|1;
ClearChain = 0x081dd478|1;
Clear64byte = 0x081dd48c|1;
TrkVolPitSet = 0x081dda44|1;
MidiKeyToFreq = 0x081dcf90|1;
SampleFreqSet = 0x081dd598|1;

PlayCry_Normal = 0x08071df0|1;
GetStringWidth = 0x08005ed4|1;

/*voice group*/
/*
voicegroup000 = 0x08489c8c;
voicegroup001 = 0x08489f74;
voicegroup002 = 0x0848a0d0;
voicegroup003 = 0x0848a508;
voicegroup004 = 0x0848a538;
voicegroup005 = 0x0848a55c;
voicegroup006 = 0x0848ab80;
voicegroup007 = 0x0848ab98;
voicegroup008 = 0x0848abb0;
voicegroup009 = 0x0848b078;
voicegroup010 = 0x0848b474;
voicegroup011 = 0x0848b8b8;
voicegroup012 = 0x0848bcfc;
voicegroup127 = 0x0848bd14;
voicegroup128 = 0x0848c314;
gCryTable = 0x0848c914;
gCryTable2 = 0x0848db44;
voicegroup129 = 0x0848ed74;
voicegroup130 = 0x0848f374;
voicegroup131 = 0x0848f974;
voicegroup132 = 0x0848ff74;
voicegroup133 = 0x08490574;
voicegroup134 = 0x08490b74;
voicegroup135 = 0x08490fac;
voicegroup136 = 0x08491390;
voicegroup137 = 0x08491990;
voicegroup138 = 0x08491f90;
voicegroup139 = 0x08492590;
voicegroup140 = 0x08492b90;
voicegroup141 = 0x08492bc0;
voicegroup142 = 0x084931c0;
voicegroup143 = 0x084935b0;
voicegroup144 = 0x08493bb0;
voicegroup145 = 0x084941b0;
voicegroup146 = 0x084947b0;
voicegroup147 = 0x08494db0;
voicegroup148 = 0x084951a0;
voicegroup149 = 0x084957a0;
voicegroup150 = 0x08495bfc;
voicegroup151 = 0x084961fc;
voicegroup152 = 0x0849661c;
voicegroup153 = 0x08496c1c;
voicegroup154 = 0x0849721c;
voicegroup155 = 0x08497678;
voicegroup156 = 0x08497c78;
voicegroup157 = 0x08498278;
voicegroup158 = 0x08498878;
voicegroup159 = 0x08498e78;
voicegroup160 = 0x08499478;
voicegroup161 = 0x08499898;
voicegroup162 = 0x08499e98;
voicegroup163 = 0x0849a2f4;
voicegroup164 = 0x0849a8f4;
voicegroup165 = 0x0849aef4;
voicegroup166 = 0x0849b4f4;
voicegroup167 = 0x0849baf4;
voicegroup168 = 0x0849c0f4;
voicegroup169 = 0x0849c6f4;
voicegroup170 = 0x0849ccf4;
voicegroup171 = 0x0849d0e4;
voicegroup172 = 0x0849d528;
voicegroup173 = 0x0849db28;
voicegroup174 = 0x0849e128;
voicegroup175 = 0x0849e884;
voicegroup176 = 0x0849eaf4;
voicegroup177 = 0x0849ed34;
voicegroup178 = 0x0849f16c;
voicegroup179 = 0x0849f58c;
voicegroup180 = 0x0849f9ac;
voicegroup181 = 0x0849ffac;
voicegroup182 = 0x084a01e0;
voicegroup183 = 0x084a0600;
voicegroup184 = 0x084a0c00;
voicegroup185 = 0x084a1008;
voicegroup186 = 0x084a1608;
voicegroup187 = 0x084a1c08;
voicegroup188 = 0x084a2208;
voicegroup189 = 0x084a2808;
voicegroup190 = 0x084a2c58;
*/

