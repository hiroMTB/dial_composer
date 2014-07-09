//
//  dt_sequence_thread_audio.cpp
//  dialt_osx
//
//  Created by mtb on 2014/06/13.
//
//

#include "def.h"
#include "dt_sequence_thread_audio.h"
#include "dt_sequencer.h"
#include "ofApp.h"
#include "dt_circle_container.h"

dt_sequence_thread_audio::dt_sequence_thread_audio()
:sampling_rate(DT_AUDIO_SAMPLING_RATE),
buffer_size(DT_AUDIO_BUFFER_SIZE),
master_step(0),
sleep_tick(1)

{
	app = ofApp::getInstance();
	
	// should be 11609.977324... = about 11ms
	min_sleep_micro_sec = (1000*1000 / (float)sampling_rate) * buffer_size;
}



void dt_sequence_thread_audio::change_bpm(int _bpm){
	
	bpm = _bpm;
	float beat_period_ms = 60.0*1000.0 / (float) bpm;						// 500		ms
	sleep_millisec = beat_period_ms / (float)DT_BEAT_RESOLUTION;		// 31.25	ms
	sleep_microsec = sleep_millisec * 1000.0;	// 1562.5 us
	
	wait_tick = (int)(sleep_microsec / min_sleep_micro_sec);
	wait_tick = max(wait_tick, 1);
}

void dt_sequence_thread_audio::audioRequested(float * output, int bufferSize, int nChannels ){
		
	master_step++;
	
	if(master_step%wait_tick==0)
		ofApp::getInstance()->all_containers.step();
}