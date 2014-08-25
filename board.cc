#include "board.h"
#include <random>
#include <iostream>
#include <algorithm>

std::ostream &operator<<(std::ostream &stream, Cell obj) {
  if (obj.visible) {
    if (obj.adjacent > 0) {
      stream << obj.adjacent;
    } else {
      stream << ' ';
    }
  } else {
    stream << '.';
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

  for (auto y = 0; y < this->y_size; y++) {
    for (auto x = 0; x < this->x_size; x++) {
      if (!this->cell_at(x, y).has_bomb) {
	this->cell_at(x, y).adjacent = this->calc_adjacent(x, y);
      }
    }
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

unsigned Board::calc_adjacent(unsigned ux, unsigned uy) {
  auto adj = 0;
  auto x = (int)ux;
  auto y = (int)uy;
  for (auto i = std::max(y - 1, 0); i <= std::min(y + 1, (int)this->y_size - 1); i++) {
    for (auto j = std::max(x - 1, 0); j <= std::min(x + 1, (int)this->x_size - 1); j++) {
      if (this->cell_at(j, i).has_bomb) {
	adj++;
      }
    }
  }
  return adj;
}

// this algorithm is wrong
void Board::expand(const unsigned ux, const unsigned uy) {
  auto x = (int)ux;
  auto y = (int)uy;

  this->inner_expand(x, std::max(y - 1, 0));
  this->inner_expand(x, std::min(y + 1, (int)this->y_size - 1));
  
  this->inner_expand(std::max(x - 1, 0), y);
  this->inner_expand(std::min(x + 1, (int)this->x_size - 1), y);
}


void Board::inner_expand(const unsigned x, const unsigned y) {
  Cell &c = this->cell_at(x, y);
  if (!c.visible && !c.has_bomb) {
    c.visible = true;
    if (c.adjacent == 0) {
      this->expand(x, y);
    }
  }
}

bool Board::click(unsigned x, unsigned y) {
  Cell &c = this->cell_at(x, y);

  if (c.has_bomb) {
    return false;
  }

  this->expand(x, y);
  return true;
}

