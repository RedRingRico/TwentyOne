#include <Cube.h>

void oneDrawCube( /*const guVector p_Position, const guVector p_Orientation,
	const f32 p_Scale, */const GXColor p_Colour/*, const guVector p_CameraPos,
	const Mtx p_ViewMatrix*/ )
{
	u8			R, G, B;
	Mtx			ModelMatrix;
	Mtx			ModelViewMatrix;
	Mtx			TmpMatrix;
	guVector	RotAxis;
	f32			SceneRotX;

	R = p_Colour.r;
	G = p_Colour.g;
	B = p_Colour.b;
/*	SceneRotX = 360.0f - p_Orientation.x;

	RotAxis.x = 1.0f;
	RotAxis.y = 0.0f;
	RotAxis.z = 0.0f;
	guMtxIdentity( ModelMatrix );
	guMtxRotAxisDeg( ModelMatrix, &RotAxis, p_Orientation.y );
	guMtxConcat( ModelMatrix, p_ViewMatrix, ModelViewMatrix );

	RotAxis.x = 0.0f;
	RotAxis.y = 1.0f;
	RotAxis.z = 0.0f;
	guMtxIdentity( ModelMatrix );
	guMtxRotAxisDeg( ModelMatrix, &RotAxis, SceneRotX );
	guMtxConcat( ModelViewMatrix, ModelMatrix, ModelViewMatrix );

	guMtxIdentity( ModelMatrix );
	guMtxApplyTrans( ModelMatrix, ModelMatrix, p_Position.x, p_Position.y,
		p_Position.z );
	guMtxConcat( ModelViewMatrix, ModelMatrix, ModelViewMatrix );

	guMtxApplyTrans( ModelViewMatrix, TmpMatrix, -p_CameraPos.x,
		-p_CameraPos.y, -p_CameraPos.z );

	GX_LoadPosMtxImm( TmpMatrix, GX_PNMTX0 );*/

	GX_Begin( GX_TRIANGLES, GX_VTXFMT0, 36 );
		/* Front */
		GX_Position3f32( -1.0f, 1.0f, 1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( 1.0f, 1.0f, 1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( -1.0f, -1.0f, 1.0f );
		GX_Color3u8( R, G, B );

		GX_Position3f32( 1.0f, 1.0f, 1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( 1.0f, -1.0f, 1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( -1.0f, -1.0f, 1.0f );
		GX_Color3u8( R, G, B );
		

		/* Back */
		GX_Position3f32( 1.0f, 1.0f, -1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( -1.0f, 1.0f, -1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( 1.0f, -1.0f, -1.0f );
		GX_Color3u8( R, G, B );

		GX_Position3f32( -1.0f, 1.0f, -1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( -1.0f, -1.0f, -1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( 1.0f, -1.0f, -1.0f );
		GX_Color3u8( R, G, B );
		
		
		/* Left */
		GX_Position3f32( -1.0f, 1.0f, -1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( -1.0f, 1.0f, 1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( -1.0f, -1.0f, 1.0f );
		GX_Color3u8( R, G, B );
		
		GX_Position3f32( -1.0f, 1.0f, -1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( -1.0f, -1.0f, 1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( -1.0f, -1.0f, -1.0f );
		GX_Color3u8( R, G, B );
		

		/* Right */
		GX_Position3f32( 1.0f, 1.0f, 1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( 1.0f, 1.0f, -1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( 1.0f, -1.0f, -1.0f );
		GX_Color3u8( R, G, B );
		
		GX_Position3f32( 1.0f, 1.0f, 1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( 1.0f, -1.0f, -1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( 1.0f, -1.0f, 1.0f );
		GX_Color3u8( R, G, B );
		

		/* Top */
		GX_Position3f32( -1.0f, 1.0f, -1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( 1.0f, 1.0f, -1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( -1.0f, 1.0f, 1.0f );
		GX_Color3u8( R, G, B );

		GX_Position3f32( 1.0f, 1.0f, -1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( 1.0f, 1.0f, 1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( -1.0f, 1.0f, 1.0f );
		GX_Color3u8( R, G, B );
		

		/* Bottom */
		GX_Position3f32( -1.0f, -1.0f, -1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( 1.0f, -1.0f, -1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( 1.0f, -1.0f, 1.0f );
		GX_Color3u8( R, G, B );

		GX_Position3f32( -1.0f, -1.0f, -1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( 1.0f, -1.0f, 1.0f );
		GX_Color3u8( R, G, B );
		GX_Position3f32( -1.0f, -1.0f, 1.0f );
		GX_Color3u8( R, G, B );
	GX_End( );
}

