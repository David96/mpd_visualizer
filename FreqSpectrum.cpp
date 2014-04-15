#include "FreqSpectrum.h"
void FreqSpectrum::drawRect(float x, float y, float w, float h, float r, float g, float b) {
        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(r, g, b);
        glVertex3f(x, y, 0.f);
        glColor3f(r, g, b);
        glVertex3f(x + w, y, 0.f);
        glColor3f(r, g, b);
        glVertex3f(x, y + h, 0.f);
        glColor3f(r, g, b);
        glVertex3f(x + w, y + h, 0.f);
        glEnd();
}

void FreqSpectrum::init() {
    FreqVisualizer::init();
    mMaxMag = 0;
}

void FreqSpectrum::draw(unsigned *mags, int count) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.f, 1.f, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    unsigned int freqs_per_col = count / COL_COUNT;
    for (unsigned int i = 0; i < COL_COUNT; ++i) {
        mHeights[i] = 0;
        for (unsigned int j = 0; j < freqs_per_col; ++j) {
            mHeights[i] += mags[(i * freqs_per_col) + j ];
        }
        mHeights[i] /= freqs_per_col;
        if (mHeights[i] > mMaxMag) mMaxMag = mHeights[i];
        mHeights[i] /= mMaxMag;
        drawRect((float)i * (1.f / (float)COL_COUNT),
                -mHeights[i] , (1.f / (float)COL_COUNT), mHeights[i] * 2.f,
                mHeights[i], i / (float)COL_COUNT, 0.5f);
    }
}
