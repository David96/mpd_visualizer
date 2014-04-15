#include "FreqVisualizer.h"

FreqVisualizer::FreqVisualizer(int samples) : Visualizer(samples) {
}

void FreqVisualizer::init() {
    mSignal = static_cast<double *>(fftw_malloc(sizeof(double)*mSamples));
    mResults = mSamples / 2 + 1;
    mResult = static_cast<fftw_complex *>(fftw_malloc(sizeof(fftw_complex)*mResults));
    mPlan = fftw_plan_dft_r2c_1d(mSamples, mSignal, mResult, FFTW_ESTIMATE);
    mMags = new unsigned[mResults];
}

void FreqVisualizer::draw(int16_t *buf, int count) {
    int results = count / 2;
    for (unsigned int i = 0, j = 0; i < count; ++i) {
        if (j < count)
            mSignal[i] = buf[j++];
        else
            mSignal[i] = 0;
    }
    fftw_execute(mPlan);
    for (unsigned int i = 0; i < results; ++i) {
        mMags[i] = sqrt(
                        mResult[i][0]*mResult[i][0]
                      + mResult[i][1]*mResult[i][1]) / sqrt(count);
    }
    draw(mMags, results);
}

void FreqVisualizer::shutdown() {
    delete[] mSignal;
    delete[] mResult;
    delete[] mMags;
    fftw_destroy_plan(mPlan);
}
