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

int dt_sequence_thread_oF::sleep_millisec = 123;
int dt_sequence_thread_oF::sleep_microsec = sleep_millisec*1000;

unsigned int dt_sequence_thread_oF::master_tick = -123456;
unsigned int dt_sequence_thread_oF::master_step = -123456;

unsigned int dt_sequence_thread_oF::sleep_tick = 1;


dt_sequence_thread_oF::dt_sequence_thread_oF()
:stopRequested(false){
	app = ofApp::getInstance();
	master_tick = 0;
	master_step = 0;
}


void dt_sequence_thread_oF::threadedFunction(){
	while(isThreadRunning()){
		master_tick++;
		if(master_tick == UINT_MAX) master_tick = 0;

		if(master_tick % sleep_tick == 0){
			ofApp::getInstance()->all_containers.step();
			master_step++;
		}

		sleep(sleep_millisec);
	}
}

void dt_sequence_thread_oF::start(){

	bool blocking = false;
	bool verbose = false;
	startThread(blocking, verbose);
}

void dt_sequence_thread_oF::stop(){
	stopThread();
}
