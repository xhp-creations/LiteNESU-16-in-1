#ifndef __HAL_H__
#define __HAL_H__

#include "nes.h"
#include <gctypes.h>

struct Pixel {
    int x, y; // (x, y) coordinate
    int c; // RGB value of colors can be found in program.h
};
typedef struct Pixel Pixel;

/* A buffer of pixels */
struct PixelBuf {
	Pixel buf[264 * 264];
	int size;
};
typedef struct PixelBuf PixelBuf;

extern PixelBuf bg, bbg, fg;

extern uint32_t buttonValue;
extern int drawFilter;

// clear a pixel buffer
#define pixbuf_clean(bf) \
	do { \
		(bf).size = 0; \
	} while (0)

// add a pending pixel into a buffer
#define pixbuf_add(bf, xa, ya, ca) \
	do { \
		if ((xa) < SCREEN_WIDTH && (ya) < SCREEN_HEIGHT) { \
			(bf).buf[(bf).size].x = (xa); \
			(bf).buf[(bf).size].y = (ya); \
			(bf).buf[(bf).size].c = (ca); \
			(bf).size++; \
		} \
	} while (0)

// fill the screen with background color
void nes_set_bg_color(int c);

// flush pixel buffer to frame buffer
void nes_flush_buf(PixelBuf *buf);

// display and empty the current frame buffer
void nes_flip_display();

// initialization
void nes_hal_init();

// query key-press status
int nes_key_state(int b);

#endif
