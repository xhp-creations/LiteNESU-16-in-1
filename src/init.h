#ifndef _INIT_H_
#define _INIT_H_

extern void (*OSDynLoad_Acquire)(char* rpl, unsigned int *handle);
extern void (*OSDynLoad_FindExport)(unsigned int handle, int isdata, char *symbol, void *address);
extern void (*OSFatal)(char* msg);
extern void (*__os_snprintf)(char* s, int n, const char * format, ... );
extern unsigned int coreinit_handle;
extern void (*OSScreenInit)();
extern unsigned int (*OSScreenPutPixelEx)(unsigned int bufferNum, unsigned int posX, unsigned int posY, unsigned int color);
extern void (*DCFlushRange)(void *buffer, unsigned int length);
extern void (*DCStoreRange)(void *buffer, unsigned int length);
extern void (*DCInvalidateRange)(void *buffer, unsigned int length);
extern unsigned int(*OSScreenFlipBuffersEx)(unsigned int bufferNum);
extern unsigned int(*OSScreenGetBufferSizeEx)(unsigned int bufferNum);
extern unsigned int(*OSScreenSetBufferEx)(unsigned int bufferNum, void * addr);
extern unsigned int(*OSScreenClearBufferEx)(unsigned int bufferNum, unsigned int temp);
extern unsigned int(*OSScreenPutFontEx)(unsigned int bufferNum, unsigned int posX, unsigned int posY, void * buffer);

#endif
