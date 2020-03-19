//Author: Benjamin Reilly
//Goal: Demonstrate Conway's Game of Life

#include "game_of_life.h"
#include "display.h"

const int frame_delay = 250; //in miliseconds

int main(int argc, char *argv[])
{
   if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
      return 1;
   
   int rows = 35,
       columns = 35,
       size = 20;
       
   float prob = 0.35;
   
   GameLife game(rows, columns);
   Display disp("Game of Life", rows, columns, size, 0);
   
   game.Randomize(prob);
   
   Uint32 time_start;
   int time_frame;
   
   while(disp.IsRunning())
   {
      //Starts Timer
      time_start = SDL_GetTicks();
      
      disp.PollEvents();
      disp.Update(game);
      disp.Show();
      game.Update();
      
      //Ends Timer
      time_frame = SDL_GetTicks() - time_start;
      
      if(disp.IsRunning() && (time_frame < frame_delay))
      {
         SDL_Delay(frame_delay - time_frame);
      }
   }
   
   SDL_Quit();
   return 0;
}
