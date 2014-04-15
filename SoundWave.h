#ifndef SOUNDWAVE_H
#define SOUNDWAVE_H
#include <GLFW/glfw3.h>
#include <limits>

#include "Visualizer.h"

#define COL_COUNT 512

class SoundWave : public Visualizer {
public:
    SoundWave(int samples) : Visualizer(samples) {}
    void draw (int16_t *buf, int count);
};

#endif // SOUNDWAVE_H
