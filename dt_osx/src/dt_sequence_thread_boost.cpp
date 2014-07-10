//
//  dt_sequence_thread_boost.cpp
//  dialt
//
//  Created by mtb on 2014/06/07.
//
//

#include "dt_sequence_thread_boost.h"

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include "ofMain.h"
#include "ofApp.h"
#include "dt_circle_container.h"

using namespace boost;
using namespace std;

boost::asio::io_service dt_sequence_thread_boost::io;

dt_sequence_thread_boost::dt_sequence_thread_boost()
:bRun(false), bStop_requested(false),bHold(false), sleep_tick(1),sleep_microsec(10000),sleep_millisec(10),master_delay(0)

{
	cout << "setting up Sequence Thread Boost" << endl;
	master_tick = 0;
	master_step = 0;
	
	random_amount = 50000;
	min_sleep_micro_sec = 1000;
	real_sleep_micro_sec = 100000;

	phase = 0;
	change_freq(0);
	
	master_clock_message.setAddress("/master_clock");
	master_clock_message.addIntArg(1);
}

void dt_sequence_thread_boost::threadFunc(){
	boost::asio::deadline_timer t(io, boost::posix_time::microseconds(sleep_microsec));
	t.async_wait(boost::bind(&dt_sequence_thread_boost::task, this, boost::asio::placeholders::error(), &t));

	if(!bRun && !bStop_requested){
		bRun = true;
		io.run();
	}
}


void dt_sequence_thread_boost::task(const boost::system::error_code& /*e*/, boost::asio::deadline_timer *t){
	app = ofApp::getInstance();
	
		ofApp * app = ofApp::getInstance();
		app->all_containers.step();

//		//if(master_step%4 == master_delay)app->osc_sender.send_message(master_clock_message);

		master_step++;
	if(!bHold){
		if(freq!=0){
				phase+=phase_adder;
				if(phase>=TWO_PI){
					phase-=TWO_PI;
				}
				real_sleep_micro_sec = (float)random_amount * (float)(sinf(phase) + 1.0);
				real_sleep_micro_sec += min_sleep_micro_sec+sleep_microsec;
		}else{
			real_sleep_micro_sec = sleep_microsec;
		}
	}
	
	if(real_sleep_micro_sec<min_sleep_micro_sec){
		real_sleep_micro_sec = min_sleep_micro_sec;
	}
	t->expires_at(t->expires_at() + boost::posix_time::microseconds( real_sleep_micro_sec ));
	t->async_wait(boost::bind(&dt_sequence_thread_boost::task, this, boost::asio::placeholders::error(), t));

}

	//
	//	strange attractor
	//
	// float a, b, c, d, x ,y;
	//
	// float newx = sinf(y*b) + c*sinf(x*b);
	// float newy = sinf(x*a) + d*sinf(y*a);
	// x = newx;
	// y = newy;
	//

void dt_sequence_thread_boost::start(){
	boost::thread thread(&dt_sequence_thread_boost::threadFunc, this);
}

void dt_sequence_thread_boost::stop(){
	io.stop();
	bRun = false;
	bStop_requested = false;
}

dt_sequence_thread_boost::~dt_sequence_thread_boost(){
	stop();
}


void dt_sequence_thread_boost::change_bpm(int _bpm){
	
	bpm = _bpm;
	float beat_period_ms = 60.0*1000.0 / (float) bpm;							// 500		ms
	float sub_beat_period_ms = beat_period_ms / (float)DT_BEAT_RESOLUTION;		// 15.625	ms
	float thread_sleep_time_ms = sub_beat_period_ms / (float)sleep_tick;		// 3.906	ms
	float thread_sleep_time_microsec = thread_sleep_time_ms * 1000;

	if(thread_sleep_time_microsec >= min_sleep_micro_sec){
		sleep_microsec = thread_sleep_time_microsec;
	}else{
		sleep_microsec = min_sleep_micro_sec;
	}

	sleep_millisec = sleep_microsec/1000.0;
}


void dt_sequence_thread_boost::change_freq(float f){
	freq = f;
	if(freq >0){
		float how_many_rotation_per_1_tick = freq / 200.0;
		phase_adder = TWO_PI * how_many_rotation_per_1_tick;
	}else{
		phase_adder = 0;
	}
}

void dt_sequence_thread_boost::change_sleep_time_microsec(int usec){
	if( usec >= min_sleep_micro_sec ){
		sleep_microsec = usec;
		sleep_millisec = sleep_microsec/1000;
	}
}
