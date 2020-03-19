#include "game_of_life.h"

#include <cstdlib>
#include <ctime>

GameLife::GameLife(int _r, int _c):
rows(_r), columns(_c)
{
   map = create_map(rows, columns);
   
   //initializes to false
   for(int i = 0; i < rows; i++)
      for(int j = 0; j < columns; j++)
         map[i][j] = false;
}

GameLife::~GameLife()
{
   destroy_map(map, rows);
   map = nullptr;
}


//randomizes map given a percent probility [0-1]
void GameLife::Randomize(float prob)
{
   srand(time(NULL));

   for(int i = 0; i < rows; i++)
   {
      for(int j = 0; j < columns; j++)
      {
         float rand_f = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
         
         if(prob >= rand_f)
            map[i][j] = true;
         else
            map[i][j] = false;
      }
   }
}

//updates based on rules
void GameLife::Update()
{
   bool **new_map = create_map(rows, columns);
   
   //update the new_map from map
   for(int i = 0; i < rows; i++)
   {
      for(int j = 0; j < columns; j++)
      {
         int num_alive = num_alive_around_cell(i, j);
         
         if(new_map[i][j])//Cell is alive
         {
            if(num_alive < 2)//------Underpopulation(Dies)
               new_map[i][j] = false;
            else if(num_alive > 3)//-Overpopulation(Dies)
               new_map[i][j] = false;
            else//-------------------Perfect(Lives)
               new_map[i][j] = true; 
         }
         else//Cell is dead
         {
            if(num_alive == 3)
               new_map[i][j] = true;
            else
               new_map[i][j] = false;
         }
      }
   }
   
   //Destroys then reassigns the updated map
   destroy_map(map, rows);
   map = new_map;
}


bool GameLife::IsAlive(int _r, int _c) const
{
   //Catch Out Bound Input
   if(_r < 0 || _r >= rows || _c < 0 || _c >= columns)
      return false;
   
   return map[_r][_c];
}

int GameLife::GetRows() const
{
   return rows;
}

int GameLife::GetColumns() const
{
   return columns;
}

//--------------------------------------------------
//                   Private
//--------------------------------------------------

bool** GameLife::create_map(int _r, int _c)
{
   bool** new_map = new bool*[_r];
   for(int i = 0; i < _r; i++)
      new_map[i] = new bool[_c];
   
   return new_map;
}

void GameLife::destroy_map(bool **arr, int _r)
{
   for(int i = 0; i < _r; i++)
      delete[] arr[i];
   
   delete[] arr;
}
int GameLife::num_alive_around_cell(int _r, int _c)
{
   int num_alive = 0;
   for(int i = -1; i <= 1; i++)
   {
      for(int j = -1; j <= 1; j++)
      {
         //Looks at the neightbors of (_r, _c)
         int neighbor_r = _r + i,
             neighbor_c = _c + j;
         
         //catch outbound error
         if(neighbor_r < 0 || neighbor_r >= rows || neighbor_c < 0 || neighbor_c >= columns)
            continue;
         
         //skips (_r, _c) the OG cell
         if(neighbor_r == _r && neighbor_c == _c)
            continue;
         
         if(map[neighbor_r][neighbor_c])
            num_alive++;
      }
   }
   return num_alive;
}