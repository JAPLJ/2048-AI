#include "montecarlo.h"

#include <algorithm>
#include "xorshift.h"

using XorShift::Random;

namespace MonteCarlo {

int Playout(Grid g) {
  g.AddRandomTile();
  while (true) {
    int dirs[4] = {0, 1, 2, 3};
    for (int i = 3; i > 0; --i) {
      std::swap(dirs[i], dirs[Random() % (i + 1)]);
    }

    bool moved = false;
    for (int i = 0; i < 4; ++i) {
      if (g.Move(dirs[i]) >= 0) {
        moved = true;
        break;
      }
    }

    if (!moved) {
      break;
    }
    g.AddRandomTile();
  }

  return g.Score();
}

double MonteCarloEval(const Grid& g, int num_trials) {
  int current_score = g.Score();
  double eval = 0.0;

  for (int i = 0; i < num_trials; ++i) {
    eval += static_cast<double>(Playout(g) - current_score) / num_trials;
  }
  return eval;
}

}
