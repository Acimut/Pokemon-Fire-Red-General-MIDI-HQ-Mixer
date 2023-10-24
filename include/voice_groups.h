#ifndef GUARD_VOICE_GROUPS_H
#define GUARD_VOICE_GROUPS_H

#include "constants/general_midi.h"
#include "gba/m4a_internal.h"

#define KEYSPLIT_RANGE(start_note,end_note,instrument_start_note) \
    (start_note - KEYSPLITTABLE_##instrument_start_note##_START) ... (end_note - KEYSPLITTABLE_##instrument_start_note##_START)

// for key split table purpose
#define SAMPLE_VOICE_0    0
#define SAMPLE_VOICE_1    1
#define SAMPLE_VOICE_2    2
#define SAMPLE_VOICE_3    3
#define SAMPLE_VOICE_4    4
#define SAMPLE_VOICE_5    5
#define SAMPLE_VOICE_6    6
#define SAMPLE_VOICE_7    7
#define SAMPLE_VOICE_8    8
#define SAMPLE_VOICE_9    9
#define SAMPLE_VOICE_10   10
#define SAMPLE_VOICE_11   11
#define SAMPLE_VOICE_12   12
#define SAMPLE_VOICE_13   13
#define SAMPLE_VOICE_14   14
#define SAMPLE_VOICE_15   15
#define SAMPLE_VOICE_16   16
#define SAMPLE_VOICE_17   17
#define SAMPLE_VOICE_18   18
#define SAMPLE_VOICE_19   19
#define SAMPLE_VOICE_20   20
#define SAMPLE_VOICE_21   21
#define SAMPLE_VOICE_22   22
#define SAMPLE_VOICE_23   23
#define SAMPLE_VOICE_24   24
#define SAMPLE_VOICE_25   25
#define SAMPLE_VOICE_26   26
#define SAMPLE_VOICE_27   27
#define SAMPLE_VOICE_28   28
#define SAMPLE_VOICE_29   29
#define SAMPLE_VOICE_30   30
#define SAMPLE_VOICE_31   31
#define SAMPLE_VOICE_32   32


#define VOICE_DIRECTSOUND(base_midi_key,pan,sample_data_pointer,_attack,_decay,_sustain,_release)   \
    {.toneData =                                                                                    \
        {                                                                                           \
            .type = 0,                                                                              \
            .key = base_midi_key,                                                                   \
            .pan_sweep = (pan)?(0x80|pan):0,                                                        \
            .wav = (struct WaveData*)&sample_data_pointer,                                          \
            .attack = _attack,                                                                      \
            .decay = _decay,                                                                        \
            .sustain = _sustain,                                                                    \
            .release = _release                                                                     \
        }                                                                                           \
    }

#define VOICE_DIRECTSOUND_NO_RESAMPLE(base_midi_key,pan,sample_data_pointer,_attack,_decay,_sustain,_release)\
    {.toneData =                                                                                             \
        {                                                                                                    \
            .type = 8,                                                                                       \
            .key = base_midi_key,                                                                            \
            .pan_sweep = (pan)?(0x80|pan):0,                                                                 \
            .wav = (struct WaveData*)&sample_data_pointer,                                                   \
            .attack = _attack,                                                                               \
            .decay = _decay,                                                                                 \
            .sustain = _sustain,                                                                             \
            .release = _release                                                                              \
        }                                                                                                    \
    }

#define VOICE_DIRECTSOUND_ALT(base_midi_key,pan,sample_data_pointer,_attack,_decay,_sustain,_release)   \
    {.toneData =                                                                                        \
        {                                                                                               \
            .type = 16,                                                                                 \
            .key = base_midi_key,                                                                       \
            .pan_sweep = (pan)?(0x80|pan):0,                                                            \
            .wav = (struct WaveData*)&sample_data_pointer,                                              \
            .attack = _attack,                                                                          \
            .decay = _decay,                                                                            \
            .sustain = _sustain,                                                                        \
            .release = _release                                                                         \
        }                                                                                               \
    }


#define VOICE_SQUARE_1(base_midi_key,_pan,_sweep,_duty_cycle,_attack,_decay,_sustain,_release)  \
    {.square =                                                                                  \
        {                                                                                       \
            .type = 1,                                                                          \
            .key = base_midi_key,                                                               \
            .pan = (_pan)?(0x80|_pan):0,                                                        \
            .sweep = _sweep,                                                                    \
            .duty_cycle = (_duty_cycle & 3),                                                    \
            .attack = (_attack & 7),                                                            \
            .decay = (_decay & 7),                                                              \
            .sustain = (_sustain & 15),                                                         \
            .release = (_release & 7)                                                           \
        }                                                                                       \
    }

#define VOICE_SQUARE_1_ALT(base_midi_key,_pan,_sweep,_duty_cycle,_attack,_decay,_sustain,_release)  \
    {.square =                                                                                      \
        {                                                                                           \
            .type = 9,                                                                              \
            .key = base_midi_key,                                                                   \
            .pan = (_pan)?(0x80|_pan):0,                                                            \
            .sweep = _sweep,                                                                        \
            .duty_cycle = (_duty_cycle & 3),                                                        \
            .attack = (_attack & 7),                                                                \
            .decay = (_decay & 7),                                                                  \
            .sustain = (_sustain & 15),                                                             \
            .release = (_release & 7)                                                               \
        }                                                                                           \
    }

#define VOICE_SQUARE_2(base_midi_key,_pan,_duty_cycle,_attack,_decay,_sustain,_release) \
    {.square =                                                                          \
        {                                                                               \
            .type = 2,                                                                  \
            .key = base_midi_key,                                                       \
            .pan = (_pan)?(0x80|_pan):0,                                                \
            .duty_cycle = (_duty_cycle & 3),                                            \
            .attack = (_attack & 7),                                                    \
            .decay = (_decay & 7),                                                      \
            .sustain = (_sustain & 15),                                                 \
            .release = (_release & 7)                                                   \
        }                                                                               \
    }

#define VOICE_SQUARE_2_ALT(base_midi_key,_pan,_duty_cycle,_attack,_decay,_sustain,_release) \
    {.square =                                                                              \
        {                                                                                   \
            .type = 10,                                                                     \
            .key = base_midi_key,                                                           \
            .pan = (_pan)?(0x80|_pan):0,                                                    \
            .duty_cycle = (_duty_cycle & 3),                                                \
            .attack = (_attack & 7),                                                        \
            .decay = (_decay & 7),                                                          \
            .sustain = (_sustain & 15),                                                     \
            .release = (_release & 7)                                                       \
        }                                                                                   \
    }


#define VOICE_PROGRAMMABLE_WAVE(base_midi_key,_pan,wave_samples_pointer,_attack,_decay,_sustain,_release)   \
    {.programmable =                                                                                        \
        {                                                                                                   \
            .type = 3,                                                                                      \
            .key = base_midi_key,                                                                           \
            .pan = (_pan)?(0x80|_pan):0,                                                                    \
            .wav = (struct WaveData*)&wave_samples_pointer,                                                 \
            .attack = (_attack & 7),                                                                        \
            .decay = (_decay & 7),                                                                          \
            .sustain = (_sustain & 15),                                                                     \
            .release = (_release & 7)                                                                       \
        }                                                                                                   \
    }

#define VOICE_PROGRAMMABLE_WAVE_ALT(base_midi_key,_pan,wave_samples_pointer,_attack,_decay,_sustain,_release)\
    {.programmable =                                                                                         \
        {                                                                                                    \
            .type = 11,                                                                                      \
            .key = base_midi_key,                                                                            \
            .pan = (_pan)?(0x80|_pan):0,                                                                     \
            .wav = (struct WaveData*)&wave_samples_pointer,                                                  \
            .attack = (_attack & 7),                                                                         \
            .decay = (_decay & 7),                                                                           \
            .sustain = (_sustain & 15),                                                                      \
            .release = (_release & 7)                                                                        \
        }                                                                                                    \
    }



#define VOICE_NOISE(base_midi_key,_pan,_period,_attack,_decay,_sustain,_release)    \
    {.noise =                                                                       \
        {                                                                           \
            .type = 4,                                                              \
            .key = base_midi_key,                                                   \
            .pan = (_pan)?(0x80|_pan):0,                                            \
            .period = (_period & 1),                                                \
            .attack = (_attack & 7),                                                \
            .decay = (_decay & 7),                                                  \
            .sustain = (_sustain & 15),                                             \
            .release = (_release & 7)                                               \
        }                                                                           \
    }

#define VOICE_NOISE_ALT(base_midi_key,_pan,_period,_attack,_decay,_sustain,_release)\
    {.noise =                                                                       \
        {                                                                           \
            .type = 12,                                                             \
            .key = base_midi_key,                                                   \
            .pan = (_pan)?(0x80|_pan):0,                                            \
            .period = (_period & 1),                                                \
            .attack = (_attack & 7),                                                \
            .decay = (_decay & 7),                                                  \
            .sustain = (_sustain & 15),                                             \
            .release = (_release & 7)                                               \
        }                                                                           \
    }


#define VOICE_KEYSPLIT(voice_group_pointer, keysplit_table_pointer) \
    {.keySplit =                                                    \
        {                                                           \
            .type = 64,                                             \
            .voiceGroup = voice_group_pointer,                      \
            .keysplit_table_ptr = keysplit_table_pointer            \
        }                                                           \
    }

#define VOICE_KEYSPLIT_ALL(voice_group_pointer) \
    {.keySplit =                                \
        {                                       \
            .type = 128,                        \
            .voiceGroup = voice_group_pointer,  \
        }                                       \
    }


#define CRY(sample)                         \
    {                                       \
        .type = 32,                         \
        .key = NOTE_060,                     \
        .wav = (struct WaveData*)&sample,   \
        .attack = 255,                      \
        .decay = 0,                         \
        .sustain = 255,                     \
        .release = 0                        \
    }

#define CRY_REVERSE(sample)                 \
    {                                       \
        .type = 48,                         \
        .key = NOTE_060,                     \
        .wav = (struct WaveData*)&sample,   \
        .attack = 255,                      \
        .decay = 0,                         \
        .sustain = 255,                     \
        .release = 0                        \
    }

#define DEFAULT_VOICE   VOICE_SQUARE_1(NOTE_060, 0, 0, 2, 0, 0, 15, 0)

extern const u8 KeySplitTable1[];
extern const u8 KeySplitTable2[];
extern const u8 KeySplitTable3[];
extern const u8 KeySplitTable4[];
extern const u8 KeySplitTable5[];

extern const union VoiceGroup voicegroup001[];
extern const union VoiceGroup voicegroup002[];
extern const union VoiceGroup voicegroup_piano1[];
extern const union VoiceGroup voicegroup_string_ensemble[];
extern const union VoiceGroup voicegroup_trumpet[];
extern const union VoiceGroup voicegroup_tuba[];
extern const union VoiceGroup voicegroup_french_horn[];
extern const union VoiceGroup voicegroup177[];
extern const union VoiceGroup voicegroup190[];


#endif // GUARD_VOICE_GROUPS_H
