//
//  dt_sequence_thread_base.h
//  dial_composer
//
//  Created by MatobaHiroshi on 4/8/17.
//
//

#pragma once

#include "dt_config.h"

class ofApp;

class dt_sequence_thread_base{

public:
    virtual void setup() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    void change_bpm( int _bpm ){
        
        bpm = _bpm;
        float beat_period_ms = 60.0*1000.0 / (float) bpm / dt_config::DT_BEAT_RESOLUTION;
        sleep_microsec = beat_period_ms * 1000;
        
        if( sleep_microsec < min_sleep_micro_sec ){
            sleep_microsec = min_sleep_micro_sec;
        }
    }
    
    ofApp * app;
    bool bRun;
    bool bStop_requested;
    unsigned int master_step;
    float bpm;    
    float sleep_microsec;
    float min_sleep_micro_sec;
    
};
