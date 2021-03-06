#pragma once

#include <vector>
#include <memory>

class Cell {
public:
  bool visible = false;
  bool has_bomb = false;
  unsigned adjacent = 0;
  friend std::ostream &operator<<(std::ostream &stream, Cell obj);
}; // class Cell

class Board {
public:
  Board(const unsigned x_size, const unsigned y_size, const unsigned bombs);
  Cell & cell_at(const unsigned x, const unsigned y);
  friend std::ostream &operator<<(std::ostream &stream, Board obj);

  bool click(const unsigned x, const unsigned y);

protected:
  void expand(const unsigned x, const unsigned y);
  void inner_expand(const unsigned x, const unsigned y);
  void populate();
  unsigned calc_adjacent(unsigned x, unsigned y);
  unsigned x_size, y_size, bombs;
  std::vector<std::vector<Cell>> board_cells;
}; // class Board
