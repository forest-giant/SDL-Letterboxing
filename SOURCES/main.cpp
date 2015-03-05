#include <SDL2/SDL.h>
#include "base.h"
#include "rungame.h"
#include "settings.h"

int main(){

    SETTINGS.load();

    ENGINE_Init();

    RUN_GAME();

    ENGINE_Quit();

    return 0;
}
