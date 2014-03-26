#include "grid.h"
#include "montecarlo.h"
#include "xorshift.h"

#include <cstdio>

int main(int argc, char** argv) {
  unsigned seed = 810893;
  if (argc > 1) {
    seed = 0;
    for (int i = 0; argv[1][i]; ++i) {
      seed = seed * 256 + argv[1][i];
    }
  }
  XorShift::SetSeed(seed);

  Grid grid;
  grid.InitGame();

  while (true) {
    int next_move = -1;
    double best = -1e9;

    for (int d = 0; d < 4; ++d) {
      Grid temp = grid;
      int step_score = temp.Move(d);
      if (step_score < 0) {
        continue;
      }

      double eval = step_score + MonteCarlo::MonteCarloEval(temp, 2000);
      if (best < eval) {
        best = eval;
        next_move = d;
      }
    }

    if (next_move == -1) {
      break;
    }
    grid.Move(next_move);
    grid.AddRandomTile();
    grid.Dump();
  }

  return 0;
}
