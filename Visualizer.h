#ifndef VISUALIZER_H_
#define VISUALIZER_H_
#include <fcntl.h>

class Visualizer {
public:
    explicit Visualizer(int samples) : mSamples(samples) {}
    virtual void init() {}
    virtual void draw(int16_t *buf, int count) = 0;
    virtual void shutdown() {}
protected:
    unsigned int mSamples;
};

#endif
