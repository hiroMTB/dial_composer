//
//  dt_sequence_thread_audio.h
//  dialt_osx
//
//  Created by mtb on 2014/06/13.
//
//

#pragma once

#include "ofMain.h"

class ofApp;

class dt_sequence_thread_audio{ // : public ofBaseSoundOutput{
	
public:
	dt_sequence_thread_audio();
	void audioRequested( float * output, int bufferSize, int nChannels );
	void change_bpm( int bpm );
	void stop(){};

	ofApp * app;
	int sampling_rate;
	int buffer_size;
	int wait_tick;
	int sleep_millisec;
	int sleep_microsec;
	int bpm;
	unsigned int master_step;
	unsigned int sleep_tick;
	float min_sleep_micro_sec;
	float random_amount;
};