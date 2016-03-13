#include "draw.h"

void flipBuffers()
{
	int buf0_size = OSScreenGetBufferSizeEx(0);
	int buf1_size = OSScreenGetBufferSizeEx(1);
	DCFlushRange((void *)0xF4000000, buf0_size);
	DCFlushRange((void *)0xF4000000 + buf0_size, buf1_size);
	OSScreenFlipBuffersEx(0);
	OSScreenFlipBuffersEx(1);
}

void fillScreen(char r,char g,char b)
{
	uint32_t num = (r << 24) | (g << 16) | (b << 8) | 0;
	OSScreenClearBufferEx(0, num);
	OSScreenClearBufferEx(1, num);
}

void drawString(int x1, int y1, int x2, int y2, char * string)
{
	OSScreenPutFontEx(0, x2, y2, string); // Draw Text to TV
	OSScreenPutFontEx(1, x1, y1, string); // Draw Text to DRC
}

void decodeImg(u8 *input, const u8 *data, uint32_t size) // Basic RLE Decoder
{
    u8 prevChar;
    u8 count;

	uint32_t dIndex = 0;
	uint32_t pIndex = 0;
	
	input[pIndex] = data[dIndex];
	pIndex++;
	dIndex++;
	prevChar = data[dIndex - 1];
	
    /* read input until there's nothing left */
    while (dIndex < size)
    {
        input[pIndex] = data[dIndex];
		
        /* check for run */
        if (data[dIndex] == prevChar)
        {
           /* we have a run.  write it out. */
			count = data[(dIndex + 1)];
            while (count > 0)
            {
				pIndex++;
				input[pIndex] = data[dIndex];
                count--;
            }
 			dIndex++;
			pIndex++;
 			dIndex++;
			prevChar = data[dIndex] + 0x01;
        }
		else {
			prevChar = data[dIndex];
			pIndex++;
			dIndex++;
		}
    }
}

void paintIndexImageFS(const u8 *data, const u8 *pal, int trans) // Takes a RAW Photoshop indexed picture (854 x 480) and shows it full-screen
{
	int y;
	int x;
	int counter = 0;
	for (y = 0; y < 480; y++) {
		for (x = 0; x < 854; x++) {
			int idx = data[counter];
			if (idx != trans) { // If palette number is our transparent one, don't draw it
				int index = (idx * 3);
				char r = pal[index];
				char g = pal[index + 1];
				char b = pal[index + 2];
				uint32_t num = (r << 24) | (g << 16) | (b << 8) | 255;
				int a;
				for (a = 0; a < 2; a++) { // basic routine to upscale 854 x 480 Wii U DRC to 720p TV screen output
					int x1 = ( ( x * 3 ) / 2 ) + a;
					int y1 = ( ( y * 3 ) / 2 ) + a;
					int x2 = ( ( x * 3 ) / 2 ) + ( 1 - a );
					int y2 = ( ( y * 3 ) / 2 ) + a;
					OSScreenPutPixelEx( 0, x1, y1, num );
					OSScreenPutPixelEx( 0, x2, y2, num );
				}
				OSScreenPutPixelEx( 1, x, y, num );
			}
			counter++;
		}
	}
}