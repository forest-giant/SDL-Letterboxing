#ifndef BASICS_H_INCLUDED
#define BASICS_H_INCLUDED

#include <iostream>
#include <sstream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "base.h"

/**
//Debug
extern ofstream DEBUG_outf;
extern ofstream DEBUG_FileLoadFails;
extern SDL_Surface *DEBUG_ExcMarkSurf;
extern SDL_Texture *DEBUG_ExcMarkTex;
**/

using namespace std;


const int UP    = 0;
const int DOWN  = 1;
const int LEFT  = 2;
const int RIGHT = 3;

///COLORS
extern SDL_Color WHITE;
extern SDL_Color BLACK;

//Basic value and string
void   BAS_ctos  ( char carray[], string &strnew );
double BAS_abs   ( double x );
void   BAS_itos  ( int nr,string &newstr );
void   BAS_strcpy( char *dest,const char *sourc );
void   BAS_strcat( char *dest,const char *sourc );

//Graphics

SDL_Texture* BAS_RenderText( TTF_Font *font,const char *text,SDL_Color color );
void         BAS_DestroyTex( SDL_Texture **tex );



#endif // BASICS_H_INCLUDED
