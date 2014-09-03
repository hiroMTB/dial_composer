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
:
bRun( false ),
bStop_requested( false ),
sleep_microsec( 123456 ),
master_delay( 0 )
{
	cout << "setting up Sequence Thread Boost" << endl;
	master_step = 0;
	
	min_sleep_micro_sec = 1000;
	master_clock_message.setAddress( "/master_clock" );
	master_clock_message.addIntArg( 1 );
}

void dt_sequence_thread_boost::setup(){
	app = ofApp::getInstance();
}

void dt_sequence_thread_boost::threadFunc(){
	boost::asio::deadline_timer t( io, boost::posix_time::microseconds(sleep_microsec) );
	t.async_wait(boost::bind( &dt_sequence_thread_boost::task, this, boost::asio::placeholders::error(), &t) );

	if( !bRun && !bStop_requested ){
		bRun = true;
		io.run();
	}
}

void dt_sequence_thread_boost::task( const boost::system::error_code& /*e*/, boost::asio::deadline_timer *t ){

	if( dt_config::DT_PLAY_GEN_RHYTHM ){
		app->all_containers.step();
		app->osc_recorder.step_fragment();
	}
	
	if( dt_config::DT_PLAY_BUFFERED_RHYTHM ){
		app->osc_recorder.play_fragment();
	}

	// mster clock osc out
	if( dt_config::DT_MASTER_CLOCK_OUT_RESOLUTION > 0 ){
		if( master_step%dt_config::DT_MASTER_CLOCK_OUT_RESOLUTION == 0 ){
			app->osc_sender.send_message( master_clock_message );
		}
	}
		
	master_step++;
	
	t->expires_at( t->expires_at() + boost::posix_time::microseconds(sleep_microsec) );
	t->async_wait( boost::bind(&dt_sequence_thread_boost::task, this, boost::asio::placeholders::error(), t) );

}

void dt_sequence_thread_boost::start(){
	boost::thread thread( &dt_sequence_thread_boost::threadFunc, this );
}

void dt_sequence_thread_boost::stop(){
	io.stop();
	bRun = false;
	bStop_requested = false;
}

dt_sequence_thread_boost::~dt_sequence_thread_boost(){
	stop();
}

void dt_sequence_thread_boost::change_bpm( int _bpm ){
	
	bpm = _bpm;
	float beat_period_ms = 60.0*1000.0 / (float) bpm;
	sleep_microsec = beat_period_ms * 1000;

	if( sleep_microsec < min_sleep_micro_sec ){
		sleep_microsec = min_sleep_micro_sec;
	}

	app->config.synch_param();
}

void dt_sequence_thread_boost::change_sleep_time_microsec( int usec ){
	if( usec >= min_sleep_micro_sec ){
		sleep_microsec = usec;
		app->config.synch_param();
	}
}