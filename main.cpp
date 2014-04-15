#include <GLFW/glfw3.h>
#include <iostream>
#include <fftw3.h>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <vector>
#include <time.h>

#include "Visualizer.h"
#include "FreqSpectrum.h"
#include "SoundWave.h"

#define SAMPLES 2048
#define COL_COUNT 400

using namespace std;

vector<Visualizer *> mVis;
unsigned int mCurrentVis;

int mStream;
int16_t mBuf[SAMPLES];

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
        mVis[mCurrentVis]->shutdown();
        if (++mCurrentVis >= mVis.size()) mCurrentVis = 0;
        mVis[mCurrentVis]->init();
    } else if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void openStream(char *file) {
    mStream = open(file, O_RDONLY | O_NONBLOCK);
}

int getFreq(int i) {
    return i * 44100 / SAMPLES;
}

bool readData() {
    int samples = read(mStream, mBuf, SAMPLES * sizeof(*mBuf)) / sizeof(*mBuf);
    if (samples != -1) {
        mVis[mCurrentVis]->draw(mBuf, samples);
        return true;
    }
    return false;
}

void closeStream() {
    close(mStream);
}

int main(int argc, char *argv[]) {
    mVis.push_back(new FreqSpectrum(SAMPLES));
    mVis.push_back(new SoundWave(SAMPLES));
    mCurrentVis = 0;
    mVis[mCurrentVis]->init();
    openStream("/tmp/mpd.fifo");
    cout << "i = " << getFreq(1) << "Hz" << endl;
    GLFWwindow *window;
    if (!glfwInit()) return -1;
    const GLFWvidmode *vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    window = glfwCreateWindow(vidmode->width, vidmode->height, "Visualizer", glfwGetPrimaryMonitor(), NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    int width, height;
    clock_t lasttime = clock();
    long diff;
    long minTime = (SAMPLES / 44100.d) * 1e6;
    bool res = true;
    while (!glfwWindowShouldClose(window)) {
        // Skip frames if reading music data failed
        if (res) {
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(0, 0, width, height);
            glClear(GL_COLOR_BUFFER_BIT);
        }
        diff = (clock() - lasttime) / (CLOCKS_PER_SEC / 1e6);
        diff = minTime - diff;
        if (diff > 0) usleep(diff);
        lasttime = clock();
        res = readData();
        if (res) {
            glfwSwapInterval(1);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
    mVis[mCurrentVis]->shutdown();
    closeStream();
    return 0;
}
