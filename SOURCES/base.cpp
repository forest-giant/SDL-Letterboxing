#include "base.h"
#include "settings.h"
#include "console.h"

// -- VAR --
int ENGINE_displaymode = DISPLAYMODE_LETTERBOX;

/// -- CLASSES --
CLS_WINDOWING   WIN_MAIN;


/// --- FUNCTIONS: CLS_WINDOWING ---
void CLS_WINDOWING::init(){
width  = 100;
height = 100;

viewport_x = 100;
viewport_y = 100;

window = NULL;
render = NULL;
}
void CLS_WINDOWING::setTitle( std::string x ){

}
void CLS_WINDOWING::setWindowWidth(int x){
width = x;
}
void CLS_WINDOWING::setWindowHeight(int x){
height = x;
}
int  CLS_WINDOWING::getWindowWidth ( void ){
return width;
}
int  CLS_WINDOWING::getWindowHeight( void ){
return height;
}
void CLS_WINDOWING::setWindowFlags( int x ){
window_flags = x;
}
void CLS_WINDOWING::setRenderFlags( int x ){
render_flags = x;
}
void CLS_WINDOWING::createWindow( void ){

window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                           width,height,window_flags);

}
void CLS_WINDOWING::createRender( void ){

render = SDL_CreateRenderer( window, 0 , render_flags );

}


/// --- FUNCTIONS: MISC ---
int  ENGINE_Init(){

//Init SDL
if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    return 1;
//Init TTF
if( TTF_Init() == -1 )
    return 2;

WIN_MAIN.setWindowWidth ( SETTINGS.getScreenWidth() );
WIN_MAIN.setWindowHeight( SETTINGS.getScreenHeight() );
WIN_MAIN.setWindowFlags( SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN * SETTINGS.getFullScreen() );
WIN_MAIN.createWindow();

if( WIN_MAIN.window == NULL )
    return 3;

//Create Renderer

WIN_MAIN.setRenderFlags( SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
WIN_MAIN.createRender();

if( WIN_MAIN.render == NULL )
    return 4;

//Set Hints
SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0" + SETTINGS.getRenderScaleQuality() );


/// -- INIT CLASSES --
ASSETS.init();
CONS.init();

return 0;
}
void ENGINE_HandleEvent_resizeWindow( SDL_Event *EVENT ){
int w,h;
    if( EVENT->type         == SDL_WINDOWEVENT &&
        EVENT->window.event == SDL_WINDOWEVENT_RESIZED )
    {
        SDL_GetWindowSize( WIN_MAIN.window, &w, &h );
        WIN_MAIN.setWindowWidth ( w );
        WIN_MAIN.setWindowHeight( h );
    }
}
void ENGINE_HandleEvents( SDL_Event *EVENT ){

    //Handle window resize events
    ENGINE_HandleEvent_resizeWindow( EVENT );
}
void ENGINE_Quit(void){
TTF_Quit();
SDL_Quit();
}

SDL_Surface *LoadSurf(string file){
SDL_Surface *loadedimg = NULL;

loadedimg = IMG_Load( file.c_str() );

if( loadedimg == NULL )
{
    //DEBUG.fout( FILE_FLF, (string)"load fail: " + file );
    //DEBUG.fout( FILE_FLF, (string)"reason: "    + SDL_GetError() + (string)"\n" );
}

return loadedimg;
}
SDL_Texture *LoadTex(string file){
SDL_Texture *loadedtex = NULL;

loadedtex = IMG_LoadTexture(WIN_MAIN.render,file.c_str() );

if( loadedtex == NULL )
{
    //DEBUG.fout( FILE_FLF, (string)"load fail: " + file );
    //DEBUG.fout( FILE_FLF, (string)"reason: "    + SDL_GetError() + (string)"\n" );
}

return loadedtex;
}
//Apply Tex
void ApplyTexFree(int x,int y,SDL_Texture *tex,SDL_Rect *clip ,int w,int h ){

    SDL_Rect pos;

    pos.x = x;
    pos.y = y;

    if( clip != NULL )
    {
        pos.w = clip->w;
        pos.h = clip->h;
    }
    else
    SDL_QueryTexture( tex,NULL,NULL,&pos.w,&pos.h );

    if( w != NO_CHANGE ) pos.w = w;
    if( h != NO_CHANGE ) pos.h = h;

    SDL_RenderCopy( RENDER_MAIN,tex,clip,&pos );
}
void ApplyTexLetterbox(int x,int y,SDL_Texture *tex,SDL_Rect *clip,int w,int h ){

    SDL_Rect pos;

    pos.y = Y_ABS;

    pos.x = ceil( (double)x * SCALE );
    pos.y += ceil( (double)y * SCALE  );


    if( clip != NULL )
    {
        pos.w = clip->w;
        pos.h = clip->h;
    }
    else
    SDL_QueryTexture( tex,NULL,NULL,&pos.w,&pos.h );

    if( w != NO_CHANGE ) pos.w = w;
    if( h != NO_CHANGE ) pos.h = h;

    //ADJUST
    pos.w = ceil((double)pos.w * SCALE);
    pos.h = ceil((double)pos.h * SCALE);


    SDL_RenderCopy( RENDER_MAIN,tex,clip,&pos );
}
void ApplyTex(int x,int y,SDL_Texture *tex,SDL_Rect *clip ,int w ,int h){

    //Free Mode
    if( ENGINE_displaymode == DISPLAYMODE_FREE )
    {
        ApplyTexFree( x, y, tex, clip, w, h );
    }
    //Letterbox Mode
    else
    if( ENGINE_displaymode == DISPLAYMODE_LETTERBOX )
    {
        ApplyTexLetterbox( x, y, tex, clip , w, h );
    }
}
//Draw Rect
void DrawRectFree(int x,int y,int x2,int y2){

    SDL_Rect target;

    target.x = x<x2 ? x : x2 ;
    target.y = y<y2 ? y : y2 ;
    target.w = BAS_abs( x - x2 );
    target.h = BAS_abs( y - y2 );

    SDL_RenderDrawRect( RENDER_MAIN, &target );
}
void DrawRectLetterbox(int x,int y,int x2,int y2){

    SDL_Rect target;

    target.y = Y_ABS;

    target.x = (x<x2 ? x : x2)  * SCALE;
    target.y += (y<y2 ? y : y2) * SCALE;
    target.w = BAS_abs( x - x2 ) * SCALE;
    target.h = BAS_abs( y - y2 ) * SCALE;


    SDL_RenderDrawRect( RENDER_MAIN, &target );
}
void DrawRect(int x,int y,int x2,int y2,SDL_Color *color){

    SDL_SetRenderDrawColor( RENDER_MAIN,color->r,color->g,color->b,color->a );

    //If in FREE MODE
    if( ENGINE_displaymode == DISPLAYMODE_FREE )
    DrawRectFree(x,y,x2,y2);

    //If in Letterbox MODE
    else
    if( ENGINE_displaymode == DISPLAYMODE_LETTERBOX )
    DrawRectLetterbox(x,y,x2,y2);
}
//Fill Rect
void FillRectFree(int x,int y,int x2,int y2){

    SDL_Rect target;

    target.x = x<x2 ? x : x2 ;
    target.y = y<y2 ? y : y2 ;
    target.w = BAS_abs( x - x2 );
    target.h = BAS_abs( y - y2 );

    SDL_RenderFillRect( RENDER_MAIN, &target );
}
void FillRectLetterbox(int x,int y,int x2,int y2){

    SDL_Rect target;

    target.y = Y_ABS;

    target.x = (x<x2 ? x : x2)  * SCALE ;
    target.y += (y<y2 ? y : y2) * SCALE ;
    target.w = BAS_abs( x - x2 ) * SCALE ;
    target.h = BAS_abs( y - y2 ) * SCALE;


    SDL_RenderFillRect( RENDER_MAIN, &target );
}
void FillRect(int x,int y,int x2,int y2,SDL_Color *color){

    SDL_SetRenderDrawColor( RENDER_MAIN,color->r,color->g,color->b,color->a );

    //If in FREE MODE
    if( ENGINE_displaymode == DISPLAYMODE_FREE )
    FillRectFree(x,y,x2,y2);

    //If in Letterbox MODE
    else
    if( ENGINE_displaymode == DISPLAYMODE_LETTERBOX )
    FillRectLetterbox(x,y,x2,y2);
}


void ENGINE_WinRenderPresent( void){

    SDL_Rect blackline1,blackline2;

    /// -- BLACKLINES --
    if( ENGINE_displaymode == DISPLAYMODE_LETTERBOX )
    {
        //--- INIT BLACKLINES ---
        blackline1.x = 0;
        blackline1.y = 0;
        blackline2.x = 0;
        blackline2.y = Y_ABS + REAL_SCREEN_HEIGHT;
        blackline1.w = WIN_MAIN.getWindowWidth();
        blackline1.h = (WIN_MAIN.getWindowHeight()-REAL_SCREEN_HEIGHT)/2;
        blackline2.w = WIN_MAIN.getWindowWidth();
        blackline2.h = (WIN_MAIN.getWindowHeight()-REAL_SCREEN_HEIGHT)/2;

        //Draw Black Lines
        SDL_SetRenderDrawColor( RENDER_MAIN, 0,0,0,255 );
        SDL_RenderFillRect( RENDER_MAIN, &blackline1 );
        SDL_RenderFillRect( RENDER_MAIN, &blackline2 );
    }


    SDL_RenderPresent( RENDER_MAIN );
}


