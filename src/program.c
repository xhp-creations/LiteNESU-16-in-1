#include "program.h"
#include "draw.h"
#include "cpu.h"
#include "memory.h"
#include "ppu.h"
#include "hal.h"

PixelBuf bg, bbg, fg;

uint32_t buttonValue;
uint32_t screenSync;
int drawFilter = 0;
unsigned char menu_pic[0x64144];

struct ines_header fce_rom_header;

int memcmp(void *ptr1, void *ptr2, uint32_t length) // Implement our own memcmp
{
	uint8_t *check1 = (uint8_t*) ptr1;
	uint8_t *check2 = (uint8_t*) ptr2;
	uint32_t i;
	for (i = 0; i < length; i++)
	{
		if (check1[i] != check2[i]) return 1;
	}

	return 0;
}

void* memcpy(void* dst, const void* src, uint32_t size) // Implement our own memcpy
{
	uint32_t i;
	for (i = 0; i < size; i++)
		((uint8_t*) dst)[i] = ((const uint8_t*) src)[i];
	return dst;
}

void _osscreeninit()
{
	OSScreenInit();
	int buf0_size = OSScreenGetBufferSizeEx(0);
	OSScreenSetBufferEx(0, (void *)0xF4000000);
	OSScreenSetBufferEx(1, (void *)0xF4000000 + buf0_size);
}

void _clearscreen()
{
	int ii;
	for( ii = 0; ii < 2; ii++ )
	{
		fillScreen(0, 0, 0);
		flipBuffers();
	}
}

void _main()
{
	void*(*memcpy)(void *dest, void *src, uint32_t length);
	OSDynLoad_FindExport(coreinit_handle, 0, "memcpy", &memcpy);
	
	OSDynLoad_Acquire("vpad.rpl", &vpad_handle);
	OSDynLoad_FindExport(vpad_handle, 0, "VPADRead", &VPADRead);

	_osscreeninit();
	_clearscreen();
	
	decodeImg(menu_pic, menu_comp_bin, menu_comp_bin_size);
	
	uint32_t screenSync = 0;
	int drawFilter = 1;
	
	int romPlay = 0;
	int menuLine = 0;
	int loadSuccess = 1;
	int readOffset = 0x00;
	
	fillScreen(0, 0, 0);

	VPADData vpad_data;
	int error;
	while(1)
	{
		VPADRead(0, &vpad_data, 1, &error);
		buttonValue = vpad_data.btn_hold; // Report button value to HAL
		
		if (romPlay == 0) { // Do we show the shitty menu, or play the game?
			fillScreen(0, 0, 0);
			displayMenu(menuLine);
			flipBuffers();
			fillScreen(0, 0, 0);
			displayMenu(menuLine);
			flipBuffers();
			screenSync = 0;
		}
		else {
			int scanlines = 262;
			while (scanlines-- > 0)
			{
				ppu_run(1);
				cpu_run(1364 / 12); // 1 scanline
			}
			screenSync++;
		}
		
		if (vpad_data.btn_trigger & BUTTON_B) {
			if (romPlay == 0) {
				if (menuLine == 16) {
					break;
				}
				if (menuLine == 0) {
					setDrawBack(1);
					loadSuccess = fce_load_rom(cap_1942_bin);
				}
				if (menuLine == 1) {
					setDrawBack(1);
					loadSuccess = fce_load_rom(ark_bin);
				}
				if (menuLine == 2) {
					setDrawBack(1);
					loadSuccess = fce_load_rom(ars_bin);
				}
				if (menuLine == 3) {
					setDrawBack(1);
					loadSuccess = fce_load_rom(balf_bin);
				}
				if (menuLine == 4) {
					setDrawBack(0);
					loadSuccess = fce_load_rom(balt_bin);
				}
				if (menuLine == 5) {
					setDrawBack(1);
					loadSuccess = fce_load_rom(batc_bin);
				}
				if (menuLine == 6) {
					setDrawBack(1);
					loadSuccess = fce_load_rom(cnp_bin);
				}
				if (menuLine == 7) {
					setDrawBack(1);
					loadSuccess = fce_load_rom(def_bin);
				}
				if (menuLine == 8) {
					setDrawBack(1);
					loadSuccess = fce_load_rom(dd_bin);
				}
				if (menuLine == 9) {
					setDrawBack(1);
					loadSuccess = fce_load_rom(dk_bin);
				}
				if (menuLine == 10) {
					setDrawBack(1);
					loadSuccess = fce_load_rom(dkjr_bin);
				}
				if (menuLine == 11) {
					setDrawBack(1);
					loadSuccess = fce_load_rom(dk3_bin);
				}
				if (menuLine == 12) {
					setDrawBack(1);
					loadSuccess = fce_load_rom(db_bin);
				}
				if (menuLine == 13) {
					setDrawBack(1);
					loadSuccess = fce_load_rom(ee_bin);
				}
				if (menuLine == 14) {
					setDrawBack(0);
					loadSuccess = fce_load_rom(ex_bin);
				}
				if (menuLine == 15) {
					setDrawBack(0);
					loadSuccess = fce_load_rom(kungfu_bin);
				}
				if (loadSuccess == -1) {
					fillScreen(0, 0, 0);
					drawString(0, 0, 0, 0, "Failed loading.\n");
					flipBuffers();
					fillScreen(0, 0, 0);
					drawString(0, 0, 0, 0, "Failed loading.\n");
					flipBuffers();
				}
				if (loadSuccess == 0) {
					fillScreen(0, 0, 0);
					flipBuffers();
					fillScreen(0, 0, 0);
					flipBuffers();
					romPlay = 1;
					fce_init();
				}
			}
		}
		if (vpad_data.btn_trigger & BUTTON_UP) {
			if (menuLine > 0) {
				menuLine = menuLine - 1;
			}
			else {
				menuLine = 16;
			}
		}
		if (vpad_data.btn_trigger & BUTTON_DOWN) {
			if (menuLine < 16) {
				menuLine = menuLine + 1;
			}
			else {
				menuLine = 0;
			}
		}
		if (vpad_data.btn_trigger & BUTTON_HOME) {
			romPlay = 0;
		}
	}
	_clearscreen();
}

void displayMenu(int menuLine)
{
	paintIndexImageFS(menu_pic, menu_pal_bin, 3); // Draw shitty logo
	char arrows[64];
	char   exit[64];
	char  game0[64];
	char  game1[64];
	char  game2[64];
	char  game3[64];
	char  game4[64];
	char  game5[64];
	char  game6[64];
	char  game7[64];
	char  game8[64];
	char  game9[64];
	char  game10[64];
	char  game11[64];
	char  game12[64];
	char  game13[64];
	char  game14[64];
	char  game15[64];
	__os_snprintf(arrows,64,  "<                  >");  // Print shitty menu
	__os_snprintf(game0, 64,   "       1942      ");
	__os_snprintf(game1, 64,   "     Arkanoid    ");
	__os_snprintf(game2, 64,   " Astro  Robo Sasa");
	__os_snprintf(game3, 64,   "  Balloon  Fight ");
	__os_snprintf(game4, 64,   "     Baltron     ");
	__os_snprintf(game5, 64,   "   Battle  City  ");
	__os_snprintf(game6, 64,   "   Chack 'n Pop  ");
	__os_snprintf(game7, 64,   "     Defender    ");
	__os_snprintf(game8, 64,   "     Dig  Dug    ");
	__os_snprintf(game9, 64,   "   Donkey  Kong  ");
	__os_snprintf(game10, 64,  "  Donkey Kong Jr ");
	__os_snprintf(game11, 64,  "  Donkey  Kong 3 ");
	__os_snprintf(game12, 64,  "    Dough  Boy   ");
	__os_snprintf(game13, 64,  "    Exed  Exes   ");
	__os_snprintf(game14, 64,  "     Exerion     ");
	__os_snprintf(game15, 64,  "  Yie Ar Kung-Fu ");
	__os_snprintf(exit,  64,   "  EXIT TO SYSTEM ");
	drawString(0, menuLine, 7, 4 + menuLine, arrows);
	drawString(1,  0, 8,  4, game0);
	drawString(1,  1, 8,  5, game1);
	drawString(1,  2, 8,  6, game2);
	drawString(1,  3, 8,  7, game3);
	drawString(1,  4, 8,  8, game4);
	drawString(1,  5, 8,  9, game5);
	drawString(1,  6, 8, 10, game6);
	drawString(1,  7, 8, 11, game7);
	drawString(1,  8, 8, 12, game8);
	drawString(1,  9, 8, 13, game9);
	drawString(1, 10, 8, 14, game10);
	drawString(1, 11, 8, 15, game11);
	drawString(1, 12, 8, 16, game12);
	drawString(1, 13, 8, 17, game13);
	drawString(1, 14, 8, 18, game14);
	drawString(1, 15, 8, 19, game15);
	drawString(1, 16, 8, 20, exit);
}

// FCE Lifecycle
void
romread(const unsigned char *rom, void *buf, int size, int reset)
{
	static int readOffset = 0x00;
	if (reset) {
		readOffset = readOffset - readOffset; // Zero static value when loading new ROM, setting it to equal zero wasn't enough in my tests.
	}
    memcpy(buf, rom + readOffset, size);
    readOffset += size;
}

int fce_load_rom(const unsigned char *rom)
{
    romread(rom, &fce_rom_header, sizeof(fce_rom_header), 1);
    if (memcmp(fce_rom_header.signature, "NES\x1A", 4)) {
        return -1;
    }

    mmc_id = ((fce_rom_header.rom_type & 0xF0) >> 4);

    int prg_size = fce_rom_header.prg_block_count * 0x4000;
    static byte buf[1048576];
    romread(rom, buf, prg_size, 0);
	
    if (mmc_id == 0 || mmc_id == 3) {
        // if there is only one PRG block, we must repeat it twice
        if (fce_rom_header.prg_block_count == 1) {
            mmc_copy(0x8000, buf, 0x4000);
            mmc_copy(0xC000, buf, 0x4000);
        }
        else {
            mmc_copy(0x8000, buf, 0x8000);
        }
    }
    else {
        return -1;
    }
	
    // Copying CHR pages into MMC and PPU
    int i;
    for (i = 0; i < fce_rom_header.chr_block_count; i++) {
        romread(rom, buf, 0x2000, 0);
        mmc_append_chr_rom_page(buf);
		
        if (i == 0) {
            ppu_copy(0x0000, buf, 0x2000);
        }
    }

    return 0;
}

void fce_init()
{
    nes_hal_init();
    cpu_init();
    ppu_init();
    ppu_set_mirroring(fce_rom_header.rom_type & 1);
    cpu_reset();
}

// Rendering
void fce_update_screen()
{
    int idx = ppu_ram_read(0x3F00);
	
	nes_set_bg_color(idx);
    
    if (ppu_shows_sprites()) {
        nes_flush_buf(&bbg);
	}

    if (ppu_shows_background()) {
        nes_flush_buf(&bg);
	}

    if (ppu_shows_sprites()) {
        nes_flush_buf(&fg);
	}
	
	if (screenSync & 0x00000002) { // Only flips the buffer every 2 cycles, slightly helps with artifacting, at least in my initial testing, may no longer need in the future
		nes_flip_display();
	}

    pixbuf_clean(bbg);
    pixbuf_clean(bg);
    pixbuf_clean(fg);
}