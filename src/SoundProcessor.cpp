#include "../include/SoundProcessor.h"

#include <QString>
#include <fftw3.h>
#include <sndfile.h>
#include <vector>
#include <iostream>

SoundProcessor::SoundProcessor() : fftIn(nullptr), fftOut(nullptr), fftPlan(nullptr), sampleRate(0), channels(0), numFrames(0) {}


SoundProcessor::~SoundProcessor() {
    if (fftPlan) fftw_destroy_plan(fftPlan);
    if (fftOut) fftw_free(fftOut);
}

void SoundProcessor::extractAudioData(QString &filePath) {
    SF_INFO sfInfo;
    SNDFILE* inFile = sf_open(filePath.toStdString().c_str(), SFM_READ, &sfInfo);

    if (!inFile) {
        std::cerr << "Error opening file " << filePath.toStdString() << std::endl;
        return;
    }

    sampleRate = sfInfo.samplerate;
    channels = sfInfo.channels;
    numFrames = sfInfo.frames;

    std::cout << "File info: " << std::endl;
    std::cout << "Sample rate: " << sampleRate << std::endl;
    std::cout << "Channels: " << channels << std::endl;
    std::cout << "Frames: " << numFrames << std::endl;

    // Read audio samples into a buffer
    audioBuffer.resize(numFrames * channels);
    sf_read_double(inFile, audioBuffer.data(), numFrames * channels);

    std::cout << "Loaded " << numFrames << " frames of audio." << std::endl;

    // Close the file after reading
    sf_close(inFile);
    prepareFFT();
}

void SoundProcessor::prepareFFT() {
  fftIn = (fftw_complex*) audioBuffer.data();
  fftOut = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * numFrames);
  fftPlan = fftw_plan_dft_1d(numFrames, fftIn, fftOut, FFTW_FORWARD, FFTW_ESTIMATE);
}

void SoundProcessor::performFFT() {
    fftw_execute(fftPlan);
}

double SoundProcessor::estimateTempo() {
    // Find the dominant frequency in the FFT output
    int peakIndex = 0;
    double maxMagnitude = 0.0;

    // Define valid tempo range (30 BPM to 240 BPM)
    // double minTempoHz = 30.0 / 60.0;  // 0.5 Hz
    // double maxTempoHz = 240.0 / 60.0; // 4 Hz

    for (int i = 1; i < numFrames / 2; ++i) {
        double freq = (i * sampleRate) / (double)numFrames;
        if (freq < 30 || freq > 16000) continue;

        double magnitude = std::sqrt(fftOut[i][0] * fftOut[i][0] + fftOut[i][1] * fftOut[i][1]);
        if (magnitude > maxMagnitude) {
            maxMagnitude = magnitude;
            peakIndex = i;
        }
    }

    // Calculate the frequency from the peak index
    double dominantFrequency = (peakIndex * sampleRate) / (double)numFrames;
    double tempo = dominantFrequency * 60; // in hz

    return tempo;
}

// Main function to detect tempo
double SoundProcessor::detectTempo() {
    performFFT();
    return estimateTempo();
}