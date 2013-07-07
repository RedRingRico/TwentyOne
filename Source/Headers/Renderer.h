#ifndef __TWENTYONE_RENDERER_H__
#define __TWENTYONE_RENDERER_H__

#include <ogcsys.h>

#define DEFAULT_FIFO_SIZE ( 256*1024 )

typedef struct __tagGX_RENDERER
{
	GXRModeObj	*pRenderMode;
	void *ppFrameBuffer[ 2 ];
	u32 FrameBufferIndex;
	f32 YScale;
	u32 FrameBufferHeight;
	GXColor ClearColour;
	void *pFIFO;
}GX_RENDERER;
extern GX_RENDERER g_Renderer;

u32 oneInitialiseRenderer( void );
void oneBeginScene( void );
void oneEndScene( );

#endif

