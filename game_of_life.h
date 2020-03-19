#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

class GameLife
{
   public:
      GameLife(int _r, int _c);
      ~GameLife();
      
      //randomizes map given a percent probility [0-1]
      void Randomize(float prob);
      
      //updates based on rules
      void Update();
      
      //gives state of a cell
      bool IsAlive(int _r, int _c) const;
      
      //give rows
      int GetRows() const;
      
      //give columns
      int GetColumns() const;
      
   private:
      int rows;
      int columns;
      bool** map;
      
      bool** create_map(int _r, int _c);
      void destroy_map(bool **arr, int _r);
      int num_alive_around_cell(int _r, int _c);
};

#endif