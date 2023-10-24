//--------------------------------------------------------------
// ACIMUT'S Trumpet 21024Hz
//--------------------------------------------------------------

const u8 KeySplitTable_AGM_060_Trumpet[] =
{
    [NOTE_000 ... NOTE_055] = SAMPLE_VOICE_0,
    [NOTE_056 ... NOTE_060] = SAMPLE_VOICE_1,
    [NOTE_061 ... NOTE_066] = SAMPLE_VOICE_2,
    [NOTE_067 ... NOTE_075] = SAMPLE_VOICE_3,
    [NOTE_076 ... NOTE_079] = SAMPLE_VOICE_4,
    [NOTE_080 ... NOTE_083] = SAMPLE_VOICE_5,
    [NOTE_084 ... NOTE_087] = SAMPLE_VOICE_6,
    [NOTE_088 ... NOTE_127] = SAMPLE_VOICE_7,
};

const union VoiceGroup voicegroup_AGM_060_Trumpet[] =
{
    [SAMPLE_VOICE_0]  = VOICE_DIRECTSOUND(NOTE_060, 0, gDirectSoundWaveData_Acimut_GM_056_Trumpet_55, 255, 0, 255, 127),
    [SAMPLE_VOICE_1]  = VOICE_DIRECTSOUND(NOTE_060, 0, gDirectSoundWaveData_Acimut_GM_056_Trumpet_60, 255, 0, 255, 127),
    [SAMPLE_VOICE_2]  = VOICE_DIRECTSOUND(NOTE_060, 0, gDirectSoundWaveData_Acimut_GM_056_Trumpet_66, 255, 0, 255, 127),
    [SAMPLE_VOICE_3]  = VOICE_DIRECTSOUND(NOTE_060, 0, gDirectSoundWaveData_Acimut_GM_056_Trumpet_75, 255, 0, 255, 127),
    [SAMPLE_VOICE_4]  = VOICE_DIRECTSOUND(NOTE_060, 0, gDirectSoundWaveData_Acimut_GM_056_Trumpet_79, 255, 0, 255, 127),
    [SAMPLE_VOICE_5]  = VOICE_DIRECTSOUND(NOTE_060, 0, gDirectSoundWaveData_Acimut_GM_056_Trumpet_83, 255, 0, 255, 127),
    [SAMPLE_VOICE_6]  = VOICE_DIRECTSOUND(NOTE_060, 0, gDirectSoundWaveData_Acimut_GM_056_Trumpet_87, 255, 0, 255, 127),
    [SAMPLE_VOICE_7]  = VOICE_DIRECTSOUND(NOTE_060, 0, gDirectSoundWaveData_Acimut_GM_056_Trumpet_88, 255, 0, 255, 127),
};
