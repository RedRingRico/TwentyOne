#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ogcsys.h>
#include <gccore.h>

#define DEFAULT_FIFO_SIZE	( 256*1024 )
static void *g_sppFrameBuffer[ 2 ] = { NULL, NULL };
static GXRModeObj *g_pMode = NULL;

int main( int argc, char **argv )
{
	f32		YScale;
	u32		FBHeight;
	u32		FBIndex = 0;
	GXColor	ClearColour = { 0x20, 0x00, 0x20, 0xFF };

	VIDEO_Init( );

	g_pMode = VIDEO_GetPreferredMode( NULL );
	PAD_Init( );

	g_sppFrameBuffer[ 0 ] = MEM_K0_TO_K1( SYS_AllocateFramebuffer( g_pMode ) );
	g_sppFrameBuffer[ 1 ] = MEM_K0_TO_K1( SYS_AllocateFramebuffer( g_pMode ) );

	VIDEO_Configure( g_pMode );
	VIDEO_SetNextFramebuffer( g_sppFrameBuffer[ FBIndex ] );
	VIDEO_SetBlack( FALSE );
	VIDEO_Flush( );
	VIDEO_WaitVSync( );

	if( g_pMode->viTVMode & VI_NON_INTERLACE )
	{
		VIDEO_WaitVSync( );
	}

	void *pFIFO = NULL;
	pFIFO = memalign( 32, DEFAULT_FIFO_SIZE );
	memset( pFIFO, 0, sizeof( DEFAULT_FIFO_SIZE ) );

	GX_Init( pFIFO, DEFAULT_FIFO_SIZE );

	GX_SetCopyClear( ClearColour, 0x00FFFFFF );

	GX_SetViewport( 0, 0, g_pMode->fbWidth, g_pMode->efbHeight, 0, 1 );
	YScale = GX_GetYScaleFactor( g_pMode->efbHeight, g_pMode->xfbHeight );
	FBHeight = GX_SetDispCopyYScale( YScale );
	GX_SetScissor( 0, 0, g_pMode->fbWidth, g_pMode->efbHeight );
	GX_SetDispCopySrc( 0, 0, g_pMode->fbWidth, g_pMode->efbHeight );
	GX_SetDispCopyDst( g_pMode->fbWidth, FBHeight );
	GX_SetCopyFilter( g_pMode->aa, g_pMode->sample_pattern, GX_TRUE,
		g_pMode->vfilter );
	GX_SetFieldMode( g_pMode->field_rendering,
		( ( g_pMode->viHeight == 2*g_pMode->xfbHeight ) ?
			GX_ENABLE : GX_DISABLE ) );
	GX_SetCullMode( GX_CULL_NONE );
	GX_CopyDisp( g_sppFrameBuffer[ FBIndex ], GX_TRUE );
	GX_SetDispCopyGamma( GX_GM_1_0 );

	while( 1 )
	{
		PAD_ScanPads( );

		int ButtonsDown = PAD_ButtonsDown( 0 );
		
		if( ButtonsDown & PAD_BUTTON_START )
		{
			exit( 0 );
		}

		GX_SetViewport( 0, 0, g_pMode->fbWidth, g_pMode->efbHeight, 0, 1 );
		GX_DrawDone( );
		FBIndex ^= 1;
		GX_SetZMode( GX_TRUE, GX_LEQUAL, GX_TRUE );
		GX_SetColorUpdate( GX_TRUE );
		GX_CopyDisp( g_sppFrameBuffer[ FBIndex ], GX_TRUE );
		VIDEO_SetNextFramebuffer( g_sppFrameBuffer[ FBIndex ] );
		VIDEO_Flush( );
		VIDEO_WaitVSync( );
	}

	return 0;
}


