//
//  dt_sequence_thread_oF.h
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//

#pragma once

#include "ofMain.h"

class ofApp;

class dt_sequence_thread_oF : public ofThread{

public:
	
	dt_sequence_thread_oF();
	virtual void threadedFunction();
	void start();
	void stop();
	
	ofApp * app;
	
	static int sleep_microsec;
	static int sleep_millisec;
	static unsigned int master_tick;
	static unsigned int master_step;
	static unsigned int sleep_tick;
	bool stopRequested;
};