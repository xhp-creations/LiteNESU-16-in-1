// #define psg_io_read(...) 0xFF
// #define psg_io_write(...) /**/

#ifndef PSG_H
#define PSG_H
#include "nescommon.h"

extern unsigned char psg_joy1[8];

byte psg_io_read(word address);
void psg_io_write(word address, byte data);

#endif