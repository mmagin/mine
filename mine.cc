#include "board.h"
#include <stdlib.h>
#include <iostream>

int main() {
  Board board(5, 5, 5);
  std::cout << board << std::endl;

  return EXIT_SUCCESS;
}
