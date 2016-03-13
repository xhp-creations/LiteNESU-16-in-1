#ifndef DRAW_H
#define DRAW_H
#include "program.h"
#include <gctypes.h>

void flipBuffers();
void fillScreen(char r, char g, char b);
void drawString(int x1, int y1, int x2, int y2, char * string);
void decodeImg(u8 *input, const u8 *data, uint32_t size);
void paintIndexImageFS(const u8 *data, const u8 *pal, int trans);

#endif /* DRAW_H */