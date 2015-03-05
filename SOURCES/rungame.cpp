#include "rungame.h"
#include "base.h"
#include "basics.h"
#include "console.h"

void RUN_GAME(void){
SDL_Event EVENT;
bool RUN = true;



/// -- MAIN LOOP --
while( RUN ){

/// -- EVENTS --
while( SDL_PollEvent( &EVENT ) )
{
    //ENGINE
    ENGINE_HandleEvents( &EVENT );
    //Console
    CONS.sendEvent( &EVENT );

    if( EVENT.type == SDL_QUIT )
        RUN = false;
    else
    if( EVENT.type == SDL_KEYDOWN )
    {
        if( EVENT.key.keysym.scancode == SDL_SCANCODE_ESCAPE )
        {
            RUN = false;
        }
        else
        if( EVENT.key.keysym.scancode == SDL_SCANCODE_GRAVE )
        {
            CONS.switch_if_display();
        }
        else
        if( EVENT.key.keysym.scancode == SDL_SCANCODE_F11 )
        {
            if( ENGINE_displaymode == DISPLAYMODE_FREE )
            ENGINE_displaymode = DISPLAYMODE_LETTERBOX;
            else
            ENGINE_displaymode = DISPLAYMODE_FREE;
        }
    }

}



/// -- RENDER --
SDL_SetRenderDrawColor( RENDER_MAIN, 40,40,40,255 );
SDL_RenderClear( RENDER_MAIN );



CONS.draw();

ENGINE_WinRenderPresent();
}

}
