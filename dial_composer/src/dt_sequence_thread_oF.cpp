//
//  dt_sequence_thread_oF.cpp
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//

#include "dt_sequence_thread_oF.h"
#include "ofApp.h"
#include "dt_circle_container.h"


dt_sequence_thread_oF::dt_sequence_thread_oF()
{}

void dt_sequence_thread_oF::setup(){
    bStop_requested = false;
    master_step = 0;
    min_sleep_micro_sec = 1000;
    app = ofApp::app;
}

void dt_sequence_thread_oF::threadedFunction(){
	while( isThreadRunning() ){
        if( dt_config::DT_PLAY_GEN_RHYTHM ){
            app->all_containers.step();
            app->osc_recorder.step_fragment();
        }
        
        if( dt_config::DT_PLAY_BUFFERED_RHYTHM ){
            app->osc_recorder.play_fragment();
        }
        
        master_step++;
		sleep( sleep_microsec*1000.0f );
	}
}

void dt_sequence_thread_oF::start(){

	bool blocking = false;
	bool verbose = false;
	startThread( blocking, verbose );
}

void dt_sequence_thread_oF::stop(){
	stopThread();
}

