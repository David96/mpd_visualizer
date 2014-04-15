#ifndef FREQVISUALIZER_H
#define FREQVISUALIZER_H
#include "Visualizer.h"
#include <fftw3.h>
#include <math.h>

class FreqVisualizer : public Visualizer {
public:
    explicit FreqVisualizer(int samples);
    void init();
    void draw(int16_t *buf, int count);
    void shutdown();
protected:
    virtual void draw ( unsigned *mags, int count) = 0;
private:
    double *mSignal;
    fftw_complex *mResult;
    int mResults;
    fftw_plan mPlan;
    unsigned *mMags;
};
#endif
