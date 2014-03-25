#ifndef __2048_AI_MONTECARLO_H__
#define __2048_AI_MONTECARLO_H__

#include "grid.h"

namespace MonteCarlo {

double MonteCarloEval(const Grid& grid, int num_trials);

}

#endif  // __2048_AI_MONTECARLO_H__
