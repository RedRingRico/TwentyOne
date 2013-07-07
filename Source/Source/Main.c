#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ogcsys.h>
#include <gccore.h>
#include <math.h>
#include <Renderer.h>

int main( int argc, char **argv )
{
	guVector	CameraPos = { 0.0f, 0.0f, 0.0f };
	guVector	CameraLook = { 0.0f, 0.0f, -1.0f };
	guVector	CameraUp = { 0.0f, 1.0f, 0.0f };
	guVector	RotAxis;
	Mtx			ViewMatrix;
	Mtx			ModelMatrix;
	Mtx			ModelViewMatrix;
	Mtx			TmpMatrix;
	Mtx44		PerspectiveMatrix;
	f32			Width;
	f32			Height;
	float		XPos = 0.0f;
	float		ZPos = 0.0f;
	float		YRot = 0.0f;
	f32			Look = 0.0f;
	f32			ZDepth = 0.0f;
	f32			SceneRotY = 0.0f;

	oneInitialiseRenderer( );
	PAD_Init( );

	GX_ClearVtxDesc( );
	GX_SetVtxDesc( GX_VA_POS, GX_DIRECT );
	GX_SetVtxDesc( GX_VA_CLR0, GX_DIRECT );

	GX_SetVtxAttrFmt( GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0 );
	GX_SetVtxAttrFmt( GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGB8, 0 );

	GX_SetNumChans( 1 );
	GX_SetNumTexGens( 0 );
	GX_SetTevOrder( GX_TEVSTAGE0, GX_TEXCOORDNULL, GX_TEXMAP_NULL,
		GX_COLOR0A0 );
	GX_SetTevOp( GX_TEVSTAGE0, GX_PASSCLR );

	guLookAt( ViewMatrix, &CameraPos, &CameraUp, &CameraLook );
	Width = g_Renderer.pRenderMode->viWidth;
	Height = g_Renderer.pRenderMode->viHeight;
	guPerspective( PerspectiveMatrix, 45, ( f32 )Width/Height, 1.0f,
		10000.0f );
	GX_LoadProjectionMtx( PerspectiveMatrix, GX_PERSPECTIVE );

	guMtxIdentity( ModelViewMatrix );

	while( 1 )
	{
		PAD_ScanPads( );
		s8 Pad = PAD_SubStickX( 0 );
		if( ( Pad < -8 ) || ( Pad > 8 ) )
		{
			YRot -= ( float )Pad / 50.0f;
		}
		Pad = PAD_StickX( 0 );
		if( Pad > 50 )
		{
			XPos += ( float )cos( DegToRad( YRot ) ) * 0.05f;
			ZPos -= ( float )sin( DegToRad( YRot ) ) * 0.05f;
		}
		if( Pad < -50 )
		{
			XPos -= ( float )cos( DegToRad( YRot ) ) * 0.05f;
			ZPos += ( float )sin( DegToRad( YRot ) ) * 0.05f;
		}

		Pad = PAD_StickY( 0 );
		if( Pad > 50 )
		{
			XPos -= ( float )sin( DegToRad( YRot ) ) * 0.05f;
			ZPos -= ( float )cos( DegToRad( YRot ) ) * 0.05f;
		}
		if( Pad < -50 )
		{
			XPos += ( float )sin( DegToRad( YRot ) ) * 0.05f;
			ZPos += ( float )cos( DegToRad( YRot ) ) * 0.05f;
		}

		Pad = PAD_SubStickY( 0 );

		if( ( ( Pad > 8 ) || ( Pad < -8 ) ) &&
			( ( 90.0f >= Look ) && ( Look >= -90.0f ) ) ) 
		{
			ZDepth -= ( ( f32 ) Pad * 0.01f );
			Look -= ( ( f32 )Pad * 0.01f );
			if( Look > 90.0f )
			{
				Look = 90.0f;
			}
			if( Look < -90.0f )
			{
				Look = -90.0f;
			}
		}

		int ButtonsDown = PAD_ButtonsDown( 0 );
		
		if( ButtonsDown & PAD_BUTTON_START )
		{
			exit( 0 );
		}
		oneBeginScene( );

		SceneRotY = 360.0f - YRot;

		RotAxis.x = 1.0f;
		RotAxis.y = 0.0f;
		RotAxis.z = 0.0f;
		guMtxIdentity( ModelMatrix );
		guMtxRotAxisDeg( ModelMatrix, &RotAxis, Look );
		guMtxConcat( ModelMatrix, ViewMatrix, ModelViewMatrix );

		RotAxis.x = 0.0f;
		RotAxis.y = 1.0f;
		RotAxis.z = 0.0f;
		guMtxIdentity( ModelMatrix );
		guMtxRotAxisDeg( ModelMatrix, &RotAxis, SceneRotY );
		guMtxConcat( ModelViewMatrix, ModelMatrix, ModelViewMatrix );

		guMtxIdentity( ModelMatrix );
		guMtxApplyTrans( ModelMatrix, ModelMatrix, 0.0f, 0.0f, -10.0f );
		guMtxConcat( ModelViewMatrix, ModelMatrix, ModelViewMatrix );

		guMtxApplyTrans( ModelViewMatrix, TmpMatrix, -XPos, 0.0f, -ZPos );

		GX_LoadPosMtxImm( TmpMatrix, GX_PNMTX0 );

		GX_Begin( GX_TRIANGLES, GX_VTXFMT0, 36 );

			/* Front */
			GX_Position3f32( -1.0f, 1.0f, 1.0f );
			GX_Color3u8( 255, 0, 0 );
			GX_Position3f32( 1.0f, 1.0f, 1.0f );
			GX_Color3u8( 255, 0, 0 );
			GX_Position3f32( -1.0f, -1.0f, 1.0f );
			GX_Color3u8( 255, 0, 0 );

			GX_Position3f32( 1.0f, 1.0f, 1.0f );
			GX_Color3u8( 255, 0, 0 );
			GX_Position3f32( 1.0f, -1.0f, 1.0f );
			GX_Color3u8( 255, 0, 0 );
			GX_Position3f32( -1.0f, -1.0f, 1.0f );
			GX_Color3u8( 255, 0, 0 );
			

			/* Back */
			GX_Position3f32( 1.0f, 1.0f, -1.0f );
			GX_Color3u8( 0, 255, 0 );
			GX_Position3f32( -1.0f, 1.0f, -1.0f );
			GX_Color3u8( 0, 255, 0 );
			GX_Position3f32( 1.0f, -1.0f, -1.0f );
			GX_Color3u8( 0, 255, 0 );

			GX_Position3f32( -1.0f, 1.0f, -1.0f );
			GX_Color3u8( 0, 255, 0 );
			GX_Position3f32( -1.0f, -1.0f, -1.0f );
			GX_Color3u8( 0, 255, 0 );
			GX_Position3f32( 1.0f, -1.0f, -1.0f );
			GX_Color3u8( 0, 255, 0 );
			
			
			/* Left */
			GX_Position3f32( -1.0f, 1.0f, -1.0f );
			GX_Color3u8( 0, 0, 255 );
			GX_Position3f32( -1.0f, 1.0f, 1.0f );
			GX_Color3u8( 0, 0, 255 );
			GX_Position3f32( -1.0f, -1.0f, 1.0f );
			GX_Color3u8( 0, 0, 255 );
			
			GX_Position3f32( -1.0f, 1.0f, -1.0f );
			GX_Color3u8( 0, 0, 255 );
			GX_Position3f32( -1.0f, -1.0f, 1.0f );
			GX_Color3u8( 0, 0, 255 );
			GX_Position3f32( -1.0f, -1.0f, -1.0f );
			GX_Color3u8( 0, 0, 255 );
			

			/* Right */
			GX_Position3f32( 1.0f, 1.0f, 1.0f );
			GX_Color3u8( 255, 255, 0 );
			GX_Position3f32( 1.0f, 1.0f, -1.0f );
			GX_Color3u8( 255, 255, 0 );
			GX_Position3f32( 1.0f, -1.0f, -1.0f );
			GX_Color3u8( 255, 255, 0 );
			
			GX_Position3f32( 1.0f, 1.0f, 1.0f );
			GX_Color3u8( 255, 255, 0 );
			GX_Position3f32( 1.0f, -1.0f, -1.0f );
			GX_Color3u8( 255, 255, 0 );
			GX_Position3f32( 1.0f, -1.0f, 1.0f );
			GX_Color3u8( 255, 255, 0 );
			

			/* Top */
			GX_Position3f32( -1.0f, 1.0f, -1.0f );
			GX_Color3u8( 255, 0, 255 );
			GX_Position3f32( 1.0f, 1.0f, -1.0f );
			GX_Color3u8( 255, 0, 255 );
			GX_Position3f32( -1.0f, 1.0f, 1.0f );
			GX_Color3u8( 255, 0, 255 );

			GX_Position3f32( 1.0f, 1.0f, -1.0f );
			GX_Color3u8( 255, 0, 255 );
			GX_Position3f32( 1.0f, 1.0f, 1.0f );
			GX_Color3u8( 255, 0, 255 );
			GX_Position3f32( -1.0f, 1.0f, 1.0f );
			GX_Color3u8( 255, 0, 255 );
			

			/* Bottom */
			GX_Position3f32( -1.0f, -1.0f, -1.0f );
			GX_Color3u8( 255, 255, 255 );
			GX_Position3f32( 1.0f, -1.0f, -1.0f );
			GX_Color3u8( 255, 255, 255 );
			GX_Position3f32( 1.0f, -1.0f, 1.0f );
			GX_Color3u8( 255, 255, 255 );

			GX_Position3f32( -1.0f, -1.0f, -1.0f );
			GX_Color3u8( 255, 255, 255 );
			GX_Position3f32( 1.0f, -1.0f, 1.0f );
			GX_Color3u8( 255, 255, 255 );
			GX_Position3f32( -1.0f, -1.0f, 1.0f );
			GX_Color3u8( 255, 255, 255 );
		GX_End( );

		oneEndScene( );
	}

	return 0;
}


