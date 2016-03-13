#include "init.h"
void (*OSDynLoad_Acquire)(char* rpl, unsigned int *handle) = (void*)0;
void (*OSDynLoad_FindExport)(unsigned int handle, int isdata, char *symbol, void *address) = (void*)0;
void (*OSFatal)(char* msg) = (void*)0;
void (*__os_snprintf)(char* s, int n, const char * format, ... ) = (void*)0;
unsigned int coreinit_handle = 0;
void (*OSScreenInit)();
unsigned int (*OSScreenPutPixelEx)(unsigned int bufferNum, unsigned int posX, unsigned int posY, unsigned int color);
void (*DCFlushRange)(void *buffer, unsigned int length);
void (*DCStoreRange)(void *buffer, unsigned int length);
void (*DCInvalidateRange)(void *buffer, unsigned int length);
unsigned int(*OSScreenFlipBuffersEx)(unsigned int bufferNum);
unsigned int(*OSScreenGetBufferSizeEx)(unsigned int bufferNum);
unsigned int(*OSScreenSetBufferEx)(unsigned int bufferNum, void * addr);
unsigned int(*OSScreenClearBufferEx)(unsigned int bufferNum, unsigned int temp);
unsigned int(*OSScreenPutFontEx)(unsigned int bufferNum, unsigned int posX, unsigned int posY, void * buffer);

void _doInit()
{
	OSDynLoad_Acquire = (void*)(*(unsigned int*)0xF5FFFFFC);
	OSDynLoad_FindExport = (void*)(*(unsigned int*)0xF5FFFFF8);
	OSFatal = (void*)(*(unsigned int*)0xF5FFFFF4);
	__os_snprintf = (void*)(*(unsigned int*)0xF5FFFFF0);
	coreinit_handle = *(unsigned int*)0xF5FFFFEC;
	OSDynLoad_FindExport(coreinit_handle, 0, "OSScreenInit", &OSScreenInit);
	OSDynLoad_FindExport(coreinit_handle, 0, "OSScreenPutPixelEx", &OSScreenPutPixelEx);
	OSDynLoad_FindExport(coreinit_handle, 0, "DCFlushRange", &DCFlushRange);
	OSDynLoad_FindExport(coreinit_handle, 0, "DCStoreRange", &DCStoreRange);
	OSDynLoad_FindExport(coreinit_handle, 0, "DCInvalidateRange", &DCInvalidateRange);
	OSDynLoad_FindExport(coreinit_handle, 0, "OSScreenFlipBuffersEx", &OSScreenFlipBuffersEx);
	OSDynLoad_FindExport(coreinit_handle, 0, "OSScreenGetBufferSizeEx", &OSScreenGetBufferSizeEx);
	OSDynLoad_FindExport(coreinit_handle, 0, "OSScreenSetBufferEx", &OSScreenSetBufferEx);
	OSDynLoad_FindExport(coreinit_handle, 0, "OSScreenPutFontEx", &OSScreenPutFontEx);
	OSDynLoad_FindExport(coreinit_handle, 0, "OSScreenClearBufferEx", &OSScreenClearBufferEx);
}

void _doExit()
{
	void(*_Exit)();
	OSDynLoad_FindExport(coreinit_handle, 0, "_Exit", &_Exit);
	_Exit();
}

void _memset(void *b, int c, int len)
{
	int i;

	for (i = 0; i < len; i++)
		((unsigned char *)b)[i] = c;
}
