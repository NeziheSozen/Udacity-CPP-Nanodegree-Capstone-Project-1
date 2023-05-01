#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <algorithm>
#include <mutex>
#include <future>

#include "SDL.h"

struct SNAKE_MOVEMENT {
  int x = 0;
  int y = 0;
};

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height);
  ~Snake() {};
  void Update();

  void GrowBody();
  bool IsOnACell(int x, int y);
  void SetDirection(const Direction direction);
  void SetSpeed(const int speed);
  Direction GetDirection() const { return snake_direction; };
  int GetSpeed() const { return snake_speed; };
  int GetSize() const { return snake_size; };
  bool IsAlive() const { return is_snake_alive; };
  float GetHeadX();
  float GetHeadY();
  void SetHeadX(const int x);
  void SetHeadY(const int y);
  std::vector<SDL_Point> GetBody();
  void UpdateHead();
  
 private:
  bool is_snake_growing = false;
  int grid_width;
  int grid_height;
  float snake_speed =1.0;
  int snake_size =1;
  bool is_snake_alive = true;
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
  Direction snake_direction = Direction::kUp;
  std::mutex snake_mutex;
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
};

#endif
