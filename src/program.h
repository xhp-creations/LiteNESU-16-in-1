#ifndef PROGRAM_H
#define PROGRAM_H
#include "init.h"
#include <gctypes.h>
#include "vpad.h"
#include "common.h"

#define FULLSCREEN_DRC_X_OFFSET 171 // Offsets to center on DRC and TV
#define FULLSCREEN_DRC_Y_OFFSET 0
#define FULLSCREEN_X_OFFSET 384
#define FULLSCREEN_Y_OFFSET 120

// Palette

typedef struct __pal {
	int r;
	int g;
	int b;
} pal;

static const pal palette[64] = {
	{ 0x80, 0x80, 0x80 },
	{ 0x00, 0x00, 0xBB },
	{ 0x37, 0x00, 0xBF },
	{ 0x84, 0x00, 0xA6 },
	{ 0xBB, 0x00, 0x6A },
	{ 0xB7, 0x00, 0x1E },
	{ 0xB3, 0x00, 0x00 },
	{ 0x91, 0x26, 0x00 },
	{ 0x7B, 0x2B, 0x00 },
	{ 0x00, 0x3E, 0x00 },
	{ 0x00, 0x48, 0x0D },
	{ 0x00, 0x3C, 0x22 },
	{ 0x00, 0x2F, 0x66 },
	{ 0x00, 0x00, 0x00 },
	{ 0x05, 0x05, 0x05 },
	{ 0x05, 0x05, 0x05 },
	{ 0xC8, 0xC8, 0xC8 },
	{ 0x00, 0x59, 0xFF },
	{ 0x44, 0x3C, 0xFF },
	{ 0xB7, 0x33, 0xCC },
	{ 0xFF, 0x33, 0xAA },
	{ 0xFF, 0x37, 0x5E },
	{ 0xFF, 0x37, 0x1A },
	{ 0xD5, 0x4B, 0x00 },
	{ 0xC4, 0x62, 0x00 },
	{ 0x3C, 0x7B, 0x00 },
	{ 0x1E, 0x84, 0x15 },
	{ 0x00, 0x95, 0x66 },
	{ 0x00, 0x84, 0xC4 },
	{ 0x11, 0x11, 0x11 },
	{ 0x09, 0x09, 0x09 },
	{ 0x09, 0x09, 0x09 },
	{ 0xFF, 0xFF, 0xFF },
	{ 0x00, 0x95, 0xFF },
	{ 0x6F, 0x84, 0xFF },
	{ 0xD5, 0x6F, 0xFF },
	{ 0xFF, 0x77, 0xCC },
	{ 0xFF, 0x6F, 0x99 },
	{ 0xFF, 0x7B, 0x59 },
	{ 0xFF, 0x91, 0x5F },
	{ 0xFF, 0xA2, 0x33 },
	{ 0xA6, 0xBF, 0x00 },
	{ 0x51, 0xD9, 0x6A },
	{ 0x4D, 0xD5, 0xAE },
	{ 0x00, 0xD9, 0xFF },
	{ 0x66, 0x66, 0x66 },
	{ 0x0D, 0x0D, 0x0D },
	{ 0x0D, 0x0D, 0x0D },
	{ 0xFF, 0xFF, 0xFF },
	{ 0x84, 0xBF, 0xFF },
	{ 0xBB, 0xBB, 0xFF },
	{ 0xD0, 0xBB, 0xFF },
	{ 0xFF, 0xBF, 0xEA },
	{ 0xFF, 0xBF, 0xCC },
	{ 0xFF, 0xC4, 0xB7 },
	{ 0xFF, 0xCC, 0xAE },
	{ 0xFF, 0xD9, 0xA2 },
	{ 0xCC, 0xE1, 0x99 },
	{ 0xAE, 0xEE, 0xB7 },
	{ 0xAA, 0xF7, 0xEE },
	{ 0xB3, 0xEE, 0xFF },
	{ 0xDD, 0xDD, 0xDD },
	{ 0x11, 0x11, 0x11 },
	{ 0x11, 0x11, 0x11 }
};

struct ines_header{
    char signature[4];
    byte prg_block_count;
    byte chr_block_count;
    word rom_type;
    byte reserved[8];
};

extern struct ines_header fce_rom_header;

unsigned int vpad_handle;
unsigned int (*VPADRead)(int controller, VPADData *buffer, unsigned int num, int *error);
void* memcpy(void* dst, const void* src, uint32_t size);

extern const unsigned char cap_1942_bin[];
extern const u32 cap_1942_bin_size;
extern const unsigned char ark_bin[];
extern const u32 ark_bin_size;
extern const unsigned char ars_bin[];
extern const u32 ars_bin_size;
extern const unsigned char balf_bin[];
extern const u32 balf_bin_size;
extern const unsigned char balt_bin[];
extern const u32 balt_bin_size;
extern const unsigned char batc_bin[];
extern const u32 batc_bin_size;
extern const unsigned char cnp_bin[];
extern const u32 cnp_bin_size;
extern const unsigned char db_bin[];
extern const u32 db_bin_size;
extern const unsigned char dd_bin[];
extern const u32 dd_bin_size;
extern const unsigned char def_bin[];
extern const u32 def_bin_size;
extern const unsigned char dk_bin[];
extern const u32 dk_bin_size;
extern const unsigned char dk3_bin[];
extern const u32 dk3_bin_size;
extern const unsigned char dkjr_bin[];
extern const u32 dkjr_bin_size;
extern const unsigned char drm_bin[];
extern const u32 drm_bin_size;
extern const unsigned char ee_bin[];
extern const u32 ee_bin_size;
extern const unsigned char ex_bin[];
extern const u32 ex_bin_size;
extern const unsigned char kungfu_bin[];
extern const u32 kungfu_bin_size;
extern const unsigned char menu_comp_bin[];
extern const u32 menu_comp_bin_size;
extern const unsigned char menu_pal_bin[];
extern const u32 menu_pal_bin_size;
extern unsigned char menu_pic[0x64144];

extern uint32_t screenSync;
extern int drawFilter;

void _osscreeninit();
void _clearscreen();
void _main();
void displayMenu(int menuLine);
int fce_load_rom(const unsigned char *rom);
void fce_init();
void fce_update_screen();

#endif /* PROGRAM_H */