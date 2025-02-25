#ifndef SOUNDPROCESSOR_H
#define SOUNDPROCESSOR_H

#include <QString>
#include <fftw3.h>
#include <sndfile.h>
#include <vector>

class SoundProcessor {
public:
    SoundProcessor();
    ~SoundProcessor();
    // Method to perform FFT and detect tempo
    void prepareFFT();
    double detectTempo();
    void extractAudioData(QString &filePath);

private:
    fftw_complex *fftOut;   
    fftw_complex *fftIn;
    fftw_plan fftPlan; 

    std::vector<double> audioBuffer;
    int sampleRate;
    int channels;
    long numFrames;

    // Method to perform FFT on audio data
    void performFFT();
    // Method to estimate tempo from FFT results
    double estimateTempo();
};

#endif // SOUNDPROCESSOR_H
