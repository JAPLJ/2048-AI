#include "xorshift.h"

namespace XorShift {

static unsigned x = 123456789, y = 362436069, z = 521288629, w = 88675123;

void SetSeed(unsigned seed) {
  w = seed;
}

unsigned Random() {
  unsigned t = x ^ (x << 11);
  x = y; y = z; z = w;
  return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

}
