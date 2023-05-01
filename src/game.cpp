#include "game.h"
#include <iostream>
#include "SDL.h"


Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      grid_width(grid_width),
      grid_height(grid_height),
      engine(random_device()),
      random_w(0, static_cast<int>(grid_width -1)),
      random_h(0, static_cast<int>(grid_height-1))
      {
  	PlaceFood();
      }

void Game::Run(Renderer &renderer, std::size_t target_frame_duration) 
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    search.reset(new Search(grid_width, grid_height));
    Update();
    
    SDL_Point start, end;
    start.x = snake.GetHeadY();
    start.y = snake.GetHeadX();
    end.x = food.y;
    end.y = food.x;

    const auto path = search->SearchWithPoints(start, end);
    snake.SetHeadY( path[1].x);
    snake.SetHeadX( path[1].y );
    Update();
    renderer.Render(snake, food, path);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(game_score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);

    if (!snake.IsOnACell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() 
{
  if (!snake.IsAlive()) return;

  snake.Update();


  int new_x = static_cast<int>(snake.GetHeadX());
  int new_y = static_cast<int>(snake.GetHeadY());

  auto near_x = ( (food.x == new_x) or ( std::abs(food.x - new_x) == 1) );
  auto near_y = ( (food.y == new_y) or ( std::abs(food.y - new_y) == 1) );

  // Check if there's food_ over here
  if ( near_x and near_y) {
    game_score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.SetSpeed(snake.GetSpeed());
  }
}

int Game::GetScore() const { return game_score; }
int Game::GetSize() const { return snake.GetSize(); }
