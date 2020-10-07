
#pragma once

namespace minimilian {

// lagging with an exponential moving average
// a lower alpha value gives a slower lag
template <class T> struct LagExp final {
  T alpha, alphaReciprocal;
  T val;

  LagExp() { init(0.5, 0.0); };

  LagExp(T initAlpha, T initVal) { init(initAlpha, initVal); }

  void init(T initAlpha, T initVal) {
    alpha = initAlpha;
    alphaReciprocal = 1.0 - alpha;
    val = initVal;
  }

  inline void addSample(T newVal) {
    val = (alpha * newVal) + (alphaReciprocal * val);
  }

  inline T value() { return val; }
};

} // namespace minimilian
