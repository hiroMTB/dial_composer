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
	
	ofApp * app;
	
	dt_sequence_thread_boost();
	~dt_sequence_thread_boost();
	
	static boost::asio::io_service io;
	
    bool bRun;
    bool bStop_requested;
	bool bHold;

	float bpm;
    float sleep_millisec;
	float sleep_microsec;

	unsigned int master_tick;
	unsigned int master_step;
	unsigned int sleep_tick;
	float real_sleep_micro_sec;
	float min_sleep_micro_sec;
	float random_amount;
	
	float freq;
	float phase_adder;
	float phase;

	ofxOscMessage master_clock_message;
	
	boost::posix_time::ptime starttime, endtime;

	void task(const boost::system::error_code& /*e*/, boost::asio::deadline_timer* t);
    void threadFunc();
	
	void start();
	void stop();
	
	void change_bpm(int bpm);
	void change_freq(float freq);
	void change_sleep_time_microsec(int usec);

	int master_delay;

};
