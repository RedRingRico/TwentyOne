#include <Grid.h>

void oneDrawGrid( const f32 p_Width, const f32 p_Depth, const f32 p_Spacing )
{
	f32 TotalLines = 0.0f;
	int i = 0;

	TotalLines = p_Width / p_Spacing;
	TotalLines += p_Depth / p_Spacing;
	TotalLines *= 2.0f;

	GX_Begin( GX_LINES, GX_VTXFMT0, 404 );
	for( i = -50; i < 51; ++i )
	{
		GX_Position3f32( ( f32 )i, -1.0f, 50.0f );
		GX_Color3u8( 255, 255, 255 );
		GX_Position3f32( ( f32 )i, -1.0f, -50.0f );
		GX_Color3u8( 255, 255, 255 );

		GX_Position3f32( 50.0f, -1.0f, ( f32 )i );
		GX_Color3u8( 255, 255, 255 );
		GX_Position3f32( -50.0f, -1.0f, ( f32 )i );
		GX_Color3u8( 255, 255, 255 );
	}
/*
		GX_Position3f32( -1.0f, -1.0f, 1.0f );
		GX_Color3u8( 255, 255, 255 );
		GX_Position3f32( -1.0f, -1.0f, -1.0f );
		GX_Color3u8( 255, 255, 255 );

		GX_Position3f32( 0.0f, -1.0f, 1.0f );
		GX_Color3u8( 255, 255, 255 );
		GX_Position3f32( 0.0f, -1.0f, -1.0f );
		GX_Color3u8( 255, 255, 255 );

		GX_Position3f32( 2.0f, -1.0f, 1.0f );
		GX_Color3u8( 255, 255, 255 );
		GX_Position3f32( 2.0f, -1.0f, -1.0f );
		GX_Color3u8( 255, 255, 255 );*/
	GX_End( );
}

