#ifndef __2048_AI_GRID_H__
#define __2048_AI_GRID_H__

class Grid {
 public:
  static const char* DIR_NAMES[4];
  static const char* DIR_ARROWS;
  static const int DR[4], DC[4];

  enum Directions {
    UP, RIGHT, DOWN, LEFT
  };

  Grid();

  int Tile(int r, int c) const;
  int Score() const;

  bool AddRandomTile();
  void InitGame();

  // returns score gained by the move, or -1 if the move is invalid
  int Move(int dir); 

  void Dump() const;

 private:
  int cells[4][4];
  int score;

  enum ColorIntensity {
    NORMAL, BRIGHT
  };
  enum Colors {
    BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE,
  };

  void Clear();
  bool MoveRow(int row, int dir);
  bool MoveCol(int col, int dir);
};

#endif  // __2048_AI_GRID_H__
