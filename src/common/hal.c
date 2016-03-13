/*
This file present all abstraction needed to port LiteNES.
  (The current working implementation uses allegro library.)

To port this project, replace the following functions by your own:
1) nes_hal_init()
    Do essential initialization work, including starting a FPS HZ timer.

2) nes_set_bg_color(c)
    Set the back ground color to be the NES internal color code c.

3) nes_flush_buf(*buf)
    Flush the entire pixel buf's data to frame buffer.

4) nes_flip_display()
    Fill the screen with previously set background color, and
    display all contents in the frame buffer.

5) wait_for_frame()
    Implement it to make the following code is executed FPS times a second:
        while (1) {
            wait_for_frame();
            do_something();
        }

6) int nes_key_state(int b) 
    Query button b's state (1 to be pressed, otherwise 0).
    The correspondence of b and the buttons:
      0 - Power
      1 - A
      2 - B
      3 - SELECT
      4 - START
      5 - UP
      6 - DOWN
      7 - LEFT
      8 - RIGHT
*/
#include "hal.h"
#include "program.h"
#include "common.h"
#include "draw.h"

uint32_t buttonValue;
int drawFilter;

// void wait_for_frame(); // Need to port this properly using system time

/* Set background color. RGB value of c is defined in program.h */
pal nextClearColour;
void nes_set_bg_color(int c)
{
	nextClearColour = palette[c];
	int x;
	int y;
	for (y = 0; y < 240; y++) {
		for (x = 0; x < 256; x++) {
			int tvx = FULLSCREEN_X_OFFSET + (x * 2);
			int tvy = FULLSCREEN_Y_OFFSET + (y * 2);
			int dx = FULLSCREEN_DRC_X_OFFSET + (x * 2);
			int dy = y * 2;
			uint32_t num = (palette[c].r << 24) | (palette[c].g << 16) | (palette[c].b << 8) | 255;
			OSScreenPutPixelEx(0, tvx + (screenSync & 0x00000001), tvy + (screenSync & 0x00000001), num);
			OSScreenPutPixelEx(1, dx + (screenSync & 0x00000001), dy + (screenSync & 0x00000001), num);
			if (drawFilter == 1) {  // Basic filter, also slows emulation down, which is good, since it runs a little fast anyway
				OSScreenPutPixelEx(0, tvx - 1 + (screenSync & 0x00000001), tvy + (screenSync & 0x00000001), num);
				OSScreenPutPixelEx(1, dx - 1 + (screenSync & 0x00000001), dy + (screenSync & 0x00000001), num);
			}
		}
	}
}

/* Flush the pixel buffer */
void nes_flush_buf(PixelBuf *buf) {
    int i;
    for (i = 0; i < buf->size; i ++) {
        Pixel *p = &buf->buf[i];
        int x = p->x, y = p->y;
		if ((x > 0) && (y > 0) && (x < 256) && (y < 240)) {
			int tvx = FULLSCREEN_X_OFFSET + (x * 2);
			int tvy = FULLSCREEN_Y_OFFSET + (y * 2);
			int dx = FULLSCREEN_DRC_X_OFFSET + (x * 2);
			int dy = y * 2;
			uint32_t num = (palette[p->c].r << 24) | (palette[p->c].g << 16) | (palette[p->c].b << 8) | 255;
			OSScreenPutPixelEx(0, tvx + (screenSync & 0x00000001), tvy + (screenSync & 0x00000001), num);
			OSScreenPutPixelEx(1, dx + (screenSync & 0x00000001), dy + (screenSync & 0x00000001), num);
			if (drawFilter == 1) { // Basic filter, also slows emulation down, which is good, since it runs a little fast anyway
				if(!(p->x & 0x3)) {
					OSScreenPutPixelEx(0, tvx - 1 + (screenSync & 0x00000001), tvy + (screenSync & 0x00000001), num);
					OSScreenPutPixelEx(1, dx - 1 + (screenSync & 0x00000001), dy + (screenSync & 0x00000001), num);
				}
			}
		}
    }
}

void nes_hal_init()
{
	buttonValue = 0x00000000; // Holds VPAD button value
	drawFilter = 0x00; // Holds whether we draw the filter or not
}

/* Update screen at FPS rate by allegro's drawing function. 
   Timer ensures this function is called FPS times a second. */
void nes_flip_display()  // Basically a Buffer-Flip
{
	int buf0_size = OSScreenGetBufferSizeEx(0);
	int buf1_size = OSScreenGetBufferSizeEx(1);
	DCFlushRange((void *)0xF4000000, buf0_size);
	DCFlushRange((void *)0xF4000000 + buf0_size, buf1_size);
	OSScreenFlipBuffersEx(0);
	OSScreenFlipBuffersEx(1);
}

/* Query a button's state.
   Returns 1 if button #b is pressed. */
int nes_key_state(int b)
{
	if (b == 0) {
		if (buttonValue & BUTTON_HOME) {
			return 1;
		}
	} else if (b == 1) {
		if (buttonValue & BUTTON_A) {
			return 1;
		}
	} else if (b == 2) {
		if (buttonValue & BUTTON_B) {
			return 1;
		}
	} else if (b == 3) {
		if (buttonValue & BUTTON_MINUS) {
			return 1;
		}
	} else if (b == 4) {
		if (buttonValue & BUTTON_PLUS) {
			return 1;
		}
	} else if (b == 5) {
		if (buttonValue & BUTTON_UP) {
			return 1;
		}
	} else if (b == 6) {
		if (buttonValue & BUTTON_DOWN) {
			return 1;
		}
	} else if (b == 7) {
		if (buttonValue & BUTTON_LEFT) {
			return 1;
		}
	} else if (b == 8) {
		if (buttonValue & BUTTON_RIGHT) {
			return 1;
		}
	}
	if (buttonValue & BUTTON_R) {
		if (drawFilter == 1) {
			drawFilter = 0;
		}
		else {
			drawFilter = 1;
		}
		fillScreen(0, 0, 0); // Clear the screen before applying updated filter
		flipBuffers();
		fillScreen(0, 0, 0);
		flipBuffers();
	}
	return 0;
}

