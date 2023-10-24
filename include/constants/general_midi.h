#ifndef GUARD_CONSTANTS_GENERAL_MIDI_H
#define GUARD_CONSTANTS_GENERAL_MIDI_H

// MIDI KEY NOTES
//                  MIDI   NOTE   PITCH (Hz with 3 decimal points)

#define NOTE_000    0   // C-1  at    8.176Hz
#define NOTE_001    1   // C#-1 at    8.662Hz
#define NOTE_002    2   // D-1  at    9.177Hz
#define NOTE_003    3   // D#-1 at    9.723Hz
#define NOTE_004    4   // E-1  at   10.301Hz
#define NOTE_005    5   // F-1  at   10.913Hz
#define NOTE_006    6   // F#-1 at   11.562Hz
#define NOTE_007    7   // G-1  at   12.250Hz
#define NOTE_008    8   // G#-1 at   12.978Hz
#define NOTE_009    9   // A-1  at   13.750Hz
#define NOTE_010    10  // A#-1 at   14.568Hz
#define NOTE_011    11  // B-1  at   15.434Hz

#define NOTE_012    12  // C0   at   16.352Hz
#define NOTE_013    13  // C#0  at   17.324Hz
#define NOTE_014    14  // D0   at   18.354Hz
#define NOTE_015    15  // D#0  at   19.445Hz
#define NOTE_016    16  // E0   at   20.602Hz
#define NOTE_017    17  // F0   at   21.827Hz
#define NOTE_018    18  // F#0  at   23.125Hz
#define NOTE_019    19  // G0   at   24.500Hz
#define NOTE_020    20  // G#0  at   25.957Hz
#define NOTE_021    21  // A0   at   27.500Hz
#define NOTE_022    22  // A#0  at   29.135Hz
#define NOTE_023    23  // B0   at   30.868Hz

#define NOTE_024    24  // C1   at   32.703Hz
#define NOTE_025    25  // C#1  at   34.648Hz
#define NOTE_026    26  // D1   at   36.708Hz
#define NOTE_027    27  // D#1  at   38.891Hz
#define NOTE_028    28  // E1   at   41.203Hz
#define NOTE_029    29  // F1   at   43.654Hz
#define NOTE_030    30  // F#1  at   46.249Hz
#define NOTE_031    31  // G1   at   48.999Hz
#define NOTE_032    32  // G#1  at   51.913Hz
#define NOTE_033    33  // A1   at   55.000Hz
#define NOTE_034    34  // A#1  at   58.270Hz
#define NOTE_035    35  // B1   at   61.735Hz

#define NOTE_036    36  // C2   at   65.406Hz
#define NOTE_037    37  // C#2  at   69.296Hz
#define NOTE_038    38  // D2   at   73.416Hz
#define NOTE_039    39  // D#2  at   77.782Hz
#define NOTE_040    40  // E2   at   82.407Hz
#define NOTE_041    41  // F2   at   87.307Hz
#define NOTE_042    42  // F#2  at   92.499Hz
#define NOTE_043    43  // G2   at   97.999Hz
#define NOTE_044    44  // G#2  at  103.826Hz
#define NOTE_045    45  // A2   at  110.000Hz
#define NOTE_046    46  // A#2  at  116.541Hz
#define NOTE_047    47  // B2   at  123.471Hz

#define NOTE_048    48  // C3   at  130.813Hz
#define NOTE_049    49  // C#3  at  138.591Hz
#define NOTE_050    50  // D3   at  146.832Hz
#define NOTE_051    51  // D#3  at  155.563Hz
#define NOTE_052    52  // E3   at  164.814Hz
#define NOTE_053    53  // F3   at  174.614Hz
#define NOTE_054    54  // F#3  at  184.997Hz
#define NOTE_055    55  // G3   at  195.998Hz
#define NOTE_056    56  // G#3  at  207.652Hz
#define NOTE_057    57  // A3   at  220.000Hz
#define NOTE_058    58  // A#3  at  233.082Hz
#define NOTE_059    59  // B3   at  246.942Hz

#define NOTE_060    60  // C4   at  261.626Hz (Middle C)
#define NOTE_061    61  // C#4  at  277.183Hz
#define NOTE_062    62  // D4   at  293.665Hz
#define NOTE_063    63  // D#4  at  311.127Hz
#define NOTE_064    64  // E4   at  329.628Hz
#define NOTE_065    65  // F4   at  349.228Hz
#define NOTE_066    66  // F#4  at  369.994Hz
#define NOTE_067    67  // G4   at  391.995Hz
#define NOTE_068    68  // G#4  at  415.305Hz
#define NOTE_069    69  // A4   at  440.000Hz
#define NOTE_070    70  // A#4  at  466.164Hz
#define NOTE_071    71  // B4   at  493.883Hz

#define NOTE_072    72  // C5   at  523.251Hz
#define NOTE_073    73  // C#5  at  554.365Hz
#define NOTE_074    74  // D5   at  587.330Hz
#define NOTE_075    75  // D#5  at  622.254Hz
#define NOTE_076    76  // E5   at  659.255Hz
#define NOTE_077    77  // F5   at  698.456Hz
#define NOTE_078    78  // F#5  at  739.989Hz
#define NOTE_079    79  // G5   at  783.991Hz
#define NOTE_080    80  // G#5  at  830.609Hz
#define NOTE_081    81  // A5   at  880.000Hz
#define NOTE_082    82  // A#5  at  932.328Hz
#define NOTE_083    83  // B5   at  987.767Hz

#define NOTE_084    84  // C6   at 1046.502Hz
#define NOTE_085    85  // C#6  at 1108.731Hz
#define NOTE_086    86  // D6   at 1174.659Hz
#define NOTE_087    87  // D#6  at 1244.508Hz
#define NOTE_088    88  // E6   at 1318.510Hz
#define NOTE_089    89  // F6   at 1396.913Hz
#define NOTE_090    90  // F#6  at 1479.978Hz
#define NOTE_091    91  // G6   at 1567.982Hz
#define NOTE_092    92  // G#6  at 1661.219Hz
#define NOTE_093    93  // A6   at 1760.000Hz
#define NOTE_094    94  // A#6  at 1864.655Hz
#define NOTE_095    95  // B6   at 1975.533Hz

#define NOTE_096    96  // C7   at 2093.005Hz
#define NOTE_097    97  // C#7  at 2217.461Hz
#define NOTE_098    98  // D7   at 2349.318Hz
#define NOTE_099    99  // D#7  at 2489.016Hz
#define NOTE_100    100 // E7   at 2637.020Hz
#define NOTE_101    101 // F7   at 2793.826Hz
#define NOTE_102    102 // F#7  at 2959.955Hz
#define NOTE_103    103 // G7   at 3135.963Hz
#define NOTE_104    104 // G#7  at 3322.438Hz
#define NOTE_105    105 // A7   at 3520.000Hz
#define NOTE_106    106 // A#7  at 3729.310Hz
#define NOTE_107    107 // B7   at 3951.066Hz

#define NOTE_108    108 // C8   at 4186.009Hz
#define NOTE_109    109 // C#8  at 4434.922Hz
#define NOTE_110    110 // D8   at 4698.636Hz
#define NOTE_111    111 // D#8  at 4978.032Hz
#define NOTE_112    112 // E8   at 5274.041Hz
#define NOTE_113    113 // F8   at 5587.652Hz
#define NOTE_114    114 // F#8  at 5919.911Hz
#define NOTE_115    115 // G8   at 6271.927Hz
#define NOTE_116    116 // G#8  at 6644.875Hz
#define NOTE_117    117 // A8   at 7040.000Hz
#define NOTE_118    118 // A#8  at 7458.620Hz
#define NOTE_119    119 // B8   at 7902.133Hz

#define NOTE_120    120 // C9   at 8372.018Hz
#define NOTE_121    121 // C#9  at 8869.844Hz
#define NOTE_122    122 // D9   at 9397.273Hz
#define NOTE_123    123 // D#9  at 9956.063Hz
#define NOTE_124    124 // E9   at10548.080Hz
#define NOTE_125    125 // F9   at11175.300Hz
#define NOTE_126    126 // F#9  at11839.820Hz
#define NOTE_127    127 // G9   at12543.850Hz


// GENERAL MIDI INSTRUMENT LIST

/**
 * These are the instruments in the
 * General MIDI Level 1 sound set;
 * instruments sound are grouped by
 * families, in each family are 8
 * specific instruments.
 *
 * The names of the instruments
 * indicate what sort of sound will
 * be heard when that instrument
 * number (MIDI Program Change or PC#)
 * is select
 *
 * The sounds are the same for all
 * MIDI Channels except Channel 10,
 * which has only drums sounds.
*/


// PIANO
#define ACOUSTIC_GRAND_PIANO    0
#define BRIGHT_ACOUSTIC_PIANO   1
#define ELECTRIC_GRAND_PIANO    2
#define HONKY_TONK_PIANO        3
#define ELECTRIC_PIANO_1        4
#define ELECTRIC_PIANO_2        5
#define HARPSICHORD             6
#define CLAVINET                7
// CHROMATIC PERCUSION
#define CELESTA                 8
#define GLOCKENSPIEL            9
#define MUSIC_BOX               10
#define VIBRAPHONE              11
#define MARINBA                 12
#define XYLOPHONE               13
#define TUBULAR_BELLS           14
#define DULCIMER                15
// ORGAN
#define DRAWBAR_ORGAN           16
#define PERCUSIVE_ORGAN         17
#define ROCK_ORGAN              18
#define CHURCH_ORGAN            19
#define REED_ORGAN              20
#define ACCORDION               21
#define HARMONICA               22
#define TANGO_ACCORDION         23
// GUITAR
#define ACOUSTIC_GUITAR_NYLON   24
#define ACOUSTIC_GUITAR_STEEL   25
#define ELECTRIC_GUITAR_JAZZ    26
#define ELECTRIC_GUITAR_CLEAN   27
#define ELECTRIC_GUITAR_MUTED   28
#define OVERDRIVEN_GUITAR       29
#define DISTORTION_GUITAR       30
#define GUITAR_HARMONICS        31
// BASS
#define ACOUSTIC_BASS           32
#define ELECTRIC_BASS_FINGER    33
#define ELECTRIC_BASS_PICK      34
#define FRETLESS_BASS           35
#define SLAP_BASS_1             36
#define SLAP_BASS_2             37
#define SYNTH_BASS_1            38
#define SYNTH_BASS_2            39
// STRINGS
#define VIOLIN                  40
#define VIOLA                   41
#define CELLO                   42
#define CONTRABASS              43
#define TREMOLO_STRINGS         44
#define PIZZICATO_STRINGS       45
#define ORCHESTRAL_HARP         46
#define TIMPANI                 47
// ENSEMBLE
#define STRING_ENSEMBLE_1       48
#define STRING_ENSEMBLE_2       49
#define SYNTH_STRINGS_1         50
#define SYNTH_STRINGS_2         51
#define CHOIR_AAHS              52
#define VOICE_OOHS              53
#define SYNTH_VOICE             54
#define ORCHESTRA_HIT           55
// BRASS
#define TRUMPET                 56
#define TROMBONE                57
#define TUBA                    58
#define MUTED_TRUMPET           59
#define FRENCH_HORN             60
#define BRASS_SECTION           61
#define SYNTH_BRASS_1           62
#define SYNTH_BRASS_2           63
// REED
#define SOPRANO_SAX             64
#define ALTO_SAX                65
#define TENOR_SAX               66
#define BARITONE_SAX            67
#define OBOE                    68
#define ENGLISH_HORN            69
#define BASSOON                 70
#define CLARINET                71
// PIPE
#define PICCOLO                 72
#define FLUTE                   73
#define RECORDER                74
#define PAN_FLUTE               75
#define BLOWN_BOTTLE            76
#define SHAKUHACHI              77
#define WHISTLE                 78
#define OCARINA                 79
// SYNTH LEAD
#define LEAD_1_SQUARE           80
#define LEAD_2_SAWTOOTH         81
#define LEAD_3_CALLIOPE         82
#define LEAD_4_CHIFF            83
#define LEAD_5_CHARANG          84
#define LEAD_6_VOICE            85
#define LEAD_7_FIFTHS           86
#define LEAD_8_BASS_LEAD        87
// SYNTH PAD
#define PAD_1_NEW_AGE           88
#define PAD_2_WARM              89
#define PAD_3_POLYSYNTH         90
#define PAD_4_CHOIR             91
#define PAD_5_BOWED             92
#define PAD_6_METALLIC          93
#define PAD_7_HALO              94
#define PAD_8_SWEEP             95
// SYNTH EFFECTS
#define FX_1_RAIN               96
#define FX_2_SOUNDTRACK         97
#define FX_3_CRYSTAL            98
#define FX_4_ATMOSPHERE         99
#define FX_5_BRIGHTNESS         100
#define FX_6_GOBLINS            101
#define FX_7_ECHOES             102
#define FX_8_SCI_FI             103
// ETHNIC
#define SITAR                   104
#define BANJO                   105
#define SHAMISEN                106
#define KOTO                    107
#define KALIMBA                 108
#define BAG_PIPE                109
#define FIDDLE                  110
#define SHANAI                  111
// PERCUSIVE
#define TINKLE_BELL             112
#define AGOGO                   113
#define STEEL_DRUMS             114
#define WOODBLOCK               115
#define TAIKO_DRUM              116
#define MELODIC_TOM             117
#define SYNTH_DRUM              118
#define REVERSE_CYMBAL          119
// SOUND EFFECTS
#define GUITAR_FRET_NOISE       120
#define BREATH_NOISE            121
#define SEASHORE                122
#define BIRD_TWEET              123
#define TELEPHONE_RING          124
#define HELICOPTER              125
#define APPLAUSE                126
#define GUNSHOT                 127


// GENERAL MIDI DRUMS/PERCUSION KEY MAP

/**
 * On MIDI Chanel 10, each MIDI Note number ("Key#") correspond to a different
 * drum sound, as show below.
 *
 * The numbers listed correspond to the MIDI note number for that drum sound.
 * Drum sounds added in General MIDI Level 2 are tagged with GM2.
*/

#define HIGH_Q_GM2          NOTE_027
#define SLAP_GM2            NOTE_028
#define SCRATCH_PUSH_GM2    NOTE_029
#define SCRATCH_PULL_GM2    NOTE_030
#define STICKS_GM2          NOTE_031
#define SQUARE_CLICK_GM2    NOTE_032
#define METRONOME_CLICK_GM2 NOTE_033
#define METRONOME_BELL_GM2  NOTE_034
#define BASS_DRUM_2         NOTE_035  // Acoustic Bass Drum
#define BASS_DRUM_1         NOTE_036
#define SIDE_STICK          NOTE_037
#define SNARE_DRUM_1        NOTE_038  // Acoustic Snare
#define HAND_CLAP           NOTE_039
#define SNARE_DRUM_2        NOTE_040  // Electric Snare
#define LOW_TOM_2           NOTE_041  // Low Floor Tom
#define CLOSED_HI_HAT       NOTE_042
#define LOW_TOM_1           NOTE_043  // High Floor Tom
#define PEDAL_HI_HAT        NOTE_044
#define MID_TOM_2           NOTE_045  // Low Tom
#define OPEN_HI_HAT         NOTE_046
#define MID_TOM_1           NOTE_047  // Low-Mid Tom
#define HIGH_TOM_2          NOTE_048  // Hi-Mid Tom
#define CRASH_CYMBAL_1      NOTE_049
#define HIGH_TOM_1          NOTE_050  // High Tom
#define RIDE_CYMBAL_1       NOTE_051
#define CHINESE_CYMBAL      NOTE_052
#define RIDE_BELL           NOTE_053
#define TAMBOURINE          NOTE_054
#define SPLASH_CYMBAL       NOTE_055
#define COWBELL             NOTE_056
#define CRASH_CYMBAL_2      NOTE_057
#define VIBRA_SLAP          NOTE_058
#define RIDE_CYMBAL_2       NOTE_059
#define HIGH_BONGO          NOTE_060
#define LOW_BONGO           NOTE_061
#define MUTE_HIGH_CONGA     NOTE_062
#define OPEN_HIGH_CONGA     NOTE_063
#define LOW_CONGA           NOTE_064
#define HIGH_TIMBALE        NOTE_065
#define LOW_TIMBALE         NOTE_066
#define HIGH_AGOGO          NOTE_067
#define LOW_AGOGO           NOTE_068
#define CABASA              NOTE_069
#define MARACAS             NOTE_070
#define SHORT_WHISTLE       NOTE_071
#define LONG_WHISTLE        NOTE_072
#define SHORT_GUIRO         NOTE_073
#define LOGN_GUIRO          NOTE_074
#define CLAVES              NOTE_075
#define HIGH_WOOD_BLOCK     NOTE_076
#define LOW_WOOD_BLOCK      NOTE_077
#define MUTE_CUICA          NOTE_078
#define OPEN_CUICA          NOTE_079
#define MUTE_TRIANGLE       NOTE_080
#define OPEN_TRIANGLE       NOTE_081
#define SHAKER_GM2          NOTE_082
#define JINGLE_BELL_GM2     NOTE_083
#define BELLTREE_GM2        NOTE_084
#define CASTANETS_GM2       NOTE_085
#define MUTE_SURDO_GM2      NOTE_086
#define OPEN_SURDO_GM2      NOTE_087


//  DRUMKIT ...
//  Drumkit name (Program Change #)

#define DRUMKIT_STANDARD    ACOUSTIC_GRAND_PIANO
#define DRUMKIT_ROOM        CELESTA
#define DRUMKIT_POWER       DRAWBAR_ORGAN
#define DRUMKIT_ELECTRONIC  ACOUSTIC_GUITAR_NYLON
#define DRUMKIT_TR_808      ACOUSTIC_GUITAR_STEEL
#define DRUMKIT_JAZZ        ACOUSTIC_BASS
#define DRUMKIT_ORCHESTRA   STRING_ENSEMBLE_1
#define DRUMKIT_CM_64_32L   GUNSHOT


#endif //GUARD_CONSTANTS_GENERAL_MIDI_H
