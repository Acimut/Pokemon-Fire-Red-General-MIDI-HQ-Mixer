#include "global.h"
#include "gflib.h"
#include "event_data.h"
#include "dynamic_placeholder_text_util.h"
#include "menu.h"
#include "new_menu_helpers.h"
#include "overworld.h"
#include "pokedex.h"
#include "scanline_effect.h"
#include "strings.h"
#include "task.h"
#include "text_window.h"

enum
{
    WIN_TITTLE,
    WIN_NUMBER,
    WIN_MUSIC_NAME,
    WIN_BUTTONS,
    WIN_PLAYER_TYPE,
};

enum
{
    PAGE_MUSIC_PLAYER,
    PAGE_CRY_PLAYER
};

struct MusicPlayerUI
{
    u8 state;
    u8 gfxStep;
    u8 callbackStep;
    u8 page;
    u16 music_id;
    u16 specie;
    u16 tilemapBuffer[0x400];
};

extern struct MusicPlayerUI *sMusicPlayerUI;


static void MusicPlayerBgInit(void);
static void MusicPlayerPrintText(void);
static u8 MusicPlayerLoadGfx(void);
static void MusicPlayerVblankHandler(void);
static void MainCB2_MusicPlayer(void);
static void Task_WaitForExit(u8);
static void Task_MusicPlayerInit(u8);
static void Task_MusicPlayerReturnToOverworld(u8);

u8 GetDigitsDec(u32 num);
u8 GetDigitsHex(u32 num);

//--------------------------------------
//static not

//--------------------------------------
//      GRAPHICS
//--------------------------------------
static const u32 sMPlayerGfx[] = INCBIN_U32("graphics/MPlayer.4bpp.lz");
static const u32 sMPlayerTilemap[] = INCBIN_U32("graphics/MPlayer.bin.lz");
static const u16 sMPlayerPal[] = INCBIN_U16("graphics/MPlayer.gbapal");


//--------------------------------------
//      TEXT
//--------------------------------------
static const u8 sText_Tittle_Player[] = _("POKéMON MUSIC PLAYER");
static const u8 sText_Tittle_Cry[] = _("POKéMON CRY PLAYER");
static const u8 sText_ExitPlayer[] = _("{B_BUTTON}SALIR");
static const u8 sText_Buttons[] = _("{DPAD_UPDOWN}PÁG.{CLEAR_TO 60}{DPAD_LEFTRIGHT}SEL.{CLEAR_TO 120}{A_BUTTON}PLAY");


//include/constants/songs.h

//static const u8 sText_MUS_DUMMY[] = _("MUS DUMMY");
static const u8 sText_SE_USE_ITEM[] = _("SE USE ITEM");
static const u8 sText_SE_PC_LOGIN[] = _("SE PC LOGIN");
static const u8 sText_SE_PC_OFF[] = _("SE PC OFF");
static const u8 sText_SE_PC_ON[] = _("SE PC ON");
static const u8 sText_SE_SELECT[] = _("SE SELECT");
static const u8 sText_SE_WIN_OPEN[] = _("SE WIN OPEN");
static const u8 sText_SE_WALL_HIT[] = _("SE WALL HIT");
static const u8 sText_SE_RS_DOOR[] = _("SE RS DOOR");
static const u8 sText_SE_EXIT[] = _("SE EXIT");
static const u8 sText_SE_LEDGE[] = _("SE LEDGE");
static const u8 sText_SE_BIKE_BELL[] = _("SE BIKE BELL");
static const u8 sText_SE_NOT_EFFECTIVE[] = _("SE NOT EFFECTIVE");
static const u8 sText_SE_EFFECTIVE[] = _("SE EFFECTIVE");
static const u8 sText_SE_SUPER_EFFECTIVE[] = _("SE SUPER EFFECTIVE");
static const u8 sText_SE_BALL_OPEN[] = _("SE BALL OPEN");
static const u8 sText_SE_FAINT[] = _("SE FAINT");
static const u8 sText_SE_FLEE[] = _("SE FLEE");
static const u8 sText_SE_SLIDING_DOOR[] = _("SE SLIDING DOOR");
static const u8 sText_SE_SHIP[] = _("SE SHIP");
static const u8 sText_SE_BANG[] = _("SE BANG");
static const u8 sText_SE_PIN[] = _("SE PIN");
static const u8 sText_SE_BOO[] = _("SE BOO");
static const u8 sText_SE_BALL[] = _("SE BALL");
static const u8 sText_SE_CONTEST_PLACE[] = _("SE CONTEST PLACE");
static const u8 sText_SE_SUCCESS[] = _("SE SUCCESS");
static const u8 sText_SE_FAILURE[] = _("SE FAILURE");
static const u8 sText_SE_EXP[] = _("SE EXP");
static const u8 sText_SE_BIKE_HOP[] = _("SE BIKE HOP");
static const u8 sText_SE_SWITCH[] = _("SE SWITCH");
static const u8 sText_SE_CLICK[] = _("SE CLICK");
static const u8 sText_SE_FU_ZAKU[] = _("SE FU ZAKU");
static const u8 sText_SE_CONTEST_CONDITION_LOSE[] = _("SE CONTEST CONDITION LOSE");
static const u8 sText_SE_LAVARIDGE_FALL_WARP[] = _("SE LAVARIDGE FALL WARP");
static const u8 sText_SE_ICE_STAIRS[] = _("SE ICE STAIRS");
static const u8 sText_SE_ICE_BREAK[] = _("SE ICE BREAK");
static const u8 sText_SE_ICE_CRACK[] = _("SE ICE CRACK");
static const u8 sText_SE_FALL[] = _("SE FALL");
static const u8 sText_SE_UNLOCK[] = _("SE UNLOCK");
static const u8 sText_SE_WARP_IN[] = _("SE WARP IN");
static const u8 sText_SE_WARP_OUT[] = _("SE WARP OUT");
static const u8 sText_SE_REPEL[] = _("SE REPEL");
static const u8 sText_SE_ROTATING_GATE[] = _("SE ROTATING GATE");
static const u8 sText_SE_TRUCK_MOVE[] = _("SE TRUCK MOVE");
static const u8 sText_SE_TRUCK_STOP[] = _("SE TRUCK STOP");
static const u8 sText_SE_TRUCK_UNLOAD[] = _("SE TRUCK UNLOAD");
static const u8 sText_SE_TRUCK_DOOR[] = _("SE TRUCK DOOR");
static const u8 sText_SE_BERRY_BLENDER[] = _("SE BERRY BLENDER");
static const u8 sText_SE_SAVE[] = _("SE SAVE");
static const u8 sText_SE_BALL_BOUNCE_1[] = _("SE BALL BOUNCE 1");
static const u8 sText_SE_BALL_BOUNCE_2[] = _("SE BALL BOUNCE 2");
static const u8 sText_SE_BALL_BOUNCE_3[] = _("SE BALL BOUNCE 3");
static const u8 sText_SE_BALL_BOUNCE_4[] = _("SE BALL BOUNCE 4");
static const u8 sText_SE_BALL_TRADE[] = _("SE BALL TRADE");
static const u8 sText_SE_BALL_THROW[] = _("SE BALL THROW");
static const u8 sText_SE_NOTE_C[] = _("SE NOTE C");
static const u8 sText_SE_NOTE_D[] = _("SE NOTE D");
static const u8 sText_SE_NOTE_E[] = _("SE NOTE E");
static const u8 sText_SE_NOTE_F[] = _("SE NOTE F");
static const u8 sText_SE_NOTE_G[] = _("SE NOTE G");
static const u8 sText_SE_NOTE_A[] = _("SE NOTE A");
static const u8 sText_SE_NOTE_B[] = _("SE NOTE B");
static const u8 sText_SE_NOTE_C_HIGH[] = _("SE NOTE C HIGH");
static const u8 sText_SE_PUDDLE[] = _("SE PUDDLE");
static const u8 sText_SE_BRIDGE_WALK[] = _("SE BRIDGE WALK");
static const u8 sText_SE_ITEMFINDER[] = _("SE ITEMFINDER");
static const u8 sText_SE_DING_DONG[] = _("SE DING DONG");
static const u8 sText_SE_BALLOON_RED[] = _("SE BALLOON RED");
static const u8 sText_SE_BALLOON_BLUE[] = _("SE BALLOON BLUE");
static const u8 sText_SE_BALLOON_YELLOW[] = _("SE BALLOON YELLOW");
static const u8 sText_SE_BREAKABLE_DOOR[] = _("SE BREAKABLE DOOR");
static const u8 sText_SE_MUD_BALL[] = _("SE MUD BALL");
static const u8 sText_SE_FIELD_POISON[] = _("SE FIELD POISON");
static const u8 sText_SE_ESCALATOR[] = _("SE ESCALATOR");
static const u8 sText_SE_THUNDERSTORM[] = _("SE THUNDERSTORM");
static const u8 sText_SE_THUNDERSTORM_STOP[] = _("SE THUNDERSTORM STOP");
static const u8 sText_SE_DOWNPOUR[] = _("SE DOWNPOUR");
static const u8 sText_SE_DOWNPOUR_STOP[] = _("SE DOWNPOUR STOP");
static const u8 sText_SE_RAIN[] = _("SE RAIN");
static const u8 sText_SE_RAIN_STOP[] = _("SE RAIN STOP");
static const u8 sText_SE_THUNDER[] = _("SE THUNDER");
static const u8 sText_SE_THUNDER2[] = _("SE THUNDER2");
static const u8 sText_SE_ELEVATOR[] = _("SE ELEVATOR");
static const u8 sText_SE_LOW_HEALTH[] = _("SE LOW HEALTH");
static const u8 sText_SE_EXP_MAX[] = _("SE EXP MAX");
static const u8 sText_SE_ROULETTE_BALL[] = _("SE ROULETTE BALL");
static const u8 sText_SE_ROULETTE_BALL2[] = _("SE ROULETTE BALL2");
static const u8 sText_SE_TAILLOW_WING_FLAP[] = _("SE TAILLOW WING FLAP");
static const u8 sText_SE_RS_SHOP[] = _("SE RS SHOP");
static const u8 sText_SE_CONTEST_HEART[] = _("SE CONTEST HEART");
static const u8 sText_SE_CONTEST_CURTAIN_RISE[] = _("SE CONTEST CURTAIN RISE");
static const u8 sText_SE_CONTEST_CURTAIN_FALL[] = _("SE CONTEST CURTAIN FALL");
static const u8 sText_SE_CONTEST_ICON_CHANGE[] = _("SE CONTEST ICON CHANGE");
static const u8 sText_SE_CONTEST_ICON_CLEAR[] = _("SE CONTEST ICON CLEAR");
static const u8 sText_SE_CONTEST_MONS_TURN[] = _("SE CONTEST MONS TURN");
static const u8 sText_SE_SHINY[] = _("SE SHINY");
static const u8 sText_SE_INTRO_BLAST[] = _("SE INTRO BLAST");
static const u8 sText_SE_MUGSHOT[] = _("SE MUGSHOT");
static const u8 sText_SE_APPLAUSE[] = _("SE APPLAUSE");
static const u8 sText_SE_VEND[] = _("SE VEND");
static const u8 sText_SE_ORB[] = _("SE ORB");
static const u8 sText_SE_DEX_SCROLL[] = _("SE DEX SCROLL");
static const u8 sText_SE_DEX_PAGE[] = _("SE DEX PAGE");
static const u8 sText_SE_POKENAV_ON[] = _("SE POKENAV ON");
static const u8 sText_SE_POKENAV_OFF[] = _("SE POKENAV OFF");
static const u8 sText_SE_DEX_SEARCH[] = _("SE DEX SEARCH");
static const u8 sText_SE_EGG_HATCH[] = _("SE EGG HATCH");
static const u8 sText_SE_BALL_TRAY_ENTER[] = _("SE BALL TRAY ENTER");
static const u8 sText_SE_BALL_TRAY_BALL[] = _("SE BALL TRAY BALL");
static const u8 sText_SE_BALL_TRAY_EXIT[] = _("SE BALL TRAY EXIT");
static const u8 sText_SE_GLASS_FLUTE[] = _("SE GLASS FLUTE");
// Move SFX
static const u8 sText_SE_M_THUNDERBOLT[] = _("SE M THUNDERBOLT");
static const u8 sText_SE_M_THUNDERBOLT2[] = _("SE M THUNDERBOLT2");
static const u8 sText_SE_M_HARDEN[] = _("SE M HARDEN");
static const u8 sText_SE_M_NIGHTMARE[] = _("SE M NIGHTMARE");
static const u8 sText_SE_M_VITAL_THROW[] = _("SE M VITAL THROW");
static const u8 sText_SE_M_VITAL_THROW2[] = _("SE M VITAL THROW2");
static const u8 sText_SE_M_BUBBLE[] = _("SE M BUBBLE");
static const u8 sText_SE_M_BUBBLE2[] = _("SE M BUBBLE2");
static const u8 sText_SE_M_BUBBLE3[] = _("SE M BUBBLE3");
static const u8 sText_SE_M_RAIN_DANCE[] = _("SE M RAIN DANCE");
static const u8 sText_SE_M_CUT[] = _("SE M CUT");
static const u8 sText_SE_M_STRING_SHOT[] = _("SE M STRING SHOT");
static const u8 sText_SE_M_STRING_SHOT2[] = _("SE M STRING SHOT2");
static const u8 sText_SE_M_ROCK_THROW[] = _("SE M ROCK THROW");
static const u8 sText_SE_M_GUST[] = _("SE M GUST");
static const u8 sText_SE_M_GUST2[] = _("SE M GUST2");
static const u8 sText_SE_M_DOUBLE_SLAP[] = _("SE M DOUBLE SLAP");
static const u8 sText_SE_M_DOUBLE_TEAM[] = _("SE M DOUBLE TEAM");
static const u8 sText_SE_M_RAZOR_WIND[] = _("SE M RAZOR WIND");
static const u8 sText_SE_M_ICY_WIND[] = _("SE M ICY WIND");
static const u8 sText_SE_M_THUNDER_WAVE[] = _("SE M THUNDER WAVE");
static const u8 sText_SE_M_COMET_PUNCH[] = _("SE M COMET PUNCH");
static const u8 sText_SE_M_MEGA_KICK[] = _("SE M MEGA KICK");
static const u8 sText_SE_M_MEGA_KICK2[] = _("SE M MEGA KICK2");
static const u8 sText_SE_M_CRABHAMMER[] = _("SE M CRABHAMMER");
static const u8 sText_SE_M_JUMP_KICK[] = _("SE M JUMP KICK");
static const u8 sText_SE_M_FLAME_WHEEL[] = _("SE M FLAME WHEEL");
static const u8 sText_SE_M_FLAME_WHEEL2[] = _("SE M FLAME WHEEL2");
static const u8 sText_SE_M_FLAMETHROWER[] = _("SE M FLAMETHROWER");
static const u8 sText_SE_M_FIRE_PUNCH[] = _("SE M FIRE PUNCH");
static const u8 sText_SE_M_TOXIC[] = _("SE M TOXIC");
static const u8 sText_SE_M_SACRED_FIRE[] = _("SE M SACRED FIRE");
static const u8 sText_SE_M_SACRED_FIRE2[] = _("SE M SACRED FIRE2");
static const u8 sText_SE_M_EMBER[] = _("SE M EMBER");
static const u8 sText_SE_M_TAKE_DOWN[] = _("SE M TAKE DOWN");
static const u8 sText_SE_M_BLIZZARD[] = _("SE M BLIZZARD");
static const u8 sText_SE_M_BLIZZARD2[] = _("SE M BLIZZARD2");
static const u8 sText_SE_M_SCRATCH[] = _("SE M SCRATCH");
static const u8 sText_SE_M_VICEGRIP[] = _("SE M VICEGRIP");
static const u8 sText_SE_M_WING_ATTACK[] = _("SE M WING ATTACK");
static const u8 sText_SE_M_FLY[] = _("SE M FLY");
static const u8 sText_SE_M_SAND_ATTACK[] = _("SE M SAND ATTACK");
static const u8 sText_SE_M_RAZOR_WIND2[] = _("SE M RAZOR WIND2");
static const u8 sText_SE_M_BITE[] = _("SE M BITE");
static const u8 sText_SE_M_HEADBUTT[] = _("SE M HEADBUTT");
static const u8 sText_SE_M_SURF[] = _("SE M SURF");
static const u8 sText_SE_M_HYDRO_PUMP[] = _("SE M HYDRO PUMP");
static const u8 sText_SE_M_WHIRLPOOL[] = _("SE M WHIRLPOOL");
static const u8 sText_SE_M_HORN_ATTACK[] = _("SE M HORN ATTACK");
static const u8 sText_SE_M_TAIL_WHIP[] = _("SE M TAIL WHIP");
static const u8 sText_SE_M_MIST[] = _("SE M MIST");
static const u8 sText_SE_M_POISON_POWDER[] = _("SE M POISON POWDER");
static const u8 sText_SE_M_BIND[] = _("SE M BIND");
static const u8 sText_SE_M_DRAGON_RAGE[] = _("SE M DRAGON RAGE");
static const u8 sText_SE_M_SING[] = _("SE M SING");
static const u8 sText_SE_M_PERISH_SONG[] = _("SE M PERISH SONG");
static const u8 sText_SE_M_PAY_DAY[] = _("SE M PAY DAY");
static const u8 sText_SE_M_DIG[] = _("SE M DIG");
static const u8 sText_SE_M_DIZZY_PUNCH[] = _("SE M DIZZY PUNCH");
static const u8 sText_SE_M_SELF_DESTRUCT[] = _("SE M SELF DESTRUCT");
static const u8 sText_SE_M_EXPLOSION[] = _("SE M EXPLOSION");
static const u8 sText_SE_M_ABSORB_2[] = _("SE M ABSORB 2");
static const u8 sText_SE_M_ABSORB[] = _("SE M ABSORB");
static const u8 sText_SE_M_SCREECH[] = _("SE M SCREECH");
static const u8 sText_SE_M_BUBBLE_BEAM[] = _("SE M BUBBLE BEAM");
static const u8 sText_SE_M_BUBBLE_BEAM2[] = _("SE M BUBBLE BEAM2");
static const u8 sText_SE_M_SUPERSONIC[] = _("SE M SUPERSONIC");
static const u8 sText_SE_M_BELLY_DRUM[] = _("SE M BELLY DRUM");
static const u8 sText_SE_M_METRONOME[] = _("SE M METRONOME");
static const u8 sText_SE_M_BONEMERANG[] = _("SE M BONEMERANG");
static const u8 sText_SE_M_LICK[] = _("SE M LICK");
static const u8 sText_SE_M_PSYBEAM[] = _("SE M PSYBEAM");
static const u8 sText_SE_M_FAINT_ATTACK[] = _("SE M FAINT ATTACK");
static const u8 sText_SE_M_SWORDS_DANCE[] = _("SE M SWORDS DANCE");
static const u8 sText_SE_M_LEER[] = _("SE M LEER");
static const u8 sText_SE_M_SWAGGER[] = _("SE M SWAGGER");
static const u8 sText_SE_M_SWAGGER2[] = _("SE M SWAGGER2");
static const u8 sText_SE_M_HEAL_BELL[] = _("SE M HEAL BELL");
static const u8 sText_SE_M_CONFUSE_RAY[] = _("SE M CONFUSE RAY");
static const u8 sText_SE_M_SNORE[] = _("SE M SNORE");
static const u8 sText_SE_M_BRICK_BREAK[] = _("SE M BRICK BREAK");
static const u8 sText_SE_M_GIGA_DRAIN[] = _("SE M GIGA DRAIN");
static const u8 sText_SE_M_PSYBEAM2[] = _("SE M PSYBEAM2");
static const u8 sText_SE_M_SOLAR_BEAM[] = _("SE M SOLAR BEAM");
static const u8 sText_SE_M_PETAL_DANCE[] = _("SE M PETAL DANCE");
static const u8 sText_SE_M_TELEPORT[] = _("SE M TELEPORT");
static const u8 sText_SE_M_MINIMIZE[] = _("SE M MINIMIZE");
static const u8 sText_SE_M_SKETCH[] = _("SE M SKETCH");
static const u8 sText_SE_M_SWIFT[] = _("SE M SWIFT");
static const u8 sText_SE_M_REFLECT[] = _("SE M REFLECT");
static const u8 sText_SE_M_BARRIER[] = _("SE M BARRIER");
static const u8 sText_SE_M_DETECT[] = _("SE M DETECT");
static const u8 sText_SE_M_LOCK_ON[] = _("SE M LOCK ON");
static const u8 sText_SE_M_MOONLIGHT[] = _("SE M MOONLIGHT");
static const u8 sText_SE_M_CHARM[] = _("SE M CHARM");
static const u8 sText_SE_M_CHARGE[] = _("SE M CHARGE");
static const u8 sText_SE_M_STRENGTH[] = _("SE M STRENGTH");
static const u8 sText_SE_M_HYPER_BEAM[] = _("SE M HYPER BEAM");
static const u8 sText_SE_M_WATERFALL[] = _("SE M WATERFALL");
static const u8 sText_SE_M_REVERSAL[] = _("SE M REVERSAL");
static const u8 sText_SE_M_ACID_ARMOR[] = _("SE M ACID ARMOR");
static const u8 sText_SE_M_SANDSTORM[] = _("SE M SANDSTORM");
static const u8 sText_SE_M_TRI_ATTACK[] = _("SE M TRI ATTACK");
static const u8 sText_SE_M_TRI_ATTACK2[] = _("SE M TRI ATTACK2");
static const u8 sText_SE_M_ENCORE[] = _("SE M ENCORE");
static const u8 sText_SE_M_ENCORE2[] = _("SE M ENCORE2");
static const u8 sText_SE_M_BATON_PASS[] = _("SE M BATON PASS");
static const u8 sText_SE_M_MILK_DRINK[] = _("SE M MILK DRINK");
static const u8 sText_SE_M_ATTRACT[] = _("SE M ATTRACT");
static const u8 sText_SE_M_ATTRACT2[] = _("SE M ATTRACT2");
static const u8 sText_SE_M_MORNING_SUN[] = _("SE M MORNING SUN");
static const u8 sText_SE_M_FLATTER[] = _("SE M FLATTER");
static const u8 sText_SE_M_SAND_TOMB[] = _("SE M SAND TOMB");
static const u8 sText_SE_M_GRASSWHISTLE[] = _("SE M GRASSWHISTLE");
static const u8 sText_SE_M_SPIT_UP[] = _("SE M SPIT UP");
static const u8 sText_SE_M_DIVE[] = _("SE M DIVE");
static const u8 sText_SE_M_EARTHQUAKE[] = _("SE M EARTHQUAKE");
static const u8 sText_SE_M_TWISTER[] = _("SE M TWISTER");
static const u8 sText_SE_M_SWEET_SCENT[] = _("SE M SWEET SCENT");
static const u8 sText_SE_M_YAWN[] = _("SE M YAWN");
static const u8 sText_SE_M_SKY_UPPERCUT[] = _("SE M SKY UPPERCUT");
static const u8 sText_SE_M_STAT_INCREASE[] = _("SE M STAT INCREASE");
static const u8 sText_SE_M_HEAT_WAVE[] = _("SE M HEAT WAVE");
static const u8 sText_SE_M_UPROAR[] = _("SE M UPROAR");
static const u8 sText_SE_M_HAIL[] = _("SE M HAIL");
static const u8 sText_SE_M_COSMIC_POWER[] = _("SE M COSMIC POWER");
static const u8 sText_SE_M_TEETER_DANCE[] = _("SE M TEETER DANCE");
static const u8 sText_SE_M_STAT_DECREASE[] = _("SE M STAT DECREASE");
static const u8 sText_SE_M_HAZE[] = _("SE M HAZE");
static const u8 sText_SE_M_HYPER_BEAM2[] = _("SE M HYPER BEAM2");
// New FRLG SFX
static const u8 sText_SE_DOOR[] = _("SE DOOR");
static const u8 sText_SE_CARD_FLIP[] = _("SE CARD FLIP");
static const u8 sText_SE_CARD_FLIPPING[] = _("SE CARD FLIPPING");
static const u8 sText_SE_CARD_OPEN[] = _("SE CARD OPEN");
static const u8 sText_SE_BAG_CURSOR[] = _("SE BAG CURSOR");
static const u8 sText_SE_BAG_POCKET[] = _("SE BAG POCKET");
static const u8 sText_SE_BALL_CLICK[] = _("SE BALL CLICK");
static const u8 sText_SE_SHOP[] = _("SE SHOP");
static const u8 sText_SE_SS_ANNE_HORN[] = _("SE SS ANNE HORN");
static const u8 sText_SE_HELP_OPEN[] = _("SE HELP OPEN");
static const u8 sText_SE_HELP_CLOSE[] = _("SE HELP CLOSE");
static const u8 sText_SE_HELP_ERROR[] = _("SE HELP ERROR");
static const u8 sText_SE_DEOXYS_MOVE[] = _("SE DEOXYS MOVE");
static const u8 sText_SE_POKE_JUMP_SUCCESS[] = _("SE POKE JUMP SUCCESS");
static const u8 sText_SE_POKE_JUMP_FAILURE[] = _("SE POKE JUMP FAILURE");
// Music kept from RS
static const u8 sText_MUS_HEAL[] = _("MUS HEAL");
static const u8 sText_MUS_LEVEL_UP[] = _("MUS LEVEL UP");
static const u8 sText_MUS_OBTAIN_ITEM[] = _("MUS OBTAIN ITEM");
static const u8 sText_MUS_EVOLVED[] = _("MUS EVOLVED");
static const u8 sText_MUS_OBTAIN_BADGE[] = _("MUS OBTAIN BADGE");
static const u8 sText_MUS_OBTAIN_TMHM[] = _("MUS OBTAIN TMHM");
static const u8 sText_MUS_OBTAIN_BERRY[] = _("MUS OBTAIN BERRY");
static const u8 sText_MUS_EVOLUTION_INTRO[] = _("MUS EVOLUTION INTRO");
static const u8 sText_MUS_EVOLUTION[] = _("MUS EVOLUTION");
static const u8 sText_MUS_RS_VS_GYM_LEADER[] = _("MUS RS VS GYM LEADER");
static const u8 sText_MUS_RS_VS_TRAINER[] = _("MUS RS VS TRAINER");
static const u8 sText_MUS_SCHOOL[] = _("MUS SCHOOL");
static const u8 sText_MUS_SLOTS_JACKPOT[] = _("MUS SLOTS JACKPOT");
static const u8 sText_MUS_SLOTS_WIN[] = _("MUS SLOTS WIN");
static const u8 sText_MUS_MOVE_DELETED[] = _("MUS MOVE DELETED");
static const u8 sText_MUS_TOO_BAD[] = _("MUS TOO BAD");
// New FRLG Music
static const u8 sText_MUS_FOLLOW_ME[] = _("MUS FOLLOW ME");
static const u8 sText_MUS_GAME_CORNER[] = _("MUS GAME CORNER");
static const u8 sText_MUS_ROCKET_HIDEOUT[] = _("MUS ROCKET HIDEOUT");
static const u8 sText_MUS_GYM[] = _("MUS GYM");
static const u8 sText_MUS_JIGGLYPUFF[] = _("MUS JIGGLYPUFF");
static const u8 sText_MUS_INTRO_FIGHT[] = _("MUS INTRO FIGHT");
static const u8 sText_MUS_TITLE[] = _("MUS TITLE");
static const u8 sText_MUS_CINNABAR[] = _("MUS CINNABAR");
static const u8 sText_MUS_LAVENDER[] = _("MUS LAVENDER");
static const u8 sText_MUS_HEAL_UNUSED[] = _("MUS HEAL UNUSED");
static const u8 sText_MUS_CYCLING[] = _("MUS CYCLING");
static const u8 sText_MUS_ENCOUNTER_ROCKET[] = _("MUS ENCOUNTER ROCKET");
static const u8 sText_MUS_ENCOUNTER_GIRL[] = _("MUS ENCOUNTER GIRL");
static const u8 sText_MUS_ENCOUNTER_BOY[] = _("MUS ENCOUNTER BOY");
static const u8 sText_MUS_HALL_OF_FAME[] = _("MUS HALL OF FAME");
static const u8 sText_MUS_VIRIDIAN_FOREST[] = _("MUS VIRIDIAN FOREST");
static const u8 sText_MUS_MT_MOON[] = _("MUS MT MOON");
static const u8 sText_MUS_POKE_MANSION[] = _("MUS POKE MANSION");
static const u8 sText_MUS_CREDITS[] = _("MUS CREDITS");
static const u8 sText_MUS_ROUTE1[] = _("MUS ROUTE1");
static const u8 sText_MUS_ROUTE24[] = _("MUS ROUTE24");
static const u8 sText_MUS_ROUTE3[] = _("MUS ROUTE3");
static const u8 sText_MUS_ROUTE11[] = _("MUS ROUTE11");
static const u8 sText_MUS_VICTORY_ROAD[] = _("MUS VICTORY ROAD");
static const u8 sText_MUS_VS_GYM_LEADER[] = _("MUS VS GYM LEADER");
static const u8 sText_MUS_VS_TRAINER[] = _("MUS VS TRAINER");
static const u8 sText_MUS_VS_WILD[] = _("MUS VS WILD");
static const u8 sText_MUS_VS_CHAMPION[] = _("MUS VS CHAMPION");
static const u8 sText_MUS_PALLET[] = _("MUS PALLET");
static const u8 sText_MUS_OAK_LAB[] = _("MUS OAK LAB");
static const u8 sText_MUS_OAK[] = _("MUS OAK");
static const u8 sText_MUS_POKE_CENTER[] = _("MUS POKE CENTER");
static const u8 sText_MUS_SS_ANNE[] = _("MUS SS ANNE");
static const u8 sText_MUS_SURF[] = _("MUS SURF");
static const u8 sText_MUS_POKE_TOWER[] = _("MUS POKE TOWER");
static const u8 sText_MUS_SILPH[] = _("MUS SILPH");
static const u8 sText_MUS_FUCHSIA[] = _("MUS FUCHSIA");
static const u8 sText_MUS_CELADON[] = _("MUS CELADON");
static const u8 sText_MUS_VICTORY_TRAINER[] = _("MUS VICTORY TRAINER");
static const u8 sText_MUS_VICTORY_WILD[] = _("MUS VICTORY WILD");
static const u8 sText_MUS_VICTORY_GYM_LEADER[] = _("MUS VICTORY GYM LEADER");
static const u8 sText_MUS_VERMILLION[] = _("MUS VERMILLION");
static const u8 sText_MUS_PEWTER[] = _("MUS PEWTER");
static const u8 sText_MUS_ENCOUNTER_RIVAL[] = _("MUS ENCOUNTER RIVAL");
static const u8 sText_MUS_RIVAL_EXIT[] = _("MUS RIVAL EXIT");
static const u8 sText_MUS_DEX_RATING[] = _("MUS DEX RATING");
static const u8 sText_MUS_OBTAIN_KEY_ITEM[] = _("MUS OBTAIN KEY ITEM");
static const u8 sText_MUS_CAUGHT_INTRO[] = _("MUS CAUGHT INTRO");
static const u8 sText_MUS_PHOTO[] = _("MUS PHOTO");
static const u8 sText_MUS_GAME_FREAK[] = _("MUS GAME FREAK");
static const u8 sText_MUS_CAUGHT[] = _("MUS CAUGHT");
static const u8 sText_MUS_NEW_GAME_INSTRUCT[] = _("MUS NEW GAME INSTRUCT");
static const u8 sText_MUS_NEW_GAME_INTRO[] = _("MUS NEW GAME INTRO");
static const u8 sText_MUS_NEW_GAME_EXIT[] = _("MUS NEW GAME EXIT");
static const u8 sText_MUS_POKE_JUMP[] = _("MUS POKE JUMP");
static const u8 sText_MUS_UNION_ROOM[] = _("MUS UNION ROOM");
static const u8 sText_MUS_NET_CENTER[] = _("MUS NET CENTER");
static const u8 sText_MUS_MYSTERY_GIFT[] = _("MUS MYSTERY GIFT");
static const u8 sText_MUS_BERRY_PICK[] = _("MUS BERRY PICK");
static const u8 sText_MUS_SEVII_CAVE[] = _("MUS SEVII CAVE");
static const u8 sText_MUS_TEACHY_TV_SHOW[] = _("MUS TEACHY TV SHOW");
static const u8 sText_MUS_SEVII_ROUTE[] = _("MUS SEVII ROUTE");
static const u8 sText_MUS_SEVII_DUNGEON[] = _("MUS SEVII DUNGEON");
static const u8 sText_MUS_SEVII_123[] = _("MUS SEVII 123");
static const u8 sText_MUS_SEVII_45[] = _("MUS SEVII 45");
static const u8 sText_MUS_SEVII_67[] = _("MUS SEVII 67");
static const u8 sText_MUS_POKE_FLUTE[] = _("MUS POKE FLUTE");
static const u8 sText_MUS_VS_DEOXYS[] = _("MUS VS DEOXYS");
static const u8 sText_MUS_VS_MEWTWO[] = _("MUS VS MEWTWO");
static const u8 sText_MUS_VS_LEGEND[] = _("MUS VS LEGEND");
static const u8 sText_MUS_ENCOUNTER_GYM_LEADER[] = _("MUS ENCOUNTER GYM LEADER");
static const u8 sText_MUS_ENCOUNTER_DEOXYS[] = _("MUS ENCOUNTER DEOXYS");
static const u8 sText_MUS_TRAINER_TOWER[] = _("MUS TRAINER TOWER");
static const u8 sText_MUS_SLOW_PALLET[] = _("MUS SLOW PALLET");
static const u8 sText_MUS_TEACHY_TV_MENU[] = _("MUS TEACHY TV MENU");

const u8 *const sText_MusicPlayer[] = {
    //sText_MUS_DUMMY,
    sText_SE_USE_ITEM,
    sText_SE_PC_LOGIN,
    sText_SE_PC_OFF,
    sText_SE_PC_ON,
    sText_SE_SELECT,
    sText_SE_WIN_OPEN,
    sText_SE_WALL_HIT,
    sText_SE_RS_DOOR,
    sText_SE_EXIT,
    sText_SE_LEDGE,
    sText_SE_BIKE_BELL,
    sText_SE_NOT_EFFECTIVE,
    sText_SE_EFFECTIVE,
    sText_SE_SUPER_EFFECTIVE,
    sText_SE_BALL_OPEN,
    sText_SE_FAINT,
    sText_SE_FLEE,
    sText_SE_SLIDING_DOOR,
    sText_SE_SHIP,
    sText_SE_BANG,
    sText_SE_PIN,
    sText_SE_BOO,
    sText_SE_BALL,
    sText_SE_CONTEST_PLACE,
    sText_SE_SUCCESS,
    sText_SE_FAILURE,
    sText_SE_EXP,
    sText_SE_BIKE_HOP,
    sText_SE_SWITCH,
    sText_SE_CLICK,
    sText_SE_FU_ZAKU,
    sText_SE_CONTEST_CONDITION_LOSE,
    sText_SE_LAVARIDGE_FALL_WARP,
    sText_SE_ICE_STAIRS,
    sText_SE_ICE_BREAK,
    sText_SE_ICE_CRACK,
    sText_SE_FALL,
    sText_SE_UNLOCK,
    sText_SE_WARP_IN,
    sText_SE_WARP_OUT,
    sText_SE_REPEL,
    sText_SE_ROTATING_GATE,
    sText_SE_TRUCK_MOVE,
    sText_SE_TRUCK_STOP,
    sText_SE_TRUCK_UNLOAD,
    sText_SE_TRUCK_DOOR,
    sText_SE_BERRY_BLENDER,
    sText_SE_SAVE,
    sText_SE_BALL_BOUNCE_1,
    sText_SE_BALL_BOUNCE_2,
    sText_SE_BALL_BOUNCE_3,
    sText_SE_BALL_BOUNCE_4,
    sText_SE_BALL_TRADE,
    sText_SE_BALL_THROW,
    sText_SE_NOTE_C,
    sText_SE_NOTE_D,
    sText_SE_NOTE_E,
    sText_SE_NOTE_F,
    sText_SE_NOTE_G,
    sText_SE_NOTE_A,
    sText_SE_NOTE_B,
    sText_SE_NOTE_C_HIGH,
    sText_SE_PUDDLE,
    sText_SE_BRIDGE_WALK,
    sText_SE_ITEMFINDER,
    sText_SE_DING_DONG,
    sText_SE_BALLOON_RED,
    sText_SE_BALLOON_BLUE,
    sText_SE_BALLOON_YELLOW,
    sText_SE_BREAKABLE_DOOR,
    sText_SE_MUD_BALL,
    sText_SE_FIELD_POISON,
    sText_SE_ESCALATOR,
    sText_SE_THUNDERSTORM,
    sText_SE_THUNDERSTORM_STOP,
    sText_SE_DOWNPOUR,
    sText_SE_DOWNPOUR_STOP,
    sText_SE_RAIN,
    sText_SE_RAIN_STOP,
    sText_SE_THUNDER,
    sText_SE_THUNDER2,
    sText_SE_ELEVATOR,
    sText_SE_LOW_HEALTH,
    sText_SE_EXP_MAX,
    sText_SE_ROULETTE_BALL,
    sText_SE_ROULETTE_BALL2,
    sText_SE_TAILLOW_WING_FLAP,
    sText_SE_RS_SHOP,
    sText_SE_CONTEST_HEART,
    sText_SE_CONTEST_CURTAIN_RISE,
    sText_SE_CONTEST_CURTAIN_FALL,
    sText_SE_CONTEST_ICON_CHANGE,
    sText_SE_CONTEST_ICON_CLEAR,
    sText_SE_CONTEST_MONS_TURN,
    sText_SE_SHINY,
    sText_SE_INTRO_BLAST,
    sText_SE_MUGSHOT,
    sText_SE_APPLAUSE,
    sText_SE_VEND,
    sText_SE_ORB,
    sText_SE_DEX_SCROLL,
    sText_SE_DEX_PAGE,
    sText_SE_POKENAV_ON,
    sText_SE_POKENAV_OFF,
    sText_SE_DEX_SEARCH,
    sText_SE_EGG_HATCH,
    sText_SE_BALL_TRAY_ENTER,
    sText_SE_BALL_TRAY_BALL,
    sText_SE_BALL_TRAY_EXIT,
    sText_SE_GLASS_FLUTE,
    sText_SE_M_THUNDERBOLT,
    sText_SE_M_THUNDERBOLT2,
    sText_SE_M_HARDEN,
    sText_SE_M_NIGHTMARE,
    sText_SE_M_VITAL_THROW,
    sText_SE_M_VITAL_THROW2,
    sText_SE_M_BUBBLE,
    sText_SE_M_BUBBLE2,
    sText_SE_M_BUBBLE3,
    sText_SE_M_RAIN_DANCE,
    sText_SE_M_CUT,
    sText_SE_M_STRING_SHOT,
    sText_SE_M_STRING_SHOT2,
    sText_SE_M_ROCK_THROW,
    sText_SE_M_GUST,
    sText_SE_M_GUST2,
    sText_SE_M_DOUBLE_SLAP,
    sText_SE_M_DOUBLE_TEAM,
    sText_SE_M_RAZOR_WIND,
    sText_SE_M_ICY_WIND,
    sText_SE_M_THUNDER_WAVE,
    sText_SE_M_COMET_PUNCH,
    sText_SE_M_MEGA_KICK,
    sText_SE_M_MEGA_KICK2,
    sText_SE_M_CRABHAMMER,
    sText_SE_M_JUMP_KICK,
    sText_SE_M_FLAME_WHEEL,
    sText_SE_M_FLAME_WHEEL2,
    sText_SE_M_FLAMETHROWER,
    sText_SE_M_FIRE_PUNCH,
    sText_SE_M_TOXIC,
    sText_SE_M_SACRED_FIRE,
    sText_SE_M_SACRED_FIRE2,
    sText_SE_M_EMBER,
    sText_SE_M_TAKE_DOWN,
    sText_SE_M_BLIZZARD,
    sText_SE_M_BLIZZARD2,
    sText_SE_M_SCRATCH,
    sText_SE_M_VICEGRIP,
    sText_SE_M_WING_ATTACK,
    sText_SE_M_FLY,
    sText_SE_M_SAND_ATTACK,
    sText_SE_M_RAZOR_WIND2,
    sText_SE_M_BITE,
    sText_SE_M_HEADBUTT,
    sText_SE_M_SURF,
    sText_SE_M_HYDRO_PUMP,
    sText_SE_M_WHIRLPOOL,
    sText_SE_M_HORN_ATTACK,
    sText_SE_M_TAIL_WHIP,
    sText_SE_M_MIST,
    sText_SE_M_POISON_POWDER,
    sText_SE_M_BIND,
    sText_SE_M_DRAGON_RAGE,
    sText_SE_M_SING,
    sText_SE_M_PERISH_SONG,
    sText_SE_M_PAY_DAY,
    sText_SE_M_DIG,
    sText_SE_M_DIZZY_PUNCH,
    sText_SE_M_SELF_DESTRUCT,
    sText_SE_M_EXPLOSION,
    sText_SE_M_ABSORB_2,
    sText_SE_M_ABSORB,
    sText_SE_M_SCREECH,
    sText_SE_M_BUBBLE_BEAM,
    sText_SE_M_BUBBLE_BEAM2,
    sText_SE_M_SUPERSONIC,
    sText_SE_M_BELLY_DRUM,
    sText_SE_M_METRONOME,
    sText_SE_M_BONEMERANG,
    sText_SE_M_LICK,
    sText_SE_M_PSYBEAM,
    sText_SE_M_FAINT_ATTACK,
    sText_SE_M_SWORDS_DANCE,
    sText_SE_M_LEER,
    sText_SE_M_SWAGGER,
    sText_SE_M_SWAGGER2,
    sText_SE_M_HEAL_BELL,
    sText_SE_M_CONFUSE_RAY,
    sText_SE_M_SNORE,
    sText_SE_M_BRICK_BREAK,
    sText_SE_M_GIGA_DRAIN,
    sText_SE_M_PSYBEAM2,
    sText_SE_M_SOLAR_BEAM,
    sText_SE_M_PETAL_DANCE,
    sText_SE_M_TELEPORT,
    sText_SE_M_MINIMIZE,
    sText_SE_M_SKETCH,
    sText_SE_M_SWIFT,
    sText_SE_M_REFLECT,
    sText_SE_M_BARRIER,
    sText_SE_M_DETECT,
    sText_SE_M_LOCK_ON,
    sText_SE_M_MOONLIGHT,
    sText_SE_M_CHARM,
    sText_SE_M_CHARGE,
    sText_SE_M_STRENGTH,
    sText_SE_M_HYPER_BEAM,
    sText_SE_M_WATERFALL,
    sText_SE_M_REVERSAL,
    sText_SE_M_ACID_ARMOR,
    sText_SE_M_SANDSTORM,
    sText_SE_M_TRI_ATTACK,
    sText_SE_M_TRI_ATTACK2,
    sText_SE_M_ENCORE,
    sText_SE_M_ENCORE2,
    sText_SE_M_BATON_PASS,
    sText_SE_M_MILK_DRINK,
    sText_SE_M_ATTRACT,
    sText_SE_M_ATTRACT2,
    sText_SE_M_MORNING_SUN,
    sText_SE_M_FLATTER,
    sText_SE_M_SAND_TOMB,
    sText_SE_M_GRASSWHISTLE,
    sText_SE_M_SPIT_UP,
    sText_SE_M_DIVE,
    sText_SE_M_EARTHQUAKE,
    sText_SE_M_TWISTER,
    sText_SE_M_SWEET_SCENT,
    sText_SE_M_YAWN,
    sText_SE_M_SKY_UPPERCUT,
    sText_SE_M_STAT_INCREASE,
    sText_SE_M_HEAT_WAVE,
    sText_SE_M_UPROAR,
    sText_SE_M_HAIL,
    sText_SE_M_COSMIC_POWER,
    sText_SE_M_TEETER_DANCE,
    sText_SE_M_STAT_DECREASE,
    sText_SE_M_HAZE,
    sText_SE_M_HYPER_BEAM2,
    sText_SE_DOOR,
    sText_SE_CARD_FLIP,
    sText_SE_CARD_FLIPPING,
    sText_SE_CARD_OPEN,
    sText_SE_BAG_CURSOR,
    sText_SE_BAG_POCKET,
    sText_SE_BALL_CLICK,
    sText_SE_SHOP,
    sText_SE_SS_ANNE_HORN,
    sText_SE_HELP_OPEN,
    sText_SE_HELP_CLOSE,
    sText_SE_HELP_ERROR,
    sText_SE_DEOXYS_MOVE,
    sText_SE_POKE_JUMP_SUCCESS,
    sText_SE_POKE_JUMP_FAILURE,
    sText_MUS_HEAL,
    sText_MUS_LEVEL_UP,
    sText_MUS_OBTAIN_ITEM,
    sText_MUS_EVOLVED,
    sText_MUS_OBTAIN_BADGE,
    sText_MUS_OBTAIN_TMHM,
    sText_MUS_OBTAIN_BERRY,
    sText_MUS_EVOLUTION_INTRO,
    sText_MUS_EVOLUTION,
    sText_MUS_RS_VS_GYM_LEADER,
    sText_MUS_RS_VS_TRAINER,
    sText_MUS_SCHOOL,
    sText_MUS_SLOTS_JACKPOT,
    sText_MUS_SLOTS_WIN,
    sText_MUS_MOVE_DELETED,
    sText_MUS_TOO_BAD,
    sText_MUS_FOLLOW_ME,
    sText_MUS_GAME_CORNER,
    sText_MUS_ROCKET_HIDEOUT,
    sText_MUS_GYM,
    sText_MUS_JIGGLYPUFF,
    sText_MUS_INTRO_FIGHT,
    sText_MUS_TITLE,
    sText_MUS_CINNABAR,
    sText_MUS_LAVENDER,
    sText_MUS_HEAL_UNUSED,
    sText_MUS_CYCLING,
    sText_MUS_ENCOUNTER_ROCKET,
    sText_MUS_ENCOUNTER_GIRL,
    sText_MUS_ENCOUNTER_BOY,
    sText_MUS_HALL_OF_FAME,
    sText_MUS_VIRIDIAN_FOREST,
    sText_MUS_MT_MOON,
    sText_MUS_POKE_MANSION,
    sText_MUS_CREDITS,
    sText_MUS_ROUTE1,
    sText_MUS_ROUTE24,
    sText_MUS_ROUTE3,
    sText_MUS_ROUTE11,
    sText_MUS_VICTORY_ROAD,
    sText_MUS_VS_GYM_LEADER,
    sText_MUS_VS_TRAINER,
    sText_MUS_VS_WILD,
    sText_MUS_VS_CHAMPION,
    sText_MUS_PALLET,
    sText_MUS_OAK_LAB,
    sText_MUS_OAK,
    sText_MUS_POKE_CENTER,
    sText_MUS_SS_ANNE,
    sText_MUS_SURF,
    sText_MUS_POKE_TOWER,
    sText_MUS_SILPH,
    sText_MUS_FUCHSIA,
    sText_MUS_CELADON,
    sText_MUS_VICTORY_TRAINER,
    sText_MUS_VICTORY_WILD,
    sText_MUS_VICTORY_GYM_LEADER,
    sText_MUS_VERMILLION,
    sText_MUS_PEWTER,
    sText_MUS_ENCOUNTER_RIVAL,
    sText_MUS_RIVAL_EXIT,
    sText_MUS_DEX_RATING,
    sText_MUS_OBTAIN_KEY_ITEM,
    sText_MUS_CAUGHT_INTRO,
    sText_MUS_PHOTO,
    sText_MUS_GAME_FREAK,
    sText_MUS_CAUGHT,
    sText_MUS_NEW_GAME_INSTRUCT,
    sText_MUS_NEW_GAME_INTRO,
    sText_MUS_NEW_GAME_EXIT,
    sText_MUS_POKE_JUMP,
    sText_MUS_UNION_ROOM,
    sText_MUS_NET_CENTER,
    sText_MUS_MYSTERY_GIFT,
    sText_MUS_BERRY_PICK,
    sText_MUS_SEVII_CAVE,
    sText_MUS_TEACHY_TV_SHOW,
    sText_MUS_SEVII_ROUTE,
    sText_MUS_SEVII_DUNGEON,
    sText_MUS_SEVII_123,
    sText_MUS_SEVII_45,
    sText_MUS_SEVII_67,
    sText_MUS_POKE_FLUTE,
    sText_MUS_VS_DEOXYS,
    sText_MUS_VS_MEWTWO,
    sText_MUS_VS_LEGEND,
    sText_MUS_ENCOUNTER_GYM_LEADER,
    sText_MUS_ENCOUNTER_DEOXYS,
    sText_MUS_TRAINER_TOWER,
    sText_MUS_SLOW_PALLET,
    sText_MUS_TEACHY_TV_MENU,
};

//--------------------------------------
//      COLOR PALETTE 15
//--------------------------------------

//                                     fondo                    fuente                  sombra
//                                     highlight                font                    shadow
static const u8 sBlackTextColor[3]  = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_DARK_GRAY,   TEXT_COLOR_LIGHT_GRAY};
static const u8 sBlueTextColor[3]   = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_BLUE,        TEXT_COLOR_LIGHT_GRAY};
static const u8 sRedTextColor[3]    = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_RED,         TEXT_COLOR_LIGHT_GRAY};
static const u8 sGrayTextColor[3]   = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_LIGHT_GRAY,  TEXT_COLOR_DARK_GRAY};
static const u8 sWhiteTextColor[3]  = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_WHITE,       TEXT_COLOR_TRANSPARENT};



//--------------------------------------
//      BACKGROUNDS
//--------------------------------------

static const struct BgTemplate sBgTemplates[] = {
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0,//1
    }, {
        .bg = 1,
        .charBaseIndex = 1,
        .mapBaseIndex = 29,
        .screenSize = 0,//1
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0,
    }
};


//--------------------------------------
//      WINDOWS
//--------------------------------------

#define BASEBLOCK_CALC(num) (WINDOW_##num##_WIDTH * WINDOW_##num##_HEIGTH) + WINDOW_##num##_BASEBLOCK

#define WINDOW_0_WIDTH   24
#define WINDOW_0_HEIGTH  2
#define WINDOW_0_BASEBLOCK   0x001

#define WINDOW_1_WIDTH   4
#define WINDOW_1_HEIGTH  2
#define WINDOW_1_BASEBLOCK  (WINDOW_0_WIDTH * WINDOW_0_HEIGTH) + WINDOW_0_BASEBLOCK

#define WINDOW_2_WIDTH   24
#define WINDOW_2_HEIGTH  2
#define WINDOW_2_BASEBLOCK WINDOW_1_WIDTH * WINDOW_1_HEIGTH + WINDOW_1_BASEBLOCK

#define WINDOW_3_WIDTH   24
#define WINDOW_3_HEIGTH  2
#define WINDOW_3_BASEBLOCK (WINDOW_2_WIDTH * WINDOW_2_HEIGTH) + WINDOW_2_BASEBLOCK

#define WINDOW_4_WIDTH   10
#define WINDOW_4_HEIGTH  2
#define WINDOW_4_BASEBLOCK BASEBLOCK_CALC(3)

static const struct WindowTemplate sWindowTemplates[] = {

    [WIN_TITTLE] = 
    {
        .bg = 0,
        .tilemapLeft = 6,
        .tilemapTop = 0,
        .width = WINDOW_0_WIDTH,
        .height = WINDOW_0_HEIGTH,
        .paletteNum = 15,
        .baseBlock = WINDOW_0_BASEBLOCK
    },
    [WIN_NUMBER] = 
    {
        .bg = 0,
        .tilemapLeft = 13,
        .tilemapTop = 3,
        .width = WINDOW_1_WIDTH,
        .height = WINDOW_1_HEIGTH,
        .paletteNum = 15,
        .baseBlock = WINDOW_1_BASEBLOCK
    },
    [WIN_MUSIC_NAME] = 
    {
        .bg = 0,
        .tilemapLeft = 5,
        .tilemapTop = 14,
        .width = WINDOW_2_WIDTH,
        .height = WINDOW_2_HEIGTH,
        .paletteNum = 15,
        .baseBlock = WINDOW_2_BASEBLOCK
    },
    [WIN_BUTTONS] = 
    {
        .bg = 0,
        .tilemapLeft = 3,
        .tilemapTop = 17,
        .width = WINDOW_3_WIDTH,
        .height = WINDOW_3_HEIGTH,
        .paletteNum = 15,
        .baseBlock = WINDOW_3_BASEBLOCK
    },
    [WIN_PLAYER_TYPE] =
    {
        .bg = 0,
        .tilemapLeft = 3,
        .tilemapTop = 3,
        .width = WINDOW_4_WIDTH,
        .height = WINDOW_4_HEIGTH,
        .paletteNum = 15,
        .baseBlock = WINDOW_4_BASEBLOCK
    },
    DUMMY_WIN_TEMPLATE
};



void ShowMusicPlayer(void)
{
    sMusicPlayerUI = AllocZeroed(sizeof(*sMusicPlayerUI));
    sMusicPlayerUI->state = 0;
    sMusicPlayerUI->gfxStep = 0;
    sMusicPlayerUI->callbackStep = 0;
    sMusicPlayerUI->page = PAGE_MUSIC_PLAYER;
    sMusicPlayerUI->music_id = 1;
    sMusicPlayerUI->specie = SPECIES_BULBASAUR;

    MusicPlayerBgInit();
    CreateTask(Task_MusicPlayerInit, 0);
    SetMainCallback2(MainCB2_MusicPlayer);
}

static void VBlankCB_MusicPlayer(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void MainCB2_MusicPlayer(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void Task_MusicPlayerInit(u8 taskId)
{
    switch (sMusicPlayerUI->callbackStep)
    {
    case 0:
        SetVBlankCallback(NULL);
        break;
    case 1:
        MusicPlayerVblankHandler();
        break;
    case 2:
        if (!MusicPlayerLoadGfx())
        {
            return;
        }
        break;
    case 3:
        CopyToBgTilemapBuffer(1, sMPlayerTilemap, 0, 0);
        break;
    case 4:
        FillWindowPixelBuffer(WIN_BUTTONS, PIXEL_FILL(0));
        AddTextPrinterParameterized3(WIN_BUTTONS, 2, 0x10, 2, sWhiteTextColor, 0, sText_Buttons);
        StringCopy(gStringVar4, sText_MusicPlayer[0]);
        break;
    case 5:
        PutWindowTilemap(WIN_BUTTONS);
        MusicPlayerPrintText();
        break;
    case 6:
        CopyBgTilemapBufferToVram(0);
        CopyBgTilemapBufferToVram(1);
        break;
    case 7:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        break;
    case 8:
        SetVBlankCallback(VBlankCB_MusicPlayer);
        break;
    default:
        if (gPaletteFade.active)
        {
            break;
        }
        gTasks[taskId].func = Task_WaitForExit;
    }
    sMusicPlayerUI->callbackStep++;
}

static void Task_WaitForExit(u8 taskId)
{
    switch (sMusicPlayerUI->state)
    {
    case 0:
        sMusicPlayerUI->state++;
        break;
    case 1:
        if (JOY_NEW(DPAD_UP) || JOY_NEW(DPAD_DOWN))
        {
            sMusicPlayerUI->page ^= 1;//xor   cambia de página.
            if(sMusicPlayerUI->page == PAGE_MUSIC_PLAYER)
                StringCopy(gStringVar4, sText_MusicPlayer[sMusicPlayerUI->music_id - 1]);
            else
                GetSpeciesName(gStringVar4, sMusicPlayerUI->specie);
            MusicPlayerPrintText();
        }
        else if(JOY_REPT(DPAD_RIGHT))
        {
            if(sMusicPlayerUI->page == PAGE_MUSIC_PLAYER)
            {
                if (sMusicPlayerUI->music_id < sizeof(sText_MusicPlayer)/sizeof(sText_MusicPlayer[0]))
                    sMusicPlayerUI->music_id++;
                else
                    sMusicPlayerUI->music_id = 1;
                StringCopy(gStringVar4, sText_MusicPlayer[sMusicPlayerUI->music_id - 1]);
            }
            else
            {
                if (sMusicPlayerUI->specie < SPECIES_CHIMECHO)
                    sMusicPlayerUI->specie++;
                else
                    sMusicPlayerUI->specie = SPECIES_BULBASAUR;
                if (sMusicPlayerUI->specie == SPECIES_OLD_UNOWN_B)
                    sMusicPlayerUI->specie = SPECIES_TREECKO;
                GetSpeciesName(gStringVar4, sMusicPlayerUI->specie);
            }
            MusicPlayerPrintText();
        }
        else if(JOY_REPT(DPAD_LEFT))
        {
            if(sMusicPlayerUI->page == PAGE_MUSIC_PLAYER)
            {
                if (sMusicPlayerUI->music_id > 1)
                    sMusicPlayerUI->music_id--;
                else
                    sMusicPlayerUI->music_id = sizeof(sText_MusicPlayer)/sizeof(sText_MusicPlayer[0]);
                StringCopy(gStringVar4, sText_MusicPlayer[sMusicPlayerUI->music_id - 1]);
            }
            else
            {
                if (sMusicPlayerUI->specie > SPECIES_BULBASAUR)
                    sMusicPlayerUI->specie--;
                else
                    sMusicPlayerUI->specie = SPECIES_CHIMECHO;
                if (sMusicPlayerUI->specie == SPECIES_OLD_UNOWN_Z)
                    sMusicPlayerUI->specie = SPECIES_CELEBI;
                GetSpeciesName(gStringVar4, sMusicPlayerUI->specie);
            }
            MusicPlayerPrintText();
        }
        else if (JOY_NEW(A_BUTTON))
        {
            if(sMusicPlayerUI->page == PAGE_MUSIC_PLAYER)
                PlayBGM(sMusicPlayerUI->music_id);
            else
                PlayCry_Normal(sMusicPlayerUI->specie, 0);
        }
        
        if (JOY_NEW(B_BUTTON))
        {
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
            sMusicPlayerUI->state++;
        }
        break;
    case 2:
        if (!IsCryPlaying())
            Task_MusicPlayerReturnToOverworld(taskId);
        break;
    }
}


static void Task_MusicPlayerReturnToOverworld(u8 taskId)
{
    if (gPaletteFade.active)
        return;
    DestroyTask(taskId);
    FreeAllWindowBuffers();
    FREE_AND_SET_NULL(sMusicPlayerUI);
    SetMainCallback2(CB2_ReturnToFieldFromDiploma);
}

static void MusicPlayerBgInit(void)
{
    ResetSpriteData();
    ResetPaletteFade();
    FreeAllSpritePalettes();
    ResetTasks();
    ScanlineEffect_Stop();
}

static void ResetGpu(void);
static void ResetBGPos(void);

static void MusicPlayerVblankHandler(void)
{
    ResetGpu();
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sBgTemplates, 2);
    ResetBGPos();
    InitWindows(sWindowTemplates);
    DeactivateAllTextPrinters();
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
    SetBgTilemapBuffer(1, sMusicPlayerUI->tilemapBuffer);
    ShowBg(0);
    ShowBg(1);
    FillBgTilemapBufferRect_Palette0(0, 0, 0, 0, 30, 20);
    FillBgTilemapBufferRect_Palette0(1, 0, 0, 0, 30, 20);
}

static void ResetGpu(void)
{
    void *vram = (void *)VRAM;
    DmaClearLarge16(3, vram, VRAM_SIZE, 0x1000);
    DmaClear32(3, (void *)OAM, OAM_SIZE);
    DmaClear16(3, (void *)PLTT, PLTT_SIZE);
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    SetGpuReg(REG_OFFSET_BG0CNT, 0);
    SetGpuReg(REG_OFFSET_BG0HOFS, 0);
    SetGpuReg(REG_OFFSET_BG0VOFS, 0);
    SetGpuReg(REG_OFFSET_BG1CNT, 0);
    SetGpuReg(REG_OFFSET_BG1HOFS, 0);
    SetGpuReg(REG_OFFSET_BG1VOFS, 0);
    SetGpuReg(REG_OFFSET_BG2CNT, 0);
    SetGpuReg(REG_OFFSET_BG2HOFS, 0);
    SetGpuReg(REG_OFFSET_BG2VOFS, 0);
    SetGpuReg(REG_OFFSET_BG3CNT, 0);
    SetGpuReg(REG_OFFSET_BG3HOFS, 0);
    SetGpuReg(REG_OFFSET_BG3VOFS, 0);
    SetGpuReg(REG_OFFSET_WIN0H, 0);
    SetGpuReg(REG_OFFSET_WIN0V, 0);
    SetGpuReg(REG_OFFSET_WININ, 0);
    SetGpuReg(REG_OFFSET_WINOUT, 0);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);
}

static void ResetBGPos(void)
{
    ChangeBgX(0, 0, 0);
    ChangeBgY(0, 0, 0);
    ChangeBgX(1, 0, 0);
    ChangeBgY(1, 0, 0);
    ChangeBgX(2, 0, 0);
    ChangeBgY(2, 0, 0);
    ChangeBgX(3, 0, 0);
    ChangeBgY(3, 0, 0);
}

static u8 MusicPlayerLoadGfx(void)
{
    switch (sMusicPlayerUI->gfxStep)
    {
    case 0:
        ResetTempTileDataBuffers();
        break;
    case 1:
        DecompressAndCopyTileDataToVram(1, sMPlayerGfx, 0, 0, 0);
        break;
    case 2:
        if (!(FreeTempTileDataBuffersIfPossible() == 1))
        {
            break;
        }
        return 0;
    case 3:
        LoadPalette(sMPlayerPal, 0, 0x20);
        LoadPalette(GetTextWindowPalette(0), 0xf0, 0x20);
    default:
        return 1;
    }
    sMusicPlayerUI->gfxStep++;
    return 0;
}

static void PrintWindow_Tittle(void);
static void PrintWindow_Number(void);
static void PrintWindow_MusicName(void);
static void PrintWindow_PlayerType(void);

static void MusicPlayerPrintText(void)
{
    FillWindowPixelBuffer(WIN_TITTLE, PIXEL_FILL(0));
    FillWindowPixelBuffer(WIN_NUMBER, PIXEL_FILL(0));
    FillWindowPixelBuffer(WIN_MUSIC_NAME, PIXEL_FILL(0));
    FillWindowPixelBuffer(WIN_PLAYER_TYPE, PIXEL_FILL(0));
    

    PrintWindow_Tittle();
    PrintWindow_Number();
    PrintWindow_MusicName();
    PrintWindow_PlayerType();

    PutWindowTilemap(WIN_TITTLE);
    PutWindowTilemap(WIN_NUMBER);
    PutWindowTilemap(WIN_MUSIC_NAME);
    PutWindowTilemap(WIN_PLAYER_TYPE);
}

#define coord_x 0x10

static void PrintWindow_Tittle(void)
{
    if(sMusicPlayerUI->page == PAGE_MUSIC_PLAYER)
        AddTextPrinterParameterized3(WIN_TITTLE, 2, coord_x, 2, sWhiteTextColor, 0, sText_Tittle_Player);
    else
        AddTextPrinterParameterized3(WIN_TITTLE, 2, coord_x, 2, sWhiteTextColor, 0, sText_Tittle_Cry);
}

static void PrintWindow_Number(void)
{
    u16 temp;
    u32 width;
    if(sMusicPlayerUI->page == PAGE_MUSIC_PLAYER)
        temp = sMusicPlayerUI->music_id;
    else
        temp = sMusicPlayerUI->specie;//PAGE_CRY_PLAYER
    ConvertIntToDecimalStringN(gStringVar1, temp, STR_CONV_MODE_LEFT_ALIGN, GetDigitsDec(temp));
    width = GetStringWidth(2, gStringVar1, -1);
    AddTextPrinterParameterized3(WIN_NUMBER, 2, 0x10 - (width / 2), 0x2, sBlackTextColor, 0, gStringVar1);
}

static void PrintWindow_MusicName(void)
{
    AddTextPrinterParameterized3(WIN_MUSIC_NAME, 2, 0x0, 0x2, sWhiteTextColor, 0, gStringVar4);
}

#include "song_table.h"

static const u8 sText_MUSIC_PLAYER_BGM[] = _("PLAYER: BGM");
static const u8 sText_MUSIC_PLAYER_SE1[] = _("PLAYER: SE1");
static const u8 sText_MUSIC_PLAYER_SE2[] = _("PLAYER: SE2");
static const u8 sText_MUSIC_PLAYER_SE3[] = _("PLAYER: SE3");
static const u8 sText_MUSIC_PLAYER_CRY[] = _("PLAYER: CRY");

static void PrintWindow_PlayerType(void)
{
    const u8 *player;
    if(sMusicPlayerUI->page == PAGE_CRY_PLAYER)
    {
        AddTextPrinterParameterized3(WIN_PLAYER_TYPE, 2, 2, 2, sBlackTextColor, 0, sText_MUSIC_PLAYER_CRY);
        return;
    }
    switch (gSongTable[sMusicPlayerUI->music_id].ms)
    {
    default:
    case MUSIC_PLAYER_BGM:
        player = sText_MUSIC_PLAYER_BGM;
        break;
    case MUSIC_PLAYER_SE1:
        player = sText_MUSIC_PLAYER_SE1;
        break;
    case MUSIC_PLAYER_SE2:
        player = sText_MUSIC_PLAYER_SE2;
        break;
    case MUSIC_PLAYER_SE3:
        player = sText_MUSIC_PLAYER_SE3;
        break;
    }
    AddTextPrinterParameterized3(WIN_PLAYER_TYPE, 2, 2, 2, sBlackTextColor, 0, player);
}

/**
 * Devuelve el número de dígitos de un número
 * 
 * Returns the number of digits in a number
*/
u8 GetDigitsDec(u32 num)
{
    u8 digits = 1;
    while (num >= 10)
    {
        digits++;
        num = num / 10;
    }
    return digits;
    /*
    if (num < 10)
        return 1;
    else
        return 1 + GetDigitsDec(num/10);
    */
}

u8 GetDigitsHex(u32 num)
{
    u8 digits = 1;
    while (num >= 0x10)
    {
        digits++;
        num = num / 0x10;
    }
    return digits;
    /*
    if (num < 0x10)
        return 1;
    else
        return 1 + GetDigitsHex(num/0x10);
        */
}


/**
 * Devuelve el número de dígitos de un entero con signo
 * 
 * Returns the number of digits in a signed int
*/
u8 GetDigitsDec_S(s32 num)
{
    if (num < 0)
        num = num * (-1);
    
    return GetDigitsDec(num);
}


