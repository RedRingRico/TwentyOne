#include <Renderer.h>

GX_RENDERER g_Renderer;

u32 oneInitialiseRenderer( void )
{
	memset( &g_Renderer, 0, sizeof( GX_RENDERER ) );
	
	g_Renderer.ClearColour.r = 0x20;
	g_Renderer.ClearColour.g = 0x00;
	g_Renderer.ClearColour.b = 0x20;
	g_Renderer.ClearColour.a = 0xFF;

	VIDEO_Init( );
	g_Renderer.pRenderMode = VIDEO_GetPreferredMode( NULL );
	g_Renderer.ppFrameBuffer[ 0 ] =
		MEM_K0_TO_K1( SYS_AllocateFramebuffer( g_Renderer.pRenderMode ) );
	g_Renderer.ppFrameBuffer[ 1 ] =
		MEM_K0_TO_K1( SYS_AllocateFramebuffer( g_Renderer.pRenderMode ) );
	
	VIDEO_Configure( g_Renderer.pRenderMode );
	VIDEO_SetNextFramebuffer(
		g_Renderer.ppFrameBuffer[ g_Renderer.FrameBufferIndex ] );
	VIDEO_SetBlack( FALSE );
	VIDEO_Flush( );
	VIDEO_WaitVSync( );

	if( g_Renderer.pRenderMode->viTVMode & VI_NON_INTERLACE )
	{
		VIDEO_WaitVSync( );
	}
	
	g_Renderer.pFIFO = memalign( 32, DEFAULT_FIFO_SIZE );
	memset( g_Renderer.pFIFO, 0, DEFAULT_FIFO_SIZE );

	GX_Init( g_Renderer.pFIFO, DEFAULT_FIFO_SIZE );
	GX_SetCopyClear( g_Renderer.ClearColour, 0x00FFFFFF );
	GX_SetViewport( 0, 0, g_Renderer.pRenderMode->fbWidth,
		g_Renderer.pRenderMode->efbHeight, 0, 1 );
	g_Renderer.YScale = GX_GetYScaleFactor( g_Renderer.pRenderMode->efbHeight,
		g_Renderer.pRenderMode->xfbHeight );

	g_Renderer.FrameBufferHeight = GX_SetDispCopyYScale( g_Renderer.YScale );
	GX_SetScissor( 0, 0, g_Renderer.pRenderMode->fbWidth,
		g_Renderer.pRenderMode->efbHeight );
	GX_SetDispCopySrc( 0, 0, g_Renderer.pRenderMode->fbWidth,
		g_Renderer.pRenderMode->efbHeight );
	GX_SetDispCopyDst( g_Renderer.pRenderMode->fbWidth,
		g_Renderer.FrameBufferHeight );
	GX_SetCopyFilter( g_Renderer.pRenderMode->aa,
		g_Renderer.pRenderMode->sample_pattern, GX_TRUE,
		g_Renderer.pRenderMode->vfilter );
	GX_SetFieldMode( g_Renderer.pRenderMode->field_rendering,
		( ( g_Renderer.pRenderMode->viHeight ==
			2*g_Renderer.pRenderMode->xfbHeight ) ? GX_ENABLE : GX_DISABLE ) );
	GX_SetCullMode( GX_CULL_NONE );
	GX_CopyDisp( g_Renderer.ppFrameBuffer[ g_Renderer.FrameBufferIndex ],
		GX_TRUE );
	GX_SetDispCopyGamma( GX_GM_1_0 );

	return 1;
}

void oneBeginScene( void )
{
	GX_SetViewport( 0, 0, g_Renderer.pRenderMode->fbWidth,
		g_Renderer.pRenderMode->efbHeight, 0, 1 );
}

void oneEndScene( void )
{
	GX_DrawDone( );
	g_Renderer.FrameBufferIndex ^= 1;
	GX_SetZMode( GX_TRUE, GX_LEQUAL, GX_TRUE );
	GX_SetColorUpdate( GX_TRUE );
	GX_CopyDisp( g_Renderer.ppFrameBuffer[ g_Renderer.FrameBufferIndex ],
		GX_TRUE );

	VIDEO_SetNextFramebuffer(
		g_Renderer.ppFrameBuffer[ g_Renderer.FrameBufferIndex ] );
	VIDEO_Flush( );	
	VIDEO_WaitVSync( );
}

