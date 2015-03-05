#include "basics.h"
#include "base.h"
#include "cmath"



//COLORS
SDL_Color WHITE = {255,255,255,255};
SDL_Color BLACK = {  0,  0,  0,255};

void   BAS_ctos( char carray[], string &strnew ){
int i;
strnew.erase();

while( carray[0] == ' ' )
{
    for( i = 1; (unsigned)i < SDL_strlen( carray ); i++ )
    carray[i-1] = carray[i];
    carray[i-1] = '\0';
}

for( int i = 0; carray[i] != '\0'; i++ )
strnew += carray[i];
}
double BAS_abs( double x ){
if( x < 0 )
return x * -1;
return x;
}
void   BAS_itos(int nr,string &newstr ){
std::stringstream ssaux;
newstr.erase();
ssaux<<nr;
ssaux>>newstr;
}
void   BAS_strcpy( char *dest,const char *sourc ){
int len_sourc,i;
len_sourc = SDL_strlen( sourc );

for( i = 0; i < len_sourc; i++ )
dest[i] = sourc[i];
dest[len_sourc] = '\0';
}
void   BAS_strcat( char *dest,const char *sourc ){
int len_dest,len_sourc,i;
len_dest  = SDL_strlen( dest );
len_sourc = SDL_strlen( sourc );

for( i = 0; i < len_sourc; i++ )
dest[i + len_dest ] = sourc[i];
dest[len_sourc + len_dest ] = '\0';
}

SDL_Texture* BAS_RenderText( TTF_Font *font,const char *text,SDL_Color color ){

SDL_Surface *aux_surf = NULL;
SDL_Texture *dest = NULL;

aux_surf = TTF_RenderText_Blended( font,text,color );
dest = SDL_CreateTextureFromSurface( WIN_MAIN.render, aux_surf );
return dest;
}
void         BAS_DestroyTex( SDL_Texture **tex ){

if( &tex != NULL )
{
    SDL_DestroyTexture( *tex );
    *tex = NULL;
}
}




