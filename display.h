#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL.h>
#include <list>
#include "game_of_life.h"

class Display
{
   public:
      Display(const char *name, int _r, int _c, int _s, Uint32 flags);
      ~Display();
      
      bool IsRunning();
      void Update(GameLife &game);
      void Show();
      void PollEvents();
      
   private:
      bool running;
      SDL_Window *win;
      SDL_Renderer *ren;
      
      int rows_cells,
          columns_cells,
          size_cells;
};

#endif