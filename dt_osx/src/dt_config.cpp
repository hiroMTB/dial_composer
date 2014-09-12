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

// status
int dt_config::DT_MASTER_CLOCK_OUT_RESOLUTION = 0;

// Generative Rhythm
bool dt_config::DT_PLAY_GEN_RHYTHM = true;
int dt_config::DT_GEN_RHYTHM_RATE = 100;
int dt_config::DT_RHYTHM_SHAPE_SLOT_MIN =	  3;
int dt_config::DT_RHYTHM_SHAPE_SLOT_MAX =	 24;
int dt_config::DT_QUANTIZE_RESOLUTION =		 16;
int dt_config::DT_BEAT_RESOLUTION =			 16;
int dt_config::DT_BEAT_SPEED_MAX =			 32;
int dt_config::DT_CONNECTION_NUM_INPUT_MAX = 16;
int dt_config::DT_CONNECTION_NUM_OUTPUT_MAX = 3;

// OSC out
int dt_config::DT_OSC_OUT_CH_MAX =			32;
int dt_config::DT_OSC_OUT_CH_MIN =			 1;
std::string dt_config::DT_OSC_OUT_ADDRESS_PREFIX = "/dt_out/";
std::string dt_config::DT_OSC_OUT_ADDRESS = "localhost";
int dt_config::DT_OSC_OUT_PORT =		   9999;

// OSC in
std::string dt_config::DT_OSC_IN_ADDRESS_PREFIX = "/dt_in/";
int dt_config::DT_OSC_IN_PORT =			   8888;

// Buffered Rhythm
bool dt_config::DT_PLAY_BUFFERED_RHYTHM = false;
int dt_config::DT_BUFFERED_RHYTHM_RATE = 0;
int dt_config::DT_BUFFERED_RHYTHM_INDICATOR = 0;
int dt_config::DT_BUFFERED_RHYTHM_LOOP_START = 0;
int dt_config::DT_BUFFERED_RHYTHM_LOOP_END = 63;
bool dt_config::DT_SHOW_BUFFERED_RHYTHM = true;

// draw mode
bool dt_config::DT_SHOW_LINER_DRAWER = false;
bool dt_config::DT_SHOW_PARAM = false;

float dt_config::DT_SIZE_BASE = 100.0;

dt_config::dt_config(){}

void dt_config::setup(){
	width = 250;
	height = 20;
	int color = 110;
	
	{
		osc.setDefaultWidth( width );
		osc.setDefaultHeight( height );
		osc.setDefaultTextColor( color );
		osc.setup();
		osc.setName( "osc" );
		
		osc.add( osc_out_ch_max.setup("/osc_out_ch_max", ofToString(DT_OSC_OUT_CH_MAX)) );
		osc.add( osc_out_ch_min.setup("/osc_out_ch_min", ofToString(DT_OSC_OUT_CH_MIN)) );
		
		osc.add( osc_out_address.setup("/osc_out_address", ofToString(DT_OSC_OUT_ADDRESS)) );
		osc.add( osc_out_port.setup("/osc_out_port", ofToString(DT_OSC_OUT_PORT)));

		osc.add( osc_in_port.setup("/osc_in_port", ofToString(DT_OSC_IN_PORT)));
	}
	
	{
		generative_rhythm.setDefaultWidth( width );
		generative_rhythm.setDefaultHeight( height );
		generative_rhythm.setDefaultTextColor( color );
		generative_rhythm.setup();
		generative_rhythm.setName( "generative_rhythm" );
		
		generative_rhythm.add( play_gen_rhythm.setup("/play_gen_rhythm", toOnOff(DT_PLAY_GEN_RHYTHM)) );
		generative_rhythm.add( gen_rhythm_rate.setup("/gen_rhythm_rate", ofToString(DT_GEN_RHYTHM_RATE)+"%") );
		generative_rhythm.add( rhythm_shape_slot_min.setup("/rhythm_shape_slot_min", ofToString(DT_RHYTHM_SHAPE_SLOT_MIN)) );
		generative_rhythm.add( rhythm_shape_slot_max.setup("/rhythm_shape_slot_max", ofToString(DT_RHYTHM_SHAPE_SLOT_MAX)) );
		generative_rhythm.add( beat_resolution.setup("/beat_resolution", ofToString(DT_BEAT_RESOLUTION)) );
		generative_rhythm.add( beat_speed_max.setup("/beat_speed_max", ofToString(DT_BEAT_SPEED_MAX)) );
		generative_rhythm.add( connection_num_input_max.setup("/connection_num_input_max", ofToString(DT_CONNECTION_NUM_INPUT_MAX)) );
		generative_rhythm.add( connection_num_output_max.setup("/connection_num_output_max", ofToString(DT_CONNECTION_NUM_OUTPUT_MAX)) );
	}
	
	{
		buffered_rhythm.setDefaultWidth( width );
		buffered_rhythm.setDefaultHeight( height );
		buffered_rhythm.setDefaultTextColor( color );
		buffered_rhythm.setup();
		buffered_rhythm.setName( "buffered_rhythm" );
		
		buffered_rhythm.add( play_buffered_rhythm.setup("/play_buffered_rhythm", toOnOff(DT_PLAY_BUFFERED_RHYTHM)) );
		buffered_rhythm.add( buffered_rhythm_rate.setup("/buffered_rhythm_rate", ofToString(DT_BUFFERED_RHYTHM_RATE)+"%") );
		buffered_rhythm.add( buffered_rhythm_indicator.setup("/buffered_rhythm_indicator", ofToString(DT_BUFFERED_RHYTHM_INDICATOR)) );
		buffered_rhythm.add( buffered_rhythm_loop_start.setup("/buffered_rhythm_loop_start", ofToString(DT_BUFFERED_RHYTHM_LOOP_START)) );
		buffered_rhythm.add( buffered_rhythm_loop_end.setup("/buffered_rhythm_loop_end", ofToString(DT_BUFFERED_RHYTHM_LOOP_END)) );

		buffered_rhythm.add( show_buffered_rhythm.setup("/show_buffered_rhythm", toOnOff(DT_SHOW_BUFFERED_RHYTHM)) );
	}
	
	reset_position();
}

void dt_config::reset_position(){
	app = ofApp::getInstance();
	int x = 20;
	int y = ofGetHeight() - width;

	int w = width + 20;
	osc.setPosition( x, y );
	generative_rhythm.setPosition( x + w, y );
	buffered_rhythm.setPosition( x + w*2, y );
	draw_mode.setPosition( x + w*3, y );
	
	osc_r.setup( DT_OSC_IN_PORT );
}

void dt_config::update(){
	app = ofApp::getInstance();
	
	while( osc_r.hasWaitingMessages() ){
		ofxOscMessage m;
		osc_r.getNextMessage( &m );
		
		string address = m.getAddress();
		string pre = DT_OSC_IN_ADDRESS_PREFIX;
		
		if( address == pre + "master_clock_out_resolution" ){
			int i= m.getArgAsInt32( 0 );
			DT_MASTER_CLOCK_OUT_RESOLUTION = i;
			
		// OSC
		}else if( address == pre + "osc_out_ch_max" ){
			
			int i = m.getArgAsInt32( 0 );
			i = max( 0, i );
			DT_OSC_OUT_CH_MAX = i;
			app->all_containers.change_osc_ch_all();
			osc_out_ch_max = ofToString( DT_OSC_OUT_CH_MAX );
			
		}else if( address == pre + "osc_out_address" ){
			
			string s = m.getArgAsString( 0 );
			DT_OSC_OUT_ADDRESS = s;
			app->osc_sender.setTargetAddress( s );
			osc_out_address = ofToString( DT_OSC_OUT_ADDRESS );
			
		}else if( address == pre + "osc_out_port" ){
			
			int i = m.getArgAsInt32( 0 );
			i = max( 1, i );
			DT_OSC_OUT_PORT = i;
			app->osc_sender.setTargetPort( i );
			osc_out_port = ofToString( DT_OSC_OUT_PORT );
			
		}else if( address == pre + "osc_in_port" ){
			
			int i = m.getArgAsInt32( 0 );
			i = max( 1, i );
			DT_OSC_IN_PORT = i;
			osc_r.setup( i );
			osc_in_port = ofToString( DT_OSC_IN_PORT );
			
		// Generative
		}else if( address == pre + "play_gen_rhythm" ){
			
			int i = m.getArgAsInt32( 0 );
			DT_PLAY_GEN_RHYTHM = i;
			play_gen_rhythm = toOnOff( DT_PLAY_GEN_RHYTHM );
			
		}else if( address == pre + "gen_rhythm_rate" ){
			
			int i = m.getArgAsInt32( 0 );
			i = max( 0, i );
			DT_GEN_RHYTHM_RATE = i;
			gen_rhythm_rate = ofToString( DT_GEN_RHYTHM_RATE ) + "%";

		}else if( address == pre + "rhythm_shape_slot_min" ){
			
			int i = m.getArgAsInt32( 0 );
			i = max( 3, i );
			DT_RHYTHM_SHAPE_SLOT_MIN = i;
	        rhythm_shape_slot_min = ofToString( DT_RHYTHM_SHAPE_SLOT_MIN );
			
		}else if( address == pre + "rhythm_shape_slot_max" ){
			
			int i = m.getArgAsInt32( 0 );
			i = max( 3, i );
			DT_RHYTHM_SHAPE_SLOT_MAX = i;
	        rhythm_shape_slot_max = ofToString( DT_RHYTHM_SHAPE_SLOT_MAX );
		}else if( address == pre + "beat_resolution" ){
			
			int i = m.getArgAsInt32( 0 );
			i = max( 1, i );
			DT_BEAT_RESOLUTION = i;
			app->all_containers.change_beat_resolution_all( i );
			beat_resolution = ofToString( DT_BEAT_RESOLUTION );

		}else if( address == pre + "beat_speed_max" ){
			
			int i = m.getArgAsInt32( 0 );
			i = max( 1, i );
			DT_BEAT_SPEED_MAX = i;
			app->all_containers.change_speed_random_all( 1, i );
	        beat_speed_max = ofToString( DT_BEAT_SPEED_MAX );

		}else if( address == pre + "connection_num_input_max" ){
			
			int i = m.getArgAsInt32( 0 );
			i = max( 0, i );
			DT_CONNECTION_NUM_INPUT_MAX = i;
			connection_num_input_max = ofToString( DT_CONNECTION_NUM_INPUT_MAX );
			
		}else if( address == pre + "connection_num_output_max" ){
			
			int i = m.getArgAsInt32( 0 );
			i = max( 0, i );
			DT_CONNECTION_NUM_OUTPUT_MAX = i;
			connection_num_output_max = ofToString( DT_CONNECTION_NUM_OUTPUT_MAX );
			
		// Buffered
		}else if( address == pre + "play_buffered_rhythm" ){
			
			int i = m.getArgAsInt32( 0 );
			DT_PLAY_BUFFERED_RHYTHM = i;
			play_buffered_rhythm = toOnOff( DT_PLAY_BUFFERED_RHYTHM );
		
		}else if( address == pre + "buffered_rhythm_rate" ){
			
			int i = m.getArgAsInt32( 0 );
			i = max( 0, i );
			DT_BUFFERED_RHYTHM_RATE = i;
			buffered_rhythm_rate = ofToString( DT_BUFFERED_RHYTHM_RATE ) + "%";
			
		}else if( address == pre + "buffered_rhythm_indicator" ){
			
			int i = m.getArgAsInt32( 0 );
			i = min( i, dt_osc_recorder::fragment_ring_max-1 );
			i = max( 0, i );
			DT_BUFFERED_RHYTHM_INDICATOR = i;
			buffered_rhythm_indicator = ofToString( DT_BUFFERED_RHYTHM_INDICATOR );
			
		}else if( address == pre + "buffered_rhythm_loop_start" ){
			
			int i = m.getArgAsInt32( 0 );
			i = max( 1, i );
			DT_BUFFERED_RHYTHM_LOOP_START = i;
			buffered_rhythm_loop_start = ofToString( DT_BUFFERED_RHYTHM_LOOP_START );

		}else if( address == pre + "buffered_rhythm_loop_end" ){
			
			int i = m.getArgAsInt32( 0 );
			i = max( 1, i );
			DT_BUFFERED_RHYTHM_LOOP_END = i;
			buffered_rhythm_loop_end = ofToString( DT_BUFFERED_RHYTHM_LOOP_END );
			
		}else if( address == pre + "show_buffered_rhythm" ){
			
			int i = m.getArgAsInt32( 0 );
			DT_SHOW_BUFFERED_RHYTHM = i;
			show_buffered_rhythm = toOnOff( DT_SHOW_BUFFERED_RHYTHM );

		}else{
			cout << "Receive strange OSC address : " << address << endl;
		}
	}
}

void dt_config::draw(){
	if( DT_SHOW_PARAM ){
		ofSetColor( 200 );
		osc.draw();
		generative_rhythm.draw();
		buffered_rhythm.draw();
		draw_mode.draw();
	}
}

void dt_config::toggle(){
    DT_SHOW_PARAM = !DT_SHOW_PARAM;
}

void dt_config::synch_param(){
	
	osc_out_ch_max = ofToString( DT_OSC_OUT_CH_MAX );
	osc_out_address = ofToString( DT_OSC_OUT_ADDRESS );
	osc_out_port = ofToString( DT_OSC_OUT_PORT );
	
	osc_in_port = ofToString( DT_OSC_IN_PORT );
	play_gen_rhythm = toOnOff( DT_PLAY_GEN_RHYTHM );
	gen_rhythm_rate = ofToString( DT_GEN_RHYTHM_RATE ) + "%";
    rhythm_shape_slot_min = ofToString( DT_RHYTHM_SHAPE_SLOT_MIN );
	rhythm_shape_slot_max = ofToString( DT_RHYTHM_SHAPE_SLOT_MAX );
	beat_resolution = ofToString( DT_BEAT_RESOLUTION );
	beat_speed_max = ofToString( DT_BEAT_SPEED_MAX );
	connection_num_input_max = ofToString( DT_CONNECTION_NUM_INPUT_MAX );
	connection_num_output_max = ofToString( DT_CONNECTION_NUM_OUTPUT_MAX );

	play_buffered_rhythm = toOnOff( DT_PLAY_BUFFERED_RHYTHM );
	buffered_rhythm_rate = ofToString( DT_BUFFERED_RHYTHM_RATE ) + "%";
	buffered_rhythm_indicator = ofToString( DT_BUFFERED_RHYTHM_INDICATOR );
	buffered_rhythm_loop_start = ofToString( DT_BUFFERED_RHYTHM_LOOP_START );
	buffered_rhythm_loop_end = ofToString( DT_BUFFERED_RHYTHM_LOOP_END );
	show_buffered_rhythm = toOnOff( DT_SHOW_BUFFERED_RHYTHM );
}
