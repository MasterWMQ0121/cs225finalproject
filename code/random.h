#pragma once

#include <vector>

using namespace std;
class Random
{
  public:
    inline Random(unsigned long seed);
    inline int nextInt();
    template <class T>
    void shuffle(vector<T>& array);

  private:
    unsigned long shiftRegister;
    inline bool LFSR();
};

#include "random.cpp"