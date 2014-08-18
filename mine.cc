#include "board.h"
#include <stdlib.h>
#include <iostream>

int main() {
  Board board(10, 10, 10);
  std::cout << board << std::endl;

  return EXIT_SUCCESS;
}
