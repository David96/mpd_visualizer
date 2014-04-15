#include "SoundWave.h"

void SoundWave::draw(int16_t *buf, int count) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.f, 1.f, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBegin(GL_LINE_STRIP);
    const int samples_per_col = count / COL_COUNT;
    double prev_point_pos = 0;
    for (size_t i = 0; i < COL_COUNT; ++i) {
        double point_pos = 0;
        for (int j = 0; j < samples_per_col; ++j)
            point_pos += buf[i*samples_per_col+j];
        point_pos /= samples_per_col;
        point_pos /= std::numeric_limits<int16_t>::max();
        glColor3f((point_pos + 1.f) / 2.f, 0.f, 1.f - ((point_pos + 1.f) / 2.f));
        glVertex3f(i / (float)COL_COUNT, point_pos, 0.f);
        prev_point_pos = point_pos;
    }
    glEnd();
}

