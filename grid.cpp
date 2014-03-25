#include "grid.h"

#include <algorithm>
#include <cstdio>
#include "xorshift.h"

using XorShift::Random;

const char* Grid::DIR_NAMES[4] = {"up", "right", "down", "left"};
const char* Grid::DIR_ARROWS = "^>v<";
const int Grid::DR[4] = {-1, 0, 1, 0};
const int Grid::DC[4] = {0, 1, 0, -1};

Grid::Grid() {
  Clear();
}

int Grid::Tile(int r, int c) const {
  return cells[r][c];
}

int Grid::Score() const {
  return score;
}

bool Grid::AddRandomTile() {
  int empty_r[16], empty_c[16], num_empty = 0;
  for (int r = 0; r < 4; ++r) {
    for (int c = 0; c < 4; ++c) {
      if (cells[r][c] == 0) {
        empty_r[num_empty] = r;
        empty_c[num_empty] = c;
        ++num_empty;
      }
    }
  }
  if (num_empty == 0) {
    return false;
  }

  int pos = Random() % num_empty;
  int num = ((Random() % 10 == 0) ? 2 : 1);
  cells[empty_r[pos]][empty_c[pos]] = num;
  return true;
}

void Grid::InitGame() {
  Clear();
  AddRandomTile();
  AddRandomTile();
}

int Grid::Move(int dir) {
  bool moved = false;
  int score_prev = score;

  if (dir == UP || dir == DOWN) {
    for (int c = 0; c < 4; ++c) {
      moved |= MoveCol(c, (dir == UP ? -1 : 1));
    }
  } else {
    for (int r = 0; r < 4; ++r) {
      moved |= MoveRow(r, (dir == LEFT ? -1 : 1));
    }
  }

  return (moved ? score - score_prev : -1);
}

static void textcolor(int attr, int fg, int bg) {
  printf("%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
}
static void clear() {
  printf("%c[1J%c[1;1H", 0x1B, 0x1B);
}

void Grid::Dump() const {
  const int COLORS[][3] = {
    {NORMAL, WHITE, BLACK},   // nothing
    {NORMAL, WHITE, BLACK},   // 2
    {BRIGHT, WHITE, BLACK},   // 4
    {NORMAL, MAGENTA, BLACK}, // 8
    {NORMAL, YELLOW, BLACK},  // 16
    {NORMAL, RED, BLACK},     // 32
    {BRIGHT, RED, BLACK},     // 64
    {BRIGHT, YELLOW, BLACK},  // 128
    {BRIGHT, GREEN, BLACK},   // 256
    {BRIGHT, CYAN, BLACK},    // 512
    {NORMAL, BLACK, YELLOW},  // 1024
    {NORMAL, RED, YELLOW},    // 2048
    {NORMAL, BLACK, RED},     // 4096
    {BRIGHT, YELLOW, RED},    // 8192
    {BRIGHT, YELLOW, RED},    // 16384
    {BRIGHT, YELLOW, RED},    // 32768
    {BRIGHT, YELLOW, RED},    // 65536
  };

  clear();
  printf("score = %d\n", score);
  for (int r = 0; r < 4; ++r) {
    for (int c = 0; c < 4; ++c) {
      int num = cells[r][c];
      textcolor(COLORS[num][0], COLORS[num][1], COLORS[num][2]);
      if (num == 0) {
        printf("    .");
      } else {
        printf("%5d", 1 << num);
      }
    }
    puts("");
  }
  textcolor(NORMAL, WHITE, BLACK);
}

void Grid::Clear() {
  for (int r = 0; r < 4; ++r) {
    for (int c = 0; c < 4; ++c) {
      cells[r][c] = 0;
    }
  }
  score = 0;
}

bool Grid::MoveRow(int r, int dir) {
  int fix[4] = {0, 0, 0, 0};
  bool moved = false;

  for (int c = (dir > 0 ? 3 : 0); 0 <= c && c < 4; c -= dir) {
    if (cells[r][c] == 0) {
      continue;
    }
    int cc = c;
    while (true) {
      int next_c = cc + dir;
      if (next_c < 0 || next_c >= 4 || fix[next_c]) {
        break;
      }
      if (cells[r][next_c] == 0) {
        std::swap(cells[r][cc], cells[r][next_c]);
        cc = next_c;
        moved = true;
        continue;
      } else if (cells[r][cc] == cells[r][next_c]) {
        ++cells[r][next_c];
        score += 1 << cells[r][next_c];
        cells[r][cc] = 0;
        fix[next_c] = 1;
        moved = true;
        break;
      } else {
        break;
      }
    }
  }

  return moved;
}

bool Grid::MoveCol(int c, int dir) {
  int fix[4] = {0, 0, 0, 0};
  bool moved = false;

  for (int r = (dir > 0 ? 3 : 0); 0 <= r && r < 4; r -= dir) {
    if (cells[r][c] == 0) {
      continue;
    }
    int rr = r;
    while (true) {
      int next_r = rr + dir;
      if (next_r < 0 || next_r >= 4 || fix[next_r]) {
        break;
      }
      if (cells[next_r][c] == 0) {
        std::swap(cells[rr][c], cells[next_r][c]);
        rr = next_r;
        moved = true;
        continue;
      } else if (cells[rr][c] == cells[next_r][c]) {
        ++cells[next_r][c];
        score += 1 << cells[next_r][c];
        cells[rr][c] = 0;
        fix[next_r] = 1;
        moved = true;
        break;
      } else {
        break;
      }
    }
  }

  return moved;
}
