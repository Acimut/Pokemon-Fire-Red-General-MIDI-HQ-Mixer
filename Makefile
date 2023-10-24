#-------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITARM)),)
$(error Please set DEVKITARM in your environment. export DEVKITARM=/path/to/devkitARM)
endif

include $(DEVKITARM)/base_tools

#-------------------------------------------------------------------------------

include config.mk

#ifeq ($(OS),Windows_NT)
EXE := .exe
#else
#EXE :=
#endif

export BUILD := build
export SRC := src
export BINARY := $(BUILD)/linked.o
export GRAPHICS_SRC := graphics

# songs
export SONG_SUBDIR := sound/songs
export SONG_BUILDDIR := $(BUILD)/$(SONG_SUBDIR)

export MID_SUBDIR := $(SONG_SUBDIR)/midi
export SAMPLE_SUBDIR := sound/direct_sound_samples
export CRY_SUBDIR := sound/direct_sound_samples/cries

export ARMIPS ?= armips$(EXE)
export GFX ?= gbagfx$(EXE)
export AIF ?= aif2pcm$(EXE)
export SCANINC ?= scaninc$(EXE)
export PREPROC ?= preproc$(EXE)
export MID ?= mid2agb$(EXE)
export RAMSCRGEN ?= ramscrgen$(EXE)
export FIX ?= gbafix$(EXE)
export MAPJSON ?= mapjson$(EXE)
export JSONPROC ?= jsonproc$(EXE)
export LD := $(PREFIX)ld
export AS := $(PREFIX)as

# -mthumb
export ASFLAGS := -mcpu=arm7tdmi -mthumb-interwork --defsym ROM_CODE=$(ROM_CODE)

# -DFLAG_X=$(FLAG_829)       -> #define FLAG_X = 0x829
# -D$(ROM_CODE)              -> #define BPRE
export INCLUDES := -I $(SRC) -I . -I include -D$(ROM_CODE)

export WARNINGFLAGS := -Wall -Wno-discarded-array-qualifiers \
	-Wno-int-conversion

# -mabi=apcs-gnu #EABI version 0
# -mabi=aapcs #EABI version 5
# -mno-thumb-interwork
# -mthumb-interwork #el código admite llamadas ARM y Thumb, genera código más grande. usar sólo en EABI menor a 5.
export CFLAGS := -g -O2 $(WARNINGFLAGS) -mthumb -std=gnu17 $(INCLUDES) -mcpu=arm7tdmi \
	-march=armv4t -mthumb-interwork -fno-inline -fno-builtin -mlong-calls -DROM_$(ROM_CODE) \
	-fdiagnostics-color -mabi=aapcs

export DEPFLAGS = -MT $@ -MMD -MP -MF "$(@:%.o=%.d)"

export LDFLAGS := -T linker.ld -r $(ROM_CODE).ld EWRAM.ld IWRAM_$(ROM_CODE).ld

#-------------------------------------------------------------------------------

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

#Esta parte se encarga de convertir las imágenes
#automáticamente de acuerdo al tipo de gráfico.

#obtenemos los nombres de los gráficos:
GRAPHICS_BIN:= $(call rwildcard,$(GRAPHICS_SRC),*.bin)
GRAPHICS_4BPP:= $(call rwildcard,$(GRAPHICS_SRC),*.png)

#creamos una copia de los nombres pero con nueva extensión
GBA_BIN_LZ := $(GRAPHICS_BIN:%=%.lz)

GBA_4BPP := $(GRAPHICS_4BPP:%.png=%.4bpp)
GBA_4BPP_PAL := $(GRAPHICS_4BPP:%.png=%.pal)
GBA_4BPP_GBAPAL := $(GBA_4BPP_PAL:%.pal=%.gbapal)
GBA_4BPP_LZ := $(GBA_4BPP:%=%.lz)

# los ponemos en una variable.
GRAPHICS := $(GBA_BIN_LZ) $(GBA_4BPP_LZ) $(GBA_4BPP_GBAPAL)


# song sources
MIDI_SRC := $(call rwildcard,$(MID_SUBDIR),*.mid)
AIF_SRC := $(call rwildcard,$(SAMPLE_SUBDIR),*.aif)
SE_SRC := $(call rwildcard,$(SONG_SUBDIR),*.s)

MIDI_ASM := $(MIDI_SRC:%.mid=%.s)
AIF_BIN := $(AIF_SRC:%.aif=%.bin)

MIDI_OBJ := $(MIDI_SRC:%.mid=$(BUILD)/%.o)
SE_OBJ := $(SE_SRC:%.s=$(BUILD)/%.o)

SONGS := $(MIDI_ASM) $(AIF_BIN) $(SE_OBJ) $(MIDI_OBJ)

RESOURCES := $(GRAPHICS) $(SONGS)


# Sources
C_SRC := $(call rwildcard,$(SRC),*.c)
S_SRC := $(call rwildcard,$(SRC),*.s)

# Binaries
C_OBJ := $(C_SRC:%.c=$(BUILD)/%.o)
S_OBJ := $(S_SRC:%.s=$(BUILD)/%.o)


ALL_OBJ := $(C_OBJ) $(S_OBJ) $(SE_OBJ) $(MIDI_OBJ)


#-------------------------------------------------------------------------------

.PHONY: all rom clean graphics

all: rom

rom: main$(ROM_CODE).asm $(BINARY)
	@echo "\nCreating ROM"
	$(ARMIPS) main$(ROM_CODE).asm \
	-definelabel insertinto $(OFFSET) \
	-sym2 offsets_$(ROM_CODE).txt

clean:
	rm -rf $(BINARY)
	rm -rf $(BUILD)/$(SRC)
	rm -rf $(SONG_BUILDDIR)
	rm -rf $(MIDI_ASM)
	rm -rf $(SAMPLE_SUBDIR)/*.bin
	rm -rf $(SAMPLE_SUBDIR)/*/*.bin
	find . \( -iname '*.1bpp' -o -iname '*.4bpp' -o -iname '*.8bpp' -o -iname '*.gbapal' -o -iname '*.lz' -o -iname '*.rl' -o -iname '*.latfont' -o -iname '*.hwjpnfont' -o -iname '*.fwjpnfont' \) -exec rm {} +


$(BINARY): $(ALL_OBJ)
	@echo "\nLinking ELF binary $@"
	@$(LD) $(LDFLAGS) -o $@ $^

$(BUILD)/%.o: %.c $(RESOURCES)
	@echo "\nCompiling $<"
	@mkdir -p $(@D)
	@$(CC) $(DEPFLAGS) $(CFLAGS) -E -c $< -o $(BUILD)/$*.i
	@$(PREPROC) $(BUILD)/$*.i charmap.txt | $(CC) $(CFLAGS) -x c -o $@ -c -

$(BUILD)/%.o: %.s
	@echo -e "Assembling $<"
	@mkdir -p $(@D)
	$(PREPROC) "$<" charmap.txt | $(AS) $(ASFLAGS) -o $@

$(BUILD)/$(SRC)/m4a_1.o: ASFLAGS := -mcpu=arm7tdmi -mthumb-interwork

$(SONG_BUILDDIR)/%.o: $(SONG_SUBDIR)/%.s
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS) -I sound -o $@ $<

include songs.mk

# %.s: ;
%.png: ;
%.pal: ;
%.aif: ;

# %.gbapal: %.pal ; $(GFX) $< $@ -num_colors 16
%.1bpp: %.png  ; $(GFX) $< $@
%.4bpp: %.png  ; $(GFX) $< $@
%.8bpp: %.png  ; $(GFX) $< $@
%.pal: %.png  ; $(GFX) $< $@
%.gbapal: %.pal ; $(GFX) $< $@
%.gbapal: %.png ; $(GFX) $< $@
%.lz: % ; $(GFX) $< $@
%.latfont: %.png  ; $(GFX) $< $@
%.fwjpnfont: %.png  ; $(GFX) $< $@

$(CRY_SUBDIR)/%.bin: $(CRY_SUBDIR)/%.aif ; $(AIF) $< $@ --compress

sound/%.bin: sound/%.aif ; $(AIF) $< $@

sound/songs/%.s: sound/songs/%.mid
	$(MID) $< $@

graphics: $(GRAPHICS)


#emerald:    ; @$(MAKE) ROM_CODE=BPEE
#esmeralda:  ; @$(MAKE) ROM_CODE=BPES

