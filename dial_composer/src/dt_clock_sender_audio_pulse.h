#pragma once

#include "ofMain.h"

class ofApp;

class dt_clock_sender_audio_pulse : public ofBaseSoundOutput{
    
public:
    dt_clock_sender_audio_pulse();
    void audioRequested( float * output, int bufferSize, int nChannels );
    void change_bpm( int bpm );
    void resetBeat();
    void stop(){};
    void beat();
    
    ofApp * app;
    int sampling_rate;
    int buffer_size;

    float samplePerBeat;
    int pulsePerBeat;
    float pulse_width;
    float pulse_pos;
};