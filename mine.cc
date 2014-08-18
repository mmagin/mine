#include "board.h"
#include <stdlib.h>
#include <iostream>

int main() {
  Board board(10, 10, 10);
  unsigned x, y;
  do {
    std::cout << board << std::endl;
    std::cin >> x >> y;
  } while (board.click(x, y));
  std::cout << "BOOM" << std::endl;
  return EXIT_SUCCESS;
}
