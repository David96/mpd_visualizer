#ifndef FREQSPECTRUM_H_
#define FREQSPECTRUM_H_
#include <GLFW/glfw3.h>
#include "FreqVisualizer.h"

#define COL_COUNT 400

class FreqSpectrum : public FreqVisualizer {
public:
    FreqSpectrum(int samples) : FreqVisualizer(samples) {}
    void init();
protected:
    void draw ( unsigned *mags, int count );
private:
    void drawRect(float x, float y, float w, float h, float r, float g, float b);

    float mHeights[COL_COUNT];
    unsigned mMaxMag;
};

#endif
