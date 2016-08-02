#ifndef MMC_H
#define MMC_H
#include "nescommon.h"

byte mmc_id;

byte mmc_read(word address);
void mmc_write(word address, byte data);
void mmc_copy(word address, byte *source, int length);
void reset_mmc_chr_pages(void);
void mmc_append_chr_rom_page(byte *source);

#endif