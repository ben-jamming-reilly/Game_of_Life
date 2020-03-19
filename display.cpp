#include "display.h"

Display::Display(const char *name, int _r, int _c, int _s, Uint32 flags):
win(nullptr), ren(nullptr), rows_cells(_r), columns_cells(_c), size_cells(_s)
{
   int height = rows_cells * size_cells,
       width  = columns_cells * size_cells;
       
   win = SDL_CreateWindow(name,
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      width,
      height,
      flags
   );
   ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
   running = true;
}

Display::~Display()
{
   SDL_DestroyRenderer(ren);
   SDL_DestroyWindow(win);
}

bool Display::IsRunning()
{
   return running;
}

void Display::Update(GameLife &game)
{
   SDL_RenderClear(ren);
   std::list<SDL_Rect> alive_cells;
   
   //scans GameLife and makes rect obj for alive cells
   for(int r = 0; r < rows_cells; r++)
   {
      for(int c = 0; c < columns_cells; c++)
      {
         //alive cell is displayed with a rectangle
         if(game.IsAlive(r, c))
         {
            SDL_Rect rec = {c * size_cells,
               r * size_cells,
               size_cells,
               size_cells
            };
            alive_cells.push_front(rec);
         }
      }
   }
   
   //set color to back
   SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
   
   //draws all rectangles to the renderer
   for(SDL_Rect t: alive_cells)
      SDL_RenderFillRect(ren, &t);
   
   //sets background color
   SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0xFF);
}

void Display::PollEvents()
{
   SDL_Event event;
   SDL_PollEvent(&event);
   
   if(event.type == SDL_QUIT)
      running = false;
}

void Display::Show()
{
   SDL_RenderPresent(ren);
}