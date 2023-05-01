#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <mutex>
#include "snake.h"

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake);

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input, Snake::Direction opposite) ;
  std::mutex controller_mutex;
};

#endif
