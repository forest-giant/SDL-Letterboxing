#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

// -- FROM CLASSES --
#include "assets.h"

#define RENDER_MAIN WIN_MAIN.render
#define WINDOW_MAIN WIN_MAIN.window

//Virtual size
#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080

//Real size
#define WIN_WIDTH WIN_MAIN.getWindowWidth()
#define WIN_HEIGHT WIN_MAIN.getWindowHeight()
#define REAL_SCREEN_HEIGHT (double)WIN_WIDTH/16*9
#define REAL_SCREEN_WIDTH  WIN_WIDTH
#define Y_ABS (WIN_HEIGHT - REAL_SCREEN_HEIGHT)/2

#define SCALE ( (long double)REAL_SCREEN_WIDTH/SCREEN_WIDTH )

using namespace std;



///CONSTANTS
const int NO_CHANGE = -30000;
const int UPDATED   = true;
//Display Mode
const int DISPLAYMODE_FREE = 0;
const int DISPLAYMODE_LETTERBOX = 1;

//VAR
extern int ENGINE_displaymode;

extern class CLS_WINDOWING{

    private:
    std::string title;
    int window_flags,render_flags;
    // --Screen --
    int width;
    int height;

    //ViewPorts
    int viewport_x;
    int viewport_y;

    public:

    //---WINDOWS AND RENDERES---
    SDL_Window   *window;
    SDL_Renderer *render;

    void init(void);
    void setTitle(std::string x );
    void setWindowWidth ( int x );
    void setWindowHeight( int x );
    int  getWindowWidth ( void );
    int  getWindowHeight( void );
    void setWindowFlags( int x );
    void setRenderFlags( int x );
    void createWindow(void);
    void createRender(void);

}WIN_MAIN;


// -- GENERAL --
int  ENGINE_Init(void);
void ENGINE_HandleEvents( SDL_Event *EVENT );
void ENGINE_HandleEvent_resizeWindow( SDL_Event *EVENT );
void ENGINE_Quit(void);

// -- RENDERING --
SDL_Surface *LoadSurf(string file);
SDL_Texture *LoadTex(string file);
void ApplyTexFree(int x,int y,SDL_Texture *tex,SDL_Rect *clip = NULL,int w = NO_CHANGE,int h = NO_CHANGE );
void ApplyTexLetterbox(int x,int y,SDL_Texture *tex,SDL_Rect *clip = NULL,int w = NO_CHANGE,int h = NO_CHANGE );
void ApplyTex(int x,int y,SDL_Texture *tex,SDL_Rect *clip = NULL,int w = NO_CHANGE,int h = NO_CHANGE );

//Draw Rectangle
void DrawRectFree(int x,int y,int x2,int y2);
void DrawRectAdjusted(int x,int y,int x2,int y2);
void DrawRect(int x,int y,int x2,int y2,SDL_Color *color);
//FillRect
void FillRectFree(int x,int y,int x2,int y2);
void FillRectAdjusted(int x,int y,int x2,int y2);
void FillRect(int x,int y,int x2,int y2,SDL_Color *color);



void ENGINE_WinRenderPresent(void);

#endif // BASE_H_INCLUDED
