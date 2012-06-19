
#include <cstdlib>
#include <string>
//#include <map>    // dont use stl
#include <SDL.h>
using namespace std;


#include "Rect.h"


class Window{
public:
    Window(){
        int opts=SDL_HWSURFACE|SDL_DOUBLEBUF;
        SDL_Surface* screen = SDL_SetVideoMode(800, 600, 32,opts);
        if ( !screen ){
            printf("Unable to set 640x480 video: %s\n", SDL_GetError());
            exit(2);
        }
    }
    SDL_Surface* getScreen(){return screen;}
private:
    SDL_Surface* screen;
};

void sdl_init(){
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        exit(1);
    }
    atexit(SDL_Quit);
}

SDL_Surface* new_win() {
    SDL_Surface* screen = SDL_SetVideoMode(800, 600, 32,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        exit(2);
    }
    return screen;
}

SDL_Surface* load_img( string filename ) {
    SDL_Surface* bmp = SDL_LoadBMP(filename.c_str() );
    if (!bmp)
    {
        printf("Unable to load bitmap: %s %s\n",
               SDL_GetError(),filename.c_str() );
        exit(3);
    }
    return bmp;
}


int main ( int argc, char** argv )
{
    Window window;
    //SDL_Surface* screen = new_win();

    SDL_Surface* bmp = load_img("art\\cb.bmp");

    // centre the bitmap on screen
    SDL_Rect dstrect;
    dstrect.x = (window.getScreen()->w - bmp->w) / 2;
    dstrect.y = (window.getScreen()->h - bmp->h) / 2;

    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    break;
                }
            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen
        SDL_FillRect(window.getScreen(), 0, SDL_MapRGB(window.getScreen()->format, 0, 0, 0));

        // draw bitmap
        SDL_BlitSurface(bmp, 0, window.getScreen(), &dstrect);

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(window.getScreen());
    } // end main loop

    // free loaded bitmap
    SDL_FreeSurface(bmp);

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
