#include "snake.h"
#include <cmath>
#include <iostream>

  Snake::Snake(int grid_width, int grid_height)
:       grid_width (grid_width),
       	grid_height (grid_height),
        head_x (grid_width/2),
        head_y (grid_height/2)

       {
       
       }

  void Snake::SetDirection(const Direction direction) 
  { 
   snake_direction = direction; 
  }

void Snake::SetSpeed(const int speed) 
{ 
snake_speed = speed; 
}

  float Snake::GetHeadX() 
  {
      std::lock_guard<std::mutex> lck(snake_mutex);
      return head_x; 
  }
  
  float Snake::GetHeadY() {
      std::lock_guard<std::mutex> lck(snake_mutex);
      return head_y;
  }
void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};

  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

  void Snake::SetHeadX(const int x) 
  {
      std::lock_guard<std::mutex> lck(snake_mutex);
      head_x = static_cast<float>(x);
  }
  
  void Snake::SetHeadY(const int y) {
      std::lock_guard<std::mutex> lck(snake_mutex);
      head_y = static_cast<float>(y);
  };
  
    std::vector<SDL_Point> Snake::GetBody() {
      std::lock_guard<std::mutex> lck(snake_mutex);
      return body;
  };
  
void Snake::UpdateHead() {
  std::lock_guard<std::mutex> lck(snake_mutex);


  switch (snake_direction) {
    case Direction::kUp:
      head_y -= snake_speed;
      break;

    case Direction::kDown:
      head_y += snake_speed;
      break;

    case Direction::kLeft:
      head_x -= snake_speed;
      break;

    case Direction::kRight:
      head_x += snake_speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  std::lock_guard<std::mutex> lck(snake_mutex);
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!is_snake_growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    is_snake_growing = false;
    snake_size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      is_snake_alive = false;
    }
  }
}

void Snake::GrowBody() { is_snake_growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::IsOnACell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}
