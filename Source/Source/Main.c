#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ogcsys.h>
#include <gccore.h>
#include <Renderer.h>

int main( int argc, char **argv )
{
	oneInitialiseRenderer( );
	PAD_Init( );

	while( 1 )
	{
		PAD_ScanPads( );

		int ButtonsDown = PAD_ButtonsDown( 0 );
		
		if( ButtonsDown & PAD_BUTTON_START )
		{
			exit( 0 );
		}
		oneBeginScene( );
		oneEndScene( );
	}

	return 0;
}


