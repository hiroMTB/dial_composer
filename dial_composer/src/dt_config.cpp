//
//  dt_config.cpp
//  dt_osx
//
//  Created by mtb on 2014/07/12.
//
//

#include "dt_config.h"
#include "ofApp.h"
#include "dt_circle_container.h"
#include "dt_circle_all_containers.h"

// Generative Rhythm
bool dt_config::DT_PLAY_GEN_RHYTHM = true;
int dt_config::DT_GEN_RHYTHM_RATE = 100;
int dt_config::DT_RHYTHM_SHAPE_SLOT_MIN = 3;
int dt_config::DT_RHYTHM_SHAPE_SLOT_MAX = 24;
int dt_config::DT_QUANTIZE_RESOLUTION = 16;
int dt_config::DT_BEAT_RESOLUTION = 24;
int dt_config::DT_BEAT_SPEED_MAX = 32;

// OSC out
bool dt_config::DT_OSC_OUT_ENABLE = true;
int dt_config::DT_OSC_OUT_CH_MAX = 32;
std::string dt_config::DT_OSC_OUT_TOP_ADDRESS = "/dial_out";
std::string dt_config::DT_OSC_OUT_IP_ADDRESS = "localhost";
int dt_config::DT_OSC_OUT_PORT = 12345;
bool dt_config::DT_OSC_OUT_PACK_RHYTHM_PARAM = true;

// OSC in
bool dt_config::DT_OSC_IN_ENABLE = true;
std::string dt_config::DT_OSC_IN_TOP_ADDRESS = "/dial_in";
int dt_config::DT_OSC_IN_PORT =	8888;

// MIDI out
bool dt_config::DT_MIDI_OUT_ENABLE = true;
bool dt_config::DT_MIDI_OUT_PACK_RHYTHM_PARAM = true;
string dt_config::DT_MIDI_OUT_PORT_NAME = "dial_midi_out";

// Buffered Rhythm
bool dt_config::DT_PLAY_BUFFERED_RHYTHM = false;
int dt_config::DT_BUFFERED_RHYTHM_RATE = 0;
int dt_config::DT_BUFFERED_RHYTHM_INDICATOR = 0;
int dt_config::DT_BUFFERED_RHYTHM_LOOP_START = 0;
int dt_config::DT_BUFFERED_RHYTHM_LOOP_END = 63;
bool dt_config::DT_SHOW_BUFFERED_RHYTHM = true;

// draw mode
bool dt_config::DT_SHOW_LINER_DRAWER = false;
float dt_config::DT_SIZE_BASE = 100.0;

dt_config::dt_config(){}

void dt_config::setup(){
	app = ofApp::app;
}

void dt_config::update(){
	if( !dt_config::DT_OSC_IN_ENABLE )
        return;
    
	while( osc_r.hasWaitingMessages() ){
		ofxOscMessage m;
		osc_r.getNextMessage( &m );
		
		string address = m.getAddress();
		string pre = DT_OSC_IN_TOP_ADDRESS;
		
		// OSC
		if( address == pre + "osc_out_ip_address" ){
			
			string s = m.getArgAsString( 0 );
			DT_OSC_OUT_IP_ADDRESS = s;
			app->osc_sender.setTargetAddress( s );
			
		}else if( address == pre + "osc_out_port" ){
			
			int i = m.getArgAsInt32( 0 );
			i = max( 1, i );
			DT_OSC_OUT_PORT = i;
			app->osc_sender.setTargetPort( i );
			
		}else if( address == pre + "osc_in_port" ){
			
			int i = m.getArgAsInt32( 0 );
			i = max( 1, i );
			DT_OSC_IN_PORT = i;
			osc_r.setup( i );
			
		// Generative
		}else if( address == pre + "play_gen_rhythm" ){
			
			int i = m.getArgAsInt32( 0 );
			DT_PLAY_GEN_RHYTHM = i;
			
		}else if( address == pre + "gen_rhythm_rate" ){
			
			int i = m.getArgAsInt32( 0 );
			i = max( 0, i );
			DT_GEN_RHYTHM_RATE = i;

		}else if( address == pre + "rhythm_shape_slot_min" ){
			
			int i = m.getArgAsInt32( 0 );
			i = max( 3, i );
			DT_RHYTHM_SHAPE_SLOT_MIN = i;
			
		// Buffered
		}else if( address == pre + "play_buffered_rhythm" ){
			
			int i = m.getArgAsInt32( 0 );
			DT_PLAY_BUFFERED_RHYTHM = i;
		
		}else if( address == pre + "buffered_rhythm_rate" ){
			
			int i = m.getArgAsInt32( 0 );
			i = max( 0, i );
			DT_BUFFERED_RHYTHM_RATE = i;
			
		}else if( address == pre + "buffered_rhythm_indicator" ){
			
			int i = m.getArgAsInt32( 0 );
			i = min( i, dt_osc_recorder::fragment_ring_max-1 );
			i = max( 0, i );
			DT_BUFFERED_RHYTHM_INDICATOR = i;
			
		}else if( address == pre + "buffered_rhythm_loop_start" ){
			
			int i = m.getArgAsInt32( 0 );
			i = max( 1, i );
			DT_BUFFERED_RHYTHM_LOOP_START = i;

		}else if( address == pre + "buffered_rhythm_loop_end" ){
			
			int i = m.getArgAsInt32( 0 );
			i = max( 1, i );
			DT_BUFFERED_RHYTHM_LOOP_END = i;
			
		}else if( address == pre + "show_buffered_rhythm" ){
			
			int i = m.getArgAsInt32( 0 );
			DT_SHOW_BUFFERED_RHYTHM = i;

		}else{
			cout << "Receive strange OSC address : " << address << endl;
		}
	}
}
