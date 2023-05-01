#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "search.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Renderer &renderer, std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  Controller controller;
  SDL_Point food;
  std::unique_ptr<Search> search;
  std::size_t grid_width;
  std::size_t grid_height;

  std::random_device random_device;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int game_score = 0;

  void PlaceFood();
  void Update();
};

#endif
