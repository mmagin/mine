#include "board.h"
#include <random>
#include <iostream>

std::ostream &operator<<(std::ostream &stream, Cell obj) {
  if (obj.visible) {
    if (obj.has_bomb) {
      stream << '*';
    } else {
      stream << ' ';
    }
  } else {
    if (obj.has_bomb) {
      stream << '+';
    } else {
      stream << '?';
    }
  }
  return stream;
}


Board::Board(const unsigned x_size, const unsigned y_size, const unsigned bombs) {
  if (bombs >= x_size * y_size) {
    throw "too many bombs";
  }
  this->x_size = x_size;
  this->y_size = y_size;
  this->bombs = bombs;
  populate();
}

void Board::populate() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<unsigned int> x_dist(0, x_size - 1);
  std::uniform_int_distribution<unsigned int> y_dist(0, y_size - 1);

  this->board_cells.resize(this->y_size, std::vector<Cell>(this->x_size, Cell()));

  for (auto i = 0; i < this->bombs; i++) {
    unsigned x, y;
    do {
      x = x_dist(gen);
      y = y_dist(gen);
    } while(this->cell_at(x, y).has_bomb);
    this->cell_at(x, y).has_bomb = true;
  }
}

Cell & Board::cell_at(const unsigned x, const unsigned y) {
  return this->board_cells[y][x];
}

std::ostream &operator<<(std::ostream &stream, Board obj) {
  for (auto row : obj.board_cells) {
    for (auto cell : row ) {
      stream << cell;
    }
    stream << std::endl;
  }
  return stream;
}
