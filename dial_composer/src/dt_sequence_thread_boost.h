//
//  dt_sequence_thread_boost.h
//  dialt
//
//  Created by mtb on 2014/06/07.
//
//

#pragma once

#include <boost/asio.hpp>
#include "ofxOsc.h"

class ofApp;

class dt_sequence_thread_boost{
	
public:
	
	dt_sequence_thread_boost();
	~dt_sequence_thread_boost();
	void task(const boost::system::error_code& /*e*/, boost::asio::deadline_timer* t);
    void threadFunc();
	void setup();
	void start();
	void stop();
	void change_freq(float freq);
			
	ofApp * app;

    bool bRun;
    bool bStop_requested;
	unsigned int master_step;
	float bpm;
	float sleep_microsec;
	float min_sleep_micro_sec;

	boost::posix_time::ptime starttime, endtime;
	static boost::asio::io_service io;
};
